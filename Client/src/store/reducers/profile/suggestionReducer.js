import * as actionTypes from "../../actions/actionTypes";
import { updateObject } from "../../utility";

const initalState = {
  suggestionData: null,
  filteredSuggestion: [],
  searchData: null,
  error: null,
};

const reducer = (state = initalState, action) => {
  switch (action.type) {
    case actionTypes.GET_SUGGESTION:
      return updateObject(state, { suggestionData: action.data });
    case actionTypes.STORE_FILTERED_SUGG:
      return updateObject(state, { filteredSuggestion: action.data });
    // case actionTypes.GET_SEARCH:
    //   return updateObject(state, { searchData: action.data });
    case actionTypes.ERROR_SUGGESTION:
      return updateObject(state, { error: action.error });
    case actionTypes.START_SUGGESTION:
      return updateObject(state, { suggestionData: null, error: null });
    default:
      return state;
  }
};

export default reducer;
