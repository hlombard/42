package main

import (
	"encoding/json"
	"errors"

	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

func handleLogout(eventReceived event, from string) (err error) {
	var msg message
	var userID int

	// Check that the logout event comes from the UserTarget
	if from != eventReceived.UserTarget {
		return errors.New(from + " and " + eventReceived.UserTarget + " needs to be the same")
	}

	// Set user status to offline
	if userID, err = utils.GetUserID(config.DB, from); err != nil {
		return err
	}
	if err := utils.UpdateUserActivity(config.DB, userID, false); err != nil {
		return err
	}

	// Send the logout event
	logout := make(map[string]string, 1)
	logout["logout"] = from
	msg.username = from
	if msg.data, err = json.Marshal(logout); err != nil {
		return err
	}
	sendMessagetoEveryone(msg)
	return nil
}
