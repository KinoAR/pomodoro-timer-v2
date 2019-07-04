
type task = {
  name:string,
  pomodori:int
};

type state = {
  title: string,
  tasks: list(task),
  currentTaskName:string,
  currentTask:option(task),
};

type action = 
| UpdateTaskName(string)
| ClickRemoveTask(task, int)
| ClickNewTask(string)
| ClickAddTask(task)
| ClickMakeCurrentTask(task)
| ClickTask(int);

let addElementToList = (list, element) => {
  let arr = list |> Array.of_list;
  arr |> Js.Array.push(element, _) |> ignore;
  arr |> Array.to_list;
};

[@react.component]
let make = (~updateTask) => {
  let (state, dispatch) = React.useReducer((state, action) => {
    switch(action) {
      | UpdateTaskName(name) => {...state, currentTaskName:name}
      | ClickTask(_) => state
      | ClickAddTask(task) => {...state, tasks: addElementToList(state.tasks, task)}
      | ClickRemoveTask(task, int) => state
      | ClickMakeCurrentTask(task) => {...state, currentTask: Some(task)}
      | _ => state
    }
  }, {title: "Add Task", currentTaskName:"", tasks: [], currentTask: None});

   let updateTaskName = event => {
     ReactEvent.Synthetic.preventDefault(event);
     let value = ReactEvent.Form.target(event);
     Js.log(value);
   };


   <div className="row">
   // Modal View

   <div className="modal fade" id="pomodoroModal" role="dialog">
     <div className="modal-dialog" role="document">
       <div className="modal-content">
         <div className="modal-header">
           <div className="modal-title"> {ReasonReact.string(state.title)} </div>
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
           {switch (state.title) {
            | "Add Task" =>
              <div className="row">
                <div className="col-12">
                  <form action="">
                    <div className="form-group">
                      <label htmlFor="Task Name">
                        {ReasonReact.string("Task Name")}
                      </label>
                      <input
                        className="form-control"
                        onChange={e => updateTaskName(e)}
                        type_="text"
                        name="taskName"
                        id="taskName"
                        placeholder="Enter Task Name"
                      />
                    </div>
                  </form>
                </div>
              </div>
            | _ => ReasonReact.null
            }}
         </div>
         <div className="modal-footer">
           <div className="row">
             <br />
             <div className="btn btn-primary"> {ReasonReact.string("Add")} </div>
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
      <h2> {ReasonReact.string("Task View")} </h2>
      <div className="row">
        // <div className="col-12">
        //   {String.length(state.currentTask.name) > 0
        //      ? <div>
        //          <h4> {ReasonReact.string("Current Task")} </h4>
        //          <div className="row text-center">
        //            <div className="offset-4 col-4 text-center">
        //              <div className="card">
        //                <div className="card-body">
        //                  <h5 className="card-title">
        //                    {ReasonReact.string(state.currentTask.name)}
        //                  </h5>
        //                  <a href="" className="btn btn-outline-primary">
        //                    {ReasonReact.string("Done")}
        //                  </a>
        //                </div>
        //              </div>
        //            </div>
        //          </div>
        //        </div>
        //      : ReasonReact.null}
        // </div>
        <div className="col-12 task-area">
          <h4> {ReasonReact.string("Tasks")} </h4>
          <div className="row">
            <div className="col-12">
              <ul className="list-group">
                <li onClick={_ => ()} className="list-group-item task-area">
                  {ReasonReact.string("Add a new task")}
                  <br />
                  {ReactDOMRe.createElementVariadic(
                     "button",
                     ~props=
                       ReactDOMRe.objToDOMProps({
                         "data-toggle": "modal",
                         "data-target": "#pomodoroModal",
                         "type": "button",
                         "className": "btn btn-secondary",
                       }),
                     [|ReasonReact.string("Add Task")|],
                   )}
                </li>
                {List.mapi(
                   (index, task: task) => {
                     let taskName = task.name;
                     let pomodoriStr = task.pomodori |> string_of_int;
                     <li
                       onClick={_ => dispatch(ClickTask(index))}
                       key={string_of_int(index)}
                       className="list-group-item">
                       {ReasonReact.string({j|$taskName : $pomodoriStr|j})}
                     </li>;
                   },
                   state.tasks,
                 )
                 |> Utils.listToReactArray}
              </ul>
            </div>
          </div>
        </div>
      </div>
    </div>
   </div>
};