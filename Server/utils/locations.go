package utils

import (
	"database/sql"
	"encoding/json"
	"errors"
	"fmt"
	"io/ioutil"
	"net/http"
	"strings"

	"github.com/hlombard/matcha/config"
)

type Coordinate struct {
	Latitude  float64 `json:"latitude"`
	Longitude float64 `json:"longitude"`
}

func StoreLocationData(db *sql.DB, username, ip string) error {
	coord, err := getLocationData(ip)
	if err != nil {
		return err
	}
	query := "UPDATE users SET longitude = ?, latitude = ? WHERE username = ?"
	_, err = db.Exec(query, coord.Longitude, coord.Latitude, username)
	if err != nil {
		return errors.New("Couldn't update " + username + " location")
	}
	return nil
}

func getLocationData(ip string) (coord Coordinate, err error) {

	// Tmp solution if client doesnt send ip
	if strings.HasPrefix(ip, "172") {
		resp, err := http.Get("https://api.ipify.org?format=json")
		if err != nil {
			return Coordinate{}, errors.New("Couldn't get user ip")
		}
		defer resp.Body.Close()
		content, err := ioutil.ReadAll(resp.Body)
		if err != nil {
			return Coordinate{}, errors.New("Couldn't get user ip")
		}
		m := make(map[string]string, 1)
		if err = json.Unmarshal(content, &m); err != nil {
			return Coordinate{}, errors.New("Couldn't unmarshal ip info")
		}
		ip = m["ip"]
	}

	resp, err := http.Get(config.APILocation + ip + "?access_key=" + config.APILocationKey)
	if err != nil {
		fmt.Println("Url:", config.APILocation+ip+"?access_key"+config.APILocationKey)
		return Coordinate{}, errors.New("Couldn't find user location") // fix err here
	}
	defer resp.Body.Close()
	bodyBytes, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return Coordinate{}, errors.New("Couldn't read user location")
	}

	if err := json.Unmarshal(bodyBytes, &coord); err != nil {
		return Coordinate{}, errors.New("Couldn't get user location")
	}
	return coord, nil
}
