package handlers

import (
	"database/sql"
	"errors"
	"fmt"
	"net/http"
	"strconv"

	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

type userData struct {
	UserID         int      `json:"user_id"`
	Username       string   `json:"username"`
	Firstname      string   `json:"firstname"`
	Lastname       string   `json:"lastname"`
	Email          string   `json:"email"`
	RegisteredDate string   `json:"registered_date"`
	Age            int      `json:"age"`
	Dob            string   `json:"dob"`
	Picture1       string   `json:"picture_1"`
	Picture2       string   `json:"picture_2"`
	Picture3       string   `json:"picture_3"`
	Picture4       string   `json:"picture_4"`
	Picture5       string   `json:"picture_5"`
	Gender         string   `json:"gender"`
	GenderTarget   string   `json:"gender_target"`
	Country        string   `json:"country"`
	City           string   `json:"city"`
	Zipcode        string   `json:"zipcode"`
	Biography      string   `json:"biography"`
	Rating         string   `json:"rating"`
	NbRating       int      `json:"nb_rating"`
	Tags           []string `json:"tags"`
	Visits         []string `json:"visits"` // last 10 visitors
	AuthorizeGPS   bool     `json:"authorizeGPS"`
	IsRated        bool     `json:"is_rated"`
	IsLiked        bool     `json:"is_liked"`
	IsBlocked      bool     `json:"is_blocked"`
	IsReported     bool     `json:"is_reported"`
	IsCompleted    bool     `json:"is_completed"`
	IsOwnProfile   bool     `json:"is_own_profile"`
	IsOnline       bool     `json:"is_online"`
	LastActivity   string   `json:"last_activity"`
}

// UserGet sends specific user data
//		ROUTE: api/user/:username
//		METHOD: GET
//		PARAM: :username to get
//		RETURN: :username data
func UserGet() gin.HandlerFunc {
	return func(c *gin.Context) {
		var err error
		var userID, userIDTarget int
		var username, usernameTarget string

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
			utils.SetContextAndLog(c, "User Get", http.StatusNotFound, err.Error())
			return
		}

		// Set username and userID
		var data userData
		data.UserID = userIDTarget
		data.Username = usernameTarget

		// Get personal data if viewing his own profile
		if username == usernameTarget {
			data.IsOwnProfile = true
			if err := getPrivateData(config.DB, &data); err != nil {
				utils.SetContextAndLog(c, "User Get", http.StatusInternalServerError, err.Error())
				return
			}
		}

		if err := getPublicData(config.DB, &data, userID); err != nil {
			utils.SetContextAndLog(c, "User Get", http.StatusInternalServerError, err.Error())
			return
		}

		// Log and send user data
		utils.SimpleLog("User Get", usernameTarget+" data was successfully sent")
		c.JSON(http.StatusOK, data)
	}
}

func getPrivateData(db *sql.DB, data *userData) error {
	var err error

	// Get Email
	if data.Email, err = getUserEmail(db, data.Username); err != nil {
		return err
	}

	// Get Authorize GPS
	if data.AuthorizeGPS, err = getAuthorizeGPS(db, data.Username); err != nil {
		return err
	}
	return nil
}

// Get all the public data viewable by anyone
func getPublicData(db *sql.DB, data *userData, userID int) error {

	// Get all the public data from 'users' table
	if err := getCommonData(db, data); err != nil {
		return err
	}

	// Get User Tags
	if err := getUserTags(db, data); err != nil {
		return err
	}

	// Get User Visits (last 10)
	if err := getUserVisits(db, data); err != nil {
		return err
	}

	data.IsOnline, data.LastActivity = getUserOnlineStatus(db, data.UserID)

	// Is user already blocked/liked/reported/rated by token's owner
	data.IsBlocked = utils.IsUserBlocked(db, userID, data.UserID)
	data.IsLiked = IsUserLiked(db, userID, data.UserID)
	data.IsReported = IsUserReported(db, userID, data.UserID)
	data.IsRated = isUserRated(db, userID, data.UserID)

	// Get User Ratings
	if err := getUserRating(db, data); err != nil {
		return err
	}
	return nil
}

func getUserOnlineStatus(db *sql.DB, userID int) (isOnline bool, lastActivity string) {
	query := "SELECT is_online, last_activity FROM user_sessions WHERE user_id = ?"
	rows := db.QueryRow(query, userID)
	if err := rows.Scan(&isOnline, &lastActivity); err != nil {
		return false, ""
	}
	return
}

func getUserRating(db *sql.DB, data *userData) error {
	var total, count int

	query := "SELECT rating FROM user_ratings WHERE user_id_target = ?"
	rows, err := db.Query(query, data.UserID)
	if err != nil {
		return errors.New("Couldn't get user ratings")
	}
	defer rows.Close()

	for rows.Next() {
		var rating int
		if err := rows.Scan(&rating); err != nil {
			return errors.New("Couldn't get user ratings")
		}
		total += rating
		count++
	}
	if total == 0 {
		data.Rating = "2.5"
	} else {
		data.Rating = fmt.Sprintf("%.1f", float32(float32(total)/float32(count)))
	}
	data.NbRating = count
	return nil
}

