import * as actionTypes from "../../actions/actionTypes";
import { updateObject } from "../../utility";

const initialState = {
  response: null,
  error: null,
  FP_password: null,
  FP_error: null,
  valid_reset: null,
};

const reducer = (state = initialState, action) => {
  switch (action.type) {
    case actionTypes.ACCOUNT_START:
      return updateObject(state, { response: null, error: null });
    case actionTypes.ACCOUNT_CREATE:
      return updateObject(state, { response: action.response, error: null });
    case actionTypes.ACCOUNT_ERROR:
      return updateObject(state, { error: action.error, response: null });
    case actionTypes.START_FORGOT_PASSWORD:
      return updateObject(state, { FP_error: null });
    case actionTypes.FORGOT_PASSWORD:
      return updateObject(state, { FP_password: action.response });
    case actionTypes.FP_ERROR:
      return updateObject(state, {
        FP_password: null,
        FP_error: action.error,
      });
    case actionTypes.FP_PASSWORD_RESET:
      return updateObject(state, {
        valid_reset: action.response,
      });
    default:
      return state;
  }
};

export default reducer;
