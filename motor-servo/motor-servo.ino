#include <RH_ASK.h>
#include <SPI.h>  // Not actualy used but needed to compile
#include <Servo.h>
#define MOT_A1_PIN 10
#define MOT_A2_PIN 9
#define MOT_B1_PIN 6
#define MOT_B2_PIN 5


Servo myServo;


int motorPin = 3;
RH_ASK driver;

void setup() {
  Serial.begin(9600);  // Debugging only
  pinMode(motorPin, OUTPUT);
  pinMode(MOT_A1_PIN, OUTPUT);
  pinMode(MOT_A2_PIN, OUTPUT);
  pinMode(MOT_B1_PIN, OUTPUT);
  pinMode(MOT_B2_PIN, OUTPUT);

  // Turn off motors - Initial state
  digitalWrite(MOT_A1_PIN, LOW);
  digitalWrite(MOT_A2_PIN, LOW);
  digitalWrite(MOT_B1_PIN, LOW);
  digitalWrite(MOT_B2_PIN, LOW);
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
  uint8_t buf[1];
  uint8_t buflen = sizeof(buf);

  char* received = nullptr;
  spin_and_wait(0,0, 0);

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
    if (strcmp(received, "U") == 0) {
      spin_and_wait(-255,-255, 10);
    }
    if (strcmp(received, "D") == 0) {
      spin_and_wait(255, 255, 10);
    }
  }
}
void set_motor_pwm(int pwm, int IN1_PIN, int IN2_PIN)
{
  if (pwm < 0) {  // reverse speeds
    analogWrite(IN1_PIN, -pwm);
    digitalWrite(IN2_PIN, LOW);

  } else { // stop or forward
    digitalWrite(IN1_PIN, LOW);
    analogWrite(IN2_PIN, pwm);
  }
}
void set_motor_currents(int pwm_A, int pwm_B)
{
  set_motor_pwm(pwm_A, MOT_A1_PIN, MOT_A2_PIN);
  set_motor_pwm(pwm_B, MOT_B1_PIN, MOT_B2_PIN);

  // Print a status message to the console.
  Serial.print("Set motor A PWM = ");
  Serial.print(pwm_A);
  Serial.print(" motor B PWM = ");
  Serial.println(pwm_B);
}
void spin_and_wait(int pwm_A, int pwm_B, int duration)
{
  set_motor_currents(pwm_A, pwm_B);
  delay(duration);
}