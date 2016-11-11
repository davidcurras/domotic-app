var reducers = require('../reducers');
var rp = require('request-promise');

var settingState = function() {
  return {
    type: 'SETTING_STATE'
  }
};

var setStateSuccess = function(newState) {
  return {
    type: 'SET_STATE_SUCCESS',
    newState: newState
  }
};

var setStateFailed = function(error) {
  return {
    type: 'SET_STATE_FAILED',
    error: error
  }
};

var setState = function(actuator, state, socket) {
  var url = 'http://192.168.5.6/'+actuator+'/'+state;
  console.log(url);
  rp(url)
    .then(function(newState) {
      var action = setStateSuccess(newState);
      reducers.act(action);
      socket.emit('state:changed', newState);
    })
    .catch(function(error) {
      console.log('client:state:error');
      socket.emit('state:error', error);
      var action = setStateFailed(error);
      reducers.act(action);
    });
  return settingState();
};

module.exports = {
  settingState: settingState,
  setStateSuccess: setStateSuccess,
  setStateFailed: setStateFailed,
  setState: setState
};
