#include <Arduino.h>
#include <analogWrite.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <TinyGPS++.h>
//Motor Pins
#define ENA 15
#define INA_1 4
#define INA_2 2
#define Btn 14
// Insert your network credentials
#define WIFI_SSID "Infinix"
#define WIFI_PASSWORD "Waseem1109"

// Insert Firebase project API Key
#define API_KEY "AIzaSyCkz-hcCe0FvNPHE7y-EV0duEaSwGq2Uio"

// Insert Authorized Email and Corresponding Password
#define USER_EMAIL "rehankhan23@gmail.com"
#define USER_PASSWORD "rehan23"

// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://esp-practice-project-default-rtdb.asia-southeast1.firebasedatabase.app/"

// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// Variables to save date and time
String formattedDate;
String dayStamp;
String timeStamp;

// Variable to save USER UID
String uid;
// Variables to save database paths
String databasePath;

struct container_path {
  String Pills_Present_path;
  String TimeSet_path;
};
container_path C1_path;
String gps_path_longitude;
String gps_path_latitude;
String notification_path;
struct container {
  int Pills_Present;
  int TimeSet;
};
container C1;
// Timer variables (send new readings every three minutes)
unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 10000;

static const int servoPin = 13;
int counts = 0;
int PrevState = 0;
int PrevState2 = 0;
int IRcountPin = 12;
int IRsubPin = 26;
int AlarmPin = 27;
int BoxPin = 25;
int prevtime1 = 0;
int prevtime2 = 0;
int prevtimer = 0;
int droptime = 0;
int M = 0;
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 4);
Servo servo1;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps; // The TinyGPS++ object
float latitude;
float longitude;

int m;          // Month Entry
int d;          // Day Entry
int yy;         // Last 2 digits of the year (ie 2016 would be 16)
int yyyy;       // Year Entry
int c;          // Century (ie 2016 would be 20)
int mTable;     // Month value based on calculation table
int SummedDate; // Add values combined in prep for Mod7 calc
int DoW;        // Day of the week value (0-6)
String WD;
int leap;       // Leap Year or not
int cTable;     // Century value based on calculation table

String dateTimeSet;


void setup()
{
  Serial.begin(115200);
  Serial2.begin(GPSBaud);
  pinMode(IRcountPin, INPUT_PULLUP);
  pinMode(IRsubPin, INPUT_PULLUP);
  pinMode(BoxPin, INPUT_PULLUP);
  pinMode(AlarmPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(IRcountPin), Increment, CHANGE);
  attachInterrupt(digitalPinToInterrupt(IRsubPin), decrement, CHANGE);
  servo1.attach(servoPin);
  // initialize the LCD
  lcd.begin();
  // Turn on the blacklight and print a message.
  lcd.backlight();
  initWiFi();
  // Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(18000);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  config.max_token_generation_retry = 5;
  Firebase.begin(&config, &auth);
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);
  databasePath = "/UsersData/" + uid;
  C1_path.Pills_Present_path = databasePath + "/Container1/Pills"; // --> UsersData/<user_uid>/temperature
  C1_path.TimeSet_path = databasePath + "/Container1/TimeSet"; // --> UsersData/<user_uid>/humiditye
  gps_path_longitude = databasePath + "/GPS_Location/Longitude";
  gps_path_latitude = databasePath + "/GPS_Location/Latitude";
  notification_path = databasePath + "/Notification";
  int pre = millis();
  while ((millis() - pre) < 2000) {
    if (Firebase.ready()) {
      // Get latest sensor readings
      C1.Pills_Present = counts;
      // Send readings to database:
      get_int(C1_path.Pills_Present_path);
      counts = C1.Pills_Present;
      sendFloat(gps_path_longitude, longitude);
      sendFloat(gps_path_latitude, latitude);
      sendFloat(notification_path, 0);
      send_String(C1_path.TimeSet_path, "MonTueWedThuFriSatSun_16:27");
    }
  }
}

