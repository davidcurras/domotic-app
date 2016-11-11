var state = require('../state')();

module.exports = function(action) {
  var defaultState = {
    fan: false,
    fireAlarm: false,
    irrigation: false,
    light: false
  };
  var actuatorsState = Object.assign(defaultState, state.actuators);
  switch(action.type) {
    case 'GET_STATE_SUCCESS':
    case 'SET_STATE_SUCCESS':
      Object.assign(actuatorsState, action.newState);
      break;
  }
  state.actuators = actuatorsState;
};
      