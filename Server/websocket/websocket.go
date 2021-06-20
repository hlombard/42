package main

import (
	"github.com/gin-gonic/gin"
	"github.com/hlombard/matcha/config"
	"github.com/hlombard/matcha/utils"
)

type WebSocket struct {
	Router *gin.Engine
}

func newWebSocket() *WebSocket {
	return &WebSocket{
		Router: gin.Default(),
	}
}

func (ws *WebSocket) Setup() {
	config.Service = "[WS] "
	config.DB = utils.InitDB(config.Service)
	gin.ForceConsoleColor()
	ws.Router.Use(gin.Recovery())
	ws.Router.GET("/ws/:token", utils.IsAuthorizedWS(), serveWs())
	go h.run()
}

func (ws *WebSocket) Start() {
	defer config.DB.Close()
	ws.Router.Run("0.0.0.0:8081")
}
