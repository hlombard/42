import React from "react";
import { useForm } from "react-hook-form";
import FieldGenerator from "./utils/FieldGenerator";
import { Redirect, withRouter } from "react-router-dom";
import { useSelector, useDispatch } from "react-redux";
import * as actionCreators from "../../store/actions/actionCreators";
import payload from "./utils/accountBaseInfo";

import "./Register.css";
import { registerStart } from "../../store/actions/account/accountAction";
import { useEffect } from "react";

function Register(props) {
  //let payload = {};
  const createReponse = useSelector((state) => state.account.response);
  const createError = useSelector((state) => state.account.error);
  const isAuth = useSelector((state) => state.auth.isAuth);
  const dispatch = useDispatch();
  const { setError, register, errors, handleSubmit } = useForm({
    criteriaMode: "all",
  });

  useEffect(() => {
    if (errors && errors[Object.keys(errors)[0]]) {
      errors[Object.keys(errors)[0]].ref.focus();
    }
    dispatch(registerStart());
  });

  if (isAuth) {
    return <Redirect to={"/profile/" + localStorage.getItem("user_name")} />;
  }
  if (createReponse) {
    return <Redirect to="/account/register/emailverify" />;
  }

  const formElementsArray = [];
  for (let key in payload) {
    formElementsArray.push({
      id: key,
      config: payload[key],
    });
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
    dispatch(actionCreators.registerCreate(data));
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
    dispatch(registerStart());
  }

  return (
    <form className="register-form" onSubmit={handleSubmit(onSubmit)}>
      {fields}
      <input type="submit" value="Register" />
    </form>
  );
}

export default withRouter(Register);
