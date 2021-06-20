function AboutMe(props) {
  return (
    <div className="about-me profile-card">
      <p className="card-title">About me </p>
      <p className="bio-text">{props.userData.biography}</p>
    </div>
  );
}

export default AboutMe;
