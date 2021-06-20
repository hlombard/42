package main

import (
	"encoding/json"
	"errors"

	"github.com/hlombard/matcha/config"
)

type typingEvent struct {
	From  string `json:"from"`
	Value bool   `json:"value"`
}

func handleIsTyping(eventReceived event, from string) (err error) {
	var msg message
	var value, ok bool

	// Check that event content is a boolean
	if value, ok = eventReceived.Content.(bool); !ok {
		return errors.New("Invalid type passed in content")
	}

	// Check that both users are matched
	if !matchExists(config.DB, from, eventReceived.UserTarget) {
		return errors.New(from + " needs to be matched with " + eventReceived.UserTarget + " to send is_typing event")
	}

	// Send data
	typing := make(map[string]typingEvent, 1)
	typing["is_typing"] = typingEvent{
		From:  from,
		Value: value,
	}
	if msg.data, err = json.Marshal(typing); err != nil {
		return err
	}
	msg.username = eventReceived.UserTarget
	sendMessageToTarget(msg)
	return nil
}
