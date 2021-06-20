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

// UserLikeAdd adds a like to :username
//		ROUTE: /api/user/:username/like
//		METHOD: POST
//		PARAM: :username to like
//		RETURN: none
func UserLikeAdd() gin.HandlerFunc {
	return func(c *gin.Context) {
		var err error
		var userID, userIDTarget int
		var username, usernameTarget string

		// Get token owner username and userID (set in isAuthorized middleware)
		username = c.MustGet("tokenOwnerUsername").(string)
		userID, err = strconv.Atoi(c.MustGet("tokenOwnerID").(string))
		if err != nil {
			utils.SetContextAndLog(c, "User Like Add", http.StatusInternalServerError, "Couldn't get userID")
			return
		}

		// Get usernameTarget and userIDTarget
		usernameTarget = c.Param("username")
		userIDTarget, err = utils.GetUserID(config.DB, usernameTarget)
		if err != nil {
			utils.SetContextAndLog(c, "User Like Add", http.StatusNotFound, err.Error())
			return
		}

		// Make sure user is not trying to like his self u_U
		if username == usernameTarget {
			utils.SetContextAndLog(c, "User Like Add", http.StatusUnprocessableEntity, "Why would you like your self...")
			return
		}

		// Make sure user and userTarget is_completed = true
		// Both need to have a profile picture to like / be liked
		if !IsUserCompleted(config.DB, username) || !IsUserCompleted(config.DB, usernameTarget) {
			utils.SetContextAndLog(c, "User Like Add", http.StatusNotAcceptable, "Both users needs to have a profile picture "+
				"to like / be liked")
			return
		}

		// Add a like in DB
		if err := addLike(config.DB, userID, userIDTarget); err != nil {
			utils.SetContextAndLog(c, "User Like Add", http.StatusUnprocessableEntity, err.Error())
			return
		}

		// Update last activity
		if err := utils.UpdateUserActivity(config.DB, userID, true); err != nil {
			utils.SetContextAndLog(c, "User Like Add", http.StatusInternalServerError, err.Error())
		}

		// Create match if they both liked each other, and create a notification of type
		// like/match
		match := createMatchIfBothLiked(config.DB, userID, userIDTarget)
		switch match {
		case true:
			if err = utils.CreateNotification(config.DB, "match", userID, userIDTarget); err != nil {
				utils.SetContextAndLog(c, "User Like Add", http.StatusInternalServerError, err.Error())
				return
			}
			utils.SetContextAndLog(c, "User Like Add", http.StatusOK, "created a match between "+usernameTarget+" and "+username)
		case false:
			if err = utils.CreateNotification(config.DB, "like", userID, userIDTarget); err != nil {
				utils.SetContextAndLog(c, "User Like Add", http.StatusInternalServerError, err.Error())
				return
			}
			utils.SetContextAndLog(c, "User Like Add", http.StatusOK, "created a like between "+usernameTarget+" and "+username)
		}

	}
}

func createMatchIfBothLiked(db *sql.DB, userID, userIDTarget int) bool {
	var found int

	// Check if userIDTarget also liked userID
	rows := db.QueryRow("SELECT user_id FROM user_likes WHERE user_id = ? and user_id_target = ?", userIDTarget, userID)
	switch err := rows.Scan(&found); err {
	case sql.ErrNoRows:
		return false
	default:
		// Check if users didn't block each other
		if utils.IsUserBlocked(db, userID, userIDTarget) {
			return false
		} else if utils.IsUserBlocked(db, userIDTarget, userID) {
			return false
		}
		// Create the match
		insert := "INSERT INTO matches (user_id_1, user_id_2) VALUES (?, ?)"
		_, err := db.Exec(insert, userID, userIDTarget)
		if err != nil {
			return false
		}
		return true
	}
}

// addLike will return an error if userID already liked userIDTarget
func addLike(db *sql.DB, userID, userIDTarget int) error {
	insert := `INSERT INTO user_likes (user_id, user_id_target)
	VALUES (?, ?)`
	_, err := db.Exec(insert, userID, userIDTarget)
	if err != nil {
		return errors.New("Cannot like twice the same person")
	}
	return nil
}

// IsUserLiked check if user is already liked
func IsUserLiked(db *sql.DB, userID, userIDTarget int) bool {
	var found int

	rows := db.QueryRow("SELECT user_id FROM user_likes WHERE user_id = ? AND user_id_target = ?", userID, userIDTarget)
	switch err := rows.Scan(&found); err {
	case sql.ErrNoRows:
		return false
	default:
		return true
	}
}
