import "../css/profile.scss";
import { withRouter } from "react-router-dom";
import { useEffect, useState } from "react";
import { useDispatch } from "react-redux";
import axios from "axios";
import * as actionCreators from "../../../store/actions/actionCreators";

import ProfileInfo from "./ProfileInfo";
import AboutMe from "./AboutMe";
import MyPictures from "./MyPictures";

function Profile(props) {
  const [userData, setUserData] = useState({});
  let dispatch = useDispatch();

  useEffect(() => {
    getProfileData(true);
  }, [props.match.params.username]); // eslint-disable-line react-hooks/exhaustive-deps

  const getProfileData = (sendVisit = false) => {
    axios({
      method: "get",
      url: "/api/user/" + props.match.params.username + "/",
    })
      .then((response) => {
        setUserData(response.data);
        if (response.data.is_own_profile === false && sendVisit) {
          console.log("calling visit from getProfile");
          dispatch(actionCreators.sendVisit(response.data.username));
        }
      })
      .catch((error) => {
        console.log("User doesn't EXIST");
        props.history.push("/home");
      });
  };

  let render = null;

  if (userData !== {} && userData) {
    render = (
      <>
        <ProfileInfo
          userData={userData}
          reloadCallback={getProfileData}
        ></ProfileInfo>
        {userData.biography ? <AboutMe userData={userData}></AboutMe> : null}
        <MyPictures userData={userData}></MyPictures>
      </>
    );
  }

  return (
    <div>
      <div className="profile-viewer">{render}</div>
    </div>
  );
}
export default withRouter(Profile);
