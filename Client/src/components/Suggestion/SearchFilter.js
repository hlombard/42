import { useSelector, useDispatch } from "react-redux";
import { useState } from "react";
import * as actionCreators from "../../store/actions/actionCreators";
import axios from "axios";

import FilterMinMax from "./FilterMinMax";
import Button from "react-bootstrap/Button";

import "./SuggestionFilter.scss";
const GEO_KEY = "AZhj6xbQX9y9cR58Z8GpGCVdQA4JTxh6";

function SuggestionFilter(props) {
  const userName = useSelector((state) => state.auth.userName);
  const [minAge, setMinAge] = useState("18");
  const [maxAge, setMaxAge] = useState("100");
  const [city, setCity] = useState("");
  const [cityResult, setCityResult] = useState({ data: null, displayName: "" });
  const [minRating, setMinRating] = useState("1");
  const [maxRating, setMaxRating] = useState("5");
  const [minTagsNbr, setMinTagsNbr] = useState("0");
  const [tags, setTags] = useState("");
  const dispatch = useDispatch();

  const getGeocoding = (location) => {
    setCity(location);
    if (!location) {
      setCityResult({ data: null, displayName: "" });
    } else {
      axios({
        method: "get",
        url:
          "http://open.mapquestapi.com/geocoding/v1/address?key=" +
          GEO_KEY +
          "&location=" +
          location,
        headers: {
          "Content-Type": "application/json",
        },
      })
        .then((response) => {
          let displayResult = "";
          if (
            response &&
            response.data &&
            response.data.results.length > 0 &&
            response.data.results[0].locations.length > 0
          ) {
            let geoInfo = response.data.results[0].locations[0];
            if (geoInfo.adminArea1) {
              displayResult = displayResult.concat(" ", geoInfo.adminArea1);
            }
            if (geoInfo.adminArea3) {
              displayResult = displayResult.concat(" ", geoInfo.adminArea3);
            }
            if (geoInfo.adminArea4) {
              displayResult = displayResult.concat(" ", geoInfo.adminArea4);
            }
            if (geoInfo.adminArea5) {
              displayResult = displayResult.concat(" ", geoInfo.adminArea5);
            }
            if (geoInfo.adminArea6) {
              displayResult = displayResult.concat(" ", geoInfo.adminArea6);
            }
            displayResult.trim();
            setCityResult({ data: geoInfo, displayName: displayResult });
          }
        })
        .catch((error) => {
          setCityResult({ data: null, displayName: "City Not found" });
        });
    }
  };

  const handlerSearchSubmit = (event) => {
    event.preventDefault();
    dispatch(actionCreators.startSuggestion());
    if (cityResult && cityResult.data && cityResult.data.latLng) {
      let tagsTab = tags.split(" ");
      tagsTab = tagsTab.filter((item) => {
        return item;
      });

      const searchForm = {
        is_suggestion: false,
        min_age: parseInt(minAge),
        max_age: parseInt(maxAge),
        min_rating: minRating,
        max_rating: maxRating,
        latitude: cityResult.data.latLng.lat.toString(),
        longitude: cityResult.data.latLng.lng.toString(),
        tags: tagsTab.length > 0 ? tagsTab : [],
      };
      dispatch(
        actionCreators.getSuggestion(userName, searchForm, props.showResult)
      );
    } else {
      dispatch(actionCreators.sendToast("City data invalid", "Search"));
    }
  };

  let filterFields = (
    <div className="filters-fields">
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
        <label htmlFor="city">City</label>
        <input
          type="text"
          id="city"
          value={city}
          onChange={(e) => getGeocoding(e.target.value)}
          autoComplete="off"
        />
        {cityResult.displayName}
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
      </div>
      <div className="sort-by">
        <label htmlFor="tags">List of Tags seperated with a space</label>
        <input
          type="text"
          id="tags"
          value={tags}
          onChange={(e) => setTags(e.target.value)}
          autoComplete="off"
        />
      </div>
      <div className="nbr-of-items">
        <Button
          className="send-button"
          onClick={handlerSearchSubmit}
          type="submit"
          variant="sub"
        >
          Search
        </Button>
      </div>
    </div>
  );

  return <div className="suggestion-filters">{filterFields}</div>;
}

export default SuggestionFilter;
