// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");

function Settings(Props) {
  var timerFunc = Props.timerFunc;
  var match = React.useReducer((function (state, action) {
          if (typeof action === "number") {
            if (action !== 0) {
              return state;
            } else {
              return /* record */[
                      /* pomodoroTime */state[/* tempPomodoroTime */1],
                      /* tempPomodoroTime */state[/* tempPomodoroTime */1],
                      /* shortBreakTime */state[/* tempShortBreakTime */3],
                      /* tempShortBreakTime */state[/* tempShortBreakTime */3],
                      /* longBreakTime */state[/* tempLongBreakTime */5],
                      /* tempLongBreakTime */state[/* tempLongBreakTime */5]
                    ];
            }
          } else {
            var time = action[1];
            switch (action[0]) {
              case 0 : 
                  return /* record */[
                          /* pomodoroTime */state[/* pomodoroTime */0],
                          /* tempPomodoroTime */time,
                          /* shortBreakTime */state[/* shortBreakTime */2],
                          /* tempShortBreakTime */state[/* tempShortBreakTime */3],
                          /* longBreakTime */state[/* longBreakTime */4],
                          /* tempLongBreakTime */state[/* tempLongBreakTime */5]
                        ];
              case 1 : 
                  return /* record */[
                          /* pomodoroTime */state[/* pomodoroTime */0],
                          /* tempPomodoroTime */state[/* tempPomodoroTime */1],
                          /* shortBreakTime */state[/* shortBreakTime */2],
                          /* tempShortBreakTime */time,
                          /* longBreakTime */state[/* longBreakTime */4],
                          /* tempLongBreakTime */state[/* tempLongBreakTime */5]
                        ];
              case 2 : 
                  return /* record */[
                          /* pomodoroTime */state[/* pomodoroTime */0],
                          /* tempPomodoroTime */state[/* tempPomodoroTime */1],
                          /* shortBreakTime */state[/* shortBreakTime */2],
                          /* tempShortBreakTime */state[/* tempShortBreakTime */3],
                          /* longBreakTime */state[/* longBreakTime */4],
                          /* tempLongBreakTime */time
                        ];
              
            }
          }
        }), /* record */[
        /* pomodoroTime */1500,
        /* tempPomodoroTime */1500,
        /* shortBreakTime */300,
        /* tempShortBreakTime */300,
        /* longBreakTime */900,
        /* tempLongBreakTime */900
      ]);
  var dispatch = match[1];
  var state = match[0];
  var settingInputs = /* array */[
    /* record */[
      /* name */"Pomodoro Time",
      /* id */"pomodoroTime",
      /* timeType : Pomodoro */0
    ],
    /* record */[
      /* name */"Short Break Time",
      /* id */"shortBreakTime",
      /* timeType : ShortBreak */1
    ],
    /* record */[
      /* name */"Long Break Time",
      /* id */"longBreakTime",
      /* timeType : LongBreak */2
    ]
  ];
  return React.createElement("div", {
              className: "row"
            }, React.createElement("div", {
                  className: "modal fade",
                  id: "settingsModal",
                  role: "dialog"
                }, React.createElement("div", {
                      className: "modal-dialog",
                      role: "document"
                    }, React.createElement("div", {
                          className: "modal-content"
                        }, React.createElement("div", {
                              className: "modal-header"
                            }, React.createElement("div", {
                                  className: "modal-title"
                                }, "Settings"), ReactDOMRe.createElementVariadic("button", {
                                  "data-dismiss": "modal",
                                  type: "button",
                                  className: "close",
                                  "aria-label": "Close"
                                }, /* array */[React.createElement("span", {
                                        "aria-hidden": true
                                      }, "Close")])), React.createElement("div", {
                              className: "modal-body"
                            }, React.createElement("div", {
                                  className: "row"
                                }, React.createElement("div", {
                                      className: "col-12"
                                    }, React.createElement("h2", undefined, "Time Settings")), React.createElement("div", {
                                      className: "col-12"
                                    }, React.createElement("form", {
                                          action: ""
                                        }, $$Array.mapi((function (index, input) {
                                                return React.createElement("div", {
                                                            key: String(index),
                                                            className: "form-group"
                                                          }, React.createElement("label", {
                                                                htmlFor: "Time"
                                                              }, input[/* name */0]), React.createElement("input", {
                                                                className: "form-control",
                                                                name: "time",
                                                                type: "text",
                                                                onChange: (function (e) {
                                                                    var time = input[/* timeType */2];
                                                                    var $$event = e;
                                                                    var value = $$event.target.value;
                                                                    return Curry._1(dispatch, /* UpdateTempTime */[
                                                                                time,
                                                                                Caml_int32.imul(value, 60)
                                                                              ]);
                                                                  })
                                                              }));
                                              }), settingInputs))))), React.createElement("div", {
                              className: "modal-footer"
                            }, React.createElement("div", {
                                  className: "row"
                                }, React.createElement("br", undefined), React.createElement("div", {
                                      className: "btn btn-primary",
                                      onClick: (function (param) {
                                          return Curry._1(dispatch, /* UpdateTime */0);
                                        })
                                    }, "Save Changes"), ReactDOMRe.createElementVariadic("button", {
                                      "data-dismiss": "modal",
                                      type: "button",
                                      className: "btn btn-secondary",
                                      "aria-label": "Close"
                                    }, /* array */["Close"])))))), React.createElement("div", {
                  className: "col-12 text-center"
                }, React.createElement("h2", undefined, "Options"), React.createElement("div", {
                      className: "row"
                    }, React.createElement("div", {
                          className: "col-12"
                        }, ReactDOMRe.createElementVariadic("button", {
                              "data-toggle": "modal",
                              "data-target": "#settingsModal",
                              type: "button",
                              className: "btn btn-secondary"
                            }, /* array */["Settings"])))), React.createElement("div", {
                  className: "col-12"
                }, React.createElement("br", undefined), Curry._3(timerFunc, state[/* pomodoroTime */0], state[/* shortBreakTime */2], state[/* longBreakTime */4])));
}

var make = Settings;

exports.make = make;
/* react Not a pure module */
