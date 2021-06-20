package main

import (
	"database/sql"
	"encoding/json"
	"errors"
	"fmt"
	"time"

	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

type message struct {
	data     []byte
	username string
}

// sends a message to a specific user
func sendMessageToTarget(m message) {
	fmt.Println(m.username, "=>", string(m.data))
	connections := h.users[m.username]
	if connections != nil {
		for c := range connections {
			select {
			case c.send <- m.data:
			default:
				close(c.send)
				delete(connections, c)
				if len(connections) == 0 {
					delete(h.users, m.username)
				}
			}
		}
	}
}

// sends a message to every connected users
func sendMessagetoEveryone(m message) {
	for username, connections := range h.users {
		if username == m.username {
			continue
		}
		for c := range connections {
			select {
			case c.send <- m.data:
			default:
				close(c.send)
				delete(connections, c)
				if len(connections) == 0 {
					delete(h.users, m.username)
				}
			}
		}
	}
}

func sendChatMessage(eventReceived event, from string) (err error) {
	// Make sure that content is string
	if _, ok := eventReceived.Content.(string); !ok {
		return errors.New("Invalid type passed in content")
	}

	if err = createMessageNotification(config.DB, from, eventReceived); err != nil {
		return err
	}

	// send msg
	chatmsg := chatMessage{
		From:    from,
		Date:    time.Now(),
		Message: eventReceived.Content.(string),
	}
	chatmsgfmt := make(map[string]chatMessage, 1)
	chatmsgfmt["message"] = chatmsg

	var msg message
	msg.username = eventReceived.UserTarget
	if msg.data, err = json.Marshal(chatmsgfmt); err != nil {
		return err
	}
	sendMessageToTarget(msg)
	return nil
}

func createMessageNotification(db *sql.DB, from string, eventReceived event) error {
	var err error

	// Check user is authorized to send message (if there is a match)
	if !matchExists(db, from, eventReceived.UserTarget) {
		return errors.New("user " + from + " is not allowed to send msg to user " + eventReceived.UserTarget)
	}

	// Check that content type is a string
	if _, ok := eventReceived.Content.(string); !ok {
		return errors.New("Invalid type passed in content")
	}

	// Add notif to database if not blocked
	var fromID, targetID int
	if fromID, err = utils.GetUserID(config.DB, from); err != nil {
		return err
	}
	if targetID, err = utils.GetUserID(config.DB, eventReceived.UserTarget); err != nil {
		return err
	}

	if err = utils.CreateNotification(config.DB, "message", fromID, targetID); err != nil {
		return err
	}
	return nil
}
