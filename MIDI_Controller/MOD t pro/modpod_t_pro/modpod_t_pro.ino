int v0 = 0;
int v0_old = 0;
int v1 = 0;
int v1_old = 0;
int v2 = 0;
int v2_old = 0;
int v3 = 0;
int v3_old = 0;
int v4 = 0;
int v4_old = 0;
int v5 = 0;
int v5_old = 0;
int v6 = 0;
int v6_old = 0;
int v7 = 0;
int v7_old = 0;
int diff = 3;


#include "MIDIUSB.h"

byte Ch = 1;
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "URTouch.h"

#define TFT_DC 7
#define TFT_CS 14
#define TFT_RST 8
#define TFT_MISO 8
#define TFT_MOSI 16
#define TFT_CLK 15
int b;
int c = 160;
int y1 = 160 , x , y;
int x1 = 0;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

#define t_SCK 2
#define t_CS 3
#define t_MOSI 4
#define t_MISO 5
#define t_IRQ 6

URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);

void setup() {
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(0);
  tft.fillRect(0, 0, 110, 320, ILI9341_BLACK);
  tft.fillRect(110, 0, 130, 320,  ILI9341_RED);
  tft.fillRect(130, 0, 240, 320, ILI9341_BLACK);

  ts.InitTouch();
  ts.setPrecision(PREC_EXTREME);
  //  tft.fillScreen(ILI9341_BLACK);

  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(1);
  tft.setCursor(30, 10);
  tft.print("PITCH");

  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(150, 10);
  tft.print("MODULATION");
  tft.drawLine(0, 160, 109, 160, ILI9341_ORANGE);
  tft.drawLine(0, 161, 109, 161, ILI9341_ORANGE);
  tft.drawLine(130, 160, 240, 160, ILI9341_ORANGE);
  tft.drawLine(130, 161, 240, 161, ILI9341_ORANGE);
}

