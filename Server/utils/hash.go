package utils

import (
	"errors"

	"golang.org/x/crypto/bcrypt"
)

func HashAndSalt(password string) (string, error) {
	hash, err := bcrypt.GenerateFromPassword([]byte(password), bcrypt.MinCost)
	if err != nil {
		return "", errors.New("Couldn't hash password")
	}
	return string(hash), nil
}
