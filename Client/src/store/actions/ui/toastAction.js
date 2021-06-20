import * as actionTypes from "../actionTypes";

export const sendToast = (message, title) => {
  return {
    type: actionTypes.SEND_TOAST,
    message: message,
    title: title,
  };
};

export const resetToast = () => {
  return {
    type: actionTypes.RESET_TOAST,
  };
};
