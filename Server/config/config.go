package config

import (
	"database/sql"
	"os"
)

var (
	Service string

	DB         *sql.DB
	DBName     = os.Getenv("MYSQL_DATABASE")
	DBUser     = os.Getenv("MYSQL_USER")
	DBPassword = os.Getenv("MYSQL_PW")
	DBHost     = "db:3306"

	EncKey = os.Getenv("ENC_KEY")

	EmailHost     = "smtp.gmail.com"
	EmailPort     = "587"
	EmailSender   = os.Getenv("EMAIL_SENDER")
	EmailPassword = os.Getenv("EMAIL_PW")

	APILocation    = os.Getenv("LOCATION_API")
	APILocationKey = os.Getenv("LOCATION_API_KEY")

	JWTAccessKey  = []byte(os.Getenv("JWT_ACCESS"))
	JWTRefreshKey = []byte(os.Getenv("JWT_REFRESH"))

	ImagePath    = "./images/"
	ImageMaxSize = 1024 * 1024 // 1MB
	ImageDefault = "http://localhost:8080/api/images/default/default.png"
)
