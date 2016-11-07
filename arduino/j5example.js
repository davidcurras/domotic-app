var five = require('johnny-five'),
    Board = five.Board,
    Leds = five.Leds;
//import { Board, Leds } from 'johnny-five';

var board = new Board();

board.on("ready", () => {
  var leds = new Leds([7, 8, 9]);

  leds.pulse();

  board.repl.inject({
    off: () => {
      leds.forEach((led, index) => {
        console.log(index);
        led.stop();
        led.off();
      })
    }
  });
  
  // var proximity = new five.Proximity({
  //   controller: "HCSR04",
  //   pin: 7,
  //   freq: 1000
  // });
  // proximity.on("data", function() {
  //   console.log(this.cm + "cm", this.in + "in");
  // });
  // proximity.on("change", function() {
  //   console.log((this.cm/100).toFixed(2) + "m", this.in + "in");
  // });

});