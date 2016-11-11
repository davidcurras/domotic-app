var actions = require('../actions');
var state = require('../state')();
var socketIO = null;

var setSocket = function(socket) {
  socketIO = socket;
};

var getState = function() {
  if(state.process && state.process.busy){
    socketIO.emit('state:error', {error: 'server is busy'});
    actions.dispatch(actions.list.client.sendBusy());
  } else {
    console.log('sensor:state:get');
    actions.dispatch(actions.list.sensor.getState(socketIO));
  }
};

var update = function(state) { };

module.exports = {
  setSocket: setSocket,
  getState: getState,
  update: update
};
