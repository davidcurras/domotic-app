var state = require('../state')();

module.exports = function(action) {
  var defaultState = {
    airConditioning: false,
    irrigation: false,
    inpureGas: false,
    fireAlarm: false,
    fan: false,
    light: false,
    led2: false,
    led6: false,
    led9: false
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
