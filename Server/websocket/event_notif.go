package main

import (
	"database/sql"
	"encoding/json"
	"errors"
	"time"

	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

type notification struct {
	ID     int    `json:"id"`
	Type   string `json:"type"`
	From   string `json:"from"`
	To     string `json:"to"`
	Date   string `json:"date"`
	Viewed bool   `json:"viewed"`
}

type event struct {
	Type       string      `json:"type"`
	UserTarget string      `json:"user_target"`
	Time       time.Time   `json:"time"`
	Content    interface{} `json:"content"`
}

type chatMessage struct {
	From    string    `json:"from"`
	Date    time.Time `json:"date"`
	Message string    `json:"message"`
}

// handles like/match/unlike/visit/message events
func handleNotif(eventReceived event, from string, notifType string) (err error) {
	notif := notification{}

	// Check if from is blocked by userTarget and return an err if true
	var fromID, toID int
	if fromID, err = utils.GetUserID(config.DB, from); err != nil {
		return err
	}
	if toID, err = utils.GetUserID(config.DB, eventReceived.UserTarget); err != nil {
		return err
	}
	if utils.IsUserBlocked(config.DB, toID, fromID) {
		return errors.New(from + " is blocked by " + eventReceived.UserTarget)
	}

	// If its a message we need to create a notif in DB
	// after checking if users are authorized to send/receive message from each others
	// and send the message data
	if notifType == "message" {
		if err := sendChatMessage(eventReceived, from); err != nil {
			return err
		}
	}

	// If its a match or an unlike, send an updated match_list to both users (from and userTarget)
	// NB: the match should already be added / delete from the previous API call (frontend)
	if notifType == "match" || notifType == "unlike" {
		sendMatchList(from)
		sendMatchList(eventReceived.UserTarget)
	}

	if notif, err = getUnsetNotification(config.DB, notifType, from, eventReceived.UserTarget); err != nil {
		return err
	}

	// Send notification message to user target
	var msg message
	msg.username = eventReceived.UserTarget
	if msg.data, err = json.Marshal(notif); err != nil {
		return err
	}
	sendMessageToTarget(msg)

	// Set Notification as sent
	if err = utils.SetNotificationInfo(config.DB, notif.ID, false, true); err != nil {
		return err
	}
	return
}

func sendNotifList(username string, userID int) {
	var err error
	var notifs []notification
	var msg message

	msg.username = username

	if notifs, err = getUserNotifications(config.DB, username, userID); err != nil {
		utils.SimpleLog("Send Notif history", err.Error())
		return
	}

	notifHist := make(map[string][]notification, 1)
	notifHist["notif_list"] = notifs
	if msg.data, err = json.Marshal(notifHist); err != nil {
		utils.SimpleLog("Send Notif history", err.Error())
		return
	}
	utils.SimpleLog("Send Notif history", "Sending notif hist to "+username)
	sendMessageToTarget(msg)
}

// Get all the notifications of username and set them as sent if they
// were not
func getUserNotifications(db *sql.DB, username string, userID int) ([]notification, error) {
	query := `SELECT notif_id, username, created_at, viewed, name, sent
	FROM notifications
		LEFT JOIN notifications_type ON notifications.type_id = notifications_type.id
		LEFT JOIN users ON notifications.user_id = users.user_id
	WHERE user_target_id = ?`

	rows, err := db.Query(query, userID)
	if err != nil {
		return nil, errors.New("Couldn't get " + username + " notif hist")
	}
	defer rows.Close()

	var notifications []notification
	for rows.Next() {
		var tmp notification
		var sent bool

		if err := rows.Scan(&tmp.ID, &tmp.From, &tmp.Date, &tmp.Viewed, &tmp.Type, &sent); err != nil {
			return nil, errors.New("Couldn't get " + username + " notif hist")
		}

		if sent == false {
			if err := utils.SetNotificationInfo(db, tmp.ID, tmp.Viewed, true); err != nil {
				return nil, err
			}
		}
		tmp.To = username
		notifications = append(notifications, tmp)
	}
	return notifications, nil
}

// getUnsetNotification get the notification data of notifType from a user to a userTarget
// that has not been sent yet
func getUnsetNotification(db *sql.DB, notifType string, from string, userTarget string) (notification, error) {
	query := `SELECT notif_id, notif_type.name as type, user.username, usertarget.username as user_target, created_at, viewed FROM notifications
	LEFT JOIN notifications_type AS notif_type ON notifications.type_id = notif_type.id
	LEFT JOIN users AS usertarget ON notifications.user_target_id = usertarget.user_id
	LEFT JOIN users AS user ON notifications.user_id = user.user_id
	WHERE notif_type.name = ?
	AND user.username = ?
	AND usertarget.username = ?
	AND sent = false`

	notif := notification{}
	notif.From = from
	notif.To = userTarget
	notif.Date = time.Now().Format("2006-01-02 15:04:05")

	rows := db.QueryRow(query, notifType, from, userTarget)
	switch err := rows.Scan(&notif.ID, &notif.Type, notif.From, notif.To, notif.Date, notif.Viewed); err {
	case sql.ErrNoRows:
		return notification{}, errors.New("No notifications of type " + notifType + " found for user " + userTarget + " from user " + from)
	default:
		return notif, nil
	}
}
