//var Rating = require("react-rating");
import Rating from "react-rating";
import { useDispatch } from "react-redux";
import * as actionCreators from "../../../store/actions/actionCreators";

function UserRating(props) {
  let dispatch = useDispatch();

  const handleRateChange = (value) => {
    dispatch(
      actionCreators.postRating(
        props.username,
        { rating: value },
        props.reloadCallback
      )
    );
  };

  return (
    <div className="rating-stars">
      <Rating
        initialRating={props.rating}
        emptySymbol={
          <img
            alt="star-empty"
            src={process.env.PUBLIC_URL + "/star.png"}
            className="icon"
          />
        }
        fullSymbol={
          <img
            alt="star-fill"
            src={process.env.PUBLIC_URL + "/star-fill.png"}
            className="icon"
          />
        }
        onChange={handleRateChange}
        readonly={props.noRating}
      />
    </div>
  );
}

export default UserRating;
