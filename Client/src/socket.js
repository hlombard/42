const URL = "ws://localhost:8081/ws/";
const initSocket = () => {
  const token = localStorage.getItem("token");
  if (token) {
    const socket = new WebSocket(URL + token);
    return socket;
  }
  return null;
};

export default initSocket;
