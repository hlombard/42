import * as actionTypes from "../actionTypes";
import * as actionCreators from "../actionCreators";
import axios from "axios";

export const stockNotify = (data) => {
  return {
    type: actionTypes.STOCK_NOTIFY,
    notifyData: data,
  };
};

export const addNotify = (data) => {
  return {
    type: actionTypes.ADD_NOTIFY,
    newNotify: data,
  };
};

export const deleteNotify = (data) => {
  return {
    type: actionTypes.DELETE_NOTIFY,
    notifyToDelete: data,
  };
};

export const stockMatch = (data) => {
  return {
    type: actionTypes.STOCK_MATCH,
    matchData: data,
  };
};

export const startChat = (userData) => {
  return {
    type: actionTypes.START_CHAT,
    username: userData.username,
    picture: userData.picture_1,
  };
};

export const stockChat = (data) => {
  return {
    type: actionTypes.STOCK_CHAT,
    chatData: data,
  };
};

export const addMessage = (message) => {
  return {
    type: actionTypes.ADD_MESSAGE,
    message: message,
  };
};

export const setShowChat = (show, roomId) => {
  return {
    type: actionTypes.SET_SHOW_CHAT,
    show: show,
    roomId: roomId,
  };
};

export const setIsTyping = (typingValue, roomId) => {
  return {
    type: actionTypes.IS_TYPING,
    typingValue: typingValue,
    roomId: roomId,
  };
};

export const like = (userName) => {
  return (dispatch) => {
    axios({
      method: "post",
      url: "/api/user/" + userName + "/like/",
    })
      .then((response) => {
        if (response.data && response.data.message) {
          if (response.data.message.includes("like")) {
            dispatch(
              wsMessage({
                type: "like",
                user_target: userName,
                time: Date.now,
                content: null,
              })
            );
          } else if (response.data.message.includes("match")) {
            dispatch(
              wsMessage({
                type: "match",
                user_target: userName,
                time: Date.now,
                content: null,
              })
            );
          }
        }
      })
      .catch((error) => {
        console.log("like error", error.response);
      });
  };
};

export const unlike = (userName) => {
  return (dispatch) => {
    axios({
      method: "DELETE",
      url: "/api/user/" + userName + "/like/",
    })
      .then((response) => {
        dispatch(
          wsMessage({
            type: "unlike",
            user_target: userName,
            time: Date.now,
            content: null,
          })
        );
      })
      .catch((error) => {
        console.log("unlike error", error.response);
      });
  };
};

export const block = (userName) => {
  return (dispatch) => {
    axios({
      method: "post",
      url: "/api/user/" + userName + "/block/",
    })
      .then((response) => {})
      .catch((error) => {
        console.log("block error", error.response);
      });
  };
};

export const unblock = (userName) => {
  return (dispatch) => {
    axios({
      method: "DELETE",
      url: "/api/user/" + userName + "/block/",
    })
      .then((response) => {})
      .catch((error) => {
        console.log("unblock error", error.response);
      });
  };
};

export const report = (userName) => {
  return (dispatch) => {
    axios({
      method: "POST",
      url: "/api/user/" + userName + "/report/",
    })
      .then((response) => {
        dispatch(actionCreators.sendToast(response.data.message, "Profile"));
      })
      .catch((error) => {
        console.log("report error", error.response);
        dispatch(actionCreators.sendToast(error.response.data.error, "Error"));
      });
  };
};

export const sendVisit = (userName) => {
  return (dispatch) => {
    axios({
      method: "post",
      url: "/api/user/" + userName + "/visit/",
    })
      .then((response) => {
        dispatch(
          wsMessage({
            type: "visit",
            user_target: userName,
            time: Date.now,
            content: null,
          })
        );
      })
      .catch((error) => {
        console.log("visit error", error);
      });
  };
};

export const wsConnect = () => ({ type: "WS_CONNECT" });
export const wsMessage = (msg) => ({ type: "WS_MSG", msg: msg });
// export const wsDisconnect = (token) => ({ type: "WS_DISCONNECT", token });
