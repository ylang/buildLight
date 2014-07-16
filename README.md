buildLight
==========

An arduino listening for serial port and a NodeJs server write to serial port.
The NodeJs server should also listen to a IP port to determine what data should send to serial port.

##Dependency
	* Nodejs
	* Express
	* [Serialport](https://github.com/voodootikigod/node-serialport)
	* [firmata](https://github.com/jgautier/firmata) Talk natively to Arduino using the firmata protocol.


##Babysteps
	*	Node server -> Arduino ->LED
	*	Data generator -> Node server
	*	Data generator -> Node server -> Arduino -> LED 
	*	Data generator -> Node server -> Arduino -> Relay board
