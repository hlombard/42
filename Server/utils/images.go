package utils

import (
	"database/sql"
	"errors"
)

// SetImageURL sets in DB a picture url for a user
func SetImageURL(db *sql.DB, url, username, number string) error {
	pictureField := "picture_" + number
	update := "UPDATE users SET " + pictureField + " = ? WHERE username = ?"
	_, err := db.Exec(update, url, username)
	if err != nil {
		return errors.New("Couldn't set picture path in DB")
	}
	return nil
}
