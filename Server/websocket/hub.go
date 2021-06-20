package main

import (
	"database/sql"
	"encoding/json"

	_ "github.com/go-sql-driver/mysql"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

// hub maintains the set of active connections and broadcasts messages to the
// connections.
type hub struct {
	// Registered connections.
	users map[string]map[*connection]bool

	// Inbound messages from the connections.
	broadcast chan message

	// Register requests from the connections.
	register chan subscription

	// Unregister requests from connections.
	unregister chan subscription

	// Database
	db *sql.DB

	// Mutex to add
}

type subscription struct {
	conn     *connection
	username string
	userID   int
}

var h = hub{
	broadcast:  make(chan message),
	register:   make(chan subscription),
	unregister: make(chan subscription),
	users:      make(map[string]map[*connection]bool),
	db:         nil,
}

// handleRegister registers the new connected user
// it sends him notifications history + match list.
// and it broadcast the login event to every connected user but him
func (h *hub) handleRegister(s subscription) {
	var msg message

	connections := h.users[s.username]
	if connections == nil {
		connections = make(map[*connection]bool)
		h.users[s.username] = connections
	}
	h.users[s.username][s.conn] = true

	// Update last activity
	utils.UpdateUserActivity(config.DB, s.userID, true)

	// Send notification List
	sendNotifList(s.username, s.userID)

	// Send match list
	sendMatchList(s.username)

	// Send login event to everyone
	m := make(map[string]string, 1)
	m["login"] = s.username
	if data, err := json.Marshal(m); err == nil {
		msg.data = data
		msg.username = s.username
		sendMessagetoEveryone(msg)
	}
}

// handleUnregister simply deletes the user connection
// and broadcast the logout event to every connected user
func (h *hub) handleUnregister(s subscription) {
	var msg message

	connections := h.users[s.username]
	if connections != nil {
		if _, ok := connections[s.conn]; ok {
			delete(connections, s.conn)
			close(s.conn.send)
			if len(connections) == 0 {
				delete(h.users, s.username)
			}

			// Update last activity
			utils.UpdateUserActivity(config.DB, s.userID, false)

			// Broadcast logout to everyone
			m := make(map[string]string)
			m["logout"] = s.username
			if data, err := json.Marshal(m); err == nil {
				msg.data = data
				msg.username = s.username
				sendMessagetoEveryone(msg)
			}
		}
	}
}

// Handle the different events and broadcast data
func (h *hub) handleEvent(dataReceived message) {
	var eventReceived event

	if err := json.Unmarshal(dataReceived.data, &eventReceived); err != nil {
		utils.SimpleLog("Handle Event", "Invalid Event received from "+dataReceived.username)
		return
	}
	utils.SimpleLog("Handle Event", "Received a valid event from "+dataReceived.username+" of type "+eventReceived.Type+" for user "+eventReceived.UserTarget)

	switch eventReceived.Type {
	case "like", "unlike", "match", "visit", "message":
		if err := handleNotif(eventReceived, dataReceived.username, eventReceived.Type); err != nil {
			utils.SimpleLog("Handle Notif", err.Error())
			return
		}
	case "viewed":
		if err := handleViewed(eventReceived, dataReceived.username); err != nil {
			utils.SimpleLog("Handle Viewed", err.Error())
			return
		}
	case "is_typing":
		if err := handleIsTyping(eventReceived, dataReceived.username); err != nil {
			utils.SimpleLog("Handle Is Typing", err.Error())
			return
		}
	case "logout":
		if err := handleLogout(eventReceived, dataReceived.username); err != nil {
			utils.SimpleLog("Handle Logout", err.Error())
			return
		}
	default:
		utils.SimpleLog("Handle Event", eventReceived.Type+" is an unknown event")
		return
	}
}

func (h *hub) run() {

	for {
		select {
		case s := <-h.register:
			h.handleRegister(s)
		case s := <-h.unregister:
			h.handleUnregister(s)
		case m := <-h.broadcast:
			h.handleEvent(m)
		}
	}
}
