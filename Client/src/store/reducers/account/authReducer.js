import * as actionTypes from "../../actions/actionTypes";
import { updateObject } from "../../utility";

const initialState = {
  access_token: null,
  refresh_token: null,
  userName: null,
  userId: null,
  error: null,
  loading: false,
  isAuth: false,
};

const authSucess = (state, action) => {
  return updateObject(state, {
    isAuth: true,
    userName: action.user_name,
    error: null,
    loading: false,
  });
};

const authError = (state, action) => {
  return updateObject(state, {
    error: action.error.response.data,
    loading: false,
  });
};

const authLogout = (state, action) => {
  return updateObject(state, {
    access_token: null,
    refresh_token: null,
    userId: null,
    isAuth: false,
  });
};

const reducer = (state = initialState, action) => {
  switch (action.type) {
    case actionTypes.AUTH_START:
      return updateObject(state, { error: null, loading: true });
    case actionTypes.AUTH_SUCCESS:
      return authSucess(state, action);
    case actionTypes.AUTH_LOGOUT:
      return authLogout(state, action);
    case actionTypes.AUTH_ERROR:
      return authError(state, action);
    default:
      return state;
  }
};
export default reducer;
