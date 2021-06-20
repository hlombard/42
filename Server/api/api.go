package main

import (
	"database/sql"
	"encoding/json"
	"errors"
	"fmt"
	"io/ioutil"
	"math/rand"
	"net/http"
	"os"
	"strconv"
	"time"

	"github.com/gin-gonic/contrib/static"
	"github.com/gin-gonic/gin"
	_ "github.com/go-sql-driver/mysql"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

var Matcha *Api

type Api struct {
	Routes *Routes
}

func New() *Api {
	return &Api{
		Routes: &Routes{
			Router: nil,
		},
	}
}

func (api *Api) Setup() {
	config.Service = "[API]"
	config.DB = utils.InitDB(config.Service)
	gin.ForceConsoleColor()
	api.initAPI()
	if err := setBotPictures(config.DB); err != nil {
		utils.SimpleLog("Setup", err.Error())
	}
}

// initAPI creates routes and set default middlewares
func (api *Api) initAPI() {
	api.Routes = createRoutes()
	api.Routes.Router.Use(static.Serve("/api/images", static.LocalFile("./images", true))) // Used to serv users pictures
	api.Routes.Router.Use(gin.Recovery())
}

func (api *Api) Start() {
	defer config.DB.Close()
	api.Routes.Router.Run()
}

func setBotPictures(db *sql.DB) error {

	// Check if bots_ok file is present
	// if it does it means we dont have to re generate pictures
	if _, err := os.Stat("bots_ok"); !os.IsNotExist(err) {
		return nil
	}

	utils.SimpleLog("Setup", "Generating fake face for bots...")

	query := "SELECT username, gender, TIMESTAMPDIFF(YEAR,dob,CURDATE()) as age, picture_1 FROM users WHERE is_bot = true"
	rows, err := db.Query(query)
	if err != nil {
		return errors.New("Couldn't get bot profiles")
	}
	defer rows.Close()

	// For each bots
	var count, total int
	for rows.Next() {
		var username, gender, age, picture, url string
		var err error

		total++
		if err := rows.Scan(&username, &gender, &age, &picture); err != nil {
			return errors.New("Couldn't Setup bot profile pictures")
		}

		// Get image link
		if url, err = getFakeFaceURL(gender, age); err != nil {
			utils.SimpleLog("Setup", "Couldn't generate fakeface for "+username)
			continue
		}

		// Update user picture
		if err = utils.SetImageURL(config.DB, url, username, "1"); err != nil {
			utils.SimpleLog("Setup", "Couldn't save fakeface url for "+username)
		}
		count++
	}

	// Create file bots_ok to avoid re generating
	// fakeface data
	set, err := os.Create("bots_ok")
	if err != nil {
		return err
	}
	set.Close()

	utils.SimpleLog("Setup", "Successfully generated fakeface for bots "+strconv.Itoa(count)+"/"+strconv.Itoa(total))
	return nil
}

func getFakeFaceURL(gender, age string) (string, error) {

	if gender == "non-binary" {
		randGender := [2]string{"male", "female"}
		rand.Seed(time.Now().UnixNano())
		gender = randGender[rand.Intn(2)]
	}

	param := "?gender=" + gender + "&minimum_age=" + age + "&maximum_age=" + age
	resp, err := http.Get("https://fakeface.rest/face/json" + param)
	if err != nil {
		return "", err
	}
	defer resp.Body.Close()

	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return "", err
	}

	fakeface := make(map[string]interface{})
	if err := json.Unmarshal(body, &fakeface); err != nil {
		return "", err
	}
	return fmt.Sprintf("%s", fakeface["image_url"]), nil
}
