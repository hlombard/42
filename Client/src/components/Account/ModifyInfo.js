import React from "react";
import { useForm } from "react-hook-form";
import FieldGenerator from "./utils/FieldGenerator";
import { withRouter } from "react-router-dom";
import { useSelector, useDispatch } from "react-redux";
import * as actionCreators from "../../store/actions/actionCreators";
import payload from "./utils/accountChangeInfo";

import "./Register.css";
import { useEffect } from "react";

function ModifyInfo(props) {
  const createError = useSelector((state) => state.profile.error);
  const userData = useSelector((state) => state.profile.userData);
  const userName = useSelector((state) => state.auth.userName);
  const dispatch = useDispatch();
  const { setError, register, errors, handleSubmit } = useForm({
    criteriaMode: "all",
  });

  useEffect(() => {
    if (errors && errors[Object.keys(errors)[0]]) {
      errors[Object.keys(errors)[0]].ref.focus();
    }
    dispatch(actionCreators.profileGetData(userName));
  }, []); // eslint-disable-line react-hooks/exhaustive-deps

  const formElementsArray = [];

  if (userData) {
    for (let key in payload) {
      let prefield = "";
      if (key === "Email1") {
        prefield = userData.email;
      } else if (key === "AuthoriseGPS") {
        prefield = userData[payload[key].name];
      } else if (userData[payload[key].name]) {
        prefield = userData[payload[key].name];
      }
      formElementsArray.push({
        id: key,
        config: payload[key],
        value: prefield,
      });
    }
  }

  let fields = formElementsArray.map((field) => {
    return (
      <div key={field.id}>
        <FieldGenerator
          inputType={field.config.inputType}
          label={field.config.label}
          name={field.config.name}
          options={field.config.options}
          type={field.config.type}
          preField={field.value}
          ref={register({
            required: field.config.required
              ? field.config.label + " is required."
              : false,
            validate:
              field.config.name === "password"
                ? {
                    isUpper: (value) =>
                      /(?=.*[A-Z])/.test(value) ||
                      "Password must contain at least 1 uppercase character.",
                    asNumber: (value) =>
                      /(?=.*\d)/.test(value) ||
                      "Password must contain at least 1 number.",
                    asSpecialChar: (value) =>
                      /(?=.*\W)/.test(value) ||
                      "Password must contain at least 1 special character.",
                    asHeightLetters: (value) =>
                      ((value || "").match(/[a-zA-Z]/g) || []).length >= 8 ||
                      "Password must contain at least 8 letters.",
                  }
                : null,
            maxLength: field.config.maxlength,
            valueAsDate: field.config.type === "date",
          })}
        ></FieldGenerator>
        <p>{errors[field.config.name] && errors[field.config.name].message}</p>
      </div>
    );
  });

  const onSubmit = (data) => {
    dispatch(
      actionCreators.profileUpdate(
        userName,
        data,
        "Your settings has been changed"
      )
    );
    dispatch(actionCreators.profileGetData(userName));
  };

  if (createError !== null && createError.Errors) {
    let errors = createError.Errors;
    Object.keys(errors).forEach((field) => {
      const messages = errors[field][0];
      setError(field, {
        type: "server",
        message: messages,
      });
    });
    dispatch(actionCreators.profileStart());
  }

  return (
    <form className="register-form" onSubmit={handleSubmit(onSubmit)}>
      {fields}
      <input type="submit" value="Submit" />
    </form>
  );
}

export default withRouter(ModifyInfo);
