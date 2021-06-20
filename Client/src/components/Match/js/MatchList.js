import { useSelector } from "react-redux";
import MatchDisplay from "./MatchDisplay";

import "../css/MatchList.scss";

function MatchList(props) {
  const matchData = useSelector((state) => state.socket.matchData);

  let render = (
    <>
      <p>You don't have any match.</p>
      <p>Like some profile to get a chance to match with someone</p>
    </>
  );
  if (matchData) {
    render = matchData.map((item) => {
      return (
        <MatchDisplay key={item.username} user={item.username}></MatchDisplay>
      );
    });
  }
  return <div className="match-list">{render}</div>;
}

export default MatchList;
