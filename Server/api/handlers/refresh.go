package handlers

import (
	"fmt"
	"net/http"
	"strconv"

	"github.com/dgrijalva/jwt-go"
	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

// Refresh checks that refresh_token is valid, generates
// new one, and update last_activity
//		ROUTE: /api/account/refresh
//		METHOD: POST
//		PARAM: none
//		RETURN: New JWT access/refresh tokens
func Refresh() gin.HandlerFunc {
	return func(c *gin.Context) {

		// Extract refresh token
		refreshToken := c.Request.Header.Get("Authorization")

		// Check validity, if not valid, redirect user to login form
		token, err := jwt.Parse(refreshToken, func(token *jwt.Token) (interface{}, error) {
			if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
				return nil, fmt.Errorf("unexpected signing method: %v", token.Header["alg"])
			}
			return config.JWTRefreshKey, nil
		})

		if err != nil {
			c.JSON(http.StatusTemporaryRedirect, "Refresh token expired, please login again")
			return
		}

		// Check if token is valid
		if _, ok := token.Claims.(jwt.Claims); !ok && !token.Valid {
			utils.SetContextAndLog(c, "Refresh", http.StatusUnauthorized, "Invalid refresh token, please log in again")
			return
		}

		// Since token is valid, get the user_id and username
		claims, ok := token.Claims.(jwt.MapClaims)
		userID, err := strconv.Atoi(fmt.Sprintf("%.f", claims["user_id"]))
		if err != nil {
			c.JSON(http.StatusUnprocessableEntity, "Error extracting user_id")
			return
		}
		username, ok := claims["username"].(string)
		if !ok {
			utils.SetContextAndLog(c, "Refresh", http.StatusInternalServerError, "Error extracting username")
			return
		}

		// Generate New Access and Refresh JWT from user_id and username
		tokensDetails, err := utils.CreateTokens(userID, username)
		if err != nil {
			utils.SetContextAndLog(c, "Refresh", http.StatusInternalServerError, err.Error())
			return
		}

		// Delete the previous tokens and save the new ones in DB
		if err := utils.SaveTokens(config.DB, userID, tokensDetails); err != nil {
			utils.SetContextAndLog(c, "Refresh", http.StatusInternalServerError, err.Error())
			return
		}

		// Update last_activity
		if err := utils.UpdateUserActivity(config.DB, userID, true); err != nil {
			utils.SetContextAndLog(c, "Refresh", http.StatusInternalServerError, err.Error())
			return
		}

		// Log and return the tokens
		utils.SimpleLog("Refresh", username+" successfully refreshed tokens !")
		c.JSON(http.StatusOK, gin.H{
			"access_token":  tokensDetails.AccessToken,
			"refresh_token": tokensDetails.RefreshToken,
		})
	}
}
