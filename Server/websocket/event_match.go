package main

import (
	"database/sql"
	"encoding/json"
	"errors"

	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

type match struct {
	Username string `json:"username"`
	Date     string `json:"date"`
}

type matchList struct {
	Matches []match `json:"match_list"`
}

func sendMatchList(username string) {
	var err error
	var matches []match

	if matches, err = getUserMatches(config.DB, username); err != nil {
		utils.SimpleLog("Send Match List", err.Error())
		return
	}

	var all matchList
	var msg message

	all.Matches = matches
	if msg.data, err = json.Marshal(all); err != nil {
		utils.SimpleLog("Send Match List", err.Error())
		return
	}
	msg.username = username
	utils.SimpleLog("Send Match List", "Sending match list to "+username)
	sendMessageToTarget(msg)
}

func getUserMatches(db *sql.DB, username string) (matches []match, err error) {
	query := `SELECT user1.username, user2.username, match_date FROM matches
	LEFT JOIN users AS user1 ON user1.user_id = matches.user_id_1
	LEFT JOIN users AS user2 ON user2.user_id = matches.user_id_2
	WHERE user1.username = ?
	OR user2.username = ?`

	rows, err := db.Query(query, username, username)
	if err != nil {
		return nil, errors.New("Couldn't get " + username + " matches")
	}
	defer rows.Close()

	for rows.Next() {
		var user1, user2, date string
		var m match

		if err := rows.Scan(&user1, &user2, &date); err != nil {
			return nil, errors.New("Couldn't get " + username + " matches")
		}

		if user1 == username {
			m.Username = user2
		} else {
			m.Username = user1
		}
		m.Date = date
		matches = append(matches, m)
	}
	return matches, nil
}

func matchExists(db *sql.DB, user1, user2 string) bool {
	var date string

	query := `SELECT match_date FROM matches
	LEFT JOIN users AS user1 ON user1.user_id = matches.user_id_1
	LEFT JOIN users AS user2 ON user2.user_id = matches.user_id_2
	WHERE (user1.username = ? OR user1.username = ?)
	AND (user2.username = ? OR user2.username = ?);`
	rows := db.QueryRow(query, user1, user2, user1, user2)
	switch err := rows.Scan(&date); err {
	case sql.ErrNoRows:
		return false
	default:
		return true
	}
}
