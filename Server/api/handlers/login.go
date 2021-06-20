package handlers

import (
	"database/sql"
	"net/http"

	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
	"golang.org/x/crypto/bcrypt"
)

type loginForm struct {
	Username string `json:"username" binding:"required"`
	Password string `json:"password" binding:"required"`
}

// Login checks for credentials and that the user is verified.
// It also uses the IP to save in db the location coordinates
//		ROUTE: /api/account/login
//		METHOD: POST
//		PARAM: none
//		RETURN: JWT access/refresh tokens and username
func Login() gin.HandlerFunc {
	return func(c *gin.Context) {
		var form loginForm
		var err error

		if err := c.ShouldBindJSON(&form); err != nil {
			utils.SetContextAndLog(c, "Login", http.StatusUnprocessableEntity, err.Error())
			return
		}

		// Check if username exists and get his userID
		formErr := utils.NewFormErrors()
		userID, err := utils.GetUserID(config.DB, form.Username)
		if err != nil {
			formErr.Add("username", []string{err.Error()})
			utils.LogForm("Login", formErr.Errors)
			c.JSON(http.StatusNotAcceptable, formErr)
			return
		}

		// Hash and compare password
		if !comparePasswords(config.DB, form.Username, form.Password) {
			formErr.Add("password", []string{"Wrong password"})
			utils.LogForm("Login", formErr.Errors)
			c.JSON(http.StatusForbidden, formErr)
			return
		}

		if !isVerified(config.DB, form.Username) {
			formErr.Add("password", []string{form.Username + " is not verified, go check your emails"})
			utils.LogForm("Login", formErr.Errors)
			c.JSON(http.StatusNotAcceptable, formErr)
			return
		}

		// Generate a Access and Refresh JWT from user id
		tokensDetails, err := utils.CreateTokens(userID, form.Username)
		if err != nil {
			utils.SetContextAndLog(c, "Login", http.StatusInternalServerError, err.Error())
			return
		}

		// Insert JWT to DB (delete previous token if they existed) and set login status ON, and update last_activity
		if err := utils.SaveTokens(config.DB, userID, tokensDetails); err != nil {
			utils.SetContextAndLog(c, "Login", http.StatusInternalServerError, err.Error())
			return
		}

		// Insert Location data collected from ip addr
		if err := utils.StoreLocationData(config.DB, form.Username, c.ClientIP()); err != nil {
			utils.SetContextAndLog(c, "Login", http.StatusInternalServerError, err.Error())
			return
		}

		// Log and send response with JWT tokens
		utils.SimpleLog("Login", form.Username+" successfully connected !")
		c.JSON(http.StatusOK, gin.H{
			"username":      form.Username,
			"access_token":  tokensDetails.AccessToken,
			"refresh_token": tokensDetails.RefreshToken,
		})
	}
}

func isVerified(db *sql.DB, username string) (verified bool) {
	rows := db.QueryRow("SELECT is_verified FROM users WHERE username = ?", username)
	if err := rows.Scan(&verified); err != nil {
		return false
	}
	return verified
}

func comparePasswords(db *sql.DB, username, formPassword string) bool {
	var password string

	rows := db.QueryRow("SELECT pw_hash FROM users WHERE username = ?", username)
	switch err := rows.Scan(&password); err {
	case sql.ErrNoRows:
		return false
	default:
		if err := bcrypt.CompareHashAndPassword([]byte(password), []byte(formPassword)); err != nil {
			return false
		}
		return true
	}
}
