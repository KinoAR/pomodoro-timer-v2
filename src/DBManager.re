open ParseAPI;
open Js.Promise;

let parse  = ParseAPI.make;
let object_ = parse -> Parse.object_;
let query = parse -> Parse.query;

let createTask = (taskName, taskDescription) =>  {
  let task = PObject.make("Task");
  task -> PObject.set("name", taskName) |> ignore;
  task -> PObject.set("description", taskDescription) |> ignore;
  PObject.save(task) 
  |> then_((result) => {
    Js.log2(result, "New Task created on the back end") |> resolve;
  })
  |> catch(Utils.logErrorResolve) |> ignore;
};