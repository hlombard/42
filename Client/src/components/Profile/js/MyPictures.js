import PictureDisplay from "./PictureDisplay";
import "../css/MyPictures.scss";

function MyPictures(props) {
  return (
    <div className="my-pictures profile-card">
      <p className="card-title">My Pictures </p>
      <div className="picture-container">
        <PictureDisplay
          userData={props.userData}
          pictureId={2}
        ></PictureDisplay>
        <PictureDisplay
          userData={props.userData}
          pictureId={3}
        ></PictureDisplay>
        <PictureDisplay
          userData={props.userData}
          pictureId={4}
        ></PictureDisplay>
        <PictureDisplay
          userData={props.userData}
          pictureId={5}
        ></PictureDisplay>
      </div>
    </div>
  );
}

export default MyPictures;
