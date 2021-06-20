import * as actionTypes from "../../actions/actionTypes";
import { updateObject } from "../../utility";

const initalState = {
  userData: null,
  error: null,
  tagStatus: 0,
  reloadConnection: 0,
};

const reducer = (state = initalState, action) => {
  switch (action.type) {
    case actionTypes.PROFILE_GET_DATA:
      return updateObject(state, { userData: action.userData });
    case actionTypes.PROFILE_ERROR_UPDATE:
      return updateObject(state, { error: action.error });
    case actionTypes.PROFILE_START:
      return updateObject(state, { error: null });
    case actionTypes.POST_TAGS:
      return updateObject(state, { tagStatus: state.tagStatus + 1 });
    case actionTypes.RELOAD_CONNECTION:
      return updateObject(state, {
        reloadConnection: state.reloadConnection + 1,
      });
    default:
      return state;
  }
};

export default reducer;
