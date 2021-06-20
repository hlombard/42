import { useForm } from "react-hook-form";
import { useEffect } from "react";
import FieldGenerator from "./utils/FieldGenerator";
import { NavLink, Redirect } from "react-router-dom";
import "./Login.css";
import { useDispatch, useSelector } from "react-redux";
import * as actionCreators from "../../store/actions/actionCreators";

function Login(props) {
  const authError = useSelector((state) => state.auth.error);
  const isAuth = useSelector((state) => state.auth.isAuth);
  const dispatch = useDispatch();
  const { setError, register, handleSubmit, errors } = useForm({
    criteriaMode: "all",
  });
  let field_payload = {
    Login: {
      name: "username",
      label: "Login",
      type: "text",
      inputType: "input",
      required: true,
      option: [],
      maxLength: 255,
    },
    Password: {
      name: "password",
      label: "Password",
      type: "password",
      inputType: "input",
      required: true,
      option: [],
      maxLength: 255,
    },
  };

  useEffect(() => {
    if (errors && errors[Object.keys(errors)[0]]) {
      errors[Object.keys(errors)[0]].ref.focus();
    }
  }, []); // eslint-disable-line react-hooks/exhaustive-deps

  if (isAuth) {
    return <Redirect to={"/profile/" + localStorage.getItem("user_name")} />;
  }

  let errorResponse = authError;

  const formElementsArray = [];
  for (let key in field_payload) {
    formElementsArray.push({
      id: key,
      config: field_payload[key],
    });
  }

  let fields = formElementsArray.map((field) => {
    return (
      <div key={field.id}>
        <FieldGenerator
          key={field.id}
          inputType={field.config.inputType}
          label={field.config.label}
          name={field.config.name}
          options={field.config.options}
          type={field.config.type}
          ref={register({
            required: field.config.required
              ? field.config.label + " is required."
              : false,
            maxLength: field.config.maxlength,
            valueAsDate: field.config.type === "date",
          })}
        ></FieldGenerator>
        <p>{errors[field.config.name] && errors[field.config.name].message}</p>
      </div>
    );
  });

  const onSubmit = (data) => {
    dispatch(actionCreators.authCreate(data));
  };

  if (errorResponse !== null && errorResponse.Errors) {
    let errors = errorResponse.Errors;
    Object.keys(errors).forEach((field) => {
      const messages = errors[field][0];
      setError(field, {
        type: "server",
        message: messages,
      });
    });
    dispatch(actionCreators.authStart());
  }

  return (
    <div>
      <form className="login-form" onSubmit={handleSubmit(onSubmit)}>
        {fields}
        <input className="login-submit" type="submit" value="Login" />
        <div className="other-link">
          <NavLink to="/account/register">Register</NavLink>
          <NavLink to="/account/reset_Password">Forgot Password</NavLink>
        </div>
      </form>
    </div>
  );
}

export default Login;
