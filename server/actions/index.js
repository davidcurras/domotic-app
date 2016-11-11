var reducers = require('../reducers');

var actions = {
  client: require('./client'),
  actuator: require('./actuator'),
  sensor: require('./sensor')
};

module.exports = {
  list: actions,
  dispatch: function(action) {
    reducers.act(action);
  }
};
