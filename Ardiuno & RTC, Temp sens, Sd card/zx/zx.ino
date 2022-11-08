// including all libraries
#include <SPI.h>
#include <SD.h>
#include <DS3231.h>
#include <OneWire.h>
#include <DallasTemperature.h>

DS3231  rtc(A4, A5); // Respresnt SDA and SLC pin
const int chipSelect = 4; // selecting CS pin of SD card Reader
int T1; // Temp variable from temperature sensor1
int T2; // Temp variable from temperature sensor2
int T3; // Temp variable from temperature sensor3
int T4;  // Temp Variable from analog temp sensor4
int a;  //

void setup() {
  Serial.begin(2000000); // set baud rate
  rtc.begin(); // Timer starts now
  while (!Serial) { // if serial is not aviable, loop remains
  }
  Serial.print("Initializing SD card...");
  if (!SD.begin(chipSelect)) { // if connection b/w sd module and arduino is not established
    Serial.println("Card failed, or not present");
    while (1);
  }
  Serial.println("card initialized.");
  rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
  rtc.setTime(6, 5, 0);     // Set the time according to real time
  rtc.setDate(15, 1, 2014);   // Set the date of today

  Serial.print(" Date");
  Serial.print("         ");
  Serial.print("Time");
  Serial.print("    ");
  Serial.print("T1");
  Serial.print("  ");
  Serial.print("T2");
  Serial.print("  ");
  Serial.print("T3");
  Serial.print("  ");
  Serial.println("T4");
}

void loop() {
  for (int i = 5; i < 8; i++)
  {
    int ONE_WIRE_BUS = i; // i  means input pins of arduino where temp sensors is connected
    OneWire oneWire(ONE_WIRE_BUS);
    DallasTemperature sensors(&oneWire);// represent sensor is attatched to following wire bus

    sensors.requestTemperatures(); // requesting sensor to update the results
    int T = sensors.getTempCByIndex(0); // variable T is declared to current sensor data
    if (T == -127)
    { // removing uncertain temp data
    }
    else {
      Serial.print(rtc.getDateStr());// printing RTC date
      Serial.print("  ");
      Serial.print(rtc.getTimeStr());// printing RTC time
      Serial.print("  ");
      if (i == 5)
      { T1 = T; // first sensor turn
        Serial.print(T1); // printing 1st sensor data
      }
      else {
        Serial.print(T1);
      }
      Serial.print("  ");
      if (i == 6)
      { T2 = T; // 2nd sensor turn
        Serial.print(T2); // printing 2nd sensor data
      }
      else {
        Serial.print(T2);
      }
      Serial.print("  ");
      if (i == 7)
      { T3 = T; // 3rd sensor turn
        Serial.print(T3); // printing 3rd sensor data
      }
      else {
        Serial.print(T3);
      }
      Serial.print("  ");
      a = analogRead(A0);
      T4 = map(a, 805, 558, -30, 120);
      if (a < 558 || a > 805)
      {}
      else
      { Serial.println(T4);
      }
      File myFile = SD.open("Carbon.txt", FILE_WRITE); // Generating File with name Waseem
      if (myFile) {
        myFile.print(rtc.getDateStr()); // writing  RTC date in Waseem.txt file
        myFile.print("  ");
        myFile.print(rtc.getTimeStr()); // writing  RTC time in Waseem.txt file
        myFile.print("  ");
        myFile.print(T1); // writing  sensor 1 data in Waseem.txt file
        myFile.print("  ");
        myFile.print(T2);// writing  sensor 2 dat in Waseem.txt file
        myFile.print("  ");
        myFile.print(T3); // writing  sensor 3 data in Waseem.txt file
        myFile.print("  ");
        myFile.println(T4);
        myFile.close(); // close the file
      }
      // if the file didn't open, print an error:
      else {
        Serial.println("error opening test.txt"); // if generated file is not opened error is displayed
      }
    }
  }
}
