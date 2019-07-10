/* Parse Node.JS Bindings */
type parse;
type appId = string;
type jsKey = string;
type masterKey = string;
type parseObject;
type parseObjectInstance;
type parseUser = parseObject;
type parseQuery;
type username = string;
type password = string;
type valueResolvable;

[@bs.module] external make: parse = "parse";

module ValueResolvable = {
  type t = valueResolvable;
  external ofString: string => t = "%identity";
  external ofInt: int => t = "%identity";
  external ofFloat: float => t = "%identity";
  external ofBool: bool => t = "%identity";
  external ofArray: array(valueResolvable) => t = "%identity";
  external toInt: t => int = "%identity";
  external toString: t => string = "%identity";
  external toFloat: t => float = "%identity";
  external toBool: t => bool = "%identity";
  external ofAny: 'a => t = "%identity";
};

module Parse = {
  type t = parse;
  [@bs.send] external initialize: (t, appId, jsKey) => unit = "";
  [@bs.send]
  external initializeWithMaster: (t, appId, jsKey, masterKey) => unit =
    "initialize";
  [@bs.set] external serverURL: (t, string) => unit = "";
  [@bs.get] external object_: t => parseObject = "Object";
  [@bs.get] external query: t => parseQuery = "Query";
  [@bs.get] external user: t => parseUser = "User";
};

module PObject = {
  type t = parseObject;
  type p = parseObjectInstance;
  [@bs.module "parse"] [@bs.scope "Object"]
  external extend: string => t = "";
  [@bs.module "parse"] [@bs.new] external make: string => t = "Object";
  [@bs.get] external id: t => string = "";
  [@bs.send] external extendWithObj: (t, Js.t({..})) => t = "extend";
  [@bs.send] external registerSubclass: (t, string, t) => unit = "";
  [@bs.send] external save: t => Js.Promise.t(t) = "";
  [@bs.send]
  external saveWithObj: (t, Js.t({..})) => Js.Promise.t(t) = "save";
  [@bs.send] external set: (t, string, valueResolvable) => bool = "";
  [@bs.send] external get: (t, string) => valueResolvable = "";
  [@bs.send] external increment: (t, string) => unit = "";
  [@bs.send]
  external incrementWithAmount: (t, string, int) => unit = "increment";
};

module PQuery = {
  type t = parseQuery;
  [@bs.module "parse/node"] [@bs.new]
  external make: parseObject => t = "Query";
  [@bs.send] external equalTo: (t, string, valueResolvable) => unit = "";
  [@bs.send] external notEqualTo: (t, string, valueResolvable) => unit = "";
  [@bs.send] external find: t => Js.Promise.t(array(parseObject)) = "";
  [@bs.send] external limit: (t, int) => unit = "";
  [@bs.send] external get: (t, string) => Js.Promise.t(parseObject) = "";
  [@bs.send] external greaterThan: (t, int) => unit = "";
  [@bs.send] external greaterThanOrEqualTo: (t, int) => unit = "";
  [@bs.send] external lessThan: (t, int) => unit = "";
  [@bs.send] external lessThanOrEqualTo: (t, int) => unit = "";
  [@bs.send] external first: t => Js.Promise.t(parseObject) = "";
  [@bs.send] external ascending: (t, string) => unit = "";
  [@bs.send] external descending: (t, string) => unit = "";
  [@bs.send] external exists: (t, string) => unit = "";
  [@bs.send] external doesNotExist: (t, string) => unit = "";
};

module PUser = {
  type t = parseUser;
  [@bs.send] external login: (t, username, password) => Js.Promise.t(t) = "";
  [@bs.send] external signUp: (t, username, password) => Js.Promise.t(t) = "";
  [@bs.send] external become: (t, string) => Js.Promise.t(t) = "";
  [@bs.send] external current: t => t = "";
  [@bs.send] external logOut: t => Js.Promise.t(unit) = "";
};