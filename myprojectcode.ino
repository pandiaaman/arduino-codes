#include <SoftwareSerial.h>
#include<Wire.h>
//SoftwareSerial BTserial(9, 10); // RX | TX
//File myfile;

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



void setup(){
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
  //BTserial.begin(9600);
  Wire.begin();
  setupMPU();
  Serial.println("CLEARDATA");
  Serial.println("LABEL,current time,total time,distance,current dist,last dist,avg distance,non precise dist,add");
}
void loop(){
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
    
   Serial.print("DATA,TIME,");
   Serial.print("totaltime");
    Serial.print(ttime);
    Serial.print(",");
    Serial.print("distance");
    Serial.print(distance);
    Serial.print(",");
    Serial.print("currdist");
    Serial.print(distcurr);
    Serial.print(",");
    Serial.print("lastdist");
    Serial.print(distlast);
    Serial.print(",");
    Serial.print("avgdist");
    Serial.print(avgd);
    Serial.print(",");
    Serial.print("npd");
    Serial.print(npd);
    Serial.print(",");
    Serial.print("add");
    Serial.print(add);
//harsh turning will be a count ... detected by gForceZ value, keeping the box straight.
//harsh braking count has to be decided manually as the constraint has to be experimented, same with harsh accel
// add value then have addition of above three as well as npd count 
//score,rank,badges have to be thought out yet
//ranks will be given once data is in database
//badges will be given on the basis of ranks
//come up with algorithm of what to call a harsh turning case, a sudden turn at lower speed, a normal turn at higher speed or both, if any , set constraints. 

    Serial.print("Gyro(deg)");
Serial.print(" X=");
Serial.print(rotX);
Serial.print(" Y=");
Serial.print(rotY);
Serial.print(" Z=");
Serial.print(rotZ);
Serial.print(" Accel (g)");
Serial.print("X=");
Serial.print(gForceX);
Serial.print("Y=");
Serial.print(gForceY);
Serial.print("Z=");
Serial.println(gForceZ);  
 
/*
    BTserial.print(ttime);
    BTserial.print(",");
    BTserial.print(distance);
    BTserial.print(",");
     BTserial.print(distcurr);
     BTserial.print(",");
      BTserial.print(distlast);
      BTserial.print(",");
      BTserial.print(avgd);
      BTserial.print(",");
       BTserial.print(npd);
       BTserial.print(",");
       BTserial.println(add);
       BTserial.print(";");

*/


    
    distlast=distcurr;
  
  delay(2000);

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






