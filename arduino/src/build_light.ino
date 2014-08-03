const unsigned int RED_PIN = 7;
const unsigned int GREEN_PIN = 8;

const unsigned int RED = B1;
const unsigned int GREEN = B10;
const unsigned int QUERY = B100;
const unsigned int FLASH = B1000;

boolean flashing;
int flashCycles;

unsigned int previousSignal = 0;
unsigned int currentSignal = 0;

void setup() {
  // Open hardware serial port, set data rate to 9600 bps.
  Serial.begin(9600);

  pinMode(RED_PIN, OUTPUT); 
  pinMode(GREEN_PIN, OUTPUT); 

  digitalWrite(RED_PIN, HIGH); 
  digitalWrite(GREEN_PIN, HIGH); 

  startFlashing();
}

void loop() {
  if (flashing) {
    flash();
  } else {
    pollSerial();
  }
}

/** Enters flashing mode. */
void startFlashing() {
  flashing = true;
  flashCycles = 6;
  previousSignal = currentSignal;
  currentSignal = GREEN;
}

/** Progress with flashing. */
void flash() {
  unsigned int signal = 0;
  if (flashCycles-- > 0) {
    if ((currentSignal & RED) == 0) {
      signal = signal | RED;
    }
    if ((currentSignal & GREEN) == 0) {
      signal = signal | GREEN;
    }
    signalToLights(signal);
    delay(1000);
  } else {
    flashing = false;
    signalToLights(previousSignal);
  }
}

/** Polls serial and control lights accordingly. */
void pollSerial() {
  if (Serial.available() > 0) {
    // read the incoming byte:
    int signal = Serial.read();
    if (signal & QUERY) {
      // Respond currentSignal.
      Serial.print(currentSignal, DEC);
    } else if (signal & FLASH) {
      startFlashing();
    } else {
      // Echo received signal
      Serial.print(signal, DEC);
      signalToLights(signal);
    }
  }

  // Check serial data every 2 seconds.
  delay(2000);
}

/** Controls lights according to the signal. */
void signalToLights(unsigned int signal) {
  // Control lights accordingly
  if (signal & RED) {
    digitalWrite(RED_PIN, LOW); 
  } else {
    digitalWrite(RED_PIN, HIGH); 
  }
  if (signal & GREEN) {
    digitalWrite(GREEN_PIN, LOW); 
  } else {
    digitalWrite(GREEN_PIN, HIGH); 
  }
  currentSignal = signal;
}
