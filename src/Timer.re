type pomodoroState =
| Pomodoro
| ShortBreak
| LongBreak;

type task = {
  name: string,
  pomodori: int,
};

type state = {
  running:bool,
  timer:int,
  initialTime:int,
  pomodoroState: pomodoroState,
  currentTask:task,
  tasks: list(task)
};

type action = 
| Click(string)
| ClickTask(int)
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
    | ClickTask(taskIndex) => {...state, currentTask: List.nth(state.tasks, taskIndex)}
    | Tick => {...state, timer: state.timer  - 1}
    | Reset => {...state, timer: state.initialTime}
  }, {running:false, timer:300, initialTime: 300, pomodoroState: Pomodoro, tasks: [], currentTask:{name:"", pomodori:0}})
  
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

  let tasks = state.tasks;
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
    <br/>
    <div className="col-12 text-center">
      <h2> {ReasonReact.string("Task View")}</h2>
      <div className="row">
        <div className="col-12">
        {
          String.length(state.currentTask.name) > 0 ?
          (<div>
            <h4> {ReasonReact.string("Current Task")} </h4>
            <div className="row text-center">
              <div className="offset-4 col-4 text-center">
                <div className="card">
                  <div className="card-body">
                    <h5 className="card-title">
                      {ReasonReact.string(state.currentTask.name)}
                    </h5>
                    <a href="" className="btn btn-outline-primary">
                      {ReasonReact.string("Done")}
                    </a>
                  </div>
                </div>
              </div>
            </div>
          </div>) : ReasonReact.null
        } 
        </div>
        <div className="col-12">
          <h4> {ReasonReact.string("Tasks")} </h4>
          <div className="row">
            <div className="col-12">
              <ul className="list-group">
                {
                  List.mapi((index, task:task) => {
                    let taskName = task.name;
                    let pomodoriStr = task.pomodori |> string_of_int;
                    <li onClick={(_) => dispatch(ClickTask(index))} key={string_of_int(index)} className="list-group-item">
                      {ReasonReact.string({j|$taskName : $pomodoriStr|j})}
                    </li>;
                  }, tasks) |> listToReactArray;
                }
              </ul>
            </div>
          </div>
        </div>
      </div>
    </div>
  </div>
};