import React, { useEffect } from "react";
import { useSelector } from "react-redux";
import { withRouter, Redirect } from "react-router-dom";
import { useDispatch } from "react-redux";
import * as actionCreators from "../../store/actions/actionCreators";
import axios from "axios";

function Verify(props) {
  const isAuth = useSelector((state) => state.auth.isAuth);
  const token = localStorage.getItem("token");
  const dispatch = useDispatch();

  useEffect(() => {
    if (!isAuth && !token) {
      const query = new URLSearchParams(props.location.search);
      const token = query.get("token");

      if (token) {
        axios({
          method: "post",
          url: "http://localhost:8080/api/account/verify/?token=" + token,
        })
          .then((response) => {
            props.history.push("/account/login");
            dispatch(
              actionCreators.sendToast(response.data.message, "Account")
            );
          })
          .catch((error) => {
            dispatch(
              actionCreators.sendToast(error.response.data.error, "Account")
            );
            props.history.push("/account/login");
          });
      }
    }
  });
  if (isAuth) {
    return <Redirect to={"/profile/" + localStorage.getItem("user_name")} />;
  }
  return <div></div>;
}

export default withRouter(Verify);
