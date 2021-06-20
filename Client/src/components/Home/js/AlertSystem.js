import { useSelector, useDispatch } from "react-redux";
import * as actionCreators from "../../../store/actions/actionCreators";

import Toast from "react-bootstrap/Toast";
import "../css/Alert.scss";

function AlertSystem(props) {
  const dispatch = useDispatch();
  const showToast = useSelector((state) => state.toast.showToast);
  const title = useSelector((state) => state.toast.title);
  const message = useSelector((state) => state.toast.message);

  return (
    <div className="alert-container">
      <Toast
        onClose={() => dispatch(actionCreators.resetToast())}
        show={showToast}
        className="notif-toast"
        autohide
      >
        <Toast.Header>
          <strong className="mr-auto">{title}</strong>
        </Toast.Header>
        <Toast.Body>{message}</Toast.Body>
      </Toast>
    </div>
  );
}
export default AlertSystem;
