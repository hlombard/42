import { useSelector, useDispatch } from "react-redux";
import { useEffect } from "react";
import { useForm } from "react-hook-form";
import * as actionCreators from "../../store/actions/actionCreators";

import FieldGenerator from "./utils/FieldGenerator";
import emailFields from "./utils/emailFieldsDescription";
import passwordFields from "./utils/passwordFieldsDescription";

function ModifyVerif(props) {
  const createError = useSelector((state) => state.profile.error);
  const FPError = useSelector((state) => state.account.FP_error);
  const userName = useSelector((state) => state.auth.userName);
  const dispatch = useDispatch();
  const { setError, register, errors, handleSubmit } = useForm({
    criteriaMode: "all",
  });
  let fieldsPayload = null;

  let errorResponse = null;
  if (props.type === "email" || props.type === "password")
    errorResponse = createError;
  else errorResponse = FPError;

  useEffect(() => {
    if (errors && errors[Object.keys(errors)[0]]) {
      errors[Object.keys(errors)[0]].ref.focus();
    }
    if (userName) dispatch(actionCreators.profileGetData(userName));
  }, []); // eslint-disable-line react-hooks/exhaustive-deps

  if (props.type === "email") fieldsPayload = emailFields;
  else if (props.type === "password" || props.type === "resetPassword")
    fieldsPayload = passwordFields;
  else if (props.type === "forgotPassword") {
    fieldsPayload = {
      Email: {
        name: "email",
        label: "Email",
        type: "email",
        required: true,
        inputType: "input",
      },
    };
  }

  const formElementsArray = [];

  for (let key in fieldsPayload) {
    formElementsArray.push({
      id: key,
      config: fieldsPayload[key],
    });
  }

  let renderFields = formElementsArray.map((field) => {
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
              field.config.name === "password_1" ||
              field.config.name === "password_2"
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

  const onFormSubmit = (data) => {
    if (props.type === "email" || props.type === "password") {
      dispatch(
        actionCreators.profileUpdate(
          userName,
          data,
          "Your " + props.type + " has been modified"
        )
      );
    }
    if (props.type === "forgotPassword") {
      dispatch(
        actionCreators.sendForgotPasswordMail(
          data,
          "An Email to reset your password has been send to " + data.email
        )
      );
    }
    if (props.type === "resetPassword") {
      dispatch(actionCreators.resetPassword(data, props.token, props.callback));
    }
  };

  if (errorResponse !== null && errorResponse.Errors) {
    let errors = errorResponse.Errors;
    Object.keys(errors).forEach((field) => {
      let messages = errors[field][0];
      setError(field, {
        type: "server",
        message: messages,
      });
    });
    if (props.type === "email" || props.type === "password") {
      dispatch(actionCreators.profileStart());
    }
    if (props.type === "forgotPassword" || props.type === "resetPassword") {
      dispatch(actionCreators.startForgotPassword());
    }
  }

  return (
    <form className="register-form" onSubmit={handleSubmit(onFormSubmit)}>
      {renderFields}
      <input type="submit" value="Submit" />
    </form>
  );
}

export default ModifyVerif;
