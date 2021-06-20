import React, { useEffect, useState, useRef } from "react";
import { useDispatch, useSelector } from "react-redux";
import { withRouter } from "react-router-dom";
import * as actionCreators from "../../../store/actions/actionCreators";

import Popover from "react-bootstrap/Popover";
import Overlay from "react-bootstrap/Overlay";
import "../css/notify.scss";

function Notify(props) {
  let dispatch = useDispatch();
  const [show, setShow] = useState(false);
  const overlayRef = useRef(null);
  const [notifyNbr, setNotifyNbr] = useState(0);
  const notifyData = useSelector((state) => state.socket.notifyData);

  useEffect(() => {
    dispatch(actionCreators.wsConnect());
  }, []); // eslint-disable-line react-hooks/exhaustive-deps

  useEffect(() => {
    setNotifyNbr(
      notifyData.reduce(
        (acc, curr) => (curr.viewed === false ? acc + 1 : acc),
        0
      )
    );
  }, [notifyData]);

  const timeDifference = (previous) => {
    var current = Date.now();
    var msPerMinute = 60 * 1000;
    var msPerHour = msPerMinute * 60;
    var msPerDay = msPerHour * 24;
    var msPerMonth = msPerDay * 30;
    var msPerYear = msPerDay * 365;
    var elapsed = current - previous;

    if (elapsed < msPerMinute) {
      return Math.round(elapsed / 1000) + " seconds ago";
    } else if (elapsed < msPerHour) {
      return Math.round(elapsed / msPerMinute) + " minutes ago";
    } else if (elapsed < msPerDay) {
      return Math.round(elapsed / msPerHour) + " hours ago";
    } else if (elapsed < msPerMonth) {
      return "approximately " + Math.round(elapsed / msPerDay) + " days ago";
    } else if (elapsed < msPerYear) {
      return (
        "approximately " + Math.round(elapsed / msPerMonth) + " months ago"
      );
    } else {
      return "approximately " + Math.round(elapsed / msPerYear) + " years ago";
    }
  };

  let notifyDisplay = <div className="notify-container">Nothing here</div>;

  const handleNotifClick = (link) => {
    setShow(false);
    setNotifyNbr(0);
    notifyData.forEach((item) => {
      item.viewed = true;
    });
    props.history.push(link);
  };

  if (notifyData && notifyData.length > 0) {
    let notifyCpy = [...notifyData];
    notifyCpy.reverse();
    if (notifyCpy.length > 10) {
      notifyCpy = notifyCpy.slice(0, 10);
    }
    notifyDisplay = notifyCpy.map((item) => {
      let message = "";
      let title = "";
      let link = "";
      let time = timeDifference(new Date(item.date));
      let dot = null;

      switch (item.type) {
        case "like":
          title = "Like";
          message = item.from + " liked your profile";
          link = "/profile/" + item.from;
          break;
        case "unlike":
          title = "Dislike";
          message = item.from + " disliked your profile";
          link = "/profile/" + item.from;
          break;
        case "match":
          title = "New Match";
          message = "You've got a new match with " + item.from + " !!!";
          link = "/home/match";
          break;
        case "visit":
          title = "New Visit";
          message = item.from + " visited your profile";
          link = "/profile/" + item.from;
          break;
        case "message":
          title = "New Message";
          message = "You get a new message from " + item.from;
          link = "/home/match";
          break;
        default:
          break;
      }
      if (item.viewed === false) {
        dot = <div className="viewed-dot"></div>;
      }
      return (
        <div key={item.id}>
          <div
            onClick={() => handleNotifClick(link)}
            className="notify-container"
          >
            {dot}
            <div className="title">{title}</div>
            <div className="message">{message}</div>
            <div className="date">{time}</div>
          </div>
          <hr />
        </div>
      );
    });
  }

  const popover = (
    <Popover id="popover-basic">
      <Popover.Title as="h3">Notifications</Popover.Title>
      <Popover.Content className="notify-pop-body">
        {notifyDisplay}
      </Popover.Content>
    </Popover>
  );

  const handleOpenNotification = () => {
    if (!show) {
      dispatch(
        actionCreators.wsMessage({
          type: "viewed",
          user_target: localStorage.getItem("user_name"),
          time: Date.now,
          content: notifyData.map((item) => item.id),
        })
      );
    }
    if (show) {
      notifyData.forEach((item) => {
        item.viewed = true;
      });
    }
    setNotifyNbr(0);
    setShow(!show);
  };

  const Example = () => (
    <>
      <div className="notify">
        <img
          ref={overlayRef}
          onClick={handleOpenNotification}
          className="circle-icon"
          id="dropdown-basic"
          src={process.env.PUBLIC_URL + "/notification.svg"}
          alt="notification-bell"
        />
        <div className="notify-badge">{notifyNbr}</div>
      </div>
      <Overlay target={overlayRef} show={show} placement="bottom">
        {popover}
      </Overlay>
    </>
  );

  return <Example />;
}

export default withRouter(Notify);
