import { withRouter } from "react-router-dom";
import { useEffect } from "react";
import { useDispatch, useSelector } from "react-redux";
import * as actionCreators from "../../../store/actions/actionCreators";
import "../css/ProfileManager.css";
import Dropdown from "react-bootstrap/Dropdown";
import DropdownButton from "react-bootstrap/DropdownButton";
import axios from "axios";

function ProfileManager(props) {
  const dispatch = useDispatch();

  const userName = useSelector((state) => state.auth.userName);
  const isAuth = useSelector((state) => state.auth.isAuth);
  const token = localStorage.getItem("token");

  useEffect(() => {
    if (userName && isAuth && token) {
      axios.defaults.headers.common["Authorization"] = token;
      dispatch(actionCreators.profileGetData(userName));
    }
  }, [userName, isAuth, token]); // eslint-disable-line react-hooks/exhaustive-deps

  const logout = () => {
    dispatch(
      actionCreators.wsMessage({
        type: "logout",
        user_target: localStorage.getItem("user_name"),
        time: Date.now,
        content: null,
      })
    );
    dispatch(actionCreators.authSendLogout());
  };

  const handleProfileClick = () => {
    props.history.push("/profile/" + userName);
  };
  const handleProfileModificationClick = () => {
    props.history.push("/profile/" + userName + "/settings");
  };
  return (
    <div className="pmanager-grid">
      <DropdownButton
        className="pman-button"
        id="profile-manager-drop"
        title={userName ? userName : "Loading"}
      >
        <Dropdown.Item onClick={handleProfileClick} as="button">
          Profile
        </Dropdown.Item>
        <Dropdown.Item onClick={handleProfileModificationClick} as="button">
          My settings
        </Dropdown.Item>
        <Dropdown.Item onClick={logout} as="button">
          Logout
        </Dropdown.Item>
      </DropdownButton>
    </div>
  );
}

export default withRouter(ProfileManager);
