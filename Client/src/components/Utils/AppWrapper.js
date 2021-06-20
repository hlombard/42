import { Redirect, Switch, Route } from "react-router-dom";
import { useDispatch, useSelector } from "react-redux";
import Profile from "../Profile/js/Profile";
import Settings from "../Profile/js/Settings";
import ModifyInfo from "../Account/ModifyInfo";
import ModifyVerif from "../Account/ModifyVerif";
import SuggestionList from "../Suggestion/SuggestionList";
import Search from "../Suggestion/Search";
import MatchList from "../Match/js/MatchList";
import GenericNotFound from "../Utils/GenericNotFound";
import * as actionCreators from "../../store/actions/actionCreators";

function AppWrapper() {
  const isAuth = useSelector((state) => state.auth.isAuth);
  const dispatch = useDispatch();

  const token = localStorage.getItem("token");
  const refresh_token = localStorage.getItem("refresh_token");
  dispatch(actionCreators.checkAuthStatus());
  if (!isAuth && !token && !refresh_token) {
    return <Redirect to="/account/login" />;
  }
  return (
    <div>
      <Switch>
        <Route path="/profile/:username/settings/password">
          <ModifyVerif type="password"></ModifyVerif>
        </Route>
        <Route path="/profile/:username/settings/email">
          <ModifyVerif type="email"></ModifyVerif>
        </Route>
        <Route path="/profile/:username/settings/info">
          <ModifyInfo></ModifyInfo>
        </Route>
        <Route path="/profile/:username/settings">
          <Settings></Settings>
        </Route>
        <Route path="/profile/:username">
          <Profile></Profile>
        </Route>
        <Route path="/home/match">
          <MatchList></MatchList>
        </Route>
        <Route path="/home/suggestion">
          <SuggestionList></SuggestionList>
        </Route>
        <Route path="/home/search">
          <Search></Search>
        </Route>
        <Route path="/404" component={GenericNotFound} />
        <Redirect to="/404" />
      </Switch>
    </div>
  );
}

export default AppWrapper;
