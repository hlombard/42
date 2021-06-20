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

// UserBlockAdd blocks :username and updates
// last_activity
//		ROUTE: api/user/:username/block
//		METHOD: POST
//		PARAM: :username to block
//		RETURN: none
func UserBlockAdd() gin.HandlerFunc {
	return func(c *gin.Context) {
		var err error
		var userID, userIDTarget int
		var username, usernameTarget string

		// Get token owner username and userID (set in isAuthorized middleware)
		username = c.MustGet("tokenOwnerUsername").(string)
		userID, err = strconv.Atoi(c.MustGet("tokenOwnerID").(string))
		if err != nil {
			utils.SetContextAndLog(c, "User Block Add", http.StatusInternalServerError, "Couldn't get userID")
			return
		}

		// Get usernameTarget and userIDTarget
		usernameTarget = c.Param("username")
		userIDTarget, err = utils.GetUserID(config.DB, usernameTarget)
		if err != nil {
			utils.SetContextAndLog(c, "User Block Add", http.StatusNotFound, err.Error())
			return
		}

		// Make sure user is not trying to block his self u_U
		if username == usernameTarget {
			utils.SetContextAndLog(c, "User Block Add", http.StatusForbidden, "You can't block your self")
			return
		}

		// Add a block in DB
		if err := addBlock(config.DB, userID, userIDTarget); err != nil {
			utils.SetContextAndLog(c, "User Block Add", http.StatusUnprocessableEntity, err.Error())
			return
		}

		// Update last activity
		if err := utils.UpdateUserActivity(config.DB, userID, true); err != nil {
			utils.SetContextAndLog(c, "User Block Add", http.StatusInternalServerError, err.Error())
		}

		utils.SetContextAndLog(c, "User Block Add", http.StatusOK, username+" blocked "+usernameTarget)
	}
}

// addBlock adds a block in DB, and returns an error
// if userIDTarget is already blocked
func addBlock(db *sql.DB, userID, userIDTarget int) error {
	insert := `INSERT INTO user_blocks (user_id, user_id_target)
	VALUES (?, ?)`
	_, err := db.Exec(insert, userID, userIDTarget)
	if err != nil {
		return errors.New("Cannot block twice the same person")
	}
	return nil
}
