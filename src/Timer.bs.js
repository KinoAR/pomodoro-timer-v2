// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_option = require("bs-platform/lib/js/caml_option.js");

var intervalIdRef = /* record */[/* contents */undefined];

function Timer(Props) {
  var match = React.useReducer((function (state, action) {
          if (typeof action === "number") {
            if (action !== 0) {
              return /* record */[
                      /* running */state[/* running */0],
                      /* timer */state[/* initialTime */2],
                      /* initialTime */state[/* initialTime */2],
                      /* pomodoroState */state[/* pomodoroState */3]
                    ];
            } else {
              return /* record */[
                      /* running */state[/* running */0],
                      /* timer */state[/* timer */1] - 1 | 0,
                      /* initialTime */state[/* initialTime */2],
                      /* pomodoroState */state[/* pomodoroState */3]
                    ];
            }
          } else {
            switch (action[0]) {
              case "longbreak" : 
                  return /* record */[
                          /* running */state[/* running */0],
                          /* timer */900,
                          /* initialTime */900,
                          /* pomodoroState : LongBreak */2
                        ];
              case "pomodoro" : 
                  return /* record */[
                          /* running */state[/* running */0],
                          /* timer */1500,
                          /* initialTime */1500,
                          /* pomodoroState : Pomodoro */0
                        ];
              case "shortbreak" : 
                  return /* record */[
                          /* running */state[/* running */0],
                          /* timer */300,
                          /* initialTime */900,
                          /* pomodoroState : ShortBreak */1
                        ];
              default:
                return state;
            }
          }
        }), /* record */[
        /* running */false,
        /* timer */300,
        /* initialTime */300,
        /* pomodoroState : Pomodoro */0
      ]);
  var dispatch = match[1];
  var startTimer = function (param) {
    var match = intervalIdRef[0];
    if (match !== undefined) {
      return /* () */0;
    } else {
      var intervalId = setInterval((function (param) {
              return Curry._1(dispatch, /* Tick */0);
            }), 1000);
      intervalIdRef[0] = Caml_option.some(intervalId);
      return /* () */0;
    }
  };
  var stopTimer = function (param) {
    var match = intervalIdRef[0];
    if (match !== undefined) {
      clearInterval(Caml_option.valFromOption(match));
      return /* () */0;
    } else {
      return /* () */0;
    }
  };
  var resetTimer = function (param) {
    stopTimer(/* () */0);
    return Curry._1(dispatch, /* Reset */1);
  };
  var timerButtons_000 = /* record */[
    /* name */"Start",
    /* className */"btn-success",
    /* fn */startTimer
  ];
  var timerButtons_001 = /* :: */[
    /* record */[
      /* name */"Stop",
      /* className */"btn-danger",
      /* fn */stopTimer
    ],
    /* :: */[
      /* record */[
        /* name */"Reset",
        /* className */"btn-secondary",
        /* fn */resetTimer
      ],
      /* [] */0
    ]
  ];
  var timerButtons = /* :: */[
    timerButtons_000,
    timerButtons_001
  ];
  var convertTimeToString = function (time) {
    var minutes = time / 60 | 0;
    var seconds = time % 60;
    var strSeconds = String(seconds);
    var strMinutes = String(minutes);
    var match = strMinutes.length < 2;
    var displayMinutes = match ? "0" + strMinutes : strMinutes;
    var match$1 = strSeconds.length < 2;
    var displaySeconds = match$1 ? strSeconds + "0" : strSeconds;
    return "" + (String(displayMinutes) + (":" + (String(displaySeconds) + "")));
  };
  return React.createElement("div", {
              className: "row"
            }, React.createElement("div", {
                  className: "offset-4 col-4"
                }, React.createElement("div", {
                      className: "col-12 text-center"
                    }, React.createElement("div", {
                          className: "btn-group"
                        }, $$Array.of_list(List.mapi((function (index, command) {
                                    return React.createElement("button", {
                                                key: String(index),
                                                className: "btn btn-primary",
                                                onClick: (function (param) {
                                                    return Curry._1(dispatch, /* Click */[command[/* name */0]]);
                                                  })
                                              }, command[/* uiName */1]);
                                  }), /* :: */[
                                  /* record */[
                                    /* name */"pomodoro",
                                    /* uiName */"Pomodoro"
                                  ],
                                  /* :: */[
                                    /* record */[
                                      /* name */"shortbreak",
                                      /* uiName */"Short Break"
                                    ],
                                    /* :: */[
                                      /* record */[
                                        /* name */"longbreak",
                                        /* uiName */"Long Break"
                                      ],
                                      /* [] */0
                                    ]
                                  ]
                                ])))), React.createElement("div", {
                      className: "col-12 text-center"
                    }, React.createElement("h1", {
                          className: "pomodoro-timer"
                        }, convertTimeToString(match[0][/* timer */1]))), React.createElement("div", {
                      className: "col-12 text-center"
                    }, React.createElement("div", {
                          className: "btn-group"
                        }, $$Array.of_list(List.mapi((function (index, button) {
                                    var className = button[/* className */1];
                                    return React.createElement("button", {
                                                key: String(index),
                                                className: "btn " + (String(className) + ""),
                                                onClick: (function (param) {
                                                    return Curry._1(button[/* fn */2], /* () */0);
                                                  })
                                              }, button[/* name */0]);
                                  }), timerButtons))))));
}

var make = Timer;

exports.intervalIdRef = intervalIdRef;
exports.make = make;
/* react Not a pure module */
