type pomodoroState =
| Pomodoro
| ShortBreak
| LongBreak;


type state = {
  running:bool,
  timer:int,
  initialTime:int,
  pomodoroState: pomodoroState,
  pomodoroCount: int,
  intervals: int,
  title:string,
};

type action = 
| Click(string)
| Tick
| CompletePomodoro
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

//Everything within this function gets updated on rerender
[@react.component]
let make = (~pomodoro, ~shortBreak, ~longBreak) => {
  let (state, dispatch) = React.useReducer((state, action) => 
  switch(action) {
    | Click(actionName) => switch(actionName) {
     | "pomodoro" => {...state, pomodoroState: Pomodoro, timer: pomodoro, initialTime: pomodoro}
     | "shortbreak" => {...state, pomodoroState: ShortBreak, timer: shortBreak, initialTime: shortBreak}
     | "longbreak" => {...state, pomodoroState: LongBreak, timer: longBreak, initialTime: longBreak}
     | _ => state
    }
    | Tick => {
      switch(state.timer) {
        | 0 => state
        | _ => {...state, timer: state.timer - 1}
      };
      // state.timer > 0 ? {...state, timer: state.timer - 1} : state;
    } 
    | Reset => {...state, timer: state.initialTime}
    | CompletePomodoro => {...state, pomodoroCount: state.pomodoroCount + 1}
  }, {running:false, title:"Add Task", pomodoroCount: 0, intervals:3,  timer:300, initialTime: 300, pomodoroState: Pomodoro});
  
  
  let stopTimer = () => {
    switch(intervalIdRef^) {
      | Some(intervalID) => {
        Js.Global.clearInterval(intervalID);
        intervalIdRef:=None
      }
      | None => ()
    };
  };

  let resetTimer = () => {
    stopTimer();
    dispatch(Reset);
  }

  let startTimer = () => {
    switch (intervalIdRef^) {
    | Some(_) => ()
    | None =>
      let intervalId =
        Js.Global.setInterval(
          () => {
            //State not updated here, because the function is run once on click
            //This function would only get a new state when you click, but is recreated
            // on rerender
            dispatch(Tick);
          },
          1000,
        );
      intervalIdRef := Some(intervalId);
    };
  };


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

  let getStatusString = (status) => switch(status) {
    | Pomodoro => "Pomodoro"
    | ShortBreak => "Short Break"
    | LongBreak => "Long Break"
  };



  let convertTimeToString = (time) => {
    let minutes = time / 60;
    let seconds = time mod 60;
    let strSeconds = seconds |> string_of_int;
    let strMinutes = minutes |> string_of_int;
    let displayMinutes = String.length(strMinutes) < 2 ? "0" ++ strMinutes : strMinutes;
    let displaySeconds = String.length(strSeconds) < 2 ? "0" ++ strSeconds : strSeconds;
    {j|$displayMinutes:$displaySeconds|j};
  };
  
  let handleTimeUpdate = (state) => {
    if (state.timer == 0) {
      if(state.pomodoroState == Pomodoro) {
        Js.log("Pomodoro Complete")
        dispatch(CompletePomodoro);
      };
      let remainderPomoCount = state.pomodoroCount / state.intervals;
      let statusTuple = (state.pomodoroState, remainderPomoCount);
      resetTimer()
      switch(statusTuple) {
        | (Pomodoro, 1) => dispatch(Click("shortbreak"))
        | (Pomodoro, 2) => dispatch(Click("shortbreak"))
        | (Pomodoro, 0) => dispatch(Click("longbreak"))
        | (ShortBreak, _) => dispatch(Click("pomodoro"))
        | (LongBreak, _) => dispatch(Click("pomodoro"))
        | (_, _) => ()
      };
    };
    let time = convertTimeToString(state.timer);
    let titleDisplay = {j|$time - NierPixel Pomodoro Timer|j};
    Utils.updateWindowTitle(titleDisplay);
  };

  let updateTask = () => {

  };


  handleTimeUpdate(state);
  /* Modal Area of the application */
  <div className="row">
    
    <div className="offset-4 col-4">
        <div className="col-12 text-center">
          <div className="btn-group">
          {
            List.mapi((index, command:command) => {
              <button onClick={(_) => {
                resetTimer();
                dispatch(Click(command.name))
                }} key={string_of_int(index)} className="btn btn-primary">
              {ReasonReact.string(command.uiName)}
              </button>;
            }, commands) |> Utils.listToReactArray;
          }
          </div>
        </div>
        <div className="col-12 text-center">
         <small className="pomodoro-state">{ReasonReact.string(getStatusString(state.pomodoroState))}</small>
          <hr className="standard-style"/>
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
              }, timerButtons) |> Utils.listToReactArray;
            }
          </div>
        </div>
    </div>
    <div className="col-12">
      <div className="offset-4 col-4">
         <hr className="standard-style" />
      </div>
      // Task View 
    <TaskView updateTask={updateTask} />
    </div>
  </div>
};