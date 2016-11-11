var reducers = require('../reducers');
var rp = require('request-promise');

var gettingState = function() {
  return {
    type: 'GETTING_STATE'
  }
};

var getStateSuccess = function(newState) {
  return {
    type: 'GET_STATE_SUCCESS',
    newState: newState
  }
};

var getStateFailed = function(error) {
  return {
    type: 'GET_STATE_FAILED',
    error: error
  }
};

var getState = function(socket) {
  var url = 'http://192.168.5.6/state';
  console.log(url);
  rp(url)
    .then(function(newState) {
      var action = getStateSuccess(newState);
      reducers.act(action);
      socket.emit('state:changed', newState);
    })
    .catch(function(error) {
      console.log('client:state:error');
      socket.emit('state:error', error);
      var action = getStateFailed(error);
      reducers.act(action);
    });
  return gettingState();
};

module.exports = {
  gettingState: gettingState,
  getStateSuccess: getStateSuccess,
  getStateFailed: getStateFailed,
  getState: getState
};
