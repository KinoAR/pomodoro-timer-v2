type window;
type document;
// [@bs.set] external setWindowTitle: string => unit = "";
[@bs.val] external window: window = "";
[@bs.get] external document: (window) => document = "";
[@bs.set] external title: (document, string) => unit = "";


let updateWindowTitle = (windowTitle) => window |> document |> title(_, windowTitle);
 let listToReactArray = list => list |> Array.of_list |> ReasonReact.array;