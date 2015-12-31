#include <Wire.h>


#define PIN_ROLE_I2C_MASTER 2

void setup() {
  // put your setup code here, to run once:
  if (is_master_i2c()) {
      Wire.begin();
  } else {
      Wire.begin(8);                // join i2c bus with address #8
      Wire.onReceive(receiveEvent); // register event
      Serial.begin(9600);
  }
  // setup that applies to both boards
  pinMode(PIN_ROLE_I2C_MASTER, INPUT_PULLUP);  
}

byte x = 0;
RingBuffer inputRing();

void loop() {
  if (is_master_i2c()) {
      digitalWrite(13, HIGH); 
      // put your main code here, to run repeatedly:
      Wire.beginTransmission(8); // transmit to device #8
      Wire.write("x is ");        // sends five bytes
      Wire.write(x);              // sends one byte
      Wire.endTransmission();    // stop transmitting
    
      x++;
      delay(500);
  } else {
      digitalWrite(13, LOW);
      delay(100);    
  }
}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
    while (1 < Wire.available()) { // loop through all but the last
        int msg = Wire.read();      // receive byte as a character
        Serial.print(c);           // print the character
        if(inputRing.spaceAvailable()) {
            inputRing.write(msg);
        } else {
            inputRing.markOverflow();
        }
    }
    
    int x = Wire.read();        // receive byte as an integer
    Serial.println(x);          // print the integer
}

// Returns true if the pin PIN_ROLE_I2C_MASTER is connected to 5V.
bool is_master_i2c(void) {
  int role = digitalRead(PIN_ROLE_I2C_MASTER == HIGH);
  return (role);
}