func getCommonData(db *sql.DB, data *userData) error {
	query := `SELECT firstname, lastname, registered_date, TIMESTAMPDIFF(YEAR,dob,CURDATE()) as age, dob,
	picture_1, picture_2, picture_3, picture_4, picture_5, gender,
	gender_target, country, city, zipcode, biography, is_completed FROM users
	WHERE username = ?`
	row := db.QueryRow(query, data.Username)
	if err := row.Scan(&data.Firstname, &data.Lastname, &data.RegisteredDate, &data.Age, &data.Dob,
		&data.Picture1, &data.Picture2, &data.Picture3, &data.Picture4, &data.Picture5, &data.Gender, &data.GenderTarget,
		&data.Country, &data.City, &data.Zipcode, &data.Biography, &data.IsCompleted); err != nil {
		return err
	}
	return nil
}

// Get the list of last 10 usernames
// that visited the username (from most recent)
func getUserVisits(db *sql.DB, data *userData) error {

	// Initialize empty slice to have empty array instead of 'null' value
	data.Visits = make([]string, 0)

	query := `SELECT username FROM user_visits
	INNER JOIN users ON user_visits.user_id = users.user_id
	WHERE user_id_target = ?
	ORDER BY visit_date DESC LIMIT 10;`

	rows, err := db.Query(query, data.UserID)
	if err != nil {
		return errors.New("Couldn't get user visits")
	}
	defer rows.Close()

	for rows.Next() {
		var username string
		if err := rows.Scan(&username); err != nil {
			return errors.New("Couldn't get user visits")
		}
		data.Visits = append(data.Visits, username)
	}
	return nil
}

func getUserTags(db *sql.DB, data *userData) error {

	// Initialize empty slice to have empty array instead of 'null' value
	data.Tags = make([]string, 0)

	query := "SELECT tag FROM user_tags WHERE user_id = ?"
	rows, err := db.Query(query, data.UserID)
	if err != nil {
		return errors.New("Couldn't get user tags")
	}
	defer rows.Close()

	for rows.Next() {
		var tag string
		if err := rows.Scan(&tag); err != nil {
			return errors.New("Couldn't get user tags")
		}
		data.Tags = append(data.Tags, tag)
	}
	return nil
}

func getAuthorizeGPS(db *sql.DB, username string) (bool, error) {
	var authorize bool

	row := db.QueryRow("SELECT authorizeGPS FROM users WHERE username = ?", username)
	switch err := row.Scan(&authorize); err {
	case sql.ErrNoRows:
		return false, errors.New("Couldn't get username gps authorize data")
	default:
		return authorize, nil
	}
}

func getUserEmail(db *sql.DB, username string) (string, error) {
	var email string

	row := db.QueryRow("SELECT email FROM users WHERE username = ?", username)
	switch err := row.Scan(&email); err {
	case sql.ErrNoRows:
		return "", errors.New("Couldn't get username email")
	default:
		return email, nil
	}
}

// IsUserReported check if user is already reported
func IsUserReported(db *sql.DB, userID, userIDTarget int) bool {
	var found int

	rows := db.QueryRow("SELECT user_id FROM user_reports WHERE user_id = ? AND user_id_target = ?", userID, userIDTarget)
	switch err := rows.Scan(&found); err {
	case sql.ErrNoRows:
		return false
	default:
		return true
	}
}

func getLocation(db *sql.DB, userID int) (float32, float32, error) {
	var lat, long float32

	row := db.QueryRow("SELECT longitude, latitude FROM users WHERE user_id = ?", userID)
	switch err := row.Scan(&long, &lat); err {
	case sql.ErrNoRows:
		return 0, 0, errors.New("Couldn't get location data")
	default:
		return lat, long, nil
	}
}

func getGenderTarget(db *sql.DB, userID int) (string, error) {
	var target string

	row := db.QueryRow("SELECT gender_target FROM users WHERE user_id = ?", userID)
	switch err := row.Scan(&target); err {
	case sql.ErrNoRows:
		return "", errors.New("Couldn't get location data")
	default:
		return target, nil
	}
}

func getGender(db *sql.DB, userID int) (string, error) {
	var gender string

	row := db.QueryRow("SELECT gender FROM users WHERE user_id = ?", userID)
	switch err := row.Scan(&gender); err {
	case sql.ErrNoRows:
		return "", errors.New("Couldn't get gender data")
	default:
		return gender, nil
	}
}

// getCommonTags find common tags between username
// and usernametarget and returns the tags
func getCommonTags(db *sql.DB, username, usernametarget string) ([]string, error) {
	var commontags []string

	query := `SELECT tag FROM user_tags
	WHERE user_id = (SELECT user_id FROM users WHERE username = ?)
	AND tag IN (SELECT tag FROM user_tags WHERE user_id = (SELECT user_id FROM users WHERE username = ?));`
	rows, err := db.Query(query, username, usernametarget)
	if err != nil {
		return commontags, err
	}
	defer rows.Close()
	for rows.Next() {
		var str string
		if err := rows.Scan(&str); err != nil {
			return commontags, err
		}
		commontags = append(commontags, str)
	}
	return commontags, nil
}
