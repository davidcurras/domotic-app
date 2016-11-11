var actions = require('../actions');
var state = require('../state')();
var socketIO = null;

var setSocket = function(socket) {
  socketIO = socket;
};

var update = function() {
  var error = state.tree.process && state.tree.process.error;
  if(error) {
    console.log('client:state:error', error);
    socket.emit('state:error', error);
    actions.dispatch(actions.list.client.sendError());
  } else {
    socket.emit(
      'state:changed',
      Object.assign({}, state.tree.sensors, state.tree.actuators)
    );
    actions.dispatch(actions.list.client.sendState());
  }
};

module.exports = {
  setSocket: setSocket,
  update: update
};
