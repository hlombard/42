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

// UserVisitAdd adds a visit to :username
//		ROUTE: /user/:username/visit
//		METHOD: POST
//		PARAM: :username to add visit
//		RETURN: none
func UserVisitAdd() gin.HandlerFunc {
	return func(c *gin.Context) {
		var username, usernameTarget string
		var userID, userIDTarget int
		var err error

		// Get token owner username and userID (set in isAuthorized middleware)
		username = c.MustGet("tokenOwnerUsername").(string)
		userID, err = strconv.Atoi(c.MustGet("tokenOwnerID").(string))
		if err != nil {
			utils.SetContextAndLog(c, "User Visit Add", http.StatusInternalServerError, "Couldn't get userID")
			return
		}

		// Get usernameTarget and userIDTarget
		usernameTarget = c.Param("username")
		userIDTarget, err = utils.GetUserID(config.DB, usernameTarget)
		if err != nil {
			utils.SetContextAndLog(c, "User Visit Add", http.StatusNotFound, err.Error())
			return
		}

		// Make sure user is not trying to add a visit to his self u_U
		if username == usernameTarget {
			utils.SetContextAndLog(c, "User Visit Add", http.StatusForbidden, "Can't add a visit to your self")
			return
		}

		// Add a visit or update the visit_date in db
		if err := addVisit(config.DB, userID, userIDTarget); err != nil {
			utils.SetContextAndLog(c, "User Visit Add", http.StatusInternalServerError, err.Error())
			return
		}

		// Update last activity
		if err := utils.UpdateUserActivity(config.DB, userID, true); err != nil {
			utils.SetContextAndLog(c, "User Visit Add", http.StatusInternalServerError, err.Error())
			return
		}

		// Create a notification
		if err := utils.CreateNotification(config.DB, "visit", userID, userIDTarget); err != nil {
			utils.SetContextAndLog(c, "User Visit Add", http.StatusInternalServerError, err.Error())
			return
		}

		utils.SetContextAndLog(c, "User Visit Add", http.StatusOK, username+" visited "+usernameTarget)
	}
}

// addVisit saves a visit. If the userID already visited
// userIDTarget's profile, it will simply update the visit_date
func addVisit(db *sql.DB, userID, userIDTarget int) error {
	replace := "REPLACE INTO user_visits (user_id, user_id_target) VALUES (?, ?)"
	_, err := db.Exec(replace, userID, userIDTarget)
	if err != nil {
		return errors.New("Couldn't save the visit in DB")
	}
	return nil
}
