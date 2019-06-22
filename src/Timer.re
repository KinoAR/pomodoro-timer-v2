type pomodoroState =
| Pomodoro
| ShortBreak
| LongBreak;

type state = {
  running:bool,
  pomodoroState: pomodoroState
};

type action = 
| ClickPomodoro
| ClickShortBreak
| ClickLongBreak;

type timerButton = {
  name:string,
  action:string
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) => 
  switch(action) {
    | ClickPomodoro => {...state, pomodoroState: Pomodoro}
    | ClickShortBreak => {...state, pomodoroState: ShortBreak}
    | ClickLongBreak => {...state, pomodoroState: LongBreak}
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