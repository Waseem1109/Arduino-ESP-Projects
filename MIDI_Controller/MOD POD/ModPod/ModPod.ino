int v0 = 0;
int v0_old = 0;
int v1 = 0;
int v1_old = 0;
int diff = 20;

#include "MIDIUSB.h"


byte Ch = 1; //Channel Number varies from 1-16


void setup () {
  Serial.begin(115200);
}
void loop () {
  potentiometers();
}


void potentiometers() {
  v0 = analogRead(A0);
  v1 = analogRead(A1);

  if (abs(v0 - v0_old) >= diff) {
    Serial.print(v0);
    Serial.print("    ");
    Serial.println(v1);
    v0_old = v0;
    v0 = map(v0, 0, 1023, 0, 127);
    pitchBend(Ch, 0, v0); //  (channel, MSB,  LSB)
    MidiUSB.flush();
  }

  if (abs(v1 - v1_old) >= diff) {
    Serial.print(v0);
    Serial.print("    ");
    Serial.println(v1);
    v1_old = v1;
    v1 = map(v1, 0, 1023, 0, 127);
    controlChange(Ch, 1, v1); //  (channel, CC number,  CC value)
    MidiUSB.flush();
  }
  //delay(50);
}

// modulation wheel
void controlChange(byte channel, byte control_num, byte control_value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control_num, control_value};
  MidiUSB.sendMIDI(event);
}
// pitch bend
void pitchBend(byte channel, byte MSB, byte LSB) {
  midiEventPacket_t event = {0x0E, 0xE0 | channel, MSB, LSB};
  MidiUSB.sendMIDI(event);
}
