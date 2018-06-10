#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

//HSAPRIL4, DUMMY, HSEDITED


SoftwareSerial BTSerial(2, 3); // RX | TX[/b]

File myFile;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only 
  }
  BTSerial.begin(9600);  // HC-05 default speed in AT command more

  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
}

void loop() {
  BTSerial.begin(38400);
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    //Serial.println("HSEDITED.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      BTSerial.begin(38400);
      char reading[10] = "";
      char temp = myFile.read();
      int idx = 0;
      bool somethingWasRead = false;
      while (temp != -1 && temp != 13 && temp != 10){
        reading[idx] = temp;
        temp = myFile.read();
        idx++;
        somethingWasRead = true;
      }
      reading[idx++]='\0';
      //reading[idx] = 10;
      if (somethingWasRead){
       BTSerial.println(reading);
       Serial.println(reading);
       delayMicroseconds(500);
       //BTSerial.flush();
      }
     
    }
    
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening HSEDITED.txt");
  }
}
