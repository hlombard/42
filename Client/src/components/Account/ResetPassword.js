import ModifyVerif from "./ModifyVerif";
import { useSelector, useDispatch } from "react-redux";
import { withRouter, Redirect } from "react-router";
import * as actionCreators from "../../store/actions/actionCreators";

function ResetPassword(props) {
  const response = useSelector((state) => state.account.FP_password);
  const valid_reset = useSelector((state) => state.account.valid_reset);
  const isAuth = useSelector((state) => state.auth.isAuth);
  const token = localStorage.getItem("token");
  const dispatch = useDispatch();

  if (isAuth) {
    return <Redirect to={"/profile/" + localStorage.getItem("user_name")} />;
  }
  const redirectLogin = (message) => {
    dispatch(actionCreators.sendToast(message, "Account"));
    props.history.push("/account/login");
  };

  if (!isAuth && !token) {
    const query = new URLSearchParams(props.location.search);
    const token = query.get("token");

    if (token) {
      return (
        <div>
          <ModifyVerif
            type="resetPassword"
            callback={redirectLogin}
            token={token}
          ></ModifyVerif>
        </div>
      );
    }
  }
  if (response || valid_reset) {
    return <Redirect to="/account/login" />;
  }
  return (
    <div>
      <ModifyVerif type="forgotPassword"></ModifyVerif>
    </div>
  );
}

export default withRouter(ResetPassword);
