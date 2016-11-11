var state = require('../state')();

module.exports = function(action) {
  var defaultState = {
    gas: '0ppm',
    gasState: 'Normal',
    fire: false,
    humidity: '0%',
    temperature: '0C',
    groundHumidity: '0%'
  };
  var sensorsState = Object.assign(defaultState, state.sensors);
  switch(action.type) {
    case 'GET_STATE_SUCCESS':
    case 'SET_STATE_SUCCESS':
      Object.assign(sensorsState, action.newState);
      break;
  }
  state.sensors = sensorsState;
};
