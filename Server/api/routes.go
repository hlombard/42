package main

import (
	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/api/handlers"
	"github.com/hlombard/matcha/utils"
)

type Routes struct {
	Router *gin.Engine
}

func newRoutes() *Routes {
	return &Routes{
		Router: gin.Default(),
	}
}

func createRoutes() *Routes {
	routes := newRoutes()
	routes.Router.Use(handlers.CORSMiddleware())
	api := routes.Router.Group("/api")
	routes.createLogin(api)
	routes.createLogout(api)
	routes.createRefresh(api)
	routes.createImages(api)
	routes.createPing(api)
	routes.createAccount(api)
	routes.createUsers(api)
	return routes
}

func (r *Routes) createImages(rg *gin.RouterGroup) {
	upload := rg.Group("/images")
	upload.POST("/", utils.IsAuthorized(), handlers.ImageUpload())
}

// createRefresh creates a simple /refresh route
// to regenerate Access token from the Refresh token
func (r *Routes) createRefresh(rg *gin.RouterGroup) {
	refresh := rg.Group("/refresh")
	refresh.GET("/", handlers.Refresh())
}

// createPing creates a simple /ping route
func (r *Routes) createPing(rg *gin.RouterGroup) {
	ping := rg.Group("/ping")
	ping.GET("/", func(c *gin.Context) {
		c.JSON(200, gin.H{
			"message": "pong",
		})
	})
}

// createAccount creates all the routes to /account/
func (r *Routes) createAccount(rg *gin.RouterGroup) {
	create := rg.Group("/account/create")
	create.POST("/", handlers.AccountCreate())

	verify := rg.Group("/account/verify")
	verify.POST("/", handlers.AccountVerify())

	forgotPassword := rg.Group("/account/forgot_password")
	forgotPassword.POST("/", handlers.AccountForgotPassword())

	resetPassword := rg.Group("/account/reset_password")
	resetPassword.POST("/", handlers.AccountResetPassword())

}

// createLogin creates route to login a user
func (r *Routes) createLogin(rg *gin.RouterGroup) {
	login := rg.Group("/login")
	login.POST("/", handlers.Login())
}

// createLogout creates route to logout a user
func (r *Routes) createLogout(rg *gin.RouterGroup) {
	logout := rg.Group("/logout")
	logout.POST("/", utils.IsAuthorized(), handlers.Logout())
}

// createUsers creates all the routes to /user/
func (r *Routes) createUsers(rg *gin.RouterGroup) {
	username := rg.Group("/user/:username")
	username.GET("/", utils.IsAuthorized(), handlers.UserGet())
	username.PATCH("/", utils.IsAuthorized(), handlers.UserUpdate())

	visit := rg.Group("/user/:username/visit")
	visit.POST("/", utils.IsAuthorized(), handlers.UserVisitAdd())

	like := rg.Group("/user/:username/like")
	like.POST("/", utils.IsAuthorized(), handlers.UserLikeAdd())
	like.DELETE("/", utils.IsAuthorized(), handlers.UserLikeDelete())

	rating := rg.Group("/user/:username/rating")
	rating.POST("/", utils.IsAuthorized(), handlers.UserRatingAdd())

	report := rg.Group("/user/:username/report")
	report.POST("/", utils.IsAuthorized(), handlers.UserReportAdd())

	block := rg.Group("/user/:username/block")
	block.POST("/", utils.IsAuthorized(), handlers.UserBlockAdd())
	block.DELETE("/", utils.IsAuthorized(), handlers.UserBlockDelete())

	tag := rg.Group("/user/:username/tag")
	tag.POST("/", utils.IsAuthorized(), handlers.UserTagAdd())
	tag.DELETE("/", utils.IsAuthorized(), handlers.UserTagDelete())

	find := rg.Group("/user/:username/find")
	find.POST("/", utils.IsAuthorized(), handlers.UserFind())

}
