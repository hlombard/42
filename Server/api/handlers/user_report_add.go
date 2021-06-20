package handlers

import (
	"database/sql"
	"errors"
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

// UserReportAdd adds a report to :username
//		ROUTE: /api/user/:username/report
//		METHOD: POST
//		PARAM: :username to report
//		RETURN: none
func UserReportAdd() gin.HandlerFunc {
	return func(c *gin.Context) {
		var err error
		var userID, userIDTarget int
		var username, usernameTarget string

		// Get token owner username and userID (set in isAuthorized middleware)
		username = c.MustGet("tokenOwnerUsername").(string)
		userID, err = strconv.Atoi(c.MustGet("tokenOwnerID").(string))
		if err != nil {
			utils.SetContextAndLog(c, "User Report Add", http.StatusInternalServerError, "Couldn't get userID")
			return
		}

		// Get usernameTarget and userIDTarget
		usernameTarget = c.Param("username")
		userIDTarget, err = utils.GetUserID(config.DB, usernameTarget)
		if err != nil {
			utils.SetContextAndLog(c, "User Report Add", http.StatusNotFound, err.Error())
			return
		}

		// Make sure user is not trying to report his self u_U
		if username == usernameTarget {
			utils.SetContextAndLog(c, "User Report Add", http.StatusNotAcceptable, "You can't report your self")
			return
		}

		// Add a report in DB
		if err := addReport(config.DB, userID, userIDTarget); err != nil {
			utils.SetContextAndLog(c, "User Report Add", http.StatusNotAcceptable, err.Error())
			return
		}

		// Update last activity
		if err := utils.UpdateUserActivity(config.DB, userID, true); err != nil {
			utils.SetContextAndLog(c, "User Report Add", http.StatusInternalServerError, err.Error())
		}

		utils.SetContextAndLog(c, "User Report Add", http.StatusOK, username+" reported "+usernameTarget)
	}
}

func addReport(db *sql.DB, userID, userIDTarget int) error {
	insert := `INSERT INTO user_reports (user_id, user_id_target)
	VALUES (?, ?)`
	_, err := db.Exec(insert, userID, userIDTarget)
	if err != nil {
		return errors.New("Cannot report twice the same person")
	}
	return nil
}
