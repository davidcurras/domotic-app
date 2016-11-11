var actions = require('../actions');
var state = require('../state')();
var socketIO = null;

var setSocket = function(socket) {
  socketIO = socket;
};

var setState = function(actuator, newState) {
  if(state.process && state.process.busy){
    socket.emit('state:error', {error: 'server is busy'});
    actions.dispatch(actions.list.client.sendBusy());
  } else {
    console.log('actuator:state:get', actuator, newState);
    actions.dispatch(actions.list.actuator.setState(actuator, newState));
  }
};

var update = function(state) { };

module.exports = {
  setSocket: setSocket,
  setState: setState,
  update: update
};
