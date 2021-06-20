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

func UserBlockDelete() gin.HandlerFunc {
	return func(c *gin.Context) {
		var err error
		var userID, userIDTarget int
		var username, usernameTarget string

		// Get token owner username and userID (set in isAuthorized middleware)
		username = c.MustGet("tokenOwnerUsername").(string)
		userID, err = strconv.Atoi(c.MustGet("tokenOwnerID").(string))
		if err != nil {
			utils.SetContextAndLog(c, "User Block Delete", http.StatusInternalServerError, "Couldn't get userID")
			return
		}

		// Get usernameTarget and userIDTarget
		usernameTarget = c.Param("username")
		userIDTarget, err = utils.GetUserID(config.DB, usernameTarget)
		if err != nil {
			utils.SetContextAndLog(c, "User Block Delete", http.StatusNotFound, err.Error())
			return
		}

		// Make sure user is not trying to unblock his self u_U
		if username == usernameTarget {
			utils.SetContextAndLog(c, "User Block Delete", http.StatusForbidden, "You can't unblock your self")
			return
		}

		// Delete block in DB
		if err := deleteBlock(config.DB, userID, userIDTarget); err != nil {
			utils.SetContextAndLog(c, "User Block Delete", http.StatusUnprocessableEntity, err.Error())
			return
		}

		// Update last activity
		if err := utils.UpdateUserActivity(config.DB, userID, true); err != nil {
			utils.SetContextAndLog(c, "User Block Delete", http.StatusInternalServerError, err.Error())
		}

		utils.SetContextAndLog(c, "User Block Delete", http.StatusOK, username+" unblocked "+usernameTarget)

	}
}

func deleteBlock(db *sql.DB, userID, userIDTarget int) error {
	delete := "DELETE FROM user_blocks WHERE user_id = ? AND user_id_target = ?"
	_, err := db.Exec(delete, userID, userIDTarget)
	if err != nil {
		return errors.New("Couldn't remove like from DB, no previous like was found")
	}
	return nil
}
