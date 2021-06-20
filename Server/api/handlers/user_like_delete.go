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

// UserLikeDelete removes a like to :username
//		ROUTE: /api/user/:username/like
//		METHOD: DELETE
//		PARAM: :username to unlike
//		RETURN: none
func UserLikeDelete() gin.HandlerFunc {
	return func(c *gin.Context) {
		var err error
		var userID, userIDTarget int
		var username, usernameTarget string
		var matchExisted bool

		// Get token owner username and userID (set in isAuthorized middleware)
		username = c.MustGet("tokenOwnerUsername").(string)
		userID, err = strconv.Atoi(c.MustGet("tokenOwnerID").(string))
		if err != nil {
			utils.SetContextAndLog(c, "User Like Delete", http.StatusInternalServerError, "Couldn't get userID")
			return
		}
		// Get usernameTarget and userIDTarget
		usernameTarget = c.Param("username")
		userIDTarget, err = utils.GetUserID(config.DB, usernameTarget)
		if err != nil {
			utils.SetContextAndLog(c, "User Like Delete", http.StatusNotFound, err.Error())
			return
		}

		// Make sure user is not trying to unlike his self u_U
		if username == usernameTarget {
			utils.SetContextAndLog(c, "User Like Delete", http.StatusUnprocessableEntity, "You might not like your self, but we do <3")
			return
		}

		// Delete like in DB (and match if existed)
		if matchExisted, err = deleteLike(config.DB, userID, userIDTarget); err != nil {
			utils.SetContextAndLog(c, "User Like Delete", http.StatusUnprocessableEntity, err.Error())
			return
		}

		// Update last activity
		if err := utils.UpdateUserActivity(config.DB, userID, true); err != nil {
			utils.SetContextAndLog(c, "User Like Delete", http.StatusInternalServerError, err.Error())
		}

		// Create a notification (only if they were matched)
		if matchExisted == true {
			if err := utils.CreateNotification(config.DB, "unlike", userID, userIDTarget); err != nil {
				utils.SetContextAndLog(c, "User Like Delete", http.StatusInternalServerError, err.Error())
				return
			}
		}

		utils.SetContextAndLog(c, "User Like Delete", http.StatusOK, username+" unliked "+usernameTarget)
	}
}

// Remove the like and the match (if existed)
// and returns a boolean to know if users were matched
func deleteLike(db *sql.DB, userID, userIDTarget int) (bool, error) {
	matchExisted := false

	delete := "DELETE FROM user_likes WHERE user_id = ? AND user_id_target = ?"
	_, err := db.Exec(delete, userID, userIDTarget)
	if err != nil {
		return false, errors.New("Couldn't remove like from DB, no previous like was found")
	}

	delete = "DELETE FROM matches WHERE (user_id_1 = ? AND user_id_2 = ?) OR (user_id_1 = ? AND user_id_2 = ?)"
	result, err := db.Exec(delete, userID, userIDTarget, userIDTarget, userID)
	if err != nil {
		return false, errors.New("Couldn't remove match from DB")
	}

	affected, err := result.RowsAffected()
	if err != nil {
		return false, errors.New("Couldn't find rows affected number")
	}
	if affected > 0 {
		matchExisted = true
	}
	return matchExisted, nil
}
