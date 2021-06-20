package handlers

import (
	"database/sql"
	"errors"
	"fmt"
	"net/http"
	"strconv"
	"time"

	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

type updateForm struct {
	Email1       string    `json:"email_1"`
	Email2       string    `json:"email_2"`
	Firstname    string    `json:"firstname"`
	Lastname     string    `json:"lastname"`
	Dob          time.Time `json:"dob"`
	Password1    string    `json:"password_1"`
	Password2    string    `json:"password_2"`
	Gender       string    `json:"gender"`
	GenderTarget string    `json:"gender_target"`
	Country      string    `json:"country"`
	City         string    `json:"city"`
	Zipcode      string    `json:"zipcode"`
	Biography    *string   `json:"biography"`
	AuthorizeGPS *bool     `json:"authorizeGPS"`
}

// UserUpdate updates :username data
//		ROUTE: /user/:username
//		METHOD: PATCH
//		PARAM: :username to modify, json (updateForm)
//		RETURN: none
func UserUpdate() gin.HandlerFunc {
	return func(c *gin.Context) {
		var err error
		var userID int
		var username, usernameTarget string

		// Get token owner username and userID (set in isAuthorized middleware)
		username = c.MustGet("tokenOwnerUsername").(string)
		userID, err = strconv.Atoi(c.MustGet("tokenOwnerID").(string))
		if err != nil {
			utils.SetContextAndLog(c, "User Update", http.StatusInternalServerError, "Couldn't get userID")
			return
		}

		// Verify that user is trying to modify his own data
		usernameTarget = c.Param("username")
		if username != usernameTarget {
			utils.SetContextAndLog(c, "User Update", http.StatusForbidden, "You can't modify someone else data")
			return
		}

		// Check that a valid form is provided
		var form updateForm
		if err := c.ShouldBindJSON(&form); err != nil {
			utils.SetContextAndLog(c, "User Update", http.StatusUnprocessableEntity, err.Error())
			return
		}

		// Parse Form
		if formErr := parseupdateForm(&form); len(formErr.Errors) > 0 {
			utils.LogForm("User Update", formErr.Errors)
			c.JSON(http.StatusNotAcceptable, formErr)
			return
		}

		// Update user data
		if err := updateUser(config.DB, username, form); err != nil {
			utils.SetContextAndLog(c, "User Update", http.StatusInternalServerError, err.Error())
			return
		}

		// Update last activity
		if err := utils.UpdateUserActivity(config.DB, userID, true); err != nil {
			utils.SetContextAndLog(c, "User Update", http.StatusInternalServerError, err.Error())
			return
		}

		utils.SetContextAndLog(c, "User Update", http.StatusOK, username+" data has been updated !")
	}
}

func updateUser(db *sql.DB, username string, form updateForm) error {
	update := `UPDATE users SET
	firstname = COALESCE(NULLIF(?, ''), firstname),
	lastname = COALESCE(NULLIF(?, ''), lastname),
	email = COALESCE(NULLIF(?, ''), email),
	pw_hash = COALESCE(NULLIF(?, ''), pw_hash),
	dob = COALESCE(NULLIF(?, '0001-01-01'), dob),
	gender = COALESCE(NULLIF(?, ''), gender),
	gender_target = COALESCE(NULLIF(?, ''), gender_target),
	country = COALESCE(NULLIF(?, ''), country),
	city = COALESCE(NULLIF(?, ''), city),
	zipcode = COALESCE(NULLIF(?, ''), zipcode),
	biography = COALESCE(?, biography),
	authorizeGPS = COALESCE(?, authorizeGPS)
	WHERE username = ?`
	_, err := db.Exec(update, form.Firstname, form.Lastname, form.Email1, form.Password1, form.Dob.Format("2006-01-02"), form.Gender,
		form.GenderTarget, form.Country, form.City, form.Zipcode, form.Biography, form.AuthorizeGPS, username)
	if err != nil {
		fmt.Println(err)
		return errors.New("Couldn't update user data into DB")
	}
	return nil
}

func parseupdateForm(form *updateForm) *utils.FormErrors {
	var passwdErr *utils.FormErrors

	formErr := utils.NewFormErrors()

	if form.Email1 != form.Email2 && form.Email1 != "" {
		formErr.Add("email_1", []string{"emails needs to be the same"})
	}
	err := utils.ValidEmail(form.Email1)
	if form.Email1 == form.Email2 && form.Email1 != "" && len(err) > 0 {
		formErr.Add("email_1", err)
	}
	if utils.EmailExists(config.DB, form.Email1) == true && form.Email1 == form.Email2 && form.Email1 != "" {
		formErr.Add("email_1", []string{"email is already used"})
	}

	err = utils.ValidFirstname(form.Firstname)
	if form.Firstname != "" && len(err) > 0 {
		formErr.Add("firstname", err)
	}

	err = utils.ValidLastname(form.Lastname)
	if form.Lastname != "" && len(err) > 0 {
		formErr.Add("lastname", err)
	}

	err = utils.ValidDob(form.Dob)
	if form.Dob.IsZero() && len(err) > 0 {
		formErr.Add("dob", err)
	}

	form.Password1, passwdErr = checkPasswordsAndHash(form.Password1, form.Password2)
	if form.Password2 != "" && len(passwdErr.Errors) > 0 {
		formErr.Copy(passwdErr)
	}

	err = utils.ValidGender(form.Gender)
	if form.Gender != "" && len(err) > 0 {
		formErr.Add("gender", err)
	}

	err = utils.ValidGenderTarget(form.GenderTarget)
	if form.GenderTarget != "" && len(err) > 0 {
		formErr.Add("gender_target", err)
	}

	err = utils.ValidCountry(form.Country)
	if form.Country != "" && len(err) > 0 {
		formErr.Add("country", err)
	}

	err = utils.ValidCity(form.City)
	if form.City != "" && len(err) > 0 {
		formErr.Add("city", err)
	}

	err = utils.ValidZipcode(form.Zipcode)
	if form.Zipcode != "" && len(err) > 0 {
		formErr.Add("zipcode", err)
	}

	if form.Biography != nil {
		err = utils.ValidBiography(*form.Biography)
	}
	if form.Biography != nil && len(err) > 0 {
		formErr.Add("biography", err)
	}

	return formErr
}
