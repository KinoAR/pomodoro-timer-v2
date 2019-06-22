// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");

function Timer(Props) {
  var match = React.useReducer((function (state, action) {
          switch (action[0]) {
            case "longbreak" : 
            case "pomodoro" : 
                return /* record */[
                        /* running */state[/* running */0],
                        /* timer */state[/* timer */1],
                        /* pomodoroState : Pomodoro */0
                      ];
            case "shortbreak" : 
                return /* record */[
                        /* running */state[/* running */0],
                        /* timer */state[/* timer */1],
                        /* pomodoroState : ShortBreak */1
                      ];
            default:
              return state;
          }
        }), /* record */[
        /* running */false,
        /* timer */300,
        /* pomodoroState : Pomodoro */0
      ]);
  var convertTimeToString = function (time) {
    var minutes = time / 60 | 0;
    var seconds = time % 60;
    var strSeconds = String(seconds);
    var match = strSeconds.length < 2;
    var displaySeconds = match ? strSeconds + "0" : strSeconds;
    return "" + (String(minutes) + (":" + (String(displaySeconds) + "")));
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
                                                className: "btn btn-primary"
                                              }, command[/* uiName */1]);
                                  }), /* :: */[
                                  /* record */[
                                    /* name */"pomodoro",
                                    /* uiName */"Pomodoro"
                                  ],
                                  /* :: */[
                                    /* record */[
                                      /* name */"shortBreak",
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
                                                className: "btn " + (String(className) + "")
                                              }, button[/* name */0]);
                                  }), /* :: */[
                                  /* record */[
                                    /* name */"Start",
                                    /* className */"btn-success"
                                  ],
                                  /* :: */[
                                    /* record */[
                                      /* name */"Stop",
                                      /* className */"btn-danger"
                                    ],
                                    /* :: */[
                                      /* record */[
                                        /* name */"Reset",
                                        /* className */"btn-secondary"
                                      ],
                                      /* [] */0
                                    ]
                                  ]
                                ]))))));
}

var make = Timer;

exports.make = make;
/* react Not a pure module */
