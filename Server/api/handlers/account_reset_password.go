package handlers

import (
	"database/sql"
	"errors"
	"fmt"
	"net/http"

	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

type resetPasswordForm struct {
	Password1 string `json:"password_1" binding:"required"`
	Password2 string `json:"password_2" binding:"required"`
}

// AccountResetPassword changes the user's password, and deletes the row in user_ResetPassword table
// to avoid multiple token usages
//		ROUTE: /api/account/reset_password
//		METHOD: POST
//		PARAM: ?token=xxx
//		RETURN: none
func AccountResetPassword() gin.HandlerFunc {
	return func(c *gin.Context) {
		var form resetPasswordForm
		var err error
		var tokenOwner string
		var hashedPw string
		var formErr *utils.FormErrors

		token := c.Query("token")
		if token == "" {
			utils.SetContextAndLog(c, "Reset Password", http.StatusUnprocessableEntity, "No tokens specified")
		}

		if err := c.ShouldBindJSON(&form); err != nil {
			utils.SetContextAndLog(c, "Reset Password", http.StatusUnprocessableEntity, err.Error())
			return
		}

		// Parse form: pw1 == pw2 and is secure enough
		if hashedPw, formErr = checkPasswordsAndHash(form.Password1, form.Password2); len(formErr.Errors) > 0 {
			utils.LogForm("Reset Password", formErr.Errors)
			c.JSON(http.StatusNotAcceptable, formErr)
			return
		}

		if tokenOwner, err = findTokenOwner(config.DB, token); err != nil {
			utils.SetContextAndLog(c, "Reset Password", http.StatusNotAcceptable, err.Error())
			return
		}

		if removeResetPasswordToken(config.DB, token); err != nil {
			utils.SetContextAndLog(c, "Reset Password", http.StatusInternalServerError, err.Error())
			return
		}

		if err := changeUserPassword(config.DB, tokenOwner, hashedPw); err != nil {
			utils.SetContextAndLog(c, "Reset Password", http.StatusInternalServerError, err.Error())
			return
		}

		utils.SetContextAndLog(c, "Reset Password", http.StatusOK, "Successfully changed "+tokenOwner+" password")
	}
}

func removeResetPasswordToken(db *sql.DB, token string) error {
	remove := "DELETE FROM user_reset_pw WHERE token = ?"
	_, err := db.Exec(remove, token)
	if err != nil {
		return errors.New("Couldn't remove token from DB")
	}
	return nil
}

func changeUserPassword(db *sql.DB, email, hashedPw string) error {
	update := "UPDATE users SET pw_hash = ? WHERE email = ?"
	_, err := db.Exec(update, hashedPw, email)
	if err != nil {
		return errors.New("Couldn't change user's password")
	}
	return nil
}

func checkPasswordsAndHash(pw1, pw2 string) (string, *utils.FormErrors) {
	var hashed string
	var err error

	formErr := utils.NewFormErrors()
	if pw1 != pw2 {
		fmt.Println("Added one error")
		formErr.Add("password_1", []string{"Passwords needs to be the same"})
	}

	if err := utils.ValidPassword(pw1); len(err) > 0 {
		formErr.Add("password_1", err)
		return "", formErr
	}

	if hashed, err = utils.HashAndSalt(pw1); err != nil {
		formErr.Add("password_1", []string{"Unexpected error"})
		return "", formErr
	}
	return hashed, formErr
}

func findTokenOwner(db *sql.DB, token string) (string, error) {
	var email string

	rows := db.QueryRow("SELECT email FROM user_reset_pw WHERE token = ?", token)
	if err := rows.Scan(&email); err != nil {
		return "", errors.New("Unknown token")
	}
	return email, nil
}
