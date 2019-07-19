type window;
type document;
// [@bs.set] external setWindowTitle: string => unit = "";
[@bs.val] external window: window = "";
[@bs.get] external document: (window) => document = "";
[@bs.set] external title: (document, string) => unit = "";


let updateWindowTitle = (windowTitle) => window |> document |> title(_, windowTitle);
let listToReactArray = list => list |> Array.of_list |> ReasonReact.array;
let rStr = (string) => ReasonReact.string(string);

let logErrorResolve = err => {
  Js.log2("Error: ", err) |> Js.Promise.resolve;
};

let nullableToString = string =>
  switch (string |> Js.Nullable.toOption) {
  | Some(string) => string
  | None => ""
  };

  let spaceForWeb = str => {
    let re = Js.Re.fromStringWithFlags("\s", ~flags="ig");
    str |> Js.String.replaceByRe(re, "%20");
  };

  let resolveEmpty = Js.Promise.resolve(Js.Undefined.empty);