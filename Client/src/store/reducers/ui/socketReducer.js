import * as actionTypes from "../../actions/actionTypes";
import { updateObject } from "../../utility";

const initialState = {
  notifyData: [],
  matchData: [],
  socket: null,
  chatData: [],
};

const startChat = (state, action) => {
  let newChat = [];
  if (state.chatData.some((item) => item.username === action.username)) {
    newChat = [...state.chatData];
    newChat.forEach((item) => {
      item.show = false;
      if (item.username === action.username) {
        item.show = true;
      }
    });

    return updateObject(state, { chatData: newChat });
  } else {
    newChat = [
      ...state.chatData,
      {
        username: action.username,
        picture: action.picture,
        show: true,
        messageList: "messageList" in action ? action.messageList : [],
        isTyping: false,
      },
    ];
    state.chatData.forEach((item) => {
      item.show = false;
    });
    return updateObject(state, { chatData: newChat });
  }
};

const addMessage = (state, action) => {
  let newChat = [...state.chatData];

  if (newChat.some((item) => item.username === action.message.roomId)) {
    newChat.forEach((item) => {
      if (item.username === action.message.roomId) {
        item.messageList.push(action.message);
        item.show = true;
      }
    });
  } else {
    let messageList = [];
    messageList.push(action.message);
    return startChat(state, {
      username: action.message.roomId,
      picture:
        "http://localhost:8080/api/images/" + action.message.roomId + "/1.png",
      show: true,
      messageList: messageList,
    });
  }
  return updateObject(state, { chatData: newChat });
};

const showChat = (state, action) => {
  let newChat = [...state.chatData];

  newChat.forEach((item) => {
    item.show = false;
    if (item.username === action.roomId) {
      item.show = action.show;
    }
  });

  return updateObject(state, { chatData: newChat });
};

const isTyping = (state, action) => {
  let newChat = [...state.chatData];

  newChat.forEach((item) => {
    if (item.username === action.roomId) {
      item.isTyping = action.typingValue;
    }
  });

  return updateObject(state, { chatData: newChat });
};

const reducer = (state = initialState, action) => {
  switch (action.type) {
    case actionTypes.STOCK_NOTIFY:
      return updateObject(state, {
        notifyData: action.notifyData !== null ? action.notifyData : [],
      });
    case actionTypes.START_CHAT:
      return startChat(state, action);
    case actionTypes.ADD_MESSAGE:
      return addMessage(state, action);
    case actionTypes.IS_TYPING:
      return isTyping(state, action);
    case actionTypes.STOCK_CHAT:
      return updateObject(state, {
        chatData: action.chatData !== null ? action.chatData : [],
      });
    case actionTypes.SET_SHOW_CHAT:
      return showChat(state, action);
    case actionTypes.ADD_NOTIFY:
      let newArray = [...state.notifyData, action.newNotify];
      return updateObject(state, { notifyData: newArray });
    case actionTypes.STOCK_MATCH:
      return updateObject(state, {
        matchData: action.matchData,
      });
    default:
      return state;
  }
};

export default reducer;
