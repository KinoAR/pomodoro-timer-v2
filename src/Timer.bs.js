// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var CamlinternalOO = require("bs-platform/lib/js/camlinternalOO.js");
var Utils$ReactHooksTemplate = require("./Utils.bs.js");
var TaskView$ReactHooksTemplate = require("./TaskView.bs.js");

var intervalIdRef = /* record */[/* contents */undefined];

var class_tables = [
  0,
  0,
  0
];

function Timer(Props) {
  var pomodoro = Props.pomodoro;
  var shortBreak = Props.shortBreak;
  var longBreak = Props.longBreak;
  var match = React.useReducer((function (state, action) {
          if (typeof action === "number") {
            switch (action) {
              case 0 : 
                  var match = state[/* timer */1];
                  if (match !== 0) {
                    return /* record */[
                            /* running */state[/* running */0],
                            /* timer */state[/* timer */1] - 1 | 0,
                            /* initialTime */state[/* initialTime */2],
                            /* pomodoroState */state[/* pomodoroState */3],
                            /* pomodoroCount */state[/* pomodoroCount */4],
                            /* intervals */state[/* intervals */5],
                            /* title */state[/* title */6]
                          ];
                  } else {
                    return state;
                  }
              case 1 : 
                  return /* record */[
                          /* running */state[/* running */0],
                          /* timer */state[/* timer */1],
                          /* initialTime */state[/* initialTime */2],
                          /* pomodoroState */state[/* pomodoroState */3],
                          /* pomodoroCount */state[/* pomodoroCount */4] + 1 | 0,
                          /* intervals */state[/* intervals */5],
                          /* title */state[/* title */6]
                        ];
              case 2 : 
                  return /* record */[
                          /* running */state[/* running */0],
                          /* timer */state[/* initialTime */2],
                          /* initialTime */state[/* initialTime */2],
                          /* pomodoroState */state[/* pomodoroState */3],
                          /* pomodoroCount */state[/* pomodoroCount */4],
                          /* intervals */state[/* intervals */5],
                          /* title */state[/* title */6]
                        ];
              
            }
          } else {
            switch (action[0]) {
              case "longbreak" : 
                  return /* record */[
                          /* running */state[/* running */0],
                          /* timer */longBreak,
                          /* initialTime */longBreak,
                          /* pomodoroState : LongBreak */2,
                          /* pomodoroCount */state[/* pomodoroCount */4],
                          /* intervals */state[/* intervals */5],
                          /* title */state[/* title */6]
                        ];
              case "pomodoro" : 
                  return /* record */[
                          /* running */state[/* running */0],
                          /* timer */pomodoro,
                          /* initialTime */pomodoro,
                          /* pomodoroState : Pomodoro */0,
                          /* pomodoroCount */state[/* pomodoroCount */4],
                          /* intervals */state[/* intervals */5],
                          /* title */state[/* title */6]
                        ];
              case "shortbreak" : 
                  return /* record */[
                          /* running */state[/* running */0],
                          /* timer */shortBreak,
                          /* initialTime */shortBreak,
                          /* pomodoroState : ShortBreak */1,
                          /* pomodoroCount */state[/* pomodoroCount */4],
                          /* intervals */state[/* intervals */5],
                          /* title */state[/* title */6]
                        ];
              default:
                return state;
            }
          }
        }), /* record */[
        /* running */false,
        /* timer */300,
        /* initialTime */300,
        /* pomodoroState : Pomodoro */0,
        /* pomodoroCount */0,
        /* intervals */3,
        /* title */"Add Task"
      ]);
  var dispatch = match[1];
  var state = match[0];
  var stopTimer = function (param) {
    var match = intervalIdRef[0];
    if (match !== undefined) {
      clearInterval(Caml_option.valFromOption(match));
      intervalIdRef[0] = undefined;
      return /* () */0;
    } else {
      return /* () */0;
    }
  };
  var resetTimer = function (param) {
    stopTimer(/* () */0);
    return Curry._1(dispatch, /* Reset */2);
  };
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
  var getStatusString = function (status) {
    switch (status) {
      case 0 : 
          return "Pomodoro";
      case 1 : 
          return "Short Break";
      case 2 : 
          return "Long Break";
      
    }
  };
  var convertTimeToString = function (time) {
    var minutes = time / 60 | 0;
    var seconds = time % 60;
    var strSeconds = String(seconds);
    var strMinutes = String(minutes);
    var match = strMinutes.length < 2;
    var displayMinutes = match ? "0" + strMinutes : strMinutes;
    var match$1 = strSeconds.length < 2;
    var displaySeconds = match$1 ? "0" + strSeconds : strSeconds;
    return "" + (String(displayMinutes) + (":" + (String(displaySeconds) + "")));
  };
  var handleTimeUpdate = function (state) {
    if (state[/* timer */1] === 0) {
      if (state[/* pomodoroState */3] === /* Pomodoro */0) {
        console.log("Pomodoro Complete");
        Curry._1(dispatch, /* CompletePomodoro */1);
      }
      var remainderPomoCount = Caml_int32.div(state[/* pomodoroCount */4], state[/* intervals */5]);
      var statusTuple_000 = state[/* pomodoroState */3];
      stopTimer(/* () */0);
      Curry._1(dispatch, /* Reset */2);
      if (statusTuple_000 !== 0) {
        Curry._1(dispatch, /* Click */["pomodoro"]);
      } else if (remainderPomoCount > 0) {
        if (remainderPomoCount >= 3) {
          
        } else {
          Curry._1(dispatch, /* Click */["shortbreak"]);
        }
      } else if (remainderPomoCount >= 0) {
        Curry._1(dispatch, /* Click */["longbreak"]);
      }
      
    }
    var time = convertTimeToString(state[/* timer */1]);
    return Utils$ReactHooksTemplate.updateWindowTitle("" + (String(time) + " - NierPixel Pomodoro Timer"));
  };
  var updateTask = function (param) {
    if (!class_tables[0]) {
      var $$class = CamlinternalOO.create_table(0);
      var env = CamlinternalOO.new_variable($$class, "");
      var env_init = function (env$1) {
        var self = CamlinternalOO.create_object_opt(0, $$class);
        self[env] = env$1;
        return self;
      };
      CamlinternalOO.init_class($$class);
      class_tables[0] = env_init;
    }
    return Curry._1(class_tables[0], 0);
  };
  handleTimeUpdate(state);
  return React.createElement("div", {
              className: "row"
            }, React.createElement("div", {
                  className: "offset-4 col-4"
                }, React.createElement("div", {
                      className: "col-12 text-center"
                    }, React.createElement("div", {
                          className: "btn-group"
                        }, Utils$ReactHooksTemplate.listToReactArray(List.mapi((function (index, command) {
                                    return React.createElement("button", {
                                                key: String(index),
                                                className: "btn btn-primary",
                                                onClick: (function (param) {
                                                    stopTimer(/* () */0);
                                                    Curry._1(dispatch, /* Reset */2);
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
                    }, React.createElement("small", {
                          className: "pomodoro-state"
                        }, getStatusString(state[/* pomodoroState */3])), React.createElement("hr", {
                          className: "standard-style"
                        }), React.createElement("h1", {
                          className: "pomodoro-timer"
                        }, convertTimeToString(state[/* timer */1]))), React.createElement("div", {
                      className: "col-12 text-center"
                    }, React.createElement("div", {
                          className: "btn-group"
                        }, Utils$ReactHooksTemplate.listToReactArray(List.mapi((function (index, button) {
                                    var className = button[/* className */1];
                                    return React.createElement("button", {
                                                key: String(index),
                                                className: "btn " + (String(className) + ""),
                                                onClick: (function (param) {
                                                    return Curry._1(button[/* fn */2], /* () */0);
                                                  })
                                              }, button[/* name */0]);
                                  }), timerButtons))))), React.createElement("div", {
                  className: "col-12"
                }, React.createElement("div", {
                      className: "offset-4 col-4"
                    }, React.createElement("hr", {
                          className: "standard-style"
                        })), React.createElement(TaskView$ReactHooksTemplate.make, {
                      updateTask: updateTask
                    })));
}

var make = Timer;

exports.intervalIdRef = intervalIdRef;
exports.make = make;
/* react Not a pure module */
