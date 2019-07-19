type state = {
  name:string,
  description:string,
  pomodoroEstimate:int,
  pomodoroActual:int,
};

type action = 
| UpdateOnChange(string);


let rStr = (string) => ReasonReact.string(string);

[@react.component]
let make = (~name, ~description, ~estimate:int, ~actual:int) => {
  let (state, dispatch) = React.useReducer((state, action) => 
    switch(action) {
      | UpdateOnChange(text) => switch(text) {
        | "name" => {...state, name: text}
        | "description" => {...state, description: text}
        | "pomodoroEstimate" => {...state, pomodoroEstimate: int_of_string(text)}
        | "pomodoroActual" => {...state, pomodoroActual: int_of_string(text)}
        | _ => state
      }
    
  }, {name: "", description: "", pomodoroEstimate: 0, pomodoroActual: 0});

  
  <div className="row">
    <div className="form-row">
      <div className="col-4">
        <input onChange={ (_) => dispatch(UpdateOnChange("name"))} value={name} type_="text" name="name" placeholder="Task Name"/>
      </div>
      <div className="col-4">
        <input onChange={(_) => dispatch(UpdateOnChange("description"))}  value={description} type_="text" name="description" placeholder="Task Description" />
      </div>
      <div className="col-1">
          <input
            onChange={_ => dispatch(UpdateOnChange("description"))}
            value={estimate |> string_of_int}
            type_="text"
            name="estimate"
            placeholder="Pomodoro Estimate"
          />
      </div>
      <div className="col-1">
        <input
          onChange={_ => dispatch(UpdateOnChange("description"))}
          value={actual |> string_of_int}
          type_="text"
          name="actual"
          placeholder="Pomodoro Estimate"
        />
      </div>
      <div className="col-1 text-center">
        <button className="btn btn-primary">
          {rStr("Save")}
        </button>
      </div>
      <div className="col-1 text-center">
        <button className="btn btn-danger">
          {rStr("Remove")}
        </button> 
      </div>
    </div>
  </div>;
}




