package handlers

import (
	"bytes"
	"database/sql"
	"errors"
	"image/jpeg"
	"image/png"
	"io"
	"mime/multipart"
	"net/http"
	"os"
	"strconv"

	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

// ImageUpload converts image to .png if needed.
// Saves it to locally ./images/:username/{1..5}.png
// And updates the user picture_number field in DB
//		ROUTE: /api/images
//		METHOD: POST
//		PARAM: image, ?number={1..5} => the user picture number (1 is profile picture)
//		RETURN: none
func ImageUpload() gin.HandlerFunc {
	return func(c *gin.Context) {
		var filetype, username string
		var err error

		// Get token owner username (set in isAuthorized middleware)
		username = c.MustGet("tokenOwnerUsername").(string)
		if username == "" {
			utils.SetContextAndLog(c, "Image Upload", http.StatusInternalServerError, "Couldn't get username")
			return
		}

		// Check the number param
		number := c.Query("number")
		if err := checkImageNumber(number); err != nil {
			utils.SetContextAndLog(c, "Image Upload", http.StatusUnprocessableEntity, err.Error())
			return
		}

		image, _, err := c.Request.FormFile("image")
		if err != nil {
			utils.SetContextAndLog(c, "Image Upload", http.StatusUnprocessableEntity, err.Error())
			return
		}
		defer image.Close()

		if filetype, err = parseImage(image); err != nil {
			utils.SetContextAndLog(c, "Image Upload", http.StatusNotAcceptable, err.Error())
			return
		}

		if err := saveImage(image, filetype, username, number); err != nil {
			utils.SetContextAndLog(c, "Image Upload", http.StatusInternalServerError, err.Error())
			return
		}
		utils.SetContextAndLog(c, "Image Upload", http.StatusOK, "Image Successfully saved !")
	}
}

func saveImage(image multipart.File, filetype, username, nb string) error {

	// Create ./image/:username if it doesnt exist
	if _, err := os.Stat(config.ImagePath + username); os.IsNotExist(err) {
		os.MkdirAll(config.ImagePath+username, 0755)
	}

	// Create a new file in the uploads directory: ./images/:username/{1..5}.png
	dst, err := os.Create(config.ImagePath + username + "/" + nb + ".png")
	if err != nil {
		return errors.New("Couldn't create image file")
	}
	defer dst.Close()

	// If user is not completed and he is uploading a profile picture
	// set is_completed = true
	if IsUserCompleted(config.DB, username) == false && nb == "1" {
		if err := setIsCompleted(config.DB, username); err != nil {
			return err
		}
	}

	// Convert to png and save
	if filetype == "jpeg" {
		if err := convertAndSave(image, dst); err != nil {
			return err
		}
		if err := utils.SetImageURL(config.DB, "http://localhost:8080/api"+config.ImagePath[1:]+username+"/"+nb+".png", username, nb); err != nil {
			return errors.New("Couldn't save image path in DB")
		}
		return nil
	}

	// Save the file
	_, err = io.Copy(dst, image)
	if err != nil {
		return errors.New("Couldn't save the image on local server")
	}

	if err := utils.SetImageURL(config.DB, "http://localhost:8080/api"+config.ImagePath[1:]+username+"/"+nb+".png", username, nb); err != nil {
		return errors.New("Couldn't save image path in DB")
	}
	return nil
}

func setIsCompleted(db *sql.DB, username string) error {
	update := "UPDATE users SET is_completed = true WHERE username = ?"
	_, err := db.Exec(update, username)
	if err != nil {
		return errors.New("Couldn't set is_completed status in DB")
	}
	return nil
}

// IsUserCompleted checks that user is_completed = true
func IsUserCompleted(db *sql.DB, username string) bool {
	var isCompleted bool

	rows := db.QueryRow("SELECT is_completed FROM users WHERE username = ?", username)
	switch err := rows.Scan(&isCompleted); err {
	case sql.ErrNoRows:
		return false
	default:
		if isCompleted == true {
			return true
		}
		return false
	}
}

func checkImageSize(image multipart.File) error {
	var buff bytes.Buffer

	imageSize, err := buff.ReadFrom(image)
	if err != nil {
		return err
	}

	if imageSize > int64(config.ImageMaxSize) {
		return errors.New("The uploaded file is too big. Please choose a file that's less than 1MB in size")
	}

	_, err = image.Seek(0, io.SeekStart)
	if err != nil {
		return errors.New("Couldn't reset image ptr")
	}
	return nil
}

// Reads the first 512 bytes to check the MIME
func detectContentType(image multipart.File) (string, error) {
	buff := make([]byte, 512)

	_, err := image.Read(buff)
	if err != nil {
		return "", errors.New("Couldn't check image MIME")
	}

	filetype := http.DetectContentType(buff)
	if filetype != "image/jpeg" && filetype != "image/png" {
		return "", errors.New("The provided file format is not allowed. Needs to be JPEG or PNG image")
	}

	_, err = image.Seek(0, io.SeekStart)
	if err != nil {
		return "", errors.New("Couldn't reset image ptr")
	}
	return filetype[6:], nil
}

// Convert a .jpg to a .png and write it in dst file
func convertAndSave(image multipart.File, dst *os.File) error {
	img, err := jpeg.Decode(image)
	if err != nil {
		return err
	}

	if err := png.Encode(dst, img); err != nil {
		return err
	}
	return nil
}

// ParseImage checks image size, and content to avoid security issues
// and returns the filetype (png/jpg)
func parseImage(image multipart.File) (string, error) {
	var filetype string
	var err error

	if err := checkImageSize(image); err != nil {
		return "", err
	}
	if filetype, err = detectContentType(image); err != nil {
		return "", err
	}
	return filetype, nil
}

func checkImageNumber(number string) error {
	if number == "" {
		return errors.New("Need to specify image number in query string: ?number={1..5}")
	}

	nb, err := strconv.Atoi(number)
	if err != nil {
		return err
	}

	if nb < 1 || nb > 5 {
		return errors.New("Parameter number needs to be between 1 and 5")
	}
	return nil
}
