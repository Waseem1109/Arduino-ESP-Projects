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
int diff = 20;


#include "MIDIUSB.h"


byte Ch = 1; //Channel Number varies from 1-16


void setup () {
  Serial.begin(2000000);
}
void loop () {
  potentiometers();
}

void potentiometers() {
  v0 = analogRead(A0); // Pitch Bend Pot
  Serial.print(v0);
  v1 = analogRead(A1); // Modulation Wheel Pot
  Serial.print("    ");
  Serial.print(v1);
  v2 = analogRead(A2); // Velocity Pot
  Serial.print("    ");
  Serial.println(v2);
//  v3 = analogRead(A3); // MacroKnob 1 pot
//  Serial.print("    ");
//  Serial.print(v3);
//  v4 = analogRead(A6); // MacroKnob 2 pot
//  Serial.print("    ");
//  Serial.print(v4);
//  v5 = analogRead(A7); // MacroKnob 3 pot
//  Serial.print("    ");
//  Serial.print(v5);
//  v6 = analogRead(A8); // MacroKnob 4 pot
//  Serial.print("    ");
//  Serial.print(v6);
//  v7 = analogRead(A9); // After Touch FSR
//  Serial.print("    ");
//  Serial.println(v7);


  // Pitch Bend
  if (abs(v0 - v0_old) >= diff) {
    v0_old = v0;
    v0 = map(v0, 0, 1023, 0, 127); // Pitch Bend
    pitchBend(Ch, 0, v0); //  (channel, MSB,  LSB)
    MidiUSB.flush();
  }
  // Modulation Wheel
  if (abs(v1 - v1_old) >= diff) {
    v1_old = v1;
    v1 = map(v1, 0, 1023, 0, 127); // Modulation
    controlChange(Ch, 1, v1); //  (channel, CC number,  CC value)
    MidiUSB.flush();
  }
  // Velocity Knob
  if (abs(v2 - v2_old) >= diff) {
    v2_old = v2;
    v2 = map(v2, 0, 1023, 0, 127); // Velocity
    controlChange(Ch, 7, v2); //  (channel, CC number,  CC value)
    MidiUSB.flush();
  }
//  // Macro 1
//  if (abs(v3 - v3_old) >= diff) {
//    v3_old = v3;
//    v3 = map(v3, 0, 1023, 0, 127); // Macro 1
//    controlChange(Ch, 21, v3); //  (channel, CC number,  CC value)
//    MidiUSB.flush();
//  }
//  // Macro 2
//  if (abs(v4 - v4_old) >= diff) {
//    v4_old = v4;
//    v4 = map(v4, 0, 1023, 0, 127); // Macro 2
//    controlChange(Ch, 22, v4); //  (channel, CC number,  CC value)
//    MidiUSB.flush();
//  }
//  // Macro 3
//  if (abs(v5 - v5_old) >= diff) {
//    v5_old = v5;
//    v5 = map(v5, 0, 1023, 0, 127); // Macro 3
//    controlChange(Ch, 23, v5); //  (channel, CC number,  CC value)
//    MidiUSB.flush();
//  }
//  // Macro 4
//  if (abs(v6 - v6_old) >= diff) {
//    v6_old = v6;
//    v6 = map(v6, 0, 1023, 0, 127); // Macro 4
//    controlChange(Ch, 24, v6); //  (channel, CC number,  CC value)
//    MidiUSB.flush();
//  }
//  // Aftor Touch Part
//
//  if (abs(v7 - v7_old) >= diff) {
//    v7_old = v7;
//    v7 = map(v7, 0, 50, 0, 127); // After Touch FSR
//    Touch(Ch, v7); //  (channel, pressure value)
//    MidiUSB.flush();
//  }
//  //delay(50);
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
