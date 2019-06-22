type pomodoroState =
| Pomodoro
| ShortBreak
| LongBreak;

type state = {
  running:bool,
  timer:int,
  pomodoroState: pomodoroState
};

type action = 
| Click(string);

type command = {
  name:string,
  uiName:string
};

type timerButton = {
  name:string,
  className:string,
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
  }, {running:false, timer:300, pomodoroState: Pomodoro})
  let commands = [
    {name:"pomodoro", uiName: "Pomodoro"},
    {name:"shortBreak", uiName: "Short Break"}, 
    {name: "longbreak", uiName: "Long Break"}
  ];

  let convertTimeToString = (time) => {
    let minutes = time / 60;
    let seconds = time mod 60;
    let strSeconds = seconds |> string_of_int;
    let displaySeconds = String.length(strSeconds) < 2 ? strSeconds ++ "0" : strSeconds;
    {j|$minutes:$displaySeconds|j};
  }

  let timerButtons = [
    {name: "Start", className:"btn-success"},
    {name: "Stop", className: "btn-danger"},
    {name: "Reset", className: "btn-secondary"}
  ];
  let listToReactArray = (list) => list |> Array.of_list |> ReasonReact.array;

  <div className="row">
    <div className="offset-4 col-4">
        <div className="col-12 text-center">
          <div className="btn-group">
          {
            List.mapi((index, command:command) => {
              <button  key={string_of_int(index)} className="btn btn-primary">
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
                <button  key={string_of_int(index)} className={j|btn $className|j}>
                {ReasonReact.string(button.name)}
                </button>
              }, timerButtons) |> listToReactArray;
            }
          </div>
        </div>
    </div>
  </div>
};