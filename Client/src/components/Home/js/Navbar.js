import { NavLink, withRouter } from "react-router-dom";
import { useDispatch } from "react-redux";
import { useEffect } from "react";
import "../css/navbar.css";

import ProfileManager from "../../Profile/js/ProfileManager";
import Notify from "./Notify";
import Navbar from "react-bootstrap/Navbar";
import * as actionCreators from "../../../store/actions/actionCreators";

function NavbarMatcha(props) {
  const token = localStorage.getItem("token");
  const refresh_token = localStorage.getItem("refresh_token");
  const dispatch = useDispatch();

  useEffect(() => {
    dispatch(actionCreators.checkAuthStatus());
  }, []); // eslint-disable-line react-hooks/exhaustive-deps

  let auth_nav = null;
  if (token && refresh_token) {
    auth_nav = (
      <>
        <Navbar.Collapse id="matcha-navbar" className="matcha-navbar">
          <div className="home-navigator">
            <NavLink className="home-onglet nav-link" to="/home/search">
              Search
            </NavLink>
            <NavLink className="home-onglet nav-link" to="/home/match">
              Match
            </NavLink>
            <NavLink className="home-onglet nav-link" to="/home/suggestion">
              Suggestions
            </NavLink>
          </div>
        </Navbar.Collapse>
        <div className="profile-management">
          <Notify></Notify>
          <ProfileManager></ProfileManager>
        </div>
      </>
    );
  }

  return (
    <>
      <Navbar fixed="top" expand="lg" className="justify-content-between">
        <Navbar.Brand className="nav-title">
          <NavLink
            exact
            className="matcha-link nav-link"
            to={"/profile/" + localStorage.getItem("user_name")}
          >
            Matcha
          </NavLink>
        </Navbar.Brand>
        <Navbar.Toggle aria-controls="basic-navbar-nav" />
        {auth_nav}
      </Navbar>
    </>
  );
}

export default withRouter(NavbarMatcha);
