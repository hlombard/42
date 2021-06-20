import Modal from "react-bootstrap/Modal";
import Form from "react-bootstrap/Form";
import { useDispatch } from "react-redux";
import { useState } from "react";
import "../css/picture-display.scss";
import * as actionCreators from "../../../store/actions/actionCreators";

function PictureDisplay(props) {
  const [show, setShow] = useState(false);
  const [imageHash, setimageHash] = useState(Math.random());
  const dispatch = useDispatch();
  let imageRender = null;

  if (props.userData && props.userData.picture_1 && props.pictureId) {
    let imageUrl = props.userData["picture_" + String(props.pictureId)];
    imageRender = (
      <img
        className="profile-img"
        src={`${imageUrl}?${imageHash}`}
        alt="profile"
      />
    );
  }

  const handleClose = () => setShow(false);
  const handleShow = () => setShow(true);

  async function handleFileChange(e) {
    const file = e.target.files[0];
    setimageHash(Math.random());
    dispatch(
      actionCreators.postImage(
        String(props.pictureId),
        file,
        handleClose,
        props.userData.username
      )
    );
  }

  let render = null;
  if (props.userData.is_own_profile) {
    render = (
      <>
        <Modal show={show} onHide={handleClose}>
          <Modal.Header closeButton>
            <Modal.Title>Change my picture</Modal.Title>
          </Modal.Header>
          <Modal.Body>
            <Form>
              <div className="mb-3">
                <Form.File id="formcheck-api-custom" custom>
                  <Form.File.Input onChange={handleFileChange} />
                  <Form.File.Label data-browse="">
                    Choose a file to upload
                  </Form.File.Label>
                </Form.File>
              </div>
            </Form>
          </Modal.Body>
        </Modal>
        <div onClick={handleShow} className="active-modal">
          <img src={process.env.PUBLIC_URL + "/pen.png"} alt="modify" />
        </div>
        <span>{imageRender}</span>
      </>
    );
  } else {
    render = <span>{imageRender}</span>;
  }

  return <div className="picture-item">{render}</div>;
}
export default PictureDisplay;
