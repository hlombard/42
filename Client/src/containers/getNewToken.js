export const forceDisconect = () => {
  localStorage.removeItem("token");
  localStorage.removeItem("refresh_token");
  localStorage.removeItem("user_name");
  window.location.reload();
  return null;
};

export const getNewToken = async () => {
  return fetch("http://localhost:8080/api/refresh/", {
    method: "GET",
    mode: "cors",
    cache: "default",
    credentials: "same-origin",
    Origin: window.location.origin.toString(),
    headers: {
      Accept: "application/json, text/plain, */*",
      Authorization: localStorage.getItem("refresh_token"),
    },
    redirect: "follow",
    referrer: "no-referrer",
  })
    .then((res) => res.json())
    .then((res) => {
      if (res.toString().includes("expired")) {
        return forceDisconect();
      }
      localStorage.setItem("token", res.access_token);
      localStorage.setItem("refresh_token", res.refresh_token);
      return res;
    });
};
