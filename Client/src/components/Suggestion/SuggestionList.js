import { withRouter } from "react-router-dom";
import { useSelector } from "react-redux";
import ProfileInfo from "../Profile/js/ProfileInfo";
import SuggestionFilter from "./SuggestionFilter";
import "./SuggestionList.scss";

function SuggestionList(props) {
  const error = useSelector((state) => state.suggestion.error);
  const suggestionData = useSelector(
    (state) => state.suggestion.filteredSuggestion
  );

  const handleSuggClick = (e, item) => {
    props.history.push("/profile/" + item.username);
  };

  let suggList = null;
  if (suggestionData && suggestionData.length > 0) {
    suggList = suggestionData.map((item) => {
      let userData = {
        firstname: item.firstname,
        lastname: item.lastname,
        age: item.age,
        gender: item.gender,
        gender_target: item.gender_target,
        city: item.city,
        country: item.country,
        rating: item.rating,
        username: item.username,
        picture_1: item.picture_1,
        is_own_profile: false,
        tags: props.isSearch ? item.search_tags : item.common_tags,
        is_online: item.is_online,
        last_activity: item.last_activity,
        registered_date: item.registered_date,
      };
      return (
        <div
          className="suggestion-card"
          key={item.username}
          style={{ color: "white" }}
        >
          <div
            className="noselect profile-info-container"
            onClick={(e) => handleSuggClick(e, item)}
          >
            <ProfileInfo
              noLikeButton="true"
              noRating={true}
              userData={userData}
              isButton={true}
            ></ProfileInfo>
          </div>
        </div>
      );
    });
  } else if (error && error.data && error.data.error) {
    suggList = <p style={{ marginTop: "2rem" }}>{error.data.error}</p>;
  } else if (suggestionData.length === 0) {
    suggList = <p>Nothing to show with the selected filters</p>;
  }

  return (
    <div className="suggestion-container">
      <SuggestionFilter isSearch={props.isSearch} />
      <div>{suggList}</div>
    </div>
  );
}

export default withRouter(SuggestionList);
