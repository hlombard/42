package utils

import (
	"database/sql"
	"errors"
	"strconv"
)

// CreateNotification creates a notification of the
// notificationName's type in DB. Only if userIDTarget didn't block
// userID
func CreateNotification(db *sql.DB, notificationName string, userID, userIDTarget int) error {
	var err error
	var notifTypeID int

	if IsUserBlocked(db, userIDTarget, userID) {
		SimpleLog("Create Notification", "Couldn't create a notification of type: "+notificationName+" user is blocked by user target")
		return nil
	}

	if notifTypeID, err = getNotificationTypeID(db, notificationName); err != nil {
		return err
	}

	insert := `INSERT INTO notifications (user_id, user_target_id, type_id)
	VALUES (?, ?, ?)`
	_, err = db.Exec(insert, userID, userIDTarget, notifTypeID)
	if err != nil {
		return errors.New("Couldn't create a notification of type: " + notificationName)
	}

	return nil
}

func getNotificationTypeID(db *sql.DB, notificationName string) (int, error) {
	var notifTypeID int

	rows := db.QueryRow("SELECT id FROM notifications_type WHERE name = ?", notificationName)
	switch err := rows.Scan(&notifTypeID); err {
	case sql.ErrNoRows:
		return -1, errors.New("Notification of type " + notificationName + " doesn't exists")
	default:
		return notifTypeID, nil
	}
}

// Check if userTarget is the actual user_target of notifID
func IsNotificationOwner(db *sql.DB, notifID int, userTarget string) bool {
	query := `SELECT notif_id FROM notifications
	LEFT JOIN users ON user_target_id = users.user_id
	WHERE username = ?
	AND notif_id = ?`

	var id int
	rows := db.QueryRow(query, userTarget, notifID)
	switch err := rows.Scan(&id); err {
	case sql.ErrNoRows:
		return false
	default:
		return true
	}
}

// SetNotificationInfo changes the value of viewed and sent of a notif_id
func SetNotificationInfo(db *sql.DB, id int, viewed, sent bool) error {
	update := "UPDATE notifications SET viewed = ?, sent = ? WHERE notif_id = ?"
	_, err := db.Exec(update, viewed, sent, id)
	if err != nil {
		return errors.New("Couldn't update notif " + strconv.Itoa(id) + " info")
	}
	return nil
}

func IsUserBlocked(db *sql.DB, userID, userIDTarget int) bool {
	var found int

	rows := db.QueryRow("SELECT user_id FROM user_blocks WHERE user_id = ? AND user_id_target = ?", userID, userIDTarget)
	switch err := rows.Scan(&found); err {
	case sql.ErrNoRows:
		return false
	default:
		return true
	}
}
