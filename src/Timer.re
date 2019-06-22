type pomodoroState =
| Pomodoro
| ShortBreak
| LongBreak;

type state = {
  running:bool,
  pomodoroState: pomodoroState
};

type action = 
| Click(string);

type timerButton = {
  name:string,
  action:string
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) => 
  switch(action) {
    | Click(actionName) => switch(actionName) {
     | "pomodoro" => {...state, pomodoroState: Pomodoro}
     | "shortbreak" => {...state, pomodoroState: ShortBreak}
     | "longbreak" => {...state, pomodoroState: Pomodoro}
     | _ => state
    } 
  }, {running:false, pomodoroState: Pomodoro})
  let commands = [];

  <div className="row">
    <div className="col-12">
    </div>
    <div className="col-12">
    </div>
    <div className="col-12">
      {ReasonReact.string("Timer Buttons")}
      <div className="btn-group">

      </div>
    </div>
  </div>
};