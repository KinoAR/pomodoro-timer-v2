type action = 
| Click;

type state = {
  pomodoroTime:int,
  shortBreakTime:int,
  longBreakTime:int
};


[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer((state, action) => 
  switch(action) {
    | _ => state
  },{pomodoroTime:1500, shortBreakTime: 300, longBreakTime: 900});

  <div className="row">
    <h2> {ReasonReact.string("Options")} </h2>
  </div>
}