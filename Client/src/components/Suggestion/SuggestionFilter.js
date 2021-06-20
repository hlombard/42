import { useSelector, useDispatch } from "react-redux";
import { useState, useEffect } from "react";
import * as actionCreators from "../../store/actions/actionCreators";
import FilterMinMax from "./FilterMinMax";

import "./SuggestionFilter.scss";

function SuggestionFilter(props) {
  const userName = useSelector((state) => state.auth.userName);
  const suggestionData = useSelector(
    (state) => state.suggestion.suggestionData
  );
  const dispatch = useDispatch();
  const [minAge, setMinAge] = useState("18");
  const [maxAge, setMaxAge] = useState("100");
  const [minDistance, setMinDistance] = useState("0");
  const [maxDistance, setMaxDistance] = useState("100");
  const [minRating, setMinRating] = useState("0");
  const [maxRating, setMaxRating] = useState("5");
  const [minTagsNbr, setMinTagsNbr] = useState("0");
  const [tagsFilter, setTagsFilter] = useState("");
  const [sortBy, setSortBy] = useState("age");
  const [resultLen, setResultLen] = useState(0);

  useEffect(() => {
    if (props.isSearch !== true) {
      dispatch(actionCreators.getSuggestion(userName));
    } else {
      initSearchFilters();
    }
  }, []); // eslint-disable-line react-hooks/exhaustive-deps

  const initSearchFilters = () => {
    if (suggestionData) {
      for (let item of suggestionData) {
        if (minAge > item.age) setMinAge(item.age.toString());
        if (maxAge < item.age) setMaxAge(item.age.toString());
        if (minDistance > item.distance)
          setMinDistance((parseInt(item.distance) + 1).toString());
        if (maxDistance < item.distance)
          setMaxDistance((parseInt(item.distance) + 1).toString());
      }
    }
  };

  useEffect(() => {
    if (suggestionData) {
      let sortedSuggestion = suggestionData.filter((item) => {
        if (
          item.age >= parseInt(minAge) &&
          item.age <= parseInt(maxAge) &&
          item.rating >= parseInt(minRating) &&
          item.rating <= parseInt(maxRating) &&
          item.distance >= parseInt(minDistance) &&
          item.distance <= parseInt(maxDistance) &&
          item.common_tags_nb >= minTagsNbr
        ) {
          if (tagsFilter) {
            let filterTagsList = tagsFilter.split(" ");
            filterTagsList = filterTagsList.map((tag) => {
              if (tag.charAt(0) !== "#") {
                return (tag = "#" + tag);
              } else {
                return tag;
              }
            });
            if (
              (item.search_tags &&
                filterTagsList.some((r) => item.search_tags.includes(r))) ||
              (item.common_tags &&
                filterTagsList.some((r) => item.common_tags.includes(r)))
            ) {
              return true;
            }
          } else {
            return true;
          }
        }
        return false;
      });
      sortedSuggestion.sort((a, b) => compare(a, b, sortBy));
      if (sortBy === "common_tags_nb" || sortBy === "rating") {
        sortedSuggestion.reverse();
      }
      setResultLen(sortedSuggestion.length);
      dispatch(actionCreators.stockFilterSugg(sortedSuggestion));
    }
  }, [
    dispatch,
    userName,
    minAge,
    maxAge,
    minDistance,
    maxDistance,
    minRating,
    maxRating,
    suggestionData,
    minTagsNbr,
    sortBy,
    tagsFilter,
  ]); // eslint-disable-line react-hooks/exhaustive-deps

  const compare = (a, b, attribut) => {
    if (a[attribut] < b[attribut]) {
      return -1;
    }
    if (a[attribut] > b[attribut]) {
      return 1;
    }
    return 0;
  };

  let filterFields = (
    <div className="filters-fields">
      {suggestionData ? (
        <>
          <div className="age-filter filter-container">
            <FilterMinMax
              id="age"
              minValue={minAge}
              maxValue={maxAge}
              setMinValue={setMinAge}
              setMaxValue={setMaxAge}
              minLabel="Min Age from 18 to 100"
              maxLabel="Max Age from 18 to 100"
              minSelectable="18"
              maxSelectable="100"
            ></FilterMinMax>
          </div>
          <div className="distance-filter filter-container">
            <FilterMinMax
              id="distance"
              minValue={minDistance}
              maxValue={maxDistance}
              setMinValue={setMinDistance}
              setMaxValue={setMaxDistance}
              minLabel="Min Distance in Miles"
              maxLabel="Max Distance in Miles"
              minSelectable="0"
            ></FilterMinMax>
          </div>
          <div className="rating-filter filter-container">
            <FilterMinMax
              id="rating"
              minValue={minRating}
              maxValue={maxRating}
              setMinValue={setMinRating}
              setMaxValue={setMaxRating}
              minLabel="Min Rating from 0 to 5"
              maxLabel="Max Rating from 0 to 5"
              minSelectable="0"
              maxSelectable="5"
            ></FilterMinMax>
          </div>
          <div className="tag-filter filter-container">
            <FilterMinMax
              id="tag"
              minValue={minTagsNbr}
              setMinValue={setMinTagsNbr}
              minLabel="Min number of tags in common"
              minSelectable="0"
            ></FilterMinMax>
            <input
              value={tagsFilter}
              onChange={(e) => setTagsFilter(e.target.value)}
              name="tag-filter"
              type="text"
              placeholder="Tags separated with space"
            />
          </div>
          <div className="sort-by">
            <label htmlFor="sort-select">Sort By</label>
            <select
              value={sortBy}
              onChange={(e) => setSortBy(e.target.value)}
              name="select"
              id="sort-select"
            >
              <option value="age">Age</option>
              <option value="distance">Distance</option>
              <option value="rating">Rating</option>
              <option value="common_tags_nb">Common Tags</option>
            </select>
          </div>
          <div className="nbr-of-items">
            {resultLen} Item{resultLen > 1 && "s"}
          </div>
        </>
      ) : (
        ""
      )}
    </div>
  );

  return <div className="suggestion-filters">{filterFields}</div>;
}

export default SuggestionFilter;
