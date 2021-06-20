import { useDispatch } from "react-redux";
import { useState } from "react";
import * as actionCreators from "../../store/actions/actionCreators";

import SearchFilter from "./SearchFilter";
import SuggestionList from "./SuggestionList";
import Button from "react-bootstrap/Button";

function Search(props) {
  const [showResult, setShowResult] = useState(false);
  const dispatch = useDispatch();

  let render = (
    <SearchFilter showResult={() => setShowResult(true)}></SearchFilter>
  );
  let newSearch = "";

  const resetSearch = () => {
    dispatch(actionCreators.startSuggestion());
    setShowResult(false);
  };

  if (showResult) {
    render = <SuggestionList isSearch={true}></SuggestionList>;
    newSearch = (
      <Button
        className="send-button"
        onClick={resetSearch}
        type="submit"
        variant="sub"
      >
        New Search
      </Button>
    );
  }

  return (
    <div>
      <span>{newSearch}</span>
      {render}
    </div>
  );
}

export default Search;
