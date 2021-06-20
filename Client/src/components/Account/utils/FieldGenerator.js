import React from "react";

const FieldGenerator = React.forwardRef((props, ref) => {
  let inputElement = null;

  switch (props.inputType) {
    case "select":
      inputElement = (
        <select
          defaultValue={props.preField}
          name={props.name}
          id={props.name}
          ref={ref}
        >
          {props.options.map((option) => {
            return (
              <option key={option.value} value={option.value}>
                {option.displayValue}
              </option>
            );
          })}
        </select>
      );
      break;
    case "checkbox":
      inputElement = (
        <input
          name={props.name}
          type={props.type}
          defaultChecked={props.preField}
          ref={ref}
        />
      );
      break;

    default:
      inputElement = (
        <input
          defaultValue={props.preField}
          name={props.name}
          type={props.type}
          ref={ref}
        />
      );
  }

  return (
    <span>
      <label>{props.label}</label>
      {inputElement}
    </span>
  );
});

export default FieldGenerator;

//   const checkValidity = (value, rules) => {
//     let isValid = true;
//     if (!rules) {
//       return true;
//     }

//     if (rules.required) {
//       isValid = value.trim() !== "" && isValid;
//     }

//     if (rules.minLength) {
//       isValid = value.length >= rules.minLength && isValid;
//     }

//     if (rules.maxLength) {
//       isValid = value.length <= rules.maxLength && isValid;
//     }

//     if (rules.isEmail) {
//       const pattern = /[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/;
//       isValid = pattern.test(value) && isValid;
//     }

//     if (rules.isNumeric) {
//       const pattern = /^\d+$/;
//       isValid = pattern.test(value) && isValid;
//     }

//     return isValid;
//   };
