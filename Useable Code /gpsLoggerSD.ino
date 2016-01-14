#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>
/********************************************************************************************
GPS DataLogger, ThoughtSTEM 2015

This example uses Software Serial and the SparkFun GPS to write NEMA GPS code to an SD Card.

This code was written for the following parts:
   Arduino UNO
   SparkFun GPS Shield (DLINE Mode!)
   SparkFun MicroSD Shield
   
Based on TinyGPSPlus/DeviceExample.ino by Mikal Hart

Modified by Stephen Gilardi (ThoughtSTEM), 2015


How to use:
  Stack MicroSD shield and GPS shield onto an Arduino.
  Confirm SD card is plugged in.
  Power Arduino, you will begin datalogging GPS coordinates.
  
Common Problems:
  MicroSD card not formatted.
  GPS shield not recieving a signal.
********************************************************************************************/

// Choose two Arduino pins to use for software serial
// The GPS Shield uses D2 and D3 by default when in DLINE mode
int RXPin = 2;
int TXPin = 3;

// The Skytaq EM-506 GPS module included in the GPS Shield Kit
// uses 4800 baud by default
int GPSBaud = 4800;


// Create a software serial port called "gpsSerial"
// This is how we will communicate with the GPS
SoftwareSerial gpsSerial(RXPin, TXPin);

void setup()
{
  // Start the Arduino hardware serial port at 9600 baud, used for debugging on a computer.
  Serial.begin(9600);
  
  

  // Start the software serial port at the GPS's default baud
  gpsSerial.begin(GPSBaud);
  
  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  pinMode(8, OUTPUT);
  if (!SD.begin(8)) {
    Serial.println("Card failed, or not present. Try formatting your card.");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
}

void loop()
{
  
  //checks to see if the GPS is outputting a new line of data.
  if(gpsSerial.available() >= 6 && gpsSerial.read() == '$' && gpsSerial.read() == 'G' && gpsSerial.read() == 'P' && gpsSerial.read() == 'G' && gpsSerial.read() == 'G' && gpsSerial.read() == 'A'){
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    char c = 0;
    dataFile.print("$GPGGA");
    Serial.print("$GPGGA");
    do{
      //Prints the data from the GPS onto the SD card and a Serial Monitor.
      if (gpsSerial.available()){
        c = gpsSerial.read();
        dataFile.write(c);
        Serial.write(c);
      }
    }
    while (c != '\n');
  dataFile.println();
  Serial.println();
  dataFile.close();
  }

 }
