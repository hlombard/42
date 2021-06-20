package handlers

import (
	"database/sql"
	"errors"
	"net/http"
	"time"

	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

// AccountCreateForm is the json expected from a /api/account/create post request
type accountCreateForm struct {
	Username     string    `json:"username" binding:"required"`
	Firstname    string    `json:"firstname" binding:"required"`
	Lastname     string    `json:"lastname" binding:"required"`
	Email        string    `json:"email" binding:"required"`
	Dob          time.Time `json:"dob" binding:"required"`
	Password     string    `json:"password" binding:"required"`
	Gender       string    `json:"gender" binding:"required"`
	Country      string    `json:"country" binding:"required"`
	City         string    `json:"city" binding:"required"`
	Zipcode      string    `json:"zipcode" binding:"required"`
	AuthorizeGPS bool      `json:"authorizeGPS"`
}

// AccountCreate creates user in DB and sends a
// mail to verify the account
//		ROUTE: /api/account/create
//		METHOD: POST
//		PARAM: json (AccountCreateForm)
//		RETURN: none
func AccountCreate() gin.HandlerFunc {
	return func(c *gin.Context) {
		var form accountCreateForm
		var err error

		if err := c.ShouldBindJSON(&form); err != nil {
			utils.SetContextAndLog(c, "Account Create", http.StatusUnprocessableEntity, err.Error())
			return
		}

		if formErr := parseCreateForm(form); len(formErr.Errors) > 0 {
			utils.LogForm("Account Create", formErr.Errors)
			c.JSON(http.StatusNotAcceptable, formErr)
			return
		}

		// Hash the password before creating user in DB
		form.Password, err = utils.HashAndSalt(form.Password)
		if err != nil {
			utils.SetContextAndLog(c, "Account Create", http.StatusInternalServerError, err.Error())
			return
		}

		// Add user to database
		if err := userAccountCreate(config.DB, form); err != nil {
			utils.SetContextAndLog(c, "Account Create", http.StatusInternalServerError, err.Error())
			return
		}

		// Send an email with a personal link
		if err := sendVerifyEmail(form); err != nil {
			utils.SetContextAndLog(c, "AccountCreate", http.StatusInternalServerError, err.Error())
			return
		}

		utils.SetContextAndLog(c, "Account Create", http.StatusOK, form.Username+" has been created and received an email !")
	}
}

func sendVerifyEmail(form accountCreateForm) error {
	personalLink, err := utils.GenerateEmailVerifyLink(form.Email)
	if err != nil {
		return errors.New("Couldn't generate personal token")
	}

	receiverMail := []string{form.Email}
	mailData := utils.GetVerifyMailData(form.Username, personalLink)
	message := []byte(mailData.Subject + mailData.Mime + mailData.Body)

	if err := utils.SendEmail(receiverMail, message); err != nil {
		return errors.New("Couldn't send a verification email to " + form.Email)
	}
	return nil
}

func userAccountCreate(db *sql.DB, form accountCreateForm) error {
	query := `INSERT INTO users
	(username, firstname, lastname, email, dob, picture_1, picture_2, picture_3, picture_4, picture_5,
	pw_hash, gender, country, city, zipcode, authorizeGPS)
	VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)`

	_, err := db.Exec(query, form.Username, form.Firstname, form.Lastname, form.Email, form.Dob, config.ImageDefault,
		config.ImageDefault, config.ImageDefault, config.ImageDefault, config.ImageDefault, form.Password,
		form.Gender, form.Country, form.City, form.Zipcode, form.AuthorizeGPS)
	if err != nil {
		return err
	}
	return nil
}

// parseCreateForm parses every fields of the AccountCreate form
// and returns every errors encountered
func parseCreateForm(form accountCreateForm) *utils.FormErrors {

	formErr := utils.NewFormErrors()

	if err := utils.ValidUsername(form.Username); len(err) > 0 {
		formErr.Add("username", err)
	}

	if err := utils.ValidFirstname(form.Firstname); len(err) > 0 {
		formErr.Add("firstname", err)
	}

	if err := utils.ValidLastname(form.Lastname); len(err) > 0 {
		formErr.Add("lastname", err)
	}

	if err := utils.ValidEmail(form.Email); len(err) > 0 {
		formErr.Add("email", err)
	}

	if err := utils.ValidDob(form.Dob); len(err) > 0 {
		formErr.Add("dob", err)
	}

	if err := utils.ValidPassword(form.Password); len(err) > 0 {
		formErr.Add("password", err)
	}

	if err := utils.ValidGender(form.Gender); len(err) > 0 {
		formErr.Add("gender", err)
	}

	if err := utils.ValidCountry(form.Country); len(err) > 0 {
		formErr.Add("country", err)
	}

	if err := utils.ValidCity(form.City); len(err) > 0 {
		formErr.Add("city", err)
	}

	if err := utils.ValidZipcode(form.Zipcode); len(err) > 0 {
		formErr.Add("zipcode", err)
	}

	if _, err := utils.GetUserID(config.DB, form.Username); err == nil {
		formErr.Add("username", []string{form.Username + " is not available"})
	}

	if utils.EmailExists(config.DB, form.Email) {
		formErr.Add("email", []string{form.Email + " is already linked to another account"})
	}

	return formErr
}