void loop()
{
  potentiometers();
  b = y1;
  if (ts.dataAvailable())
  {

    ts.read();
    x = ts.getX();
    y = ts.getY();
    y1 = 320 - x;
    x1 = y;
    //        Serial.print("x = ");
    //        Serial.print(x1);
    //        Serial.print("  y = ");
    //        Serial.println(y1);
    if (x1 < 100 && x1 > 0 && y1 > 30) {
      tft.drawLine(0, 160, 109, 160, ILI9341_BLACK);
      tft.drawLine(0, 160 + 1, 109, 160 + 1, ILI9341_BLACK);
      tft.drawLine(0, y1, 109, y1, ILI9341_ORANGE);
      tft.drawLine(0, y1 + 1, 109, y1 + 1, ILI9341_ORANGE);
      delay(10);
      tft.drawLine(0, b, 109, b, ILI9341_BLACK);
      tft.drawLine(0, b + 1, 109, b + 1, ILI9341_BLACK);
      tft.drawLine(0, y1, 109, y1, ILI9341_BLACK);
      tft.drawLine(0, y1 + 1, 109, y1 + 1, ILI9341_BLACK);
      v0 = map(x, 30, 320, 0, 127);
      if (abs(v0 - v0_old) >= 1) {
        v0_old = v0;
        pitchBend(Ch, 0, v0); //  (channel, MSB,  LSB)
        MidiUSB.flush();
      }
    }
    if (x1 < 240 && x1 > 130 && y1 > 30) {
      tft.drawLine(130, 160, 240, 160, ILI9341_BLACK);
      tft.drawLine(130, 160 + 1, 240, 160 + 1, ILI9341_BLACK);
      tft.drawLine(130, y1, 240, y1, ILI9341_ORANGE);
      tft.drawLine(130, y1 + 1, 240, y1 + 1, ILI9341_ORANGE);
      delay(10);
      tft.drawLine(130, c, 240, c, ILI9341_BLACK);
      tft.drawLine(130, c + 1, 240, c + 1, ILI9341_BLACK);
      tft.drawLine(130, y1, 240, y1, ILI9341_BLACK);
      tft.drawLine(130, y1 + 1, 240, y1 + 1, ILI9341_BLACK);
      v1 = map(x, 30, 320, 0, 127);
      if (abs(v1 - v1_old) >= 1) {
        v1_old = v1;
        controlChange(Ch, 1, v1);
        MidiUSB.flush();
      }
    }
  }
  else {
    if (x1 < 240 && x1 > 130 && y1 > 30) {
      tft.drawLine(130, y1, 240, y1, ILI9341_ORANGE);
      tft.drawLine(130, y1 + 1, 240, y1 + 1, ILI9341_ORANGE);
      c = y1;
    }

    tft.drawLine(0, 160, 109, 160, ILI9341_ORANGE);
    tft.drawLine(0, 160 + 1, 109, 160 + 1, ILI9341_ORANGE);
    v0 = map(160, 30, 320, 0, 127);
    if (abs(v0 - v0_old) >= 1) {
      v0_old = v0;
      pitchBend(Ch, 0, v0); //  (channel, MSB,  LSB)
      MidiUSB.flush();
    }
  }
}
void potentiometers() {
  v2 = analogRead(A10); // Velocity Pot
 // Serial.print("    ");
 // Serial.print(v2);
  v3 = analogRead(A0); // MacroKnob 1 pot
 // Serial.print("    ");
  //Serial.print(v3);
  v4 = analogRead(A1); // MacroKnob 2 pot
 // Serial.print("    ");
 // Serial.print(v4);
  v5 = analogRead(A2); // MacroKnob 3 pot
 // Serial.print("    ");
 // Serial.print(v5);
  v6 = analogRead(A3); // MacroKnob 4 pot
//  Serial.print("    ");
//  Serial.print(v6);
  v7 = analogRead(A9); // After Touch FSR
// Serial.print("    ");
// Serial.println(v7);


  //  v0 = map(v0, 0, 1023, 0, 127); // Pitch Bend
  //  v1 = map(v1, 0, 1023, 0, 127); // Modulation
  //  v2 = map(v2, 0, 1023, 0, 127); // Velocity
  //  v3 = map(v3, 0, 1023, 0, 127); // Macro 1
  //  v4 = map(v4, 0, 1023, 0, 127); // Macro 2
  //  v5 = map(v5, 0, 1023, 0, 127); // Macro 3
  //  v6 = map(v6, 0, 1023, 0, 127); // Macro 4
  //  v7 = map(v7, 0, 1023, 0, 127); // After Touch FSR

  // Velocity Knob
  if (abs(v2 - v2_old) >= diff) {
    v2_old = v2;
    v2 = map(v2, 0, 1023, 0, 127); // Velocity
    controlChange(Ch, 7, v2); //  (channel, CC number,  CC value)
    MidiUSB.flush();
  }
  // Macro 1
  if (abs(v3 - v3_old) >= diff) {
    v3_old = v3;
    v3 = map(v3, 0, 1023, 0, 127); // Macro 1
    controlChange(Ch, 21, v3); //  (channel, CC number,  CC value)
    MidiUSB.flush();
  }
  // Macro 2
  if (abs(v4 - v4_old) >= diff) {
    v4_old = v4;
    v4 = map(v4, 0, 1023, 0, 127); // Macro 2
    controlChange(Ch, 22, v4); //  (channel, CC number,  CC value)
    MidiUSB.flush();
  }
  // Macro 3
  if (abs(v5 - v5_old) >= diff) {
    v5_old = v5;
    v5 = map(v5, 0, 1023, 0, 127); // Macro 3
    controlChange(Ch, 23, v5); //  (channel, CC number,  CC value)
    MidiUSB.flush();
  }
  // Macro 4
  if (abs(v6 - v6_old) >= diff) {
    v6_old = v6;
    v6 = map(v6, 0, 1023, 0, 127); // Macro 4
    controlChange(Ch, 24, v6); //  (channel, CC number,  CC value)
    MidiUSB.flush();
  }
  // Aftor Touch Part

  if (abs(v7 - v7_old) >= diff) {
    v7_old = v7;
    v7 = map(v7, 0, 50, 0, 127); // After Touch FSR
    Touch(Ch, v7); //  (channel, pressure value)
    MidiUSB.flush();
  }
}

// modulation wheel function
void controlChange(byte channel, byte control_num, byte control_value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control_num, control_value};
  MidiUSB.sendMIDI(event);
}
// pitch bend function
void pitchBend(byte channel, byte MSB, byte LSB) {
  midiEventPacket_t event = {0x0E, 0xE0 | channel, MSB, LSB};
  MidiUSB.sendMIDI(event);
}
// After Touch function
void Touch(byte channel, byte Pressure) {
  midiEventPacket_t event = {0x0D, 0xD0 | channel, Pressure};
  MidiUSB.sendMIDI(event);
}
