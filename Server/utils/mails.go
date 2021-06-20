package utils

import (
	"database/sql"
	"net/smtp"

	"github.com/hlombard/matcha/config"
)

type MailData struct {
	Mime    string
	Subject string
	Body    string
}

func SendEmail(receiverEmail []string, message []byte) error {

	auth := smtp.PlainAuth("", config.EmailSender, config.EmailPassword, config.EmailHost)
	err := smtp.SendMail(config.EmailHost+":"+config.EmailPort, auth, config.EmailSender, receiverEmail, message)
	if err != nil {
		return err
	}
	return nil
}

func GetVerifyMailData(username, personalLink string) *MailData {
	data := &MailData{}

	data.Mime = "MIME-version: 1.0;\nContent-Type: text/html; charset=\"UTF-8\";\n\n"
	data.Subject = "Subject: Matcha: verify your account\n"

	data.Body = "<html><body><h1>" +
		"Welcome to Matcha " + username + " !</br></br></h1><h2>" +
		"Please verify your email by clicking on this " + personalLink +
		"</br></br>Best regards,</h2></br><h4>Matcha Team</h4>" +
		"</body></html>"

	return data
}

func GetForgotPasswordMailData(personalLink string) *MailData {
	data := &MailData{}

	data.Mime = "MIME-version: 1.0;\nContent-Type: text/html; charset=\"UTF-8\";\n\n"
	data.Subject = "Subject: Matcha: Reset your password\n"

	data.Body = "<html><body>" +
		"<h1>Hello !</br></br></h1>" +
		"<h3> Did you forget your password ?</br></h3>" +
		"<h3>Click on this " + personalLink + " to reset your password.</br></br></h3>" +
		"<h3>Best regards,</br></h3>" +
		"<h4>Matcha Team</h4>" +
		"</body></html>"

	return data
}

// EmailExists checks in users DB if the email is present
func EmailExists(db *sql.DB, email string) bool {
	var found string

	row := db.QueryRow("SELECT email FROM users WHERE email = ?", email)
	switch err := row.Scan(&found); err {
	case sql.ErrNoRows:
		return false
	default:
		return true
	}
}

// GenerateEmailVerifyLink will generate a link by encrypting user email using AES.
// This allow to easily identify the owner of the token without having to store the token
// we simply need to decrypt it. Right now the link is permanent.
// Returns the link formated in html
func GenerateEmailVerifyLink(email string) (string, error) {
	token, err := Encrypt(email, config.EncKey)
	if err != nil {
		return "", err
	}
	personalLink := "<a href=\"http://localhost:3000/account/verify?token=" + token + "\">LINK</a>"
	return personalLink, nil
}
