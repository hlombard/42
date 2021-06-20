import { useEffect, useState, useRef } from "react";
import { useDispatch } from "react-redux";

import Form from "react-bootstrap/Form";
import Button from "react-bootstrap/Button";

import * as actionCreators from "../../../store/actions/actionCreators";
import "../css/ChatEngine.scss";

function ChatEngine(props) {
  const [message, setMessage] = useState("");
  let dispatch = useDispatch();
  const messagesEndRef = useRef(null);

  const scrollToBottom = () => {
    messagesEndRef.current.scrollIntoView({
      behavior: "smooth",
      block: "nearest",
      inline: "start",
    });
  };

  useEffect(() => {
    scrollToBottom();
  }, [props.chatData.messageList.length]);

  const sendMessage = (event) => {
    event.preventDefault();
    if (message) {
      dispatch(
        actionCreators.addMessage({
          roomId: props.chatData.username,
          from: localStorage.getItem("user_name"),
          date: Date.now(),
          message: message,
        })
      );
      dispatch(
        actionCreators.wsMessage({
          type: "is_typing",
          user_target: props.chatData.username,
          time: Date.now,
          content: false,
        })
      );
      dispatch(
        actionCreators.wsMessage({
          type: "message",
          user_target: props.chatData.username,
          time: Date.now,
          content: message,
        })
      );
    }
    setMessage("");
  };

  const handleChatInput = (message) => {
    if (message) {
      dispatch(
        actionCreators.wsMessage({
          type: "is_typing",
          user_target: props.chatData.username,
          time: Date.now,
          content: true,
        })
      );
    } else if (message === "") {
      dispatch(
        actionCreators.wsMessage({
          type: "is_typing",
          user_target: props.chatData.username,
          time: Date.now,
          content: false,
        })
      );
    }
    setMessage(message);
  };

  let chatRender = <div>Loading...</div>;
  let messageHistory = <p>Start the conversation with props.chatData.from</p>;

  if (props.chatData) {
    messageHistory = (
      <div className="start-conv">
        Start a conversation with{" "}
        <span className="match-name">{props.chatData.username}</span>
        <div ref={messagesEndRef}></div>
      </div>
    );
    if (props.chatData.messageList.length > 0) {
      messageHistory = (
        <>
          {props.chatData.messageList.map((item) => {
            return (
              <div
                key={item.date}
                className={`message-item ${
                  item.from === item.roomId ? "message-target" : "message-me"
                }`}
              >
                <span className="sender">{item.from}</span>
                <div className="message-text">{item.message}</div>
              </div>
            );
          })}
          <div id="scroller" ref={messagesEndRef}></div>
        </>
      );
    }
    chatRender = (
      <div className="chat-render">
        <div className="message-history">{messageHistory}</div>
        {props.chatData.isTyping ? (
          <div className="is-typing">
            {props.chatData.username + " is typing..."}
          </div>
        ) : (
          <div className="is-typing">&zwnj;</div>
        )}
        <Form className="chat-input">
          <Form.Group className="message-box" controlId="formBasicEmail">
            <Form.Control
              value={message}
              onChange={(e) => handleChatInput(e.target.value)}
              type="text"
              autoComplete="off"
              placeholder={"Send a message"}
            />
          </Form.Group>
          <Button
            className="send-button"
            onClick={sendMessage}
            type="submit"
            variant="sub"
          >
            send
          </Button>
        </Form>
      </div>
    );
  }
  return <>{chatRender}</>;
}

export default ChatEngine;
