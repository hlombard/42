package utils

import (
	"database/sql"
	"errors"
	"fmt"
	"net/http"
	"strconv"
	"time"

	jwt "github.com/dgrijalva/jwt-go"
	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	uuid "github.com/satori/go.uuid"
)

type JWTData struct {
	AccessUuid string
	UserId     uint64
	Username   string
}

type TokenDetails struct {
	AccessToken  string
	RefreshToken string
	AccessUuid   string
	RefreshUuid  string
	AtExpires    int64
	RtExpires    int64
}

// CreateTokens creates 1 Access and 1 Refresh JWT
func CreateTokens(userid int, username string) (*TokenDetails, error) {
	var err error

	td := &TokenDetails{}
	td.AtExpires = time.Now().Add(time.Minute * 15).Unix()
	td.AccessUuid = uuid.NewV4().String()
	td.RtExpires = time.Now().Add(time.Hour * 24 * 7).Unix()
	td.RefreshUuid = uuid.NewV4().String()

	//Creating Access Token
	atClaims := jwt.MapClaims{}
	atClaims["authorized"] = true
	atClaims["access_uuid"] = td.AccessUuid
	atClaims["user_id"] = userid
	atClaims["username"] = username
	atClaims["exp"] = td.AtExpires
	at := jwt.NewWithClaims(jwt.SigningMethodHS256, atClaims)
	td.AccessToken, err = at.SignedString(config.JWTAccessKey)
	if err != nil {
		return nil, err
	}

	//Creating Refresh Token
	rtClaims := jwt.MapClaims{}
	rtClaims["refresh_uuid"] = td.RefreshUuid
	rtClaims["user_id"] = userid
	rtClaims["username"] = username
	rtClaims["exp"] = td.RtExpires
	rt := jwt.NewWithClaims(jwt.SigningMethodHS256, rtClaims)
	td.RefreshToken, err = rt.SignedString(config.JWTRefreshKey)
	if err != nil {
		return nil, err
	}
	return td, nil
}

// SaveTokens saves tokens data into db
func SaveTokens(db *sql.DB, userid int, td *TokenDetails) error {

	convertAtdate := time.Unix(td.AtExpires, 0)
	convertRtdate := time.Unix(td.RtExpires, 0)

	dateAccessToken := convertAtdate.Format("2006-01-02 15:04:05")
	dateRefreshToken := convertRtdate.Format("2006-01-02 15:04:05")

	// Remove previous tokens if user already had some
	remove := "DELETE FROM user_sessions WHERE user_id = ?"
	_, err := db.Exec(remove, userid)
	if err != nil {
		return errors.New("Couldn't remove previous tokens from DB")
	}

	insert := `INSERT INTO user_sessions
	(user_id, access_uuid, refresh_uuid, access_exp, refresh_exp, is_online)
	VALUES (?, ?, ?, ?, ?, ?)`
	_, err = db.Exec(insert, userid, td.AccessUuid, td.RefreshUuid, dateAccessToken, dateRefreshToken, true)
	if err != nil {
		return errors.New("Couldn't insert tokens metadata into DB")
	}
	return nil
}

// VeryfyToken, extract the token and checks that it is valid
// it then returns the token
func VerifyToken(r *http.Request) (*jwt.Token, error) {

	// Extract the token from authorization
	tokenString := r.Header.Get("Authorization")

	// Check the alg
	token, err := jwt.Parse(tokenString, func(token *jwt.Token) (interface{}, error) {
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("Unexpected signing method: %v", token.Header["alg"])
		}
		return config.JWTAccessKey, nil
	})
	if err != nil {
		return nil, err
	}

	// Check the validity
	if _, ok := token.Claims.(jwt.Claims); !ok && !token.Valid {
		return nil, fmt.Errorf("Token is not valid anymore")
	}
	return token, nil
}

// ExtractJWTData is used to get meta data of token (UserId, username and access token uuid)
func ExtractJWTData(r *http.Request) (*JWTData, error) {
	token, err := VerifyToken(r)

	if err != nil {
		return &JWTData{}, err
	}
	claims, ok := token.Claims.(jwt.MapClaims)
	if ok && token.Valid {
		accessUuid, ok := claims["access_uuid"].(string)
		if !ok {
			return nil, err
		}
		userId, err := strconv.ParseUint(fmt.Sprintf("%.f", claims["user_id"]), 10, 64)
		if err != nil {
			return nil, err
		}
		username, ok := claims["username"].(string)
		if !ok {
			return nil, err
		}
		return &JWTData{
			AccessUuid: accessUuid,
			UserId:     userId,
			Username:   username,
		}, nil
	}
	return nil, err
}

// Midleware checks that users is authorized to access route (valid Access token)
// It also sets a variable tokenOwner with username value
// Abort in case of unauthorized user else go continue to the next handler
func IsAuthorized() gin.HandlerFunc {
	return func(c *gin.Context) {
		var tokenDetails *JWTData
		var err error

		if tokenDetails, err = ExtractJWTData(c.Request); err != nil {
			SetContextAndLog(c, "API Auth", http.StatusUnauthorized, err.Error())
			c.Abort()
			return
		}

		c.Set("tokenOwnerID", strconv.Itoa(int(tokenDetails.UserId)))
		c.Set("tokenOwnerUsername", tokenDetails.Username)

		c.Next()
	}
}

// Delete Tokens
func DeleteTokens(db *sql.DB, data *JWTData) error {
	userid := data.UserId

	update := `UPDATE user_sessions SET access_uuid = '',
	refresh_uuid = '', access_exp = null, refresh_exp = null, is_online = false, last_activity = CURRENT_TIMESTAMP
	WHERE user_id = ?`
	_, err := db.Exec(update, userid)
	if err != nil {
		return errors.New("Couldn't remove JWT tokens from DB")
	}
	return nil
}

func IsAuthorizedWS() gin.HandlerFunc {
	return func(c *gin.Context) {
		var err error
		var td *JWTData

		// Check JWT access token
		token := c.Param("token")
		if td, err = CheckJWT(token); err != nil {
			SetContextAndLog(c, "WS Auth", http.StatusUnauthorized, err.Error())
			c.Abort()
			return
		}
		c.Set("tokenOwnerID", strconv.Itoa(int(td.UserId)))
		c.Set("tokenOwnerUsername", td.Username)

		c.Next()
	}

}

func CheckJWT(input string) (*JWTData, error) {
	// Check the alg
	token, err := jwt.Parse(input, func(token *jwt.Token) (interface{}, error) {
		if _, ok := token.Method.(*jwt.SigningMethodHMAC); !ok {
			return nil, fmt.Errorf("Unexpected signing method: %v", token.Header["alg"])
		}
		return config.JWTAccessKey, nil
	})
	if err != nil {
		return nil, err
	}

	// Check the validity
	if _, ok := token.Claims.(jwt.Claims); !ok && !token.Valid {
		return nil, fmt.Errorf("Token is not valid anymore")
	}

	claims, ok := token.Claims.(jwt.MapClaims)
	if ok && token.Valid {
		accessUuid, ok := claims["access_uuid"].(string)
		if !ok {
			return nil, err
		}
		userId, err := strconv.ParseUint(fmt.Sprintf("%.f", claims["user_id"]), 10, 64)
		if err != nil {
			return nil, err
		}
		username, ok := claims["username"].(string)
		if !ok {
			return nil, err
		}
		return &JWTData{
			AccessUuid: accessUuid,
			UserId:     userId,
			Username:   username,
		}, nil
	}
	return nil, err
}
