import * as actionTypes from "../../actions/actionTypes";
import { updateObject } from "../../utility";

const initialState = {
  showToast: false,
  message: "",
  title: "",
};

const reducer = (state = initialState, action) => {
  switch (action.type) {
    case actionTypes.SEND_TOAST:
      return updateObject(state, {
        showToast: true,
        message: action.message,
        title: action.title,
      });
    case actionTypes.RESET_TOAST:
      return updateObject(state, {
        showToast: false,
        message: "",
        color: "primary",
      });
    default:
      return state;
  }
};

export default reducer;
