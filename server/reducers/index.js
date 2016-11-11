//var components = require('../components');

var reducers = [
  require('./process'),
  require('./sensors'),
  require('./actuators')
];

var act = function(action) {
  reducers.forEach(function(reducer) {
    reducer(action);
  });
  //components.update();
};

module.exports = {
  act: act
};
