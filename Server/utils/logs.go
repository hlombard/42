package utils

import (
	"fmt"
	"strings"
	"time"

	"github.com/gin-gonic/gin"
	"github.com/gookit/color"
	"github.com/hlombard/matcha/config"
)

func SetContextAndLog(c *gin.Context, handler string, code int, message string) {
	data := make(map[string]interface{})

	col := getLogColor(config.Service)
	now := time.Now()
	date := now.Format("2006-01-02")
	date = strings.ReplaceAll(date, "-", "/")
	date += " - " + now.Format("15:04:05")

	data["code"] = code
	if code == 200 {
		data["message"] = message
		col.Println(config.Service, date, handler+":", message)
	} else {
		data["error"] = message
		col.Println(config.Service, date, handler+":", "error:", message)
	}
	c.JSON(code, data)
}

func SimpleLog(handler, message string) {
	col := getLogColor(config.Service)
	now := time.Now()
	date := now.Format("2006-01-02")
	date = strings.ReplaceAll(date, "-", "/")
	date += " - " + now.Format("15:04:05")
	col.Println(config.Service, date, handler+":", message)
}

func LogForm(handler string, formErr map[string][]string) {
	col := getLogColor(config.Service)
	now := time.Now()
	date := now.Format("2006-01-02")
	date = strings.ReplaceAll(date, "-", "/")
	date += " - " + now.Format("15:04:05")

	col.Println(config.Service, date, handler+":", "Submitted Form is not valid")
	for field := range formErr {
		col.Println(field + ":")
		for _, err := range formErr[field] {
			col.Println("\t\t- " + err)
		}
	}
	fmt.Println("")
}

func getLogColor(service string) color.Color {
	var col color.Color

	if service == "[API]" {
		col = color.Yellow
	} else {
		col = color.LightBlue
	}
	return col
}
