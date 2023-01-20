#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Arduino.h>
#include <BleGamepad.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#define numOfButtons 32
#define numOfHatSwitches 0
#define enableX true
#define enableY true
#define enableZ false
#define enableRZ false
#define enableRX false
#define enableRY false
#define enableSlider1 false
#define enableSlider2 false
#define enableRudder true
#define enableThrottle true
#define enableAccelerator false
#define enableBrake false
#define enableSteering false
#define ToggleButton 15

BleGamepad bleGamepad("GAMMING PAD", "lemmingDev", 100);
Adafruit_MPU6050 mpu;
float Xangle = 0, Yangle = 0;
int8_t Xangl = 0, Yangl = 0;
int16_t X = 0, Y = 0;
int8_t n = 0, newState = 0, prevState = 0;
void setup(void) {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.begin(115200);
  pinMode(ToggleButton, INPUT_PULLUP);
  delay(1000);
  while (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  Serial.println("Starting BLE work!");

  // Setup controller with 32 buttons, accelerator, brake and steering
  BleGamepadConfiguration bleGamepadConfig;
  bleGamepadConfig.setAutoReport(false);
  bleGamepadConfig.setControllerType(CONTROLLER_TYPE_GAMEPAD); // CONTROLLER_TYPE_JOYSTICK, CONTROLLER_TYPE_GAMEPAD (DEFAULT), CONTROLLER_TYPE_MULTI_AXIS
  bleGamepadConfig.setButtonCount(numOfButtons);
  bleGamepadConfig.setIncludeStart(true);
  bleGamepadConfig.setIncludeSelect(true);
  bleGamepadConfig.setWhichAxes(enableX, enableY, enableZ, enableRX, enableRY, enableRZ, enableSlider1, enableSlider2);      // Can also be done per-axis individually. All are true by default
  bleGamepadConfig.setWhichSimulationControls(enableRudder, enableThrottle, enableAccelerator, enableBrake, enableSteering); // Can also be done per-control individually. All are false by default
  bleGamepadConfig.setHatSwitchCount(numOfHatSwitches);                                                                      // 1 by default
  // Some non-Windows operating systems and web based gamepad testers don't like min axis set below 0, so 0 is set by default
  bleGamepadConfig.setAxesMin(0x8001); // -32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
  bleGamepadConfig.setAxesMax(0x7FFF); // 32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
  bleGamepad.begin(&bleGamepadConfig);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  Xangle = atan(a.acceleration.x / a.acceleration.z);
  Yangle = atan(a.acceleration.y / a.acceleration.z);
  Xangl = Xangle * 57.3;
  Yangl = Yangle * 57.3;
  newState = digitalRead(ToggleButton);
  if (newState == LOW)  {
    if (newState != prevState) {
      n ^= 1;
    }
  }
  prevState = newState;
  if (bleGamepad.isConnected())
  {

    if (Xangle < -85) {
      Xangle = -85;
    }
    if (Yangle < -85) {
      Yangle = -85;
    }
    if (Xangle > 85) {
      Xangle = 85;
    }
    if (Yangle > 85) {
      Xangle = 85;
    }
    if (n == 0) {
      X = map(Xangl, 85, -85, 0, 32767);
      Y = map(Yangl, -85, 85, 0, 32767);

    }
    else if (n == 1) {
      X = map(Xangl, -85, 85, 0, 32767);
      Y = map(Yangl, 85, -85, 0, 32767);
    }

    bleGamepad.setX(Y);
    bleGamepad.sendReport();
    delay(10);

    bleGamepad.setY(X);
    bleGamepad.sendReport();
    delay(10);
  }
  Serial.print("Button = "); Serial.print(digitalRead(ToggleButton)); Serial.print(" || Mode = "); Serial.print(n); Serial.print("|| Pitch = "); Serial.print(X); Serial.print(" || roll = "); Serial.println(Y);
}
