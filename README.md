buildLight
==========

An arduino listening for serial port and a NodeJs server write to serial port.
The NodeJs server should also listen to a IP port to determine what data should send to serial port.

##Babysteps
	*	Node server -> Arduino ->LED
	*	Data generator -> Node server
	*	Data generator -> Node server -> Arduino -> LED 
	*	Data generator -> Node server -> Arduino -> Relay board
