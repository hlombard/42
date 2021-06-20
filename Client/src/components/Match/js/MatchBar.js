import Navbar from "react-bootstrap/Navbar";
import Nav from "react-bootstrap/Nav";

import ChatRoom from "./ChatRoom";
import "../css/MatchBar.scss";
import { useSelector } from "react-redux";

function MatchBar(props) {
  const chatData = useSelector((state) => state.socket.chatData);

  return (
    <>
      <Navbar fixed="bottom" expand="lg" className="justify-content-end">
        <Navbar.Brand style={{ marginLeft: "1rem" }} href="#home">
          Chat Bar
        </Navbar.Brand>
        <Navbar.Toggle aria-controls="basic-navbar-nav" />
        <Navbar.Collapse id="match-navbar" className="matchbar">
          <Nav>
            <ChatRoom chatData={chatData}></ChatRoom>
          </Nav>
        </Navbar.Collapse>
      </Navbar>
    </>
  );
}

export default MatchBar;
