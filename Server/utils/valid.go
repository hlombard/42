package utils

import (
	"errors"
	"math"
	"net"
	"regexp"
	"strings"
	"time"
	"unicode"
)

// Used to return all the fields and errors
// in once, when a user post a form
type FormErrors struct {
	Errors map[string][]string
}

func NewFormErrors() *FormErrors {
	return &FormErrors{
		Errors: make(map[string][]string),
	}
}

func (f *FormErrors) Add(field string, err []string) {
	for _, desc := range err {
		f.Errors[field] = append(f.Errors[field], desc)
	}
}

func (f *FormErrors) Copy(src *FormErrors) {
	for field, err := range src.Errors {
		for _, eachErr := range err {
			f.Errors[field] = append(f.Errors[field], eachErr)
		}
	}
}

// ValidUsername checks the length of the field
func ValidUsername(username string) (err []string) {
	if len(username) > 20 {
		err = append(err, "Is too long (max 20 chars)")
	}

	// because of server/images/default/default.png
	if username == "default" {
		err = append(err, "Is not a valid username")
	}

	return err
}

// ValidFirstname checks the length of the field and uses a regex
// to avoid non sense input
func ValidFirstname(firstname string) (err []string) {
	if len(firstname) > 20 {
		err = append(err, "Is too long (max 20 chars)")
	}

	var isvalid = regexp.MustCompile(`^[\w'\-,.][^0-9_!¡?÷?¿/\\+=@#$%ˆ&*(){}|~<>;:[\]]{2,}$`).MatchString
	if isvalid(firstname) == false {
		err = append(err, "Is not formated correctly")
	}
	return err
}

// ValidLastname checks the length of the field and uses a regex
// to avoid non sense input
func ValidLastname(lastname string) (err []string) {
	if len(lastname) > 40 {
		err = append(err, "Is too long (max 40 chars)")
	}

	var isvalid = regexp.MustCompile(`^[\w'\-,.][^0-9_!¡?÷?¿/\\+=@#$%ˆ&*(){}|~<>;:[\]]{2,}$`).MatchString
	if isvalid(lastname) == false {
		err = append(err, "Is not formated correctly")
	}
	return err
}

// ValidEmail verifies if the email is correctly formated
// and if it is, it checks that the domain name exists (@gmail.com for example)
func ValidEmail(email string) (err []string) {
	if len(email) > 100 {
		err = append(err, "Is too long (max 100 chars)")
	}

	var emailRegex = regexp.MustCompile("^[a-zA-Z0-9.!#$%&'*+\\/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$")
	if !emailRegex.MatchString(email) {
		err = append(err, "Is not formated correctly")
		return err
	}
	split := strings.Split(email, "@")
	mx, erro := net.LookupMX(split[1]) // this can take a while...
	if erro != nil || len(mx) == 0 {
		err = append(err, "Is unreachable")
	}
	return err
}

// validDob Receives a date in this format: "1995-01-30T00:00:00Z" and
// if the age is less than 18 y/o returns an error
func ValidDob(dob time.Time) (err []string) {
	age := math.Floor(time.Now().Sub(dob).Hours() / 24 / 365)
	if age < 18 {
		err = append(err, "You need to be at least 18 y/o")
	}
	return err
}

// ValidPassword checks that the password is secured enough
// needs 1 special char, 1 number and 8 letters (with at least one of them in uppercase)
func ValidPassword(password string) (err []string) {
	letters := 0
	number := false
	upper := false
	special := false
	for _, c := range password {
		switch {
		case unicode.IsNumber(c):
			number = true
		case unicode.IsUpper(c):
			upper = true
			letters++
		case unicode.IsPunct(c) || unicode.IsSymbol(c):
			special = true
		case unicode.IsLetter(c) || c == ' ':
			letters++
		default:
		}
	}
	if number && upper && special && letters >= 8 {
		return err
	}
	err = append(err, "Needs to have 1 special char, 1 number, 8 letters (with at least 1 in uppercase)")
	return err
}

// ValidGender verifies if the gender is one of SQL ENUM
func ValidGender(gender string) (err []string) {
	allowed := []string{"male", "female", "non-binary"}
	for _, gen := range allowed {
		if gender == gen {
			return err
		}
	}
	err = append(err, "Needs to be either male, female or non-binary")
	return err
}

// ValidGenderTarget verifies if the gender target is one of SQL ENUM
func ValidGenderTarget(gender string) (err []string) {
	allowed := []string{"male", "female", "bisexual"}
	for _, gen := range allowed {
		if gender == gen {
			return err
		}
	}
	err = append(err, "needs to be either male, female or bisexual")
	return err
}

// ValidCountry for now only checks the length size
// smallest country is 4 chars
// max size in db is 50 chars
func ValidCountry(country string) (err []string) {
	if len(country) < 4 || len(country) > 50 {
		err = append(err, "Needs to be between 4 and 50 chars")
	}
	return err
}

// ValidCity for now only checks the length size
// max size in db is 85 chars
func ValidCity(city string) (err []string) {
	if len(city) > 85 {
		err = append(err, "Can't be more than 85 chars")
	}
	return err
}

// ValidZipcode for now only checks the length size
// max size in db is 10 chars
func ValidZipcode(zip string) (err []string) {
	if len(zip) > 10 {
		err = append(err, "Can't be more than 10 chars")
	}
	return err
}

// ValidBiography verifies length of the field
func ValidBiography(bio string) (err []string) {
	if len(bio) > 250 {
		err = append(err, "Can't be more than 250 chars")
	}
	return err
}

func ValidTag(tag string) error {
	if len(tag) > 25 {
		return errors.New("tags can't be longer than 25 chars")
	}
	if strings.HasPrefix(tag, "#") == false {
		return errors.New("tags always starts with a '#'")
	}
	return nil
}
