import * as actionTypes from "../actionTypes";
import * as actionCreators from "../actionCreators";
import axios from "axios";

export const startSuggestion = () => {
  return {
    type: actionTypes.START_SUGGESTION,
  };
};

export const saveSuggestion = (data) => {
  return {
    type: actionTypes.GET_SUGGESTION,
    data: data,
  };
};

export const errorSuggestion = (error) => {
  return {
    type: actionTypes.ERROR_SUGGESTION,
    error: error,
  };
};

export const stockFilterSugg = (suggList) => {
  return {
    type: actionTypes.STORE_FILTERED_SUGG,
    data: suggList,
  };
};

export const getSuggestion = (
  userName,
  searchData = {
    min_age: 18,
    max_age: 100,
    min_rating: "1",
    max_rating: "5",
    latitude: "0",
    longitude: "0",
    tags: [],
    is_suggestion: true,
  },
  callBack
) => {
  return (dispatch) => {
    dispatch(startSuggestion());
    axios({
      method: "post",
      url: "/api/user/" + userName + "/find/",
      data: searchData,
    })
      .then((response) => {
        if (searchData) {
          dispatch(saveSuggestion(response.data));
        } else {
          dispatch(saveSuggestion(response.data));
        }
        callBack();
      })
      .catch((error) => {
        dispatch(errorSuggestion(error.response));
        if (error.response && error.response.data) {
          dispatch(
            actionCreators.sendToast(error.response.data.error, "Search")
          );
        }
      });
  };
};
