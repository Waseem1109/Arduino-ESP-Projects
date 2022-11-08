/******************************************************************************
DS3234_RTC_Demo.ino
Jim Lindblom @ SparkFun Electronics
original creation date: October 2, 2016
https://github.com/sparkfun/SparkFun_DS3234_RTC_Arduino_Library
Configures, sets, and reads from the DS3234 real-time clock (RTC).
Resources:
SPI.h - Arduino SPI Library
Development environment specifics:
Arduino 1.6.8
SparkFun RedBoard
SparkFun Real Time Clock Module (v14)
*****************************************************************************/
#include <SPI.h>
#include <SparkFunDS3234RTC.h>

// Comment out the line below if you want date printed before month.
// E.g. October 31, 2016: 10/31/16 vs. 31/10/16
#define PRINT_USA_DATE

//////////////////////////////////
// Configurable Pin Definitions //
//////////////////////////////////
#define DS13074_CS_PIN 10 // DeadOn RTC Chip-select pin
//#define INTERRUPT_PIN 2 // DeadOn RTC SQW/interrupt pin (optional)

void setup() 
{
  // Use the serial monitor to view time/date output
  Serial.begin(9600);
#ifdef INTERRUPT_PIN // If using the SQW pin as an interrupt
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
#endif

  // Call rtc.begin([cs]) to initialize the library
  // The chip-select pin should be sent as the only parameter
  rtc.begin(DS13074_CS_PIN);
  //rtc.set12Hour(); // Use rtc.set12Hour to set to 12-hour mode

  // Now set the time...
  // You can use the autoTime() function to set the RTC's clock and
  // date to the compiler's predefined time. (It'll be a few seconds
  // behind, but close!)
  rtc.autoTime();
  // Or you can use the rtc.setTime(s, m, h, day, date, month, year)
  // function to explicitly set the time:
  // e.g. 7:32:16 | Monday October 31, 2016:
  //rtc.setTime(16, 32, 7, 2, 31, 10, 16);  // Uncomment to manually set time

  // Update time/date values, so we can set alarms
  rtc.update();
  // Configure Alarm(s):
  // (Optional: enable SQW pin as an interrupt)
  rtc.enableAlarmInterrupt();
  // Set alarm1 to alert when seconds hits 30
  rtc.setAlarm1(30);
  // Set alarm2 to alert when minute increments by 1
  rtc.setAlarm2(rtc.minute() + 1);
}

void loop() 
{
  static int8_t lastSecond = -1;
  
  // Call rtc.update() to update all rtc.seconds(), rtc.minutes(),
  // etc. return functions.
  rtc.update();

  if (rtc.second() != lastSecond) // If the second has changed
  {
    printTime(); // Print the new time
    
    lastSecond = rtc.second(); // Update lastSecond value
  } 

  // Check for alarm interrupts
#ifdef INTERRUPT_PIN
  // Interrupt pin is active-low, if it's low, an alarm is triggered
  if (!digitalRead(INTERRUPT_PIN))
  {
#endif
    // Check rtc.alarm1() to see if alarm 1 triggered the interrupt
    if (rtc.alarm1())
    {
      Serial.println("ALARM 1!");
      // Re-set the alarm for when s=30:
      rtc.setAlarm1(30);
    }
    // Check rtc.alarm2() to see if alarm 2 triggered the interrupt
    if (rtc.alarm2())
    {
      Serial.println("ALARM 2!");
      // Re-set the alarm for when m increments by 1
      rtc.setAlarm2(rtc.minute() + 1, rtc.hour());
    }
#ifdef INTERRUPT_PIN
  }
#endif
}

void printTime()
{
  Serial.print(String(rtc.hour()) + ":"); // Print hour
  if (rtc.minute() < 10)
    Serial.print('0'); // Print leading '0' for minute
  Serial.print(String(rtc.minute()) + ":"); // Print minute
  if (rtc.second() < 10)
    Serial.print('0'); // Print leading '0' for second
  Serial.print(String(rtc.second())); // Print second

  if (rtc.is12Hour()) // If we're in 12-hour mode
  {
    // Use rtc.pm() to read the AM/PM state of the hour
    if (rtc.pm()) Serial.print(" PM"); // Returns true if PM
    else Serial.print(" AM");
  }
  
  Serial.print(" | ");

  // Few options for printing the day, pick one:
  Serial.print(rtc.dayStr()); // Print day string
  //Serial.print(rtc.dayC()); // Print day character
  //Serial.print(rtc.day()); // Print day integer (1-7, Sun-Sat)
  Serial.print(" - ");
#ifdef PRINT_USA_DATE
  Serial.print(String(rtc.month()) + "/" +   // Print month
                 String(rtc.date()) + "/");  // Print date
#else
  Serial.print(String(rtc.date()) + "/" +    // (or) print date
                 String(rtc.month()) + "/"); // Print month
#endif
  Serial.println(String(rtc.year()));        // Print year
}
