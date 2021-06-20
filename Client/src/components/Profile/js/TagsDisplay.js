import { useState } from "react";
import { useDispatch } from "react-redux";

import Button from "react-bootstrap/Button";
import Badge from "react-bootstrap/Badge";
import Form from "react-bootstrap/Form";

import * as actionCreators from "../../../store/actions/actionCreators";
import "../css/TagsDisplay.scss";

function TagsDisplay(props) {
  const [tagInput, setTagInput] = useState("");
  const dispatch = useDispatch();

  const addTag = (event) => {
    event.preventDefault();
    dispatch(
      actionCreators.postTags(
        props.userData.username,
        {
          tag: tagInput,
        },
        "post",
        props.reloadCallback
      )
    );
    setTagInput("");
  };

  const handleTagDelete = (e, item) => {
    if (props.userData.is_own_profile) {
      dispatch(
        actionCreators.postTags(
          props.userData.username,
          {
            tag: item,
          },
          "delete",
          props.reloadCallback
        )
      );
    }
  };

  let tagInputForm = (
    <>
      <Form className="tag-input-form">
        <Form.Group className="message-box" controlId="formBasicEmail">
          <Form.Control
            value={tagInput}
            onChange={(e) => setTagInput(e.target.value)}
            type="text"
            autoComplete="off"
            placeholder={"EX:#food"}
          />
        </Form.Group>
        <Button
          className="send-button"
          onClick={addTag}
          type="submit"
          variant="sub"
        >
          add tag
        </Button>
      </Form>
    </>
  );
  let tagsDisplay = "";
  if (props.userData.tags) {
    tagsDisplay = props.userData.tags.map((item, index) => {
      return (
        <span
          onClick={(e) => handleTagDelete(e, item)}
          key={index}
          className="tag-container"
        >
          <Badge variant="secondary">
            {item} {props.userData.is_own_profile ? "x" : ""}
          </Badge>{" "}
        </span>
      );
    });
  }

  return (
    <div className="tags-display">
      <div className="tag-list">{tagsDisplay}</div>
      {props.userData.is_own_profile ? tagInputForm : ""}
    </div>
  );
}

export default TagsDisplay;
