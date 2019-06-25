type pomodoroState =
| Pomodoro
| ShortBreak
| LongBreak;

type state = {
  running:bool,
  timer:int,
  initialTime:int,
  pomodoroState: pomodoroState
};

type action = 
| Click(string)
| Tick
| Reset;

type command = {
  name:string,
  uiName:string
};

type timerButton = {
  name:string,
  className:string,
  fn: unit => unit
};
//Has to be outside of the component to prevent it 
//from being reinitialized on rerender
let intervalIdRef = ref(None);

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) => 
  switch(action) {
    | Click(actionName) => switch(actionName) {
     | "pomodoro" => {...state, pomodoroState: Pomodoro, timer: 1500, initialTime: 1500}
     | "shortbreak" => {...state, pomodoroState: ShortBreak, timer: 300, initialTime: 900}
     | "longbreak" => {...state, pomodoroState: LongBreak, timer: 900, initialTime: 900}
     | _ => state
    }
    | Tick => {...state, timer: state.timer  - 1}
    | Reset => {...state, timer: state.initialTime}
  }, {running:false, timer:300, initialTime: 300, pomodoroState: Pomodoro})
  
  let startTimer = () => {
    switch(intervalIdRef^) {
      | Some(_) => ()
      | None => {
        let intervalId = Js.Global.setInterval(() => dispatch(Tick), 1000);
        intervalIdRef := Some(intervalId);
      }
    };
  };

  let stopTimer = () => {
    switch(intervalIdRef^) {
      | Some(intervalID) => Js.Global.clearInterval(intervalID)
      | None => ()
    };
  };

  let resetTimer = () => {
    stopTimer();
    dispatch(Reset);
  }

  let commands = [
    {name:"pomodoro", uiName: "Pomodoro"},
    {name:"shortbreak", uiName: "Short Break"}, 
    {name: "longbreak", uiName: "Long Break"}
  ];

  let timerButtons = [
    {name: "Start", className: "btn-success", fn: startTimer},
    {name: "Stop", className: "btn-danger", fn: stopTimer},
    {name: "Reset", className: "btn-secondary", fn:resetTimer},
  ];



  let convertTimeToString = (time) => {
    let minutes = time / 60;
    let seconds = time mod 60;
    let strSeconds = seconds |> string_of_int;
    let strMinutes = minutes |> string_of_int;
    let displayMinutes = String.length(strMinutes) < 2 ? "0" ++ strMinutes : strMinutes;
    let displaySeconds = String.length(strSeconds) < 2 ? strSeconds ++ "0" : strSeconds;
    {j|$displayMinutes:$displaySeconds|j};
  }

  
  let listToReactArray = (list) => list |> Array.of_list |> ReasonReact.array;

  <div className="row">
    <div className="offset-4 col-4">
        <div className="col-12 text-center">
          <div className="btn-group">
          {
            List.mapi((index, command:command) => {
              <button onClick={(_) => dispatch(Click(command.name))} key={string_of_int(index)} className="btn btn-primary">
              {ReasonReact.string(command.uiName)}
              </button>;
            }, commands) |> listToReactArray;
          }
          </div>
        </div>
        <div className="col-12 text-center">
          <h1 className="pomodoro-timer">
            {ReasonReact.string(convertTimeToString(state.timer))}
          </h1>
        </div>
        <div className="col-12 text-center"> 
          <div className="btn-group">
            {
              List.mapi((index, button: timerButton) => {
                let className = button.className;
                <button onClick={(_) => button.fn()}  key={string_of_int(index)} className={j|btn $className|j}>
                {ReasonReact.string(button.name)}
                </button>
              }, timerButtons) |> listToReactArray;
            }
          </div>
        </div>
    </div>
  </div>
};