[%%bs.raw
{|
  require("./styles.css");
|}];

let timerFunc = (~pomodoro, ~shortBreak, ~longBreak) => <Timer pomodoro={pomodoro} shortBreak={shortBreak} longBreak={longBreak} />;
ReactDOMRe.renderToElementWithId(<Settings timerFunc=timerFunc />, "settings");

