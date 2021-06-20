package handlers

import (
	"net/http"

	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

// Logout deletes JWT tokens in DB and updates
// last activity, and is_online status
//		ROUTE: /api/account/logout
//		METHOD: POST
//		PARAM: none
//		RETURN: none
func Logout() gin.HandlerFunc {
	return func(c *gin.Context) {

		data, err := utils.ExtractJWTData(c.Request)
		if err != nil {
			utils.SetContextAndLog(c, "Logout", http.StatusUnauthorized, err.Error())
			return
		}

		if err := utils.DeleteTokens(config.DB, data); err != nil {
			utils.SetContextAndLog(c, "Logout", http.StatusInternalServerError, err.Error())
			return
		}

		if err := utils.UpdateUserActivity(config.DB, int(data.UserId), false); err != nil {
			utils.SetContextAndLog(c, "Logout", http.StatusInternalServerError, err.Error())
			return
		}

		utils.SetContextAndLog(c, "Logout", http.StatusOK, data.Username+" successfully logged out !")
	}
}
