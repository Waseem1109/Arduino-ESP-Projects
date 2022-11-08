int v0 = 0;
int v0_old = 0;
int v1 = 0;
int v1_old = 0;



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
