#include <DS3231.h>
DS3231  rtc(A4, A5);
void setup()
{
  // Setup Serial connection
  Serial.begin(115200);
  // Uncomment the next line if you are using an Arduino Leonardo
  //while (!Serial) {}
  
  // Initialize the rtc object
  rtc.begin();
  
  // The following lines can be uncommented to set the date and time
rtc.setDOW(WEDNESDAY);     // Set Day-of-Week to SUNDAY
rtc.setTime(12, 0, 0);     // Set the time to 12:00:00 (24hr format)
rtc.setDate(1, 1, 2014);   // Set the date to January 1st, 2014
}
void loop()
{
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  // Send time
  Serial.println(rtc.getTimeStr());
  
  // Wait one second before repeating
  delay (1000);
}
