import { useSelector, useDispatch } from "react-redux";
import { useState, useEffect } from "react";
import * as actionCreators from "../../../store/actions/actionCreators";
import "../css/ProfileInfo.scss";

import Button from "react-bootstrap/Button";
import Modal from "react-bootstrap/Modal";
import PictureDisplay from "./PictureDisplay";
import TagsDisplay from "./TagsDisplay";
import UserRating from "./Rating";
import OverlayTrigger from "react-bootstrap/OverlayTrigger";
import Tooltip from "react-bootstrap/Tooltip";

function ProfileInfo(props) {
  const myData = useSelector((state) => state.profile);
  const reloadConnection = useSelector(
    (state) => state.profile.reloadConnection
  );
  const [show, setShow] = useState(false);
  const [isLiked, setIsLiked] = useState(null);
  const [isBlocked, setIsBlocked] = useState(null);
  let dispatch = useDispatch();
  let render = null;

  useEffect(() => {
    if (props.reloadCallback && typeof props.reloadCallback === "function") {
      props.reloadCallback();
    }
  }, [reloadConnection]); // eslint-disable-line react-hooks/exhaustive-deps

  // Check if object is not empty
  if (
    props.userData &&
    Object.keys(props.userData).length === 0 &&
    props.userData.constructor === Object
  ) {
    return <div>{render}</div>;
  }

  if (props.userData && props.userData.firstname) {
    render = (
      <div className="base-info">
        <div className="firstname">
          <p>
            {props.userData.firstname.charAt(0).toUpperCase() +
              props.userData.firstname.slice(1)}
          </p>
          <p style={{ marginLeft: "1rem" }}>
            {props.userData.lastname.toUpperCase()}
          </p>
        </div>
        <p className="age">{props.userData.age} years old</p>
        <p className="gender">
          {props.userData.gender.charAt(0).toUpperCase() +
            props.userData.gender.slice(1)}
        </p>
        <p className="gender-target">
          Sexual orientation: {props.userData.gender_target}
        </p>
        <p className="location">
          {props.userData.city + " " + props.userData.country}
        </p>
      </div>
    );
  }
  const handleLike = () => {
    dispatch(actionCreators.like(props.userData.username));
    setIsLiked(true);
  };
  const handleDislike = () => {
    dispatch(actionCreators.unlike(props.userData.username));
    setIsLiked(false);
  };
  const handleBlock = (event) => {
    event.stopPropagation();
    dispatch(actionCreators.block(props.userData.username));
    setIsBlocked(true);
  };
  const handleUnblock = (event) => {
    event.stopPropagation();
    dispatch(actionCreators.unblock(props.userData.username));
    setIsBlocked(false);
  };
  const handleChat = (event) => {
    event.stopPropagation();
    dispatch(actionCreators.startChat(props.userData));
  };
  const handleVisit = () => {
    setShow(true);
  };
  const handleClose = () => setShow(false);
  let newClass = "";
  if (props.isButton) {
    newClass = "button-cmp";
  }
  let actionButton = null;
  if (isLiked === null) {
    setIsLiked(props.userData.is_liked);
  }
  if (isBlocked === null) {
    setIsBlocked(props.userData.is_blocked);
  }
  if (
    isLiked != null &&
    isBlocked != null &&
    myData.userData &&
    myData.userData.is_completed &&
    props.userData.is_completed &&
    props.userData.is_own_profile === false &&
    !props.noLikeButton
  ) {
    let likeButton = (
      <Button onClick={handleLike} className="like" variant="primary">
        Like
      </Button>
    );
    if (isLiked) {
      likeButton = (
        <Button onClick={handleDislike} className="unlike" variant="primary">
          Dislike
        </Button>
      );
    }
    if (props.isMatch) {
      likeButton = (
        <Button
          onClick={(e) => handleChat(e)}
          className="chat"
          variant="primary"
        >
          Chat
        </Button>
      );
    }

    let blockButton = (
      <Button
        onClick={(e) => handleBlock(e)}
        className="block"
        variant="danger"
      >
        Block
      </Button>
    );
    if (isBlocked) {
      blockButton = (
        <Button
          onClick={(e) => handleUnblock(e)}
          className="block"
          variant="danger"
        >
          Unblock
        </Button>
      );
    }

    actionButton = (
      <div className="action-button">
        {likeButton}
        {blockButton}
      </div>
    );
  } else if (props.userData.is_own_profile === true) {
    let visitList = props.userData.visits.map((item, key) => {
      return (
        <div key={key} className="visit-list">
          <div>{item}</div>
        </div>
      );
    });
    actionButton = (
      <>
        <div className="action-button">
          <Button onClick={handleVisit} className="like" variant="primary">
            Visit list
          </Button>
        </div>
        <Modal show={show} onHide={handleClose}>
          <Modal.Header closeButton>
            <Modal.Title>Who visited my profile</Modal.Title>
          </Modal.Header>
          <Modal.Body>{visitList}</Modal.Body>
        </Modal>
      </>
    );
  } else if (myData.userData && myData.userData.is_completed === false) {
    actionButton = (
      <p
        className="action-button"
        style={{ fontSize: "0.6rem", fontStyle: "italic" }}
      >
        Please Complete your profile to like other people
      </p>
    );
  }

  let last_activity = new Date(props.userData.last_activity).toLocaleString();
  if (!props.userData.last_activity) {
    last_activity = new Date(props.userData.registered_date).toLocaleString();
  }
  let isOnline = (
    <div className="status-container">
      <span className="red dot"></span>
      <span className="statut-string">
        Is Offline {"since " + last_activity}
      </span>
    </div>
  );

  if (props.userData.is_online) {
    isOnline = (
      <div className="status-container">
        <span className="green dot"></span>
        <span className="statut-string">Is Online</span>
      </div>
    );
  }

  const handleReportButton = () => {
    dispatch(actionCreators.report(props.userData.username));
  };
  let reportButton = null;
  if (
    props.userData.is_own_profile === false &&
    props.noLikeButton !== "true" &&
    props.noRating !== true
  ) {
    reportButton = (
      <OverlayTrigger
        key={"top"}
        placement={"top"}
        overlay={
          <Tooltip id="report-button">
            Report account as <strong>fake</strong>.
          </Tooltip>
        }
      >
        <img
          onClick={handleReportButton}
          id="report-button"
          className="report-svg"
          src={process.env.PUBLIC_URL + "/report.svg"}
          alt="report-user"
        />
      </OverlayTrigger>
    );
  }
  return (
    <div className={"user-info profile-card " + newClass}>
      <div>
        <div className="profile-title-container">
          <p className="card-title profile-pseudo">
            @{props.userData.username}
          </p>

          {reportButton}
        </div>
        {isOnline}
      </div>
      <PictureDisplay userData={props.userData} pictureId={1}></PictureDisplay>
      <UserRating
        username={props.userData.username}
        rating={props.userData.rating}
        reloadCallback={props.reloadCallback}
        noRating={props.noRating}
      ></UserRating>
      {render}
      {actionButton}
      <TagsDisplay
        reloadCallback={props.reloadCallback}
        userData={props.userData}
      ></TagsDisplay>
    </div>
  );
}
export default ProfileInfo;
