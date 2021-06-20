import { Switch, Route } from "react-router-dom";
import { useDispatch, useSelector } from "react-redux";
import * as actionCreators from "../store/actions/actionCreators";
import "./App.scss";

import AlertSystem from "../components/Home/js/AlertSystem";
import Navbar from "../components/Home/js/Navbar";
import MatchBar from "../components/Match/js/MatchBar";
import Login from "../components/Account/Login";
import Register from "../components/Account/Register";
import Verify from "../components/Account/Verify";
import ResetPassword from "../components/Account/ResetPassword";
import AppWrapper from "../components/Utils/AppWrapper";

function App() {
  const isAuth = useSelector((state) => state.auth.isAuth);
  const dispatch = useDispatch();

  const token = localStorage.getItem("token");
  const refresh_token = localStorage.getItem("refresh_token");
  dispatch(actionCreators.checkAuthStatus());
  if (!isAuth && !token && !refresh_token) {
  }

  return (
    <div className="App">
      <Navbar></Navbar>
      <AlertSystem></AlertSystem>
      <div className="app-page-container">
        <Switch>
          <Route path="/account/verify">
            <Verify></Verify>
          </Route>
          <Route path="/account/register/emailverify">
            <p>verify your email</p>
          </Route>
          <Route path="/account/register">
            <Register></Register>
          </Route>
          <Route path="/account/login">
            <Login></Login>
          </Route>
          <Route path="/account/reset_password">
            <ResetPassword></ResetPassword>
          </Route>
          <Route path="/">
            <AppWrapper></AppWrapper>
          </Route>
        </Switch>
      </div>
      {isAuth && token && refresh_token ? <MatchBar></MatchBar> : ""}
    </div>
  );
}

export default App;
