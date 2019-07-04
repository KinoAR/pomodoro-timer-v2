
type pomodoroState =
| Pomodoro
| ShortBreak
| LongBreak;

type action =
| UpdateTime
| UpdateTempTime(pomodoroState, int)
| Click;

type state = {
  pomodoroTime:int,
  tempPomodoroTime:int,
  shortBreakTime:int,
  tempShortBreakTime:int,
  longBreakTime:int,
  tempLongBreakTime:int,
};

type settingInput = {
  name:string,
  id:string,
  timeType:pomodoroState
};

[@react.component]
let make = (~timerFunc) => {
  let (state, dispatch) = React.useReducer((state, action) => 
  switch(action) {
    | UpdateTempTime(pomodoroState, time) => switch(pomodoroState) {
      | Pomodoro => {...state, tempPomodoroTime: time}
      | ShortBreak => {...state, tempShortBreakTime: time}
      | LongBreak => {...state, tempLongBreakTime: time}
    }
    | UpdateTime => {
     {...state, pomodoroTime: state.tempPomodoroTime, shortBreakTime: state.tempShortBreakTime, longBreakTime: state.tempLongBreakTime}
    }
    | _ => state
  },{pomodoroTime:1500, tempPomodoroTime: 1500, shortBreakTime: 300, tempShortBreakTime: 300, longBreakTime: 900, tempLongBreakTime: 900});


  let settingInputs = [|
   {name: "Pomodoro Time", id:"pomodoroTime", timeType: Pomodoro},
   {name: "Short Break Time", id: "shortBreakTime", timeType: ShortBreak},
   {name: "Long Break Time", id: "longBreakTime",timeType: LongBreak}
  |];

  let convertMinutesToSeconds = (minutes) => minutes * 60;

  let convertSecondsToMinutes = (seconds) => seconds / 60;

  let getTimeByTimeType = (timeType) => switch(timeType) {
    | Pomodoro => state.pomodoroTime
    | ShortBreak => state.shortBreakTime
    | LongBreak => state.longBreakTime
  };

  let updateSettingsTempTime = (time, event) => {
    let value = ReactEvent.Form.target(event)##value;
    dispatch(UpdateTempTime(time, convertMinutesToSeconds(value)))
  };

  //Modal Area of the application
  
  <div className="row">
    <div className="modal fade" id="settingsModal" role="dialog">
      <div className="modal-dialog" role="document">
        <div className="modal-content">
          <div className="modal-header">
            <div className="modal-title"> {ReasonReact.string("Settings")} </div>
            {ReactDOMRe.createElementVariadic(
               "button",
               ~props=
                 ReactDOMRe.objToDOMProps({
                   "data-dismiss": "modal",
                   "type": "button",
                   "className": "close",
                   "aria-label": "Close",
                 }),
               [|<span ariaHidden=true> {ReasonReact.string("Close")} </span>|],
             )}
          </div>
          <div className="modal-body">
               <div className="row">
                <div className="col-12">
                  <h2> {ReasonReact.string("Time Settings")}</h2>
                </div>
                 <div className="col-12">
                   <form action="">
                     {
                       settingInputs |> Array.mapi((index, input) => {
                         <div key={string_of_int(index)} className="form-group">
                          <label htmlFor="Time"> {ReasonReact.string(input.name)} </label>
                          <input
                            className="form-control"
                            onChange={e => updateSettingsTempTime(input.timeType, e)}
                            type_="text"
                            name="time"
                            // value={input.timeType |> getTimeByTimeType |> convertSecondsToMinutes |>string_of_int}
                          />
                         </div>;
                       }) |> React.array;
                     }
                   </form>
                 </div>
               </div>
             
          </div>
          <div className="modal-footer">
            <div className="row">
              <br />
              <div onClick={_ => dispatch(UpdateTime)} className="btn btn-primary">
                {ReasonReact.string("Save Changes")}
              </div>
              {ReactDOMRe.createElementVariadic(
                 "button",
                 ~props=
                   ReactDOMRe.objToDOMProps({
                     "data-dismiss": "modal",
                     "type": "button",
                     "className": "btn btn-secondary",
                     "aria-label": "Close",
                   }),
                 [|ReasonReact.string("Close")|],
               )}
            </div>
          </div>
        </div>
      </div>
    </div>
    <div className="col-12 text-center">
      <h2> {ReasonReact.string("Options")} </h2>
      <div className="row">
        <div className="col-12">
          {
            ReactDOMRe.createElementVariadic(
              "button",
              ~props=
                ReactDOMRe.objToDOMProps({
                  "data-toggle": "modal",
                  "data-target": "#settingsModal",
                  "type": "button",
                  "className": "btn btn-secondary",
                }),
              [|ReasonReact.string("Settings")|],
            );
          }
        </div>
      </div>
    </div>
    
    <div className="col-12">
        <br/>
        {
          timerFunc(
            ~pomodoro=state.pomodoroTime,
            ~shortBreak=state.shortBreakTime,
            ~longBreak=state.longBreakTime,
          );
        }
    </div>
 </div>
}