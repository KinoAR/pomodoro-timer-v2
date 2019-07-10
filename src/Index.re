open ParseAPI;
[%%bs.raw
{|
  require("./styles.css");
|}];
let parse = ParseAPI.make;
parse -> Parse.initialize("CHxKR1K47E6gap2r9Uo5t8MSnX2i7AbjHOGMMqJ5", "9Q7sUPSsJUxijG1yMjoDrlGoRolmJjcYNKcusUJt")
parse -> Parse.serverURL("https://parseapi.back4app.com")
let timerFunc = (~pomodoro, ~shortBreak, ~longBreak) => <Timer pomodoro={pomodoro} shortBreak={shortBreak} longBreak={longBreak} />;
ReactDOMRe.renderToElementWithId(<Settings timerFunc=timerFunc />, "settings");

