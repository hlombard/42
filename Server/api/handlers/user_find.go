package handlers

import (
	"database/sql"
	"errors"
	"net/http"
	"strconv"
	"strings"

	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

// searchForm is some optional input parameters
type searchForm struct {
	MinAge       int      `json:"min_age" binding:"required"`
	MaxAge       int      `json:"max_age" binding:"required"`
	MinRating    string   `json:"min_rating" binding:"required"`
	MaxRating    string   `json:"max_rating" binding:"required"`
	Latitude     string   `json:"latitude" binding:"required"`
	Longitude    string   `json:"longitude" binding:"required"`
	Tags         []string `json:"tags" binding:"required"`
	IsSuggestion *bool    `json:"is_suggestion" binding:"required"`
}

type searchParameters struct {
	TagsRequired bool
	MinAge       int
	MaxAge       int
	MinRating    float32
	MaxRating    float32
	Latitude     float32
	Longitude    float32
	Tags         []string // Required tags
	IsSuggestion bool
}

type userInfo struct {
	UserID       int
	Username     string
	GenderTarget string
	Gender       string
	Tags         []string // User tags
}

type profile struct {
	Username       string   `json:"username"`
	UserID         int      `json:"user_id"`
	Firstname      string   `json:"firstname"`
	Lastname       string   `json:"lastname"`
	Age            int      `json:"age"`
	Picture1       string   `json:"picture_1"`
	Gender         string   `json:"gender"`
	GenderTarget   string   `json:"gender_target"`
	Country        string   `json:"country"`
	City           string   `json:"city"`
	Zipcode        string   `json:"zipcode"`
	Rating         string   `json:"rating"`
	CommonTags     []string `json:"common_tags"`
	CommonTagsNB   int      `json:"common_tags_nb"`
	SearchTags     []string `json:"search_tags"`
	SearchTagsNB   int      `json:"search_tags_nb"`
	Latitude       float64  `json:"latitude"`
	Longitude      float64  `json:"longitude"`
	Distance       string   `json:"distance"`
	IsOnline       bool     `json:"is_online"`
	LastActivity   string   `json:"last_activity"`
	RegisteredDate string   `json:"registered_date"`
}

// UserFind gets a list of profiles
// according  to the optional searchparam json
//		ROUTE: api/user/:username/find
//		METHOD: POST
//		PARAM: :username, json searchForm (optional)
//		RETURN: list of profiles
func UserFind() gin.HandlerFunc {
	return func(c *gin.Context) {
		var err error
		var profiles []profile
		var form searchForm
		var userInfo userInfo

		// Get token owner username and userID (set in isAuthorized middleware)
		userInfo.Username = c.MustGet("tokenOwnerUsername").(string)
		userInfo.UserID, err = strconv.Atoi(c.MustGet("tokenOwnerID").(string))
		if err != nil {
			utils.SetContextAndLog(c, "User Find", http.StatusInternalServerError, "Couldn't get userID")
			return
		}

		// Make sure user is trying to access his own route
		usernameTarget := c.Param("username")
		if userInfo.Username != usernameTarget {
			utils.SetContextAndLog(c, "User Find", http.StatusForbidden, "Not allowed")
			return
		}

		// Make sure user is_completed = true
		if !IsUserCompleted(config.DB, userInfo.Username) {
			utils.SetContextAndLog(c, "User Find", http.StatusForbidden, "You need to upload a profile picture first")
			return
		}

		// Check if a valid search form was provided, else set default values
		if err := c.ShouldBindJSON(&form); err != nil {
			utils.SetContextAndLog(c, "User Find", http.StatusNotAcceptable, "Invalid Form provided")
			return
		}

		// Set default search values
		if *form.IsSuggestion == true {
			if err := setDefaultValues(&form); err != nil {
				utils.SetContextAndLog(c, "User Find", http.StatusInternalServerError, "Couldn't set default values")
				return
			}
		}

		// Parse form param and get final param info
		param, err := parseFormParam(&form, userInfo.UserID)
		if err != nil {
			utils.SetContextAndLog(c, "User Find", http.StatusNotAcceptable, err.Error())
			return
		}

		// Get user infos to complete query request (gender, gender_target, ...)
		if err := getUserInfo(config.DB, &userInfo); err != nil {
			utils.SetContextAndLog(c, "User Find", http.StatusInternalServerError, err.Error())
			return
		}

		// Request the profiles
		if profiles, err = findProfiles(config.DB, param, userInfo); err != nil {
			utils.SetContextAndLog(c, "User Find", http.StatusInternalServerError, err.Error())
			return
		}

		// Add some more data to the profiles we found (tags in common, ...)
		if err := addProfileData(config.DB, profiles, userInfo, param); err != nil {
			utils.SetContextAndLog(c, "User Find", http.StatusInternalServerError, err.Error())
			return
		}

		// Log and return data
		utils.SimpleLog("User Find", "Found "+strconv.Itoa(len(profiles))+" profiles for "+userInfo.Username)
		c.JSON(http.StatusOK, profiles)
	}
}

func addProfileData(db *sql.DB, profiles []profile, info userInfo, param searchParameters) error {
	var err error
	var commontags []string

	for idx, prof := range profiles {

		// Add common tags, and the number of them
		if commontags, err = getCommonTags(db, prof.Username, info.Username); err != nil {
			return err
		}
		profiles[idx].CommonTags = commontags
		profiles[idx].CommonTagsNB = len(commontags)

		// Add UserID
		profiles[idx].UserID, err = utils.GetUserID(config.DB, prof.Username)

		// Add IsOnline and LastActivity data
		profiles[idx].IsOnline, profiles[idx].LastActivity = getUserOnlineStatus(config.DB, profiles[idx].UserID)

		// Add registered_date
		profiles[idx].RegisteredDate, _ = utils.GetUserRegDate(config.DB, prof.Username)

		// if tagsrequired = true get common search tags
		if param.TagsRequired == true {
			profiles[idx].SearchTags = getCommonSearchTags(config.DB, param, profiles[idx].UserID)
			profiles[idx].SearchTagsNB = len(profiles[idx].SearchTags)
		}
	}
	return nil
}

func getCommonSearchTags(db *sql.DB, param searchParameters, userID int) []string {
	var commonSearchTags []string

	args := make([]interface{}, len(param.Tags)+1)
	args[0] = userID
	for i, tag := range param.Tags {
		args[i+1] = tag
	}
	query := `SELECT distinct tag FROM user_tags WHERE user_id = ? AND tag IN (?` + strings.Repeat(",?", len(args)-2) + `)`
	rows, err := db.Query(query, args...)
	if err != nil {
		return nil
	}
	defer rows.Close()
	for rows.Next() {
		var tag string
		if err := rows.Scan(&tag); err != nil {
			continue
		}
		commonSearchTags = append(commonSearchTags, tag)
	}
	return commonSearchTags
}

func parseFormParam(form *searchForm, userID int) (searchParameters, error) {
	var err error
	var param searchParameters

	// Age gap
	if form.MinAge < 18 || form.MaxAge < 18 {
		return searchParameters{}, errors.New("min/max age has to be greater than 18")
	}
	param.MaxAge, param.MinAge = form.MaxAge, form.MinAge
	if form.MinAge > form.MaxAge {
		param.MaxAge, param.MinAge = param.MinAge, param.MaxAge
	}

	// Rating gap
	minrating, err := strconv.ParseFloat(form.MinRating, 32)
	if err != nil {
		return searchParameters{}, err
	}
	maxrating, err := strconv.ParseFloat(form.MaxRating, 32)
	if err != nil {
		return searchParameters{}, err
	}
	param.MinRating = float32(minrating)
	param.MaxRating = float32(maxrating)
	if param.MinRating < 1.0 || param.MaxRating < 1.0 {
		return searchParameters{}, errors.New("min/max rating has to be greater than 1.0")
	}
	if param.MinRating > 5.0 || param.MaxRating > 5.0 {
		return searchParameters{}, errors.New("min/max rating has to be lower than 5.0")
	}
	if param.MinRating > param.MaxRating {
		param.MaxRating, param.MinRating = param.MinRating, param.MaxRating
	}

	// If location is set as default, get user location
	if form.Latitude == "0" && form.Longitude == "0" {
		param.Latitude, param.Longitude, err = getLocation(config.DB, userID)
		if err != nil {
			return searchParameters{}, err
		}
	}

	// If tags = null means that the tags are not required (not a research with specific tags)
	if form.Tags != nil && len(form.Tags) > 0 {
		param.TagsRequired = true
	}
	for _, tag := range form.Tags {
		if strings.HasPrefix(tag, "#") == false {
			return searchParameters{}, errors.New("All tags must start with a '#")
		}
	}
	param.Tags = form.Tags
	param.IsSuggestion = *form.IsSuggestion
	return param, nil
}

func getUserInfo(db *sql.DB, info *userInfo) error {
	var err error

	info.GenderTarget, err = getGenderTarget(config.DB, info.UserID)
	if err != nil {
		return err
	}

	info.Gender, err = getGender(config.DB, info.UserID)
	if err != nil {
		return err
	}

	// Get user tags
	var data userData
	data.UserID = info.UserID
	if err = getUserTags(db, &data); err != nil {
		return err
	}
	info.Tags = data.Tags
	return nil
}

func setDefaultValues(form *searchForm) error {
	form.MinAge = 18
	form.MaxAge = 100
	form.MinRating = "1.0"
	form.MaxRating = "5.0"

	// Set tags to user tags
	var data userData
	if err := getUserTags(config.DB, &data); err != nil {
		return err
	}
	form.Tags = data.Tags

	// Set lat and long to default
	form.Latitude = "0"
	form.Longitude = "0"

	form.Tags = nil
	return nil
}

func getQueryArgs(param searchParameters, info userInfo) []interface{} {
	var args []interface{}

	args = append(args, param.Latitude, param.Longitude)
	if param.IsSuggestion == true {
		args = append(args, info.GenderTarget, info.GenderTarget)
		args = append(args, info.Gender, info.Gender)
	}
	args = append(args, param.MinAge, param.MaxAge)
	args = append(args, info.UserID, info.UserID, info.UserID)
	if param.TagsRequired {
		for _, tag := range param.Tags {
			args = append(args, string(tag))
		}
	}
	args = append(args, param.MinRating)
	args = append(args, param.MaxRating)
	return args
}

// Select the matching profiles
func findProfiles(db *sql.DB, param searchParameters, info userInfo) ([]profile, error) {
	var profiles []profile

	// Prepare the tag query if tags are required
	tagRequiredQuery := ""
	if param.TagsRequired == true {
		tagRequiredQuery = `AND users.user_id IN (SELECT user_id FROM user_tags WHERE tag IN (?` + strings.Repeat(",?", len(param.Tags)-1) + `))`
	}

	genderCriterias := ""
	if param.IsSuggestion == true {
		genderCriterias = `AND IF(? = 'bisexual', gender IN ('male', 'female', 'non-binary'), IF(? = 'male', gender IN ('male', 'non-binary'), gender IN ('female', 'non-binary')))
		AND IF(? = 'non-binary', gender_target IN ('male', 'female', 'bisexual'), IF(? = 'male', gender_target IN ('male', 'bisexual'), gender_target IN ('female', 'bisexual')))`
	}

	query := `SELECT
	username, firstname, lastname, country, city, zipcode, picture_1, gender, gender_target, latitude, longitude,
	TIMESTAMPDIFF(YEAR,dob,CURDATE()) as age,
	SQRT(POW(69.1 * (latitude - ?), 2) + POW(69.1 * (? - longitude) * COS(latitude / 57.3), 2)) AS distance,
	IFNULL(avg(rating), 2.5) as rating
	FROM users
		LEFT JOIN user_ratings ON users.user_id = user_ratings.user_id_target
		LEFT JOIN user_tags ON users.user_id = user_tags.user_id
	WHERE
	is_verified = 1 AND is_completed = 1
	` + genderCriterias + `
	AND TIMESTAMPDIFF(YEAR,dob,CURDATE()) BETWEEN ? AND ?
	AND users.user_id NOT IN (SELECT user_id_target FROM user_reports WHERE user_id = ?)
	AND users.user_id NOT IN (SELECT user_id_target FROM user_blocks WHERE user_id = ?)
	AND users.user_id != ?
	 ` + tagRequiredQuery + `
	GROUP BY users.user_id
	HAVING IFNULL(avg(rating), 2.5) between ? and ?
	ORDER BY distance
	LIMIT 25`

	// Get the query args
	args := getQueryArgs(param, info)

	rows, err := db.Query(query, args...)
	if err != nil {
		return nil, errors.New("Couldn't find profile with these parameters")
	}
	defer rows.Close()
	for rows.Next() {
		var tmp profile

		if err := rows.Scan(&tmp.Username, &tmp.Firstname, &tmp.Lastname, &tmp.Country, &tmp.City,
			&tmp.Zipcode, &tmp.Picture1, &tmp.Gender, &tmp.GenderTarget, &tmp.Latitude, &tmp.Longitude, &tmp.Age, &tmp.Distance, &tmp.Rating); err != nil {
			return nil, errors.New("Couldn't get profile data")
		}
		profiles = append(profiles, tmp)
	}
	return profiles, nil
}
