import { useRef } from "react";
import { useDispatch } from "react-redux";

import Popover from "react-bootstrap/Popover";
import Overlay from "react-bootstrap/Overlay";

import ChatEngine from "./ChatEngine";

import "../css/ChatRoom.scss";
import * as actionCreators from "../../../store/actions/actionCreators";

function ChatRoom(props) {
  let render = "";
  const overlayRef = useRef(null);
  let dispatch = useDispatch();

  const openChat = (item) => {
    dispatch(actionCreators.setShowChat(!item.show, item.username));
  };

  if (props.chatData) {
    render = props.chatData.map((item) => {
      return (
        <div key={item.username} className="chat-room">
          <img
            ref={overlayRef}
            onClick={() => openChat(item)}
            className="profile-picture"
            src={item.picture}
            alt="chat-room"
          />
          <Overlay target={overlayRef} show={item.show} placement="top">
            <Popover id="popover-basic">
              <Popover.Title as="h3">
                <span className="room-name">{item.username}</span> Direct
                Message
              </Popover.Title>
              <Popover.Content className="chat-pop">
                <ChatEngine chatData={item}></ChatEngine>
              </Popover.Content>
            </Popover>
          </Overlay>
        </div>
      );
    });
  }
  return <>{render}</>;
}

export default ChatRoom;
