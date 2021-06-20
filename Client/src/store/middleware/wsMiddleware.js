import * as actionCreators from "../actions/actionCreators";
import { getNewToken } from "../../containers/getNewToken";

const URL = "ws://localhost:8081/ws/";
const initSocket = () => {
  const token = localStorage.getItem("token");
  if (token) {
    const socket = new WebSocket(URL + token);
    return socket;
  }
  return null;
};

const wsMiddleware = () => {
  let socket = null;

  const onOpen = (store) => (event) => {};

  const onClose = (store) => (event) => {
    store.dispatch(actionCreators.wsConnect());
  };

  const onMessage = (store) => (event) => {
    let msg = JSON.parse(event.data);
    if ("logout" in msg || "login" in msg) {
      store.dispatch(actionCreators.newConnectionStatus());
    }
    if ("notif_list" in msg) {
      store.dispatch(actionCreators.stockNotify(msg.notif_list));
    }
    if ("match_list" in msg) {
      store.dispatch(actionCreators.stockMatch(msg.match_list));
    }
    if ("message" in msg) {
      msg.message.roomId = msg.message.from;
      store.dispatch(actionCreators.addMessage(msg.message));
    }
    if ("is_typing" in msg) {
      store.dispatch(
        actionCreators.setIsTyping(msg.is_typing.value, msg.is_typing.from)
      );
    }
    switch (msg.type) {
      case "message":
        store.dispatch(actionCreators.addNotify(msg));
        store.dispatch(
          actionCreators.sendToast(
            "You get a new message from " + msg.from,
            "Message"
          )
        );
        break;
      case "like":
        store.dispatch(actionCreators.addNotify(msg));
        store.dispatch(
          actionCreators.sendToast(
            "User " + msg.from + " liked your profile",
            "Like"
          )
        );
        break;
      case "unlike":
        store.dispatch(actionCreators.addNotify(msg));
        store.dispatch(
          actionCreators.sendToast(
            "User " + msg.from + " unliked your profile",
            "Unlike"
          )
        );
        break;
      case "match":
        store.dispatch(actionCreators.addNotify(msg));
        store.dispatch(
          actionCreators.sendToast(
            "You have a new match with " + msg.from + " !!!",
            "It's a match !!!"
          )
        );
        break;
      case "visit":
        store.dispatch(actionCreators.addNotify(msg));
        store.dispatch(
          actionCreators.sendToast(
            "User " + msg.from + " just visited your profile !",
            "Profile"
          )
        );
        break;
      default:
        break;
    }
  };

  const send = function (ws, message, callback) {
    waitForConnection(
      ws,
      function () {
        ws.send(message);
        if (typeof callback !== "undefined") {
          callback();
        }
      },
      1000
    );
  };

  const waitForConnection = function (ws, callback, interval) {
    if (ws && ws.readyState === 1) {
      callback();
    } else {
      // optional: implement backoff for interval here
      setTimeout(function () {
        waitForConnection(callback, interval);
      }, interval);
    }
  };

  // the middleware part of this function
  return (store) => (next) => (action) => {
    switch (action.type) {
      case "WS_CONNECT":
        if (socket !== null) {
          console.log("[WEBSOCKER] Trying to close the websocket");
          socket.close();
        }

        // connect to the remote host
        socket = initSocket();

        // websocket handlers
        if (socket) {
          socket.onmessage = onMessage(store);
          socket.onclose = onClose(store);
          socket.onopen = onOpen(store);
          socket.onerror = function (event) {
            getNewToken()
              .then((res) => {
                store.dispatch(actionCreators.checkAuthStatus());
              })
              .catch(function (error) {
                console.log(
                  "Il y a eu un problème avec l'opération fetch: " +
                    error.message
                );
              });
          };
        } else {
          socket = initSocket();
        }

        break;
      case "WS_MSG":
        if (socket) {
          send(socket, JSON.stringify(action.msg));
        }
        //socket.send(JSON.stringify(action.msg));
        break;
      default:
        return next(action);
    }
  };
};

export default wsMiddleware();
