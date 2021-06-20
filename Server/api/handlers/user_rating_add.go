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

type ratingForm struct {
	Value int `json:"rating" binding:"required"`
}

// UserRatingAdd adds a rating to :username
//		ROUTE: api/user/:username/rating
//		METHOD: POST
//		PARAM: :username to rate, json (Rating)
//		RETURN: none
func UserRatingAdd() gin.HandlerFunc {
	return func(c *gin.Context) {
		var err error
		var userID, userIDTarget int
		var username, usernameTarget string
		var rating ratingForm

		// Get token owner username and userID (set in isAuthorized middleware)
		username = c.MustGet("tokenOwnerUsername").(string)
		userID, err = strconv.Atoi(c.MustGet("tokenOwnerID").(string))
		if err != nil {
			utils.SetContextAndLog(c, "User Rating Add", http.StatusInternalServerError, "Couldn't get userID")
			return
		}

		// Get usernameTarget and userIDTarget
		usernameTarget = c.Param("username")
		userIDTarget, err = utils.GetUserID(config.DB, usernameTarget)
		if err != nil {
			utils.SetContextAndLog(c, "User Rating Add", http.StatusNotFound, err.Error())
			return
		}

		// Make sure user is not trying to rate his self u_U
		if username == usernameTarget {
			utils.SetContextAndLog(c, "User Rating Add", http.StatusUnprocessableEntity, "You can't rate yourself")
			return
		}

		// Check rating value has been provided and is valid
		if err := c.ShouldBindJSON(&rating); err != nil {
			utils.SetContextAndLog(c, "User Rating Add", http.StatusUnprocessableEntity, err.Error())
			return
		}
		if rating.Value < 1 || rating.Value > 5 {
			utils.SetContextAndLog(c, "User Rating Add", http.StatusNotAcceptable, "Rating V has to be between 1 and 5")
			return
		}

		// Make sure user and userTarget is_completed = true
		if !IsUserCompleted(config.DB, username) || !IsUserCompleted(config.DB, usernameTarget) {
			utils.SetContextAndLog(c, "User Rating Add", http.StatusNotAcceptable, "both profiles needs to be completed")
			return
		}

		// Add a rating in DB
		if err := addRating(config.DB, userID, userIDTarget, rating.Value); err != nil {
			utils.SetContextAndLog(c, "User Rating Add", http.StatusUnprocessableEntity, err.Error())
			return
		}

		// Update last activity
		if err := utils.UpdateUserActivity(config.DB, userID, true); err != nil {
			utils.SetContextAndLog(c, "User Rating Add", http.StatusInternalServerError, err.Error())
		}

		utils.SetContextAndLog(c, "User Rating Add", http.StatusOK, username+" rated "+usernameTarget+" : "+strconv.Itoa(rating.Value)+"/5")
	}
}

func addRating(db *sql.DB, userID, userIDTarget, rating int) error {
	replace := "REPLACE INTO user_ratings (user_id, user_id_target, rating) VALUES (?, ?, ?)"
	_, err := db.Exec(replace, userID, userIDTarget, rating)
	if err != nil {
		return errors.New("Couldn't add the rating into DB")
	}
	return nil
}

func isUserRated(db *sql.DB, userID, userIDTarget int) bool {
	var found int

	rows := db.QueryRow("SELECT rating FROM user_ratings WHERE user_id = ? AND user_id_target = ?", userID, userIDTarget)
	switch err := rows.Scan(&found); err {
	case sql.ErrNoRows:
		return false
	default:
		return true
	}
}
