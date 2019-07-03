// Generated by BUCKLESCRIPT VERSION 5.0.4, PLEASE EDIT WITH CARE
'use strict';

var List = require("bs-platform/lib/js/list.js");
var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReactDOMRe = require("reason-react/src/ReactDOMRe.js");
var Caml_option = require("bs-platform/lib/js/caml_option.js");

function createTask(taskName) {
  return /* record */[
          /* name */taskName,
          /* pomodori */0
        ];
}

var intervalIdRef = /* record */[/* contents */undefined];

function Timer(Props) {
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
                            /* currentTask */state[/* currentTask */5],
                            /* taskNameInput */state[/* taskNameInput */6],
                            /* title */state[/* title */7],
                            /* tasks */state[/* tasks */8]
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
                          /* currentTask */state[/* currentTask */5],
                          /* taskNameInput */state[/* taskNameInput */6],
                          /* title */state[/* title */7],
                          /* tasks */state[/* tasks */8]
                        ];
              case 2 : 
                  return /* record */[
                          /* running */state[/* running */0],
                          /* timer */state[/* initialTime */2],
                          /* initialTime */state[/* initialTime */2],
                          /* pomodoroState */state[/* pomodoroState */3],
                          /* pomodoroCount */state[/* pomodoroCount */4],
                          /* currentTask */state[/* currentTask */5],
                          /* taskNameInput */state[/* taskNameInput */6],
                          /* title */state[/* title */7],
                          /* tasks */state[/* tasks */8]
                        ];
              
            }
          } else {
            switch (action.tag | 0) {
              case 0 : 
                  switch (action[0]) {
                    case "longbreak" : 
                        return /* record */[
                                /* running */state[/* running */0],
                                /* timer */900,
                                /* initialTime */900,
                                /* pomodoroState : LongBreak */2,
                                /* pomodoroCount */state[/* pomodoroCount */4],
                                /* currentTask */state[/* currentTask */5],
                                /* taskNameInput */state[/* taskNameInput */6],
                                /* title */state[/* title */7],
                                /* tasks */state[/* tasks */8]
                              ];
                    case "pomodoro" : 
                        return /* record */[
                                /* running */state[/* running */0],
                                /* timer */1500,
                                /* initialTime */1500,
                                /* pomodoroState : Pomodoro */0,
                                /* pomodoroCount */state[/* pomodoroCount */4],
                                /* currentTask */state[/* currentTask */5],
                                /* taskNameInput */state[/* taskNameInput */6],
                                /* title */state[/* title */7],
                                /* tasks */state[/* tasks */8]
                              ];
                    case "shortbreak" : 
                        return /* record */[
                                /* running */state[/* running */0],
                                /* timer */10,
                                /* initialTime */300,
                                /* pomodoroState : ShortBreak */1,
                                /* pomodoroCount */state[/* pomodoroCount */4],
                                /* currentTask */state[/* currentTask */5],
                                /* taskNameInput */state[/* taskNameInput */6],
                                /* title */state[/* title */7],
                                /* tasks */state[/* tasks */8]
                              ];
                    default:
                      return state;
                  }
              case 1 : 
                  return /* record */[
                          /* running */state[/* running */0],
                          /* timer */state[/* timer */1],
                          /* initialTime */state[/* initialTime */2],
                          /* pomodoroState */state[/* pomodoroState */3],
                          /* pomodoroCount */state[/* pomodoroCount */4],
                          /* currentTask */List.nth(state[/* tasks */8], action[0]),
                          /* taskNameInput */state[/* taskNameInput */6],
                          /* title */state[/* title */7],
                          /* tasks */state[/* tasks */8]
                        ];
              case 2 : 
                  return state;
              case 3 : 
                  return /* record */[
                          /* running */state[/* running */0],
                          /* timer */state[/* timer */1],
                          /* initialTime */state[/* initialTime */2],
                          /* pomodoroState */state[/* pomodoroState */3],
                          /* pomodoroCount */state[/* pomodoroCount */4],
                          /* currentTask */state[/* currentTask */5],
                          /* taskNameInput */action[0],
                          /* title */state[/* title */7],
                          /* tasks */state[/* tasks */8]
                        ];
              
            }
          }
        }), /* record */[
        /* running */false,
        /* timer */300,
        /* initialTime */300,
        /* pomodoroState : Pomodoro */0,
        /* pomodoroCount */0,
        /* currentTask : record */[
          /* name */"",
          /* pomodori */0
        ],
        /* taskNameInput */"",
        /* title */"Add Task",
        /* tasks : [] */0
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
  var tasks = state[/* tasks */8];
  var handleTimeUpdate = function (state) {
    if (state[/* timer */1] === 0) {
      var remainderPomoCount = state[/* pomodoroCount */4] / 3 | 0;
      var statusTuple_000 = state[/* pomodoroState */3];
      stopTimer(/* () */0);
      Curry._1(dispatch, /* Reset */2);
      if (statusTuple_000 !== 0) {
        return /* () */0;
      } else if (remainderPomoCount > 0) {
        if (remainderPomoCount >= 3) {
          return /* () */0;
        } else {
          return Curry._1(dispatch, /* Click */Block.__(0, ["shortbreak"]));
        }
      } else if (remainderPomoCount >= 0) {
        return Curry._1(dispatch, /* Click */Block.__(0, ["longbreak"]));
      } else {
        return /* () */0;
      }
    } else {
      return 0;
    }
  };
  handleTimeUpdate(state);
  var match$1 = state[/* title */7];
  var tmp = match$1 === "Add Task" ? React.createElement("div", {
          className: "row"
        }, React.createElement("div", {
              className: "col-12"
            }, React.createElement("form", {
                  action: ""
                }, React.createElement("div", {
                      className: "form-group"
                    }, React.createElement("label", {
                          htmlFor: "Task Name"
                        }, "Task Name"), React.createElement("input", {
                          id: "taskName",
                          name: "taskName",
                          placeholder: "Enter Task Name",
                          type: "text",
                          onChange: (function (e) {
                              var $$event = e;
                              $$event.preventDefault();
                              var value = $$event.target;
                              console.log(value);
                              return /* () */0;
                            })
                        }))))) : null;
  var match$2 = state[/* currentTask */5][/* name */0].length !== 0;
  return React.createElement("div", {
              className: "row"
            }, React.createElement("div", {
                  className: "modal fade",
                  id: "pomodoroModal",
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
                                }, state[/* title */7]), ReactDOMRe.createElementVariadic("button", {
                                  "data-dismiss": "modal",
                                  type: "button",
                                  className: "close",
                                  "aria-label": "Close"
                                }, /* array */[React.createElement("span", {
                                        "aria-hidden": true
                                      }, "Close")])), React.createElement("div", {
                              className: "modal-body"
                            }, tmp), React.createElement("div", {
                              className: "modal-footer"
                            }, React.createElement("div", {
                                  className: "row"
                                }, React.createElement("br", undefined), React.createElement("div", {
                                      className: "btn btn-primary"
                                    }, "Save Changes"), ReactDOMRe.createElementVariadic("button", {
                                      "data-dismiss": "modal",
                                      type: "button",
                                      className: "btn btn-secondary",
                                      "aria-label": "Close"
                                    }, /* array */["Close"])))))), React.createElement("div", {
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
                                                    return Curry._1(dispatch, /* Click */Block.__(0, [command[/* name */0]]));
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
                        }, $$Array.of_list(List.mapi((function (index, button) {
                                    var className = button[/* className */1];
                                    return React.createElement("button", {
                                                key: String(index),
                                                className: "btn " + (String(className) + ""),
                                                onClick: (function (param) {
                                                    return Curry._1(button[/* fn */2], /* () */0);
                                                  })
                                              }, button[/* name */0]);
                                  }), timerButtons))))), React.createElement("br", undefined), React.createElement("div", {
                  className: "col-12 text-center"
                }, React.createElement("h2", undefined, "Task View"), React.createElement("div", {
                      className: "row"
                    }, React.createElement("div", {
                          className: "col-12"
                        }, match$2 ? React.createElement("div", undefined, React.createElement("h4", undefined, "Current Task"), React.createElement("div", {
                                    className: "row text-center"
                                  }, React.createElement("div", {
                                        className: "offset-4 col-4 text-center"
                                      }, React.createElement("div", {
                                            className: "card"
                                          }, React.createElement("div", {
                                                className: "card-body"
                                              }, React.createElement("h5", {
                                                    className: "card-title"
                                                  }, state[/* currentTask */5][/* name */0]), React.createElement("a", {
                                                    className: "btn btn-outline-primary",
                                                    href: ""
                                                  }, "Done")))))) : null), React.createElement("div", {
                          className: "col-12 task-area"
                        }, React.createElement("h4", undefined, "Tasks"), React.createElement("div", {
                              className: "row"
                            }, React.createElement("div", {
                                  className: "col-12"
                                }, React.createElement("ul", {
                                      className: "list-group"
                                    }, React.createElement("li", {
                                          className: "list-group-item task-area",
                                          onClick: (function (param) {
                                              return /* () */0;
                                            })
                                        }, "Add a new task", ReactDOMRe.createElementVariadic("button", {
                                              "data-toggle": "modal",
                                              "data-target": "#pomodoroModal",
                                              type: "button",
                                              className: "btn btn-secondary"
                                            }, /* array */["Add Task"])), $$Array.of_list(List.mapi((function (index, task) {
                                                var taskName = task[/* name */0];
                                                var pomodoriStr = String(task[/* pomodori */1]);
                                                return React.createElement("li", {
                                                            key: String(index),
                                                            className: "list-group-item",
                                                            onClick: (function (param) {
                                                                return Curry._1(dispatch, /* ClickTask */Block.__(1, [index]));
                                                              })
                                                          }, "" + (String(taskName) + (" : " + (String(pomodoriStr) + ""))));
                                              }), tasks)))))))));
}

var make = Timer;

exports.createTask = createTask;
exports.intervalIdRef = intervalIdRef;
exports.make = make;
/* react Not a pure module */
