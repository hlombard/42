import * as actionTypes from "../actionTypes";
import axios from "axios";

export const authStart = () => {
  return {
    type: actionTypes.AUTH_START,
    response: null,
  };
};

export const authSuccess = (access_token, refresh_token, user_name) => {
  localStorage.setItem("token", access_token);
  localStorage.setItem("refresh_token", refresh_token);
  localStorage.setItem("user_name", user_name);
  axios.defaults.headers.common["Authorization"] = access_token;
  return {
    type: actionTypes.AUTH_SUCCESS,
    isAuth: true,
    user_name: user_name,
  };
};

export const authError = (error) => {
  return {
    type: actionTypes.AUTH_ERROR,
    error: error,
  };
};

export const authLogout = () => {
  localStorage.removeItem("token");
  localStorage.removeItem("refresh_token");
  localStorage.removeItem("user_name");
  return {
    type: actionTypes.AUTH_LOGOUT,
  };
};

export const authSendLogout = () => {
  return (dispatch) => {
    axios({
      method: "post",
      url: "/api/logout/",
    })
      .then((response) => {
        if (response) dispatch(authLogout());
      })
      .catch((error) => {
        dispatch(authError(error));
      });
  };
};

export const checkAuthStatus = () => {
  return (dispatch) => {
    const token = localStorage.getItem("token");
    const refresh_token = localStorage.getItem("refresh_token");
    const user_name = localStorage.getItem("user_name");

    if (!token) {
      dispatch(authSendLogout);
    } else {
      dispatch(authSuccess(token, refresh_token, user_name));
    }
  };
};

export function authCreate(authData) {
  return (dispatch) => {
    dispatch(authStart());
    axios({
      method: "post",
      url: "/api/login/",
      data: authData,
    })
      .then((response) => {
        dispatch(
          authSuccess(
            response.data.access_token,
            response.data.refresh_token,
            response.data.username
          )
        );
      })
      .catch((error) => {
        dispatch(authError(error));
      });
  };
}
