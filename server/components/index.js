var components = [
  require('./client'),
  require('./sensor'),
  require('./actuator')
];

var update = function() {
  components.forEach(function(component) {
    component.update();
  });
};

module.exports = {
  update: update
};
