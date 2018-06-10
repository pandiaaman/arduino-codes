#include <SD.h>
#include <SPI.h>
//#include <SoftwareSerial.h>

//SoftwareSerial BTserial(9, 10); // RX | TX


#include<Wire.h>
long accelX,accelY,accelZ;
float gForceX,gForceY,gForceZ;

long gyroX,gyroY,gyroZ;
float rotX,rotY,rotZ;

const int trigPin = 11;
const int echoPin =12;
const int ledPin =4 ;
long duration;
int distance;
int sum=0;
long ttime=0;
int avgd;
int npd=0;
int add=0;
int distcurr;
int distlast=0;
int count=0;


File myFile;
int pinCS = 9; 


// https://howtomechatronics.com/tutorials/arduino/arduino-sd-card-data-logging-excel-tutorial/
void setup() {

  
    pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(ledPin,OUTPUT);

   Serial.begin(9600);
    pinMode(pinCS, OUTPUT);
  Wire.begin();
  setupMPU();
   Serial.println("CLEARDATA");
  Serial.println("LABEL,current time,total time,distance,current dist,last dist,avg distance,non precise dist,add");

  
  //pinMode(pinCS, OUTPUT);
  
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }  

//https://www.allaboutcircuits.com/projects/reading-and-writing-files-from-an-sd-card-with-an-arduino/
  myFile = SD.open("test.txt");

  // if the file is available, read the file
  if (myFile) 
  {
    while (myFile.available())
    {
      Serial.write(myFile.read());
    }
    myFile.close();
  }  
  // if the file cannot be opened give error report
  else {
    Serial.println("error opening the text file");
  } 


}
void loop() {
 
 
 ///////////////////////////////////////////////////////////////////////////////
 //SD.remove("test.txt");//to overwrite
  myFile = SD.open("test.txt", FILE_WRITE);
/////////////////////////////////////////////////////////////////////////////////
recordAccelRegisters();
  recordGyroRegisters();
  digitalWrite(trigPin,LOW);
  delayMicroseconds(100);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  distance=duration*0.034/2;


  distcurr=distance;
  if(distcurr<10 && distlast<10){
    npd=npd;
  }
  else if(distcurr>10 && distlast<10){
    npd=npd;
  }
  else if(distcurr<10 && distlast>10){
    npd=npd+1;
  }
  add=npd;

  count=count+1;
  ttime=ttime+2;
  sum=sum+distance;
  avgd=sum/count;
  

  if(distance<10){
    digitalWrite(ledPin,HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }

//////////////////////////////////////////////////////////////////////////////////
  
  if (myFile) {    
    ////////////////////////////////////////////////////////////////////////////////////////
      myFile.print("DATA,TIME,");
   myFile.print("totaltime");
    myFile.print(ttime);
    myFile.print(",");
    myFile.print("distance");
    myFile.print(distance);
    myFile.print(",");
    myFile.print("currdist");
    myFile.print(distcurr);
    myFile.print(",");
    myFile.print("lastdist");
    myFile.print(distlast);
   myFile.print(",");
   myFile.print("avgdist");
    myFile.print(avgd);
    myFile.print(",");
    myFile.print("npd");
    myFile.print(npd);
    myFile.print(",");
    myFile.print("add");
    myFile.print(add);
//harsh turning will be a count ... detected by gForceZ value, keeping the box straight.
//harsh braking count has to be decided manually as the constraint has to be experimented, same with harsh accel
// add value then have addition of above three as well as npd count 
//score,rank,badges have to be thought out yet
//ranks will be given once data is in database
//badges will be given on the basis of ranks
//come up with algorithm of what to call a harsh turning case, a sudden turn at lower speed, a normal turn at higher speed or both, if any , set constraints. 

    myFile.print("Gyro(deg)");
myFile.print(" X=");
myFile.print(rotX);
myFile.print(" Y=");
myFile.print(rotY);
myFile.print(" Z=");
myFile.print(rotZ);
myFile.print(" Accel (g)");
myFile.print("X=");
myFile.print(gForceX);
myFile.print("Y=");
myFile.print(gForceY);
myFile.print("Z=");
myFile.println(gForceZ);  
    ///////////////////////////////////////////////////////////////////////////////////////
    myFile.close(); 
    Serial.println("Done.");// close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening test.txt");
  }
  delay(3000);
}






void setupMPU(){
Wire.beginTransmission(0b1101000);
Wire.write(0x6B);
Wire.write(0b00000000);
Wire.endTransmission();


Wire.beginTransmission(0b1101000);
Wire.write(0x1B);
Wire.write(0x00000000);
Wire.endTransmission();


Wire.beginTransmission(0b1101000);
Wire.write(0x1C);
Wire.write(0b00000000);
Wire.endTransmission();
}

void recordAccelRegisters(){
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B);
  Wire.endTransmission();

  Wire.requestFrom(0b1101000,6);
  while(Wire.available() <6);
  accelX=Wire.read()<<8|Wire.read();
  accelY=Wire.read()<<8|Wire.read();
  accelZ=Wire.read()<<8|Wire.read();
  processAcceldata();
}

void processAcceldata(){
  gForceX=accelX/16384.0;
  gForceY=accelY/16384.0;
  gForceZ=accelZ/16384.0;
}




void recordGyroRegisters(){
  Wire.beginTransmission(0b1101000);
  Wire.write(0x43);
  Wire.endTransmission();

  Wire.requestFrom(0b1101000,6);
  while(Wire.available() <6);
  gyroX=Wire.read()<<8|Wire.read();
  gyroY=Wire.read()<<8|Wire.read();
  gyroZ=Wire.read()<<8|Wire.read();
  processGyrodata();
}

void processGyrodata(){
  rotX=gyroX/131.0;
  rotY=gyroY/131.0;
  rotZ=gyroZ/131.0;
}






