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

var setState = function(actuator, state) {
  //return rp('http://196.162.0.1/'+actuator+'/'+state)
  rp('http://sushihomearg.com/api/v1/category')
    .then(function(newState) {
      var action = setStateSuccess(newState);
      reducers.act(action);
    })
    .catch(function(error) {
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
