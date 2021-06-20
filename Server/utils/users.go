package utils

import (
	"database/sql"
	"errors"
)

// GetUserID returns user_id from username
func GetUserID(db *sql.DB, username string) (int, error) {
	var id int

	rows := db.QueryRow("SELECT user_id FROM users WHERE username = ?", username)
	switch err := rows.Scan(&id); err {
	case sql.ErrNoRows:
		return -1, errors.New(username + " doesn't exists")
	default:
		return id, nil
	}
}

// UpdateUserActivity updates userID last_activity and is_online status in DB
func UpdateUserActivity(db *sql.DB, userID int, isOnline bool) error {
	update := "UPDATE user_sessions SET last_activity = CURRENT_TIMESTAMP, is_online = ? WHERE user_id = ?"
	_, err := db.Exec(update, isOnline, userID)
	if err != nil {
		return errors.New("Couldn't update user status")
	}
	return nil
}

// Get User registered_date
func GetUserRegDate(db *sql.DB, username string) (regDate string, err error) {
	rows := db.QueryRow("SELECT registered_date FROM users WHERE username = ?", username)
	switch err := rows.Scan(&regDate); err {
	case sql.ErrNoRows:
		return "", errors.New(username + " doesn't exists")
	default:
		return regDate, nil
	}
}
