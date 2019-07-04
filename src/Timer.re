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
  pomodoroCount: int,
  currentTask:task,
  taskNameInput:string,
  title:string,
  tasks: list(task)
};

type action = 
| Click(string)
| ClickTask(int)
| ClickNewTask(string)
| UpdateTaskName(string)
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

let createTask  = (taskName) => {
  {name:taskName, pomodori:0};
}


//Has to be outside of the component to prevent it 
//from being reinitialized on rerender
let intervalIdRef = ref(None);

//Everything within this function gets updated on rerender
[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) => 
  switch(action) {
    | Click(actionName) => switch(actionName) {
     | "pomodoro" => {...state, pomodoroState: Pomodoro, timer: 1500, initialTime: 1500}
     | "shortbreak" => {...state, pomodoroState: ShortBreak, timer: 300, initialTime: 300}
     | "longbreak" => {...state, pomodoroState: LongBreak, timer: 900, initialTime: 900}
     | _ => state
    }
    | ClickTask(taskIndex) => {...state, currentTask: List.nth(state.tasks, taskIndex)}
    | Tick => {
      switch(state.timer) {
        | 0 => state
        | _ => {...state, timer: state.timer - 1}
      };
      // state.timer > 0 ? {...state, timer: state.timer - 1} : state;
    } 
    | Reset => {...state, timer: state.initialTime}
    | CompletePomodoro => {...state, pomodoroCount: state.pomodoroCount + 1}
    | UpdateTaskName(taskName) => {...state, taskNameInput: taskName}
    | _ => state
  }, {running:false, title:"Add Task", pomodoroCount: 0, taskNameInput: "", timer:300, initialTime: 300, pomodoroState: Pomodoro, tasks: [], currentTask:{name:"", pomodori:0}})
  
  
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
  }

  let updateTaskName = (event) => {
    ReactEvent.Synthetic.preventDefault(event);
    let value = ReactEvent.Form.target(event);
    Js.log(value);
  }

  let tasks = state.tasks;
  let listToReactArray = (list) => list |> Array.of_list |> ReasonReact.array;
  
  let handleTimeUpdate = (state) => {
    if (state.timer == 0) {
      if(state.pomodoroState == Pomodoro) {
        Js.log("Pomodoro Complete")
        dispatch(CompletePomodoro);
      };
      let remainderPomoCount = state.pomodoroCount / 3;
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
  };

  handleTimeUpdate(state);
  /* Modal Area of the application */
  <div className="row">
    <div className="modal fade" id="pomodoroModal" role="dialog">
     <div className="modal-dialog" role="document">
      <div className="modal-content">
        <div className="modal-header">
          <div className="modal-title">
            {ReasonReact.string(state.title)}
          </div>
          {ReactDOMRe.createElementVariadic(
            "button",
            ~props=(ReactDOMRe.objToDOMProps({
              "data-dismiss": "modal",
              "type": "button",
              "className": "close",
              "aria-label": "Close"
              })),
            [|
              (<span ariaHidden={true}>{ReasonReact.string("Close")}</span>)
            |]
          )}
          </div>
          <div className="modal-body">
          {
            switch(state.title) {
              | "Add Task" => {
                <div className="row">
                  <div className="col-12">
                    <form action="">
                      <div className="form-group">
                        <label htmlFor="Task Name">{ReasonReact.string("Task Name")}</label>
                        <input onChange={(e) => updateTaskName(e)} type_="text" name="taskName" id="taskName" placeholder="Enter Task Name"/>
                      </div>
                    </form>
                  </div>
                </div>
              }
              | _ => ReasonReact.null
            }
          }
          </div>
          <div className="modal-footer">
          <div className="row">
          <br/>
          <div className="btn btn-primary"> {ReasonReact.string("Save Changes")} </div>(
            {
              ReactDOMRe.createElementVariadic(
                "button",
                ~props=
                  ReactDOMRe.objToDOMProps({
                    "data-dismiss": "modal",
                    "type": "button",
                    "className": "btn btn-secondary",
                    "aria-label": "Close",
                  }),
                [|ReasonReact.string("Close")|],
              );
            },
          )
          </div>
        </div>
      </div>
     </div>
    </div>
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
        <div className="col-12 task-area">
          <h4> {ReasonReact.string("Tasks")} </h4>
          <div className="row">
            <div className="col-12">
              <ul className="list-group">
                <li onClick={(_) => () } className="list-group-item task-area">
                  {ReasonReact.string("Add a new task")}
                  {
                    ReactDOMRe.createElementVariadic(
                      "button",
                      ~props=
                        ReactDOMRe.objToDOMProps({
                          "data-toggle": "modal",
                          "data-target": "#pomodoroModal",
                          "type": "button",
                          "className": "btn btn-secondary",
                        }),
                      [|ReasonReact.string("Add Task")|],
                    );
                  }
                </li>
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