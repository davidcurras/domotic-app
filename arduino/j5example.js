var five = require('johnny-five'),
    Board = five.Board,
    Leds = five.Leds;
//import { Board, Leds } from 'johnny-five';

var board = new Board();

board.on("ready", () => {
  var leds = new Leds([2, 5, 6, 8, 9]);

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

});