import React from "react";
import ReactDOM from "react-dom";
import "./index.css";
import "bootstrap/dist/css/bootstrap.min.css";
import App from "./containers/App";
import AuthService from "./containers/AuthService";
import reportWebVitals from "./reportWebVitals";
import { BrowserRouter } from "react-router-dom";

import { Provider } from "react-redux";
import { createStore, applyMiddleware, compose, combineReducers } from "redux";
import thunkMiddleware from "redux-thunk";
import accountReducer from "./store/reducers/account/accountReducer";
import authReducer from "./store/reducers/account/authReducer";
import profileReducer from "./store/reducers/profile/profileReducer";
import toastReducer from "./store/reducers/ui/toastReducer";
import suggestionReducer from "./store/reducers/profile/suggestionReducer";
import socketReducer from "./store/reducers/ui/socketReducer";
import wsMiddleware from "./store/middleware/wsMiddleware";

const composeEnhancers = window.__REDUX_DEVTOOLS_EXTENSION_COMPOSE__ || compose;

const rootReducer = combineReducers({
  account: accountReducer,
  auth: authReducer,
  profile: profileReducer,
  toast: toastReducer,
  suggestion: suggestionReducer,
  socket: socketReducer,
});

const middleware = [thunkMiddleware, wsMiddleware];

const store = createStore(
  rootReducer,
  composeEnhancers(applyMiddleware(...middleware))
);

ReactDOM.render(
  <Provider store={store}>
    <BrowserRouter>
      <AuthService></AuthService>
      <App />
    </BrowserRouter>
  </Provider>,
  document.getElementById("root")
);

reportWebVitals();
