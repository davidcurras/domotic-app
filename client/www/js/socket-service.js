(function(){

  angular
    .module('starter')
    .service('SocketService', [
      'socketFactory',
      function(socketFactory){
        return socketFactory({
          ioSocket: io.connect('http://192.168.5.100:3111')
        });
      }
    ]);

})();
