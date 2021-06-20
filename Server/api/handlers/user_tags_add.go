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

type tagForm struct {
	Tag string `json:"tag" binding:"required"`
}

// UserTagAdd adds a tag :username
//		ROUTE: /api/user/:username/tag
//		METHOD: POST
//		PARAM: :username that adds tag, json (TagStruct)
//		RETURN: none
func UserTagAdd() gin.HandlerFunc {
	return func(c *gin.Context) {
		var username, usernameTarget string
		var userID int
		var err error
		var tagStruct tagForm

		// Check that a tag was sent
		if err := c.ShouldBindJSON(&tagStruct); err != nil {
			utils.SetContextAndLog(c, "User Tag Add", http.StatusUnprocessableEntity, err.Error())
			return
		}

		// Get token owner username and userID (set in isAuthorized middleware)
		username = c.MustGet("tokenOwnerUsername").(string)
		userID, err = strconv.Atoi(c.MustGet("tokenOwnerID").(string))
		if err != nil {
			utils.SetContextAndLog(c, "User Tag Add", http.StatusInternalServerError, "Couldn't get userID")
			return
		}

		// Make sure user is not trying to add a tag for someone else
		usernameTarget = c.Param("username")
		if username != usernameTarget {
			utils.SetContextAndLog(c, "User Tag Add", http.StatusForbidden, "Can't add a tag to someone else")
			return
		}

		// Check that tag is correctly formated
		if err = utils.ValidTag(tagStruct.Tag); err != nil {
			utils.SetContextAndLog(c, "User Tag Add", http.StatusNotAcceptable, err.Error())
			return
		}

		// Add a tag in DB
		if err = addTag(config.DB, userID, tagStruct.Tag); err != nil {
			utils.SetContextAndLog(c, "User Tag Add", http.StatusNotAcceptable, err.Error())
			return
		}

		// Update last activity
		if err = utils.UpdateUserActivity(config.DB, userID, true); err != nil {
			utils.SetContextAndLog(c, "User Tag Add", http.StatusInternalServerError, err.Error())
			return
		}

		utils.SetContextAndLog(c, "User Tag Add", http.StatusOK, username+" added tag: "+tagStruct.Tag)
	}
}

func addTag(db *sql.DB, userID int, tag string) error {
	insert := "INSERT INTO user_tags (user_id, tag) VALUES (?, ?)"
	_, err := db.Exec(insert, userID, tag)
	if err != nil {
		return errors.New("Cannot add twice the same tag")
	}
	return nil
}
