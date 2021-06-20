import { useSelector } from "react-redux";
import { NavLink } from "react-router-dom";
import "../css/settings.scss";

function Settings(props) {
  const userName = useSelector((state) => state.auth.userName);

  return (
    <div className="settings-list">
      <NavLink to={"/profile/" + userName + "/settings/info"}>
        Change my informations
      </NavLink>
      <NavLink to={"/profile/" + userName + "/settings/email"}>
        Change my email
      </NavLink>
      <NavLink to={"/profile/" + userName + "/settings/password"}>
        Change my password
      </NavLink>
    </div>
  );
}

export default Settings;
