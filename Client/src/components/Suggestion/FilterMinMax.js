function FilterMinMax(props) {
  const setValue = (set, value) => {
    if (value) set(value);
    else set("0");
    set(value);
  };

  return (
    <div>
      <label htmlFor={props.id + "-min"}>{props.minLabel}</label>
      <input
        type="number"
        id={props.id + "-min"}
        value={props.minValue}
        onChange={(e) => setValue(props.setMinValue, e.target.value)}
        min={props.minSelectable}
        max={props.maxSelectable}
      />
      {"maxValue" in props && (
        <>
          <label htmlFor={props.id + "-max"}>{props.maxLabel}</label>
          <input
            type="number"
            id={props.id + "-max"}
            value={props.maxValue}
            onChange={(e) => setValue(props.setMaxValue, e.target.value)}
            min={props.minSelectable}
            max={props.maxSelectable}
          />
        </>
      )}
    </div>
  );
}
export default FilterMinMax;
