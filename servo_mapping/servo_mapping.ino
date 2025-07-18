#include <RH_ASK.h>
#include <SPI.h>  // Not actualy used but needed to compile
#include <Servo.h>

Servo myServo;


int motorPin = 3;
RH_ASK driver;

void setup() {
  Serial.begin(9600);  // Debugging only
  pinMode(motorPin, OUTPUT);
  myServo.attach(8);  // Connect signal wire of servo to pin 9

  while (!Serial)
    ;
  if (!driver.init())
    Serial.println("init failed");
  else {
    Serial.println("init guccid");
  }
}

void loop() {
  uint8_t buf[10];  // Make sure this is big enough to hold your full message
  uint8_t buflen = sizeof(buf);

  if (driver.recv(buf, &buflen))  // Non-blocking
  {
    buf[buflen] = '\0';  // Null-terminate just in case
    String str = String((char*)buf);  // Convert to Arduino String

    int commaIndex = str.indexOf(',');
    if (commaIndex != -1) {
      String value = str.substring(0,commaIndex);

      float floatTurnValue = value.toFloat();
      floatTurnValue = floatTurnValue * 180 / 1024;

      int intTurnValue = (int)floatTurnValue;

      myServo.write(intTurnValue);

      Serial.print("X value received: ");
      Serial.println(value);
      Serial.print("degrees turning: ");
      Serial.println(intTurnValue);
    } else {
      Serial.println("Comma not found in received string");
    }
  }
}

// void loop() {
//   uint8_t buf[1];
//   uint8_t buflen = sizeof(buf);

//   char* received = nullptr;

//   if (driver.recv(buf, &buflen))  // Non-blocking
//   {

//     // Message with a good checksum received, dump it.
//     received = (char*)buf;
      
//     // Find the position of the comma
//     int commaIndex = received.indexOf(',');

//     // Extract the substring after the comma
//     String value = received.substring(commaIndex + 1);

//     Serial.print("Y value recieved: ");
//     Serial.println(value);  // This will print: 1023

//     // Serial.println(received);
//     // if (strcmp(received, "L") == 0) {
//     //   myServo.write(180);  // Move to 90 degrees
//     // }
//     // if (strcmp(received, "R") == 0) {
//     //   myServo.write(0);  // Move to 90 degrees
//     // }
//   }
// }