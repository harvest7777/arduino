

// void setup() {
  // pinMode(motorPin, OUTPUT);
//   Serial.begin(9600);
//   while (!Serial);  // Wait for Serial Monitor (only necessary for some boards like Leonardo)
//   Serial.println("Enter speed between 0 and 255:");
// }

// void loop() {
//   if (Serial.available()) {
//     int speed = Serial.parseInt();

//     if (speed >= 0 && speed <= 255) {
//       analogWrite(motorPin, speed);
//       Serial.print("Motor speed set to: ");
//       Serial.println(speed);
//     } else {
//       Serial.println("Invalid input. Enter a number between 0 and 255.");
//     }
//   }
// }
#include <RH_ASK.h>
#include <SPI.h>  // Not actualy used but needed to compile
int motorPin = 3;
RH_ASK driver;

void setup() {
  Serial.begin(9600);  // Debugging only
  pinMode(motorPin, OUTPUT);
  while (!Serial);
  if (!driver.init())
    Serial.println("init failed");
  else {
    Serial.println("init guccid");
  }
}

void loop() {
  uint8_t buf[1];
  uint8_t buflen = sizeof(buf);

  char* received = nullptr;

  if (driver.recv(buf, &buflen))  // Non-blocking
  {
    // Message with a good checksum received, dump it.
    received = (char*)buf;
    Serial.println(received);
    if (strcmp(received, "U") == 0) {
      analogWrite(motorPin, 255);
      delay(100);
      analogWrite(motorPin,0);
    } 
  } 
}