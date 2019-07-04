
type pomodoroState =
| Pomodoro
| ShortBreak
| LongBreak;

type action =
| UpdateTime(pomodoroState, int) 
| Click;

type state = {
  pomodoroTime:int,
  shortBreakTime:int,
  longBreakTime:int
};

type settingInput = {
  name:string,
  timeType:pomodoroState
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) => 
  switch(action) {
    | UpdateTime(pomodoroState, time) => switch(pomodoroState) {
      | Pomodoro => {...state, pomodoroTime: time}
      | ShortBreak => {...state, shortBreakTime: time}
      | LongBreak => {...state, longBreakTime: time}
    }
    | _ => state
  },{pomodoroTime:1500, shortBreakTime: 300, longBreakTime: 900});


  let settingInputs = [|
   {name: "Pomodoro Time", timeType: Pomodoro},
   {name: "Short Break Time", timeType: ShortBreak},
   {name: "Long Break Time", timeType: LongBreak}
  |];

  let convertMinutesToSeconds = (minutes) => minutes * 60;

  let convertSecondsToMinutes = (seconds) => seconds / 60;

  let getTimeByTimeType = (timeType) => switch(timeType) {
    | Pomodoro => state.pomodoroTime
    | ShortBreak => state.shortBreakTime
    | LongBreak => state.longBreakTime
  };


  let updateSettingsTime = (time, event) => {
    let value = ReactEvent.Form.target(event)##value;
    dispatch(UpdateTime(time, convertMinutesToSeconds(value)));
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
                            onChange={e => updateSettingsTime(input.timeType, e)}
                            type_="text"
                            name="time"
                            value={input.timeType |> getTimeByTimeType |> convertSecondsToMinutes |>string_of_int}
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
              <div className="btn btn-primary">
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

        </div>
      </div>
    </div>
  </div>
}