int ledPin = 13;
void setup()
{
  // Start the hardware serial port
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT); 
  digitalWrite(ledPin, LOW); 
}

void loop()
{
  // send data only when you receive data:
  if (Serial.available() > 0) {
     // read the incoming byte:
     int incomingByte = Serial.read();

     // say what you got:
     Serial.print("I received: ");
     Serial.println(incomingByte, DEC);
     if (incomingByte == 97) {
       digitalWrite(ledPin, HIGH); 
     } else if (incomingByte = 98) {
       digitalWrite(ledPin, LOW); 
     }
   }

}