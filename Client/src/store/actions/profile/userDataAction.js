import * as actionTypes from "../actionTypes";
import * as actionCreators from "../../../store/actions/actionCreators";
import axios from "axios";

export const profileData = (response) => {
  return {
    type: actionTypes.PROFILE_GET_DATA,
    userData: response,
  };
};

export const updateError = (error) => {
  return {
    type: actionTypes.PROFILE_ERROR_UPDATE,
    error: error,
  };
};

export const profileStart = (error) => {
  return {
    type: actionTypes.PROFILE_START,
  };
};

export const newConnectionStatus = (h) => {
  return {
    type: actionTypes.RELOAD_CONNECTION,
  };
};

export function profileUpdate(userName, newData, message) {
  return (dispatch) => {
    axios({
      method: "patch",
      url: "/api/user/" + userName + "/",
      data: newData,
    })
      .then((response) => {
        dispatch(actionCreators.sendToast(message, "Profile"));
      })
      .catch((error) => {
        console.log("Profile Updatae error", error, error.response);
        dispatch(updateError(error.response.data));
      });
  };
}

export function profileGetData(userName) {
  return (dispatch) => {
    axios({
      method: "get",
      url: "/api/user/" + userName + "/",
    })
      .then((response) => {
        dispatch(profileData(response.data));
      })
      .catch((error) => {
        console.log("API Profile Get Error", error.response);
      });
  };
}

export function postImage(imgNumber, imageData, callBack, userName) {
  const formData = new FormData();

  formData.append("image", imageData);
  return (dispatch) => {
    axios({
      method: "post",
      headers: {
        "content-type": "multipart/form-data",
      },
      url: "/api/images/?number=" + imgNumber,
      data: formData,
    })
      .then((response) => {
        dispatch(actionCreators.sendToast(response.data.message, "Upload"));
        dispatch(profileGetData(userName));
        window.location.reload();
        callBack();
      })
      .catch((error) => {
        console.log("img error", error.response);
        dispatch(actionCreators.sendToast(error.response.data.error, "Error"));
        callBack();
      });
  };
}

export const updateTagStatus = (error) => {
  return {
    type: actionTypes.POST_TAGS,
  };
};

export function postTags(username, tags, method, callBack) {
  return (dispatch) => {
    axios({
      method: method,
      url: "/api/user/" + username + "/tag/",
      data: tags,
    })
      .then((response) => {
        callBack();
      })
      .catch((error) => {
        console.log("tags error", error, error.response);
        dispatch(actionCreators.sendToast(error.response.data.error, "Rating"));
      });
  };
}

export function postRating(username, rate, callBack) {
  return (dispatch) => {
    axios({
      method: "post",
      url: "api/user/" + username + "/rating/",
      data: rate,
    })
      .then((response) => {
        dispatch(actionCreators.sendToast(response.data.message, "Rating"));
        callBack();
      })
      .catch((error) => {
        dispatch(actionCreators.sendToast(error.response.data.error, "Rating"));
        callBack();
      });
  };
}
