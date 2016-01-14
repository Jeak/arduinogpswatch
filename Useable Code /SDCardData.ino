#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define accelAddress 0x53

#define LOG_INTERVAL  1000
#define ECHO_TO_SERIAL   1 // echo data to serial port
#define WAIT_TO_START    0 // Wait for serial input in setup()

File logfile;

void setup() {
  Wire.begin();
  Serial.begin(9600);



  Serial.print("Initializing SD card...");
  // see if the card is present and can be initialized:
  pinMode(8, OUTPUT);
  if (!SD.begin(8)) {
    Serial.println("Card failed, or not present. Try formatting your card.");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  char filename[] = "LOGGER00.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i / 10 + '0';
    filename[7] = i % 10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      logfile = SD.open(filename, FILE_WRITE);
      break;  // leave the loop!
    }
  }

  if (! logfile) {
    error("couldnt create file");
  }

  Serial.print("Logging to: ");
  Serial.println(filename);
  logfile.println("XAccel,YAccel,ZAccel");
#if ECHO_TO_SERIAL
  Serial.println("XAccel,YAccel,ZAccel");
#endif //ECHO_TO_SERIAL

  
}

void loop() {
 

  


  delay((LOG_INTERVAL - 1) - (millis() % LOG_INTERVAL));
  
#if ECHO_TO_SERIAL
  
#endif
  logfile.flush();

}
void error(char *str)
{
  Serial.print("error: ");
  Serial.println(str);

  // red LED indicates error
  digitalWrite(13, HIGH);

  while (1);


}
