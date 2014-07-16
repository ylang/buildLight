var SerialPort = require("serialport").SerialPort;

var sp = new SerialPort("/dev/tty.usbmodem1411", {
  baudrate: 9600
});

var flag = false;

sp.on('open',function() {
  sp.on('data', function(data) {
    console.log('>>>>>' + data);
  });

  function writeThenWait() {
    console.log('Calling write...');
    flag = !flag;
    var message = flag ? new Buffer('a') : new Buffer('b');
    sp.write(message, function() {
      console.log('...Waiting 5000 milliseconds...');
      // Even though write returned, the data may still be in the pipe, and hasn't reached your robot yet.
      //setInterval(writeThenWait, duration);
    });
  };

  // Stuff starts happening here
  setInterval(writeThenWait, 5000);

});