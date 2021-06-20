package utils

import (
	"database/sql"
	"log"

	"github.com/hlombard/matcha/config"
)

// Init config.DB pointer
func InitDB(service string) *sql.DB {
	databasePath := config.DBUser + ":" + config.DBPassword + "@tcp(" + config.DBHost + ")/" + config.DBName

	db, err := sql.Open("mysql", databasePath)
	if err != nil {
		log.Fatal(service, err)
	}
	err = db.Ping()
	if err != nil {
		log.Fatal(service, err)
	} else {
		SimpleLog("Database", "Successfully connected to Database !")
	}
	return db
}
