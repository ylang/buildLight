var SerialPort = require("serialport").SerialPort,
    http = require('http'),
    url = require('url');

var RED = 1; // 0001
var GREEN = 2; // 0010
var QUERY = 4; // 0100
var FLASH = 8; // 1000

// Initialize serial port.
var serialPort = new SerialPort("/dev/tty.usbmodem1411", {
  baudrate: 9600
});

var serialOpened = false;

serialPort.on('open',function() {
  serialPort.on('data', function(data) {
    var received = '';
    if (data & RED) {
      received += 'RED ';
    }
    if (data & GREEN) {
      received += 'GREEN ';
    }
    if (data & QUERY) {
      received += 'QUERY ';
    }
    if (data & FLASH) {
      received += 'FLASH ';
    }
    console.log('received: ' + data + ' ' + received);
  });
  serialOpened = true;
});

function writeRequestToSerial(request, cb) {
  if (request.indexOf('query') != -1) {
    writeToSerial(QUERY, cb);
  } else if (request.indexOf('flash') != -1) {
    writeToSerial(FLASH, cb);
  } else {
    var signal = 0;
    if (request.indexOf('red') != -1) {
      signal = signal | RED;
    }
    if (request.indexOf('green') != -1) {
      signal = signal | GREEN;
    }
    writeToSerial(signal, cb);
  }
}

function writeToSerial(signal, cb) {
  if (!serialOpened) {
    cb('Serial port has not opened');
    return;
  }
  var buffer = new Buffer([signal]);
  serialPort.write(buffer, cb);
  console.log('Sent: ' + signal);
}

http.createServer(function(request, response) {
  var pathname = url.parse(request.url).pathname;
  if (pathname.indexOf('/buildlight/') == 0) {
    writeRequestToSerial(pathname, function(err) {
      if (err) {
        response.writeHead(500, {'Content-Type': 'text/plain'});
        response.write(err);
      } else {
        response.writeHead(200, {'Content-Type': 'text/plain'});
        response.write('OK');
      }
      response.end();
    });
  } else {
    response.writeHead(400, {'Content-Type': 'text/plain'});
    response.write('Unknown request');
    response.end();
  }
}).listen(18990);
