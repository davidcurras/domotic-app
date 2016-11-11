var io = require('socket.io')(3111),
    client = require('./components/client'),
    sensor = require('./components/sensor'),
    actuator = require('./components/actuator');

var response = function(res) {
  socket.emit('state:changed', res);
};

io.on('connection', function(socket){

  client.setSocket(socket);
  sensor.setSocket(socket);
  actuator.setSocket(socket);

  socket.on('get:state', function(){
    sensor.getState();
  });

  socket.on('change:state', function(data){
    if(data && data.actuator) {
      var state = data.state ? 1 : 0;
      actuator.setState(data.actuator, state);
    } else {
      socket.emit('state:error', {
        error: 'invalid actuator',
        data: data.actuator
      });
    }
  });

  socket.on('disconnect', function(){
    console.log('user disconnected');
  });
});

console.log('listen on port: ' + 3111);