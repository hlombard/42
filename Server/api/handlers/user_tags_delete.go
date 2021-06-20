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

// UserTagDelete removes a tag :username
//		ROUTE: /api/user/:username/tag
//		METHOD: DELETE
//		PARAM: :username to remove tag, json (TagStruct)
//		RETURN: none
func UserTagDelete() gin.HandlerFunc {
	return func(c *gin.Context) {
		var username, usernameTarget string
		var userID int
		var err error
		var tagStruct tagForm

		// Check that a tag was sent
		if err := c.ShouldBindJSON(&tagStruct); err != nil {
			utils.SetContextAndLog(c, "User Tag Delete", http.StatusUnprocessableEntity, err.Error())
			return
		}

		// Get token owner username and userID (set in isAuthorized middleware)
		username = c.MustGet("tokenOwnerUsername").(string)
		userID, err = strconv.Atoi(c.MustGet("tokenOwnerID").(string))
		if err != nil {
			utils.SetContextAndLog(c, "User Tag Delete", http.StatusInternalServerError, "Couldn't get userID")
			return
		}

		// Make sure user is not trying to remove someone else tag
		usernameTarget = c.Param("username")
		if username != usernameTarget {
			utils.SetContextAndLog(c, "User Tag Delete", http.StatusForbidden, "Can't remove someone else tag")
			return
		}

		// Remove the tag from DB
		if err := removeTag(config.DB, userID, tagStruct.Tag); err != nil {
			utils.SetContextAndLog(c, "User Tag Delete", http.StatusNotAcceptable, err.Error())
			return
		}

		// Update last activity
		if err := utils.UpdateUserActivity(config.DB, userID, true); err != nil {
			utils.SetContextAndLog(c, "User Tag Delete", http.StatusInternalServerError, err.Error())
			return
		}

		utils.SetContextAndLog(c, "User Tag Delete", http.StatusOK, username+" removed tag: "+tagStruct.Tag)
	}
}

func removeTag(db *sql.DB, userID int, tag string) error {
	delete := "DELETE FROM user_tags WHERE user_id = ? AND tag = ?"
	_, err := db.Exec(delete, userID, tag)
	if err != nil {
		return errors.New("Couldn't remove tag from DB")
	}
	return nil
}
