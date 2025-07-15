#include <RH_ASK.h>
#include <SPI.h>  // Not actualy used but needed to compile
#include <Servo.h>

Servo myServo;


int motorPin = 3;
RH_ASK driver;

void setup() {
  Serial.begin(9600);  // Debugging only
  pinMode(motorPin, OUTPUT);
  myServo.attach(9);  // Connect signal wire of servo to pin 9

  while (!Serial)
    ;
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
    if (strcmp(received, "L") == 0) {
      myServo.write(180);  // Move to 90 degrees
    }
    if (strcmp(received, "R") == 0) {
      myServo.write(0);  // Move to 90 degrees
    }
  }
}