void loop()
{
  int PRE = millis();
  while ((millis() - PRE) < 500) {
    if (Serial2.available() > 0) {
      if (gps.encode(Serial2.read())) {
        displayInfo();
      }
    }
  }
  printLocalTime();
  if (Firebase.ready() && (millis() - sendDataPrevMillis) > timerDelay) {
    sendDataPrevMillis = millis();
    // Get latest sensor readings
    C1.Pills_Present = counts;
    // Send readings to database:
    sendFloat(C1_path.Pills_Present_path, C1.Pills_Present);
    sendFloat(gps_path_longitude, longitude);
    sendFloat(gps_path_latitude, latitude);
    get_String(C1_path.TimeSet_path);
  }
  DATE_TO_WEEKDAY(dayStamp);
  Serial.print("Date_match = "); Serial.print(checkDate()); Serial.print("  |  "); Serial.print("Time_match = "); Serial.println(checkTime());
  if (checkDate() == 1 && checkTime() == 1) {
    if ((millis() - droptime) > 60000) {
      servo1.write(60);
      delay(1000);
      servo1.write(176);
      ALARM();
      droptime = millis();
    }
  }
  else {
    servo1.write(176);
  }
  lcd.setCursor(0, 0);
  lcd.print("C1 = "); lcd.print(counts);
  lcd.setCursor(0, 1);
  lcd.print("C1_Time = "); lcd.print(dateTimeSet.substring(22, 27));
}
void Increment() {
  int NewState = digitalRead(IRcountPin);
  if (NewState != PrevState) {
    if (NewState == HIGH) {
      if ((millis() - prevtime1) > 60) {
        counts++;
        prevtime1 = millis();
      }
    }
    PrevState = NewState;
  }
}
void decrement() {
  if (checkDate() == 1 && checkTime() == 1) {
    int NewState = digitalRead(IRsubPin);
    if (NewState != PrevState2) {
      if (NewState == HIGH) {
        if ((millis() - prevtime2) > 3000) {
          counts--;
          if (counts < 0) {
            counts = 0;
          }
          prevtime2 = millis();
        }
      }
      PrevState2 = NewState;
    }
  }
}
// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Write float values to the database
void sendFloat(String path, float value) {
  if (Firebase.RTDB.setFloat(&fbdo, path.c_str(), value)) {
  }
  else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }
}
void send_String(String path, String value) {
  if (Firebase.RTDB.setString(&fbdo, path.c_str(), value)) {
  }
  else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }
}
void get_String(String path) {
  if (Firebase.RTDB.getString(&fbdo, path)) {
    if (fbdo.dataType() == "string") {
      dateTimeSet = fbdo.stringData();
    }
  }
  else {
    Serial.println(fbdo.errorReason());
  }
}
void get_int(String path) {
  if (Firebase.RTDB.getInt(&fbdo, path)) {
    if (fbdo.dataType() == "int") {
      counts = fbdo.intData();
    }
  }
  else {
    Serial.println(fbdo.errorReason());
  }
}
void printLocalTime() {
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();

  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  Serial.print("DATE: ");
  Serial.println(dayStamp);
  // Extract time
  timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
  Serial.print("HOUR: ");
  Serial.println(timeStamp);
}

void DATE_TO_WEEKDAY(String DATE) {
  String years = formattedDate.substring(0, 4);
  String months = formattedDate.substring(5, 7);
  String DAY = formattedDate.substring(8, 10);
  yyyy = years.toInt();
  m = months.toInt();
  d = DAY.toInt();
  if ((fmod(yyyy, 4) == 0 && fmod(yyyy, 100) != 0) || (fmod(yyyy, 400) == 0))
  {
    leap = 1;
  }
  else
  {
    leap = 0;
  }

  // Limit results to year 1900-2299 (to save memory)
  while (yyyy > 2299)
  {
    yyyy = yyyy - 400;
  }
  while (yyyy < 1900)
  {
    yyyy = yyyy + 400;
  }

  // Calculating century
  c = yyyy / 100;

  // Calculating two digit year
  yy = fmod(yyyy, 100);

  // Century value based on Table
  if (c == 19) {
    cTable = 1;
  }
  if (c == 20) {
    cTable = 0;
  }
  if (c == 21) {
    cTable = 5;
  }
  if (c == 22) {
    cTable = 3;
  }

  // Jan and Feb calculations affected by leap years
  if (m == 1)
  { if (leap == 1) {
      mTable = 6;
    }
    else          {
      mTable = 0;
    }
  }
  if (m == 2)
  { if (leap == 1) {
      mTable = 2;
    }
    else          {
      mTable = 3;
    }
  }
  // Other months not affected and have set values
  if (m == 10) {
    mTable = 0;
  }
  if (m == 8) {
    mTable = 2;
  }
  if (m == 3 || m == 11) {
    mTable = 3;
  }
  if (m == 4 || m == 7) {
    mTable = 6;
  }
  if (m == 5) {
    mTable = 1;
  }
  if (m == 6) {
    mTable = 4;
  }
  if (m == 9 || m == 12) {
    mTable = 5;
  }

  // Enter the data into the formula
  SummedDate = d + mTable + yy + (yy / 4) + cTable;

  // Find remainder
  DoW = fmod(SummedDate, 7);

  // Output result

  // Remainder determines day of the week
  if (DoW == 0) {
    WD = "Sat";
  }
  if (DoW == 1) {
    WD = "Sun";
  }
  if (DoW == 2) {
    WD = "Mon";
  }
  if (DoW == 3) {
    WD = "Tue";
  }
  if (DoW == 4) {
    WD = "Wed";
  }
  if (DoW == 5) {
    WD = "Thu";
  }
  if (DoW == 6) {
    WD = "Fri";
  }
}

bool checkDate() {
  bool DT = 0;
  int ii = 0; int ii_1 = 3;
  for (int i = 0; i < 7; i++) {
    ii = ii + 3; ii_1 = ii_1 + 3;
    if (WD == dateTimeSet.substring(ii, ii_1)) {
      DT = 1;
      break;
    }
  }
  return DT;
}
bool checkTime() {
  bool TT = 0;
  String HH = timeStamp.substring(0, 2);
  String MM = timeStamp.substring(3, 5);
  if (HH == dateTimeSet.substring(22, 24)) {
    if (MM == dateTimeSet.substring(25, 27)) {
      TT = 1;
    }
  }
  return TT;
}
// GPS displayInfo
void displayInfo() {
  if (gps.location.isValid()) {
    latitude = (gps.location.lat());
    longitude = (gps.location.lng());
    Serial.print(latitude); Serial.print(" ||| "); Serial.println(longitude);
  } else {
    Serial.println(F("INVALID"));
  }
}
void ALARM() {
  int BP = digitalRead(BoxPin);
  int prev = millis();
  while (BP == 0) {
    BP = digitalRead(BoxPin);
    digitalWrite(AlarmPin, HIGH);
    sendFloat(notification_path, 1);
  }
  digitalWrite(AlarmPin, LOW);
  sendFloat(notification_path, 0);
}
