(function(){

  angular
    .module('starter')
    .service('SocketService', [
      'socketFactory',
      function(socketFactory){
        return socketFactory({
          ioSocket: io.connect('http://localhost:3111')
        });
      }
    ]);

})();
