import { useEffect, useState } from "react";
import axios from "axios";
import { Redirect, withRouter } from "react-router-dom";
import ProfileInfo from "../../Profile/js/ProfileInfo";
import "../css/MatchDisplay.scss";

function MatchDisplay(props) {
  const [userData, setUserData] = useState({});

  useEffect(() => {
    axios({
      method: "get",
      url: "/api/user/" + props.user + "/",
    })
      .then((response) => {
        setUserData(response.data);
      })
      .catch((error) => {
        return (
          <Redirect to={"/profile/" + localStorage.getItem("user_name")} />
        );
      });
  }, []); // eslint-disable-line react-hooks/exhaustive-deps

  const handleSuggClick = (e, item) => {
    props.history.push("/profile/" + item.username);
  };
  let render = <p>Loading...</p>;
  if (userData) {
    render = (
      <div className="noselect" onClick={(e) => handleSuggClick(e, userData)}>
        <ProfileInfo
          isMatch={true}
          noRating={true}
          noLikeButton={false}
          userData={userData}
          isButton={true}
        ></ProfileInfo>
      </div>
    );
  }
  return <div className="match-list-container">{render}</div>;
}

export default withRouter(MatchDisplay);
