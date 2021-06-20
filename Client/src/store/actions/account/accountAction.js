import * as actionTypes from "../actionTypes";
import * as actionCreators from "../../../store/actions/actionCreators";
import axios from "axios";

export const registerStart = () => {
  return {
    type: actionTypes.ACCOUNT_START,
    response: null,
  };
};

export const registerValid = (response) => {
  return {
    type: actionTypes.ACCOUNT_CREATE,
    response: response,
  };
};

export const registerError = (error) => {
  return {
    type: actionTypes.ACCOUNT_ERROR,
    error: error,
  };
};

export function registerCreate(registerData) {
  return (dispatch) => {
    dispatch(registerStart());
    axios({
      method: "post",
      url: "/api/account/create/",
      data: registerData,
    })
      .then((response) => {
        dispatch(registerValid(response));
      })
      .catch((error) => {
        if (error.response.status === 406) {
          dispatch(registerError(error.response.data));
        } else {
          dispatch(registerError(error.response));
        }
      });
  };
}

export function FPMailSend(response) {
  return {
    type: actionTypes.FORGOT_PASSWORD,
    response: response,
  };
}

export function startForgotPassword() {
  return {
    type: actionTypes.START_FORGOT_PASSWORD,
  };
}

export function FPError(error) {
  return {
    type: actionTypes.FP_ERROR,
    error: error.response.data,
  };
}

export function sendForgotPasswordMail(email, message) {
  localStorage.removeItem("token");
  localStorage.removeItem("refresh_token");
  localStorage.removeItem("user_name");
  return (dispatch) => {
    dispatch(startForgotPassword());
    axios({
      method: "post",
      url: "/api/account/forgot_password/",
      data: email,
    })
      .then((response) => {
        dispatch(FPMailSend(response));
        dispatch(actionCreators.sendToast(message, "Password recover"));
      })
      .catch((error) => {
        dispatch(FPError(error));
      });
  };
}

export function FPpasswordReset(response) {
  return {
    type: actionTypes.FP_PASSWORD_RESET,
    response: response,
  };
}

export function resetPassword(data, token, callback) {
  return (dispatch) => {
    dispatch(startForgotPassword());

    axios.defaults.headers.common["Authorization"] = token;
    axios({
      method: "post",
      url: "/api/account/reset_password/?token=" + token,
      data: data,
      Authorization: token,
    })
      .then((response) => {
        callback(response.data.message);
        dispatch(FPpasswordReset(response));
        dispatch(
          actionCreators.sendToast(
            "Your Password has been change",
            "Password recover"
          )
        );
      })
      .catch((error) => {
        if (error.response) {
          if (
            error.response &&
            error.response.data.error &&
            error.response.data.error.includes("Unknown token")
          ) {
            callback(error.response.data.error);
          }
          dispatch(FPError(error));
        }
      });
  };
}
