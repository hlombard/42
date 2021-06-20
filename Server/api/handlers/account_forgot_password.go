package handlers

import (
	"crypto/rand"
	"database/sql"
	"encoding/hex"
	"errors"
	"net/http"

	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

const (
	tokenSize = 50
)

type forgotForm struct {
	Email string `json:"email" binding:"required"`
}

// AccountForgotPassword sends a mail
// to the json Email value, with a personal link
//		ROUTE: /api/account/forgot_password
//		METHOD: POST
//		PARAM: json (forgotForm)
//		RETURN: none
func AccountForgotPassword() gin.HandlerFunc {
	return func(c *gin.Context) {
		var form forgotForm
		var token string

		if err := c.ShouldBindJSON(&form); err != nil {
			utils.SetContextAndLog(c, "Forgot Password", http.StatusUnprocessableEntity, err.Error())
			return
		}

		formErr := utils.NewFormErrors()
		if utils.EmailExists(config.DB, form.Email) == false {
			formErr.Add("email", []string{form.Email + " is not associated with an account"})
			utils.LogForm("Forgot Password", formErr.Errors)
			c.JSON(http.StatusNotAcceptable, formErr)
			return
		}

		if token = generateRandomToken(tokenSize); token == "" {
			utils.SetContextAndLog(c, "Forgot Password", http.StatusInternalServerError, "Couldn't generate a token")
			return
		}

		if err := storeTokenResetPassword(config.DB, token, form.Email); err != nil {
			utils.SetContextAndLog(c, "Forgot Password", http.StatusInternalServerError, err.Error())
			return
		}

		if err := sendForgotPasswordMail(token, form.Email); err != nil {
			utils.SetContextAndLog(c, "Forgot Password", http.StatusInternalServerError, err.Error())
			return
		}

		utils.SetContextAndLog(c, "Forgot Password", http.StatusOK, "Sent a reset_password link to "+form.Email)
	}
}

func sendForgotPasswordMail(token, email string) error {
	personalLink := "<a href=\"http://localhost:3000/account/reset_password?token=" +
		token + "\">LINK</a>"

	receiverMail := []string{email}
	mailData := utils.GetForgotPasswordMailData(personalLink)
	message := []byte(mailData.Subject + mailData.Mime + mailData.Body)

	if err := utils.SendEmail(receiverMail, message); err != nil {
		return errors.New("Couldn't send a verification email to " + email)
	}
	return nil
}

// storeTokenResetPassword deletes previous token
// in case there was any and store the new token
func storeTokenResetPassword(db *sql.DB, token, email string) error {
	remove := "DELETE FROM user_reset_pw WHERE email = ?"
	_, err := db.Exec(remove, email)
	if err != nil {
		return errors.New("Couldn't remove previous tokens from DB")
	}

	store := "INSERT INTO user_reset_pw (email, token) VALUES (?, ?)"
	_, err = db.Exec(store, email, token)
	if err != nil {
		return errors.New("Couldn't store generated token")
	}
	return nil
}

// generateRandomToken generates a random token
// of length size
func generateRandomToken(length int) string {
	b := make([]byte, length)
	if _, err := rand.Read(b); err != nil {
		return ""
	}
	return hex.EncodeToString(b)[0:50]
}
