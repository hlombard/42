package handlers

import (
	"database/sql"
	"errors"
	"net/http"

	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

// AccountVerify decrypts token to get the email trying to be verified
// and updates the is_verified field in users table.
//		ROUTE: /api/account/verify
//		METHOD: POST
//		PARAM: ?token=xxx
//		RETURN: none
func AccountVerify() gin.HandlerFunc {
	return func(c *gin.Context) {
		token := c.Query("token")
		if token == "" {
			utils.SetContextAndLog(c, "Account Verify", http.StatusNotAcceptable, "Need a token value to verify account")
			return
		}

		emailToVerify, err := utils.Decrypt(token, config.EncKey)
		if err != nil {
			utils.SetContextAndLog(c, "Account Verify", http.StatusNotAcceptable, "Token is not valid")
			return
		}

		if isAlreadyVerified(emailToVerify, config.DB) {
			utils.SetContextAndLog(c, "Account Verify", http.StatusNotAcceptable, emailToVerify+" is already verified")
			return
		}

		if err := verifyAccount(emailToVerify, config.DB); err != nil {
			utils.SetContextAndLog(c, "Account Verify", http.StatusInternalServerError, err.Error())
			return
		}

		utils.SetContextAndLog(c, "Account Verify", http.StatusOK, emailToVerify+" has been verified !")
	}
}

// isAlreadyVerified checks if email is already verified
func isAlreadyVerified(email string, db *sql.DB) bool {
	var isVerified bool

	rows := db.QueryRow("SELECT is_verified FROM users WHERE email = ?", email)
	if err := rows.Scan(&isVerified); err != nil {
		return false
	}
	return isVerified
}

// verifyAccount sets is_verified field on users table to true
func verifyAccount(emailToVerify string, db *sql.DB) error {
	query := "UPDATE users SET is_verified = true WHERE email = ?"
	_, err := db.Exec(query, emailToVerify)
	if err != nil {
		return errors.New("Couldn't update verify for " + emailToVerify)
	}
	return nil
}
