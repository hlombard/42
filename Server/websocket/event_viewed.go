package main

import (
	"errors"
	"reflect"
	"strconv"

	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

// handleViewed make sure that notifIDs belongs to 'from'
// and sets them as viewed
func handleViewed(eventReceived event, from string) (err error) {
	switch reflect.TypeOf(eventReceived.Content).Kind() {
	case reflect.Slice:
		values := reflect.ValueOf(eventReceived.Content)
		for i := 0; i < values.Len(); i++ {

			tmp, ok := values.Index(i).Interface().(float64) // float64 because it is passed as an Interface{}
			if !ok {
				return errors.New("Invalid type passed in content")
			}

			notifID := int(tmp)
			if !utils.IsNotificationOwner(config.DB, notifID, from) {
				utils.SimpleLog("Handle Viewed", "notif "+strconv.Itoa(notifID)+" doesn't belong to "+from)
				continue
			}

			if err := utils.SetNotificationInfo(config.DB, notifID, true, true); err != nil {
				utils.SimpleLog("Handle Viewed", err.Error())
				continue
			}
			utils.SimpleLog("Handle Viewed", "Set notif ID "+strconv.Itoa(notifID)+" as viewed")
		}
	default:
		return errors.New("Invalid type passed in content")
	}
	return nil
}
