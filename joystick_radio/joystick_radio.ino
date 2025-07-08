#include <RH_ASK.h>
#include <SPI.h> // Required for RH_ASK, even if not used directly

#define VRX_PIN  A1 // Arduino pin connected to VRX pin
#define VRY_PIN  A0 // Arduino pin connected to VRY pin

#define LEFT_THRESHOLD  400
#define RIGHT_THRESHOLD 800
#define UP_THRESHOLD    400
#define DOWN_THRESHOLD  800

#define COMMAND_NO     0x00
#define COMMAND_LEFT   0x01
#define COMMAND_RIGHT  0x02
#define COMMAND_UP     0x04
#define COMMAND_DOWN   0x08

int xValue = 0;
int yValue = 0;
int command = COMMAND_NO;

RH_ASK driver;

void setup() {
  Serial.begin(9600);

  if (!driver.init()) {
    Serial.println("RH_ASK init failed");
  } else {
    Serial.println("RH_ASK init success");
  }
}

void loop() {
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  command = COMMAND_NO;

  if (xValue < LEFT_THRESHOLD) command |= COMMAND_LEFT;
  else if (xValue > RIGHT_THRESHOLD) command |= COMMAND_RIGHT;

  if (yValue < UP_THRESHOLD) command |= COMMAND_UP;
  else if (yValue > DOWN_THRESHOLD) command |= COMMAND_DOWN;


  // Hardcoded single-direction message
  const char* msg = nullptr;

  if (command & COMMAND_LEFT) {
    msg = "L";
    Serial.println("COMMAND LEFT");
  } else if (command & COMMAND_RIGHT) {
    msg = "R";
    Serial.println("COMMAND RIGHT");
  } else if (command & COMMAND_UP) {
    msg = "U";
    Serial.println("COMMAND UP");
  } else if (command & COMMAND_DOWN) {
    msg = "D";
    Serial.println("COMMAND DOWN");
  }

  if (msg != nullptr) {
    driver.send((uint8_t*)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.print("Sent: ");
    Serial.println(msg);
  }
  

}
