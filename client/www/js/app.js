// Ionic Starter App

// angular.module is a global place for creating, registering and retrieving Angular modules
// 'starter' is the name of this angular module example (also set in a <body> attribute in index.html)
// the 2nd parameter is an array of 'requires'
angular.module('starter', ['ionic', 'btford.socket-io'])
  .run(function($ionicPlatform) {
    $ionicPlatform.ready(function() {
      if(window.cordova && window.cordova.plugins.Keyboard) {
        // Hide the accessory bar by default (remove this to show the accessory bar above the keyboard
        // for form inputs)
        cordova.plugins.Keyboard.hideKeyboardAccessoryBar(true);

        // Don't remove this line unless you know what you are doing. It stops the viewport
        // from snapping when text inputs are focused. Ionic handles this internally for
        // a much nicer keyboard experience.
        cordova.plugins.Keyboard.disableScroll(true);
      }
      if(window.StatusBar) {
        StatusBar.styleDefault();
      }
    });
  })
  .controller('MainCtrl', function($scope, $timeout, $interval, SocketService) {

    $timeout(function() {
      $scope.loaded = true;
      SocketService.emit('get:state');
    }, 3000);

    $scope.state = {
      gas: '0 ppm',
      gasState: 'Normal',
      fire: false,
      humidity: '0%',
      temperature: '0C',
      groundHumidity: '0%',
      airConditioning: false,
      irrigation: false,
      inpureGas: false,
      fireAlarm: false,
      fan: false,
      light: false,
      led2: false,
      led6: false,
      led9: false
    };

    $scope.changeState = function(actuator, state) {
      var val = state ? 1 : 0;
      console.log('change:state', actuator, val);
      SocketService.emit('change:state', {
        actuator: actuator,
        state: val
      });
    };

    SocketService.on('state:changed', function(data){
      if(data.substr(0,1) !== '{') {
        console.error('Can not parse non json data: \n\n'+data);
        return;
      }
      var state = JSON.parse(data);
      console.log('state:changed', state);
      $timeout(function() {
        angular.extend($scope.state, state);
      });
    });

    SocketService.on('state:error', function(err){
      console.log('state:error', err);
      console.error(err);
    });

  });
