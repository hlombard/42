import axios from "axios";
import React, { useEffect } from "react";
import { useDispatch } from "react-redux";
import * as actionCreators from "../store/actions/actionCreators";
import { getNewToken, forceDisconect } from "./getNewToken";

function AuthService() {
  const dispatch = useDispatch();
  const token = localStorage.getItem("token");

  axios.defaults.headers.common["Authorization"] = token;
  axios.defaults.baseURL = "http://localhost:8080";

  useEffect(() => {
    setInterceptor();
  }, []); // eslint-disable-line react-hooks/exhaustive-deps

  const setInterceptor = () => {
    axios.interceptors.response.use(
      (response) => {
        return response;
      },
      (err) => {
        if (err.response && err.response.status !== 401) {
          return Promise.reject(err);
        }
        console.log("[JWT] TOKEN Expired");
        return new Promise((resolve, reject) => {
          const originalReq = err.config;
          if (
            err.response &&
            err.response.status === 401 &&
            err.config &&
            !err.config.__isRetryRequest
          ) {
            originalReq._retry = true;
            console.log("[JWT] Fetching a new TOKEN");

            let res = getNewToken()
              .then((res) => {
                dispatch(actionCreators.checkAuthStatus());
                originalReq.headers["Authorization"] = res.access_token;
                console.log("[JWT] Calling back last request with new token");
                return axios(originalReq);
              })
              .catch(function (error) {
                console.log(
                  "Il y a eu un problème avec l'opération fetch: " +
                    error.message
                );
                return forceDisconect();
              });
            resolve(res);
          }
          return Promise.reject(err);
        });
      }
    );
  };

  return <></>;
}

export default AuthService;
