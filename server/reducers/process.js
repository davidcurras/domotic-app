var state = require('../state')();

module.exports = function(action) {
  var defaultState = {
    busy: false,
    error: null
  };
  var processState = Object.assign(defaultState, state.process);
  switch(action.type) {
    case 'SETTING_STATE':
    case 'GETTING_STATE':
      processState.busy = true;
      break;
    case 'SET_STATE_SUCCESS':
    case 'GET_STATE_SUCCESS':
      processState.busy = false;
      processState.error = null;
      break;
    case 'SET_STATE_FAILED':
    case 'GET_STATE_FAILED':
      processState.busy = false;
      processState.error = action.error;
      break;
  }
  state.process = processState;
};
