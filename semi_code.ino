#include <SoftwareSerial.h>
#include<Wire.h>
SoftwareSerial BTserial(9, 10); // RX | TX
//need to select the state of the bluetooth module,that is if it is connected then state is 1 and if it is not connected then state will be 0, now check if , system is connected that is state =is 1 flag is 0 then print all the values 
//once printed then convert the value of flag to 1,so it will not print again once connected, now once disconnected, again put the value of the flag as 0;

int buzz=8;
long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;

const int trigPin = 11;
const int echoPin = 12;
const int ledPin = 4 ;
long duration;
int distance;
int sum = 0;
long ttime = 0;
int avgd;
int npd = 0;
int add = 0;
int distcurr;
int distlast = 0;
int count = 0;

int flag=0;

int harsha = 0;
int harshb = 0;
float lasta = 0.00;
float curra;
float diffa;
float mdiffa;


int turna;
float turndeg;


float lastdiffa;
float lastturndeg;
const byte BTpin = 2;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  pinMode(BTpin, INPUT); 
  Serial.begin(9600);
  BTserial.begin(9600);
  Wire.begin();
  setupMPU();
  Serial.println("LABEL,current time,total time,distance,current dist,last dist,avg distance,non precise dist,add");


}
void loop() {
    Serial.println("LABEL,current time,total time,distance,current dist,last dist,avg distance,non precise dist,add");

Serial.write(13); 
  recordAccelRegisters();
  recordGyroRegisters();
  digitalWrite(trigPin, LOW);
  delayMicroseconds(100);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;


  distcurr = distance;
  if (distcurr < 3 && distlast < 3) {
    npd = npd;
  }
  else if (distcurr > 3 && distlast < 3) {
    npd = npd;
  }
  else if (distcurr < 3 && distlast > 3) {
    npd = npd + 1;
    add = add + 1;
    tone(buzz,1000,500);
  }

  /////////////////////////////////////////////////////////////////
  curra = gForceX;
  diffa = curra - lasta;
  mdiffa = abs(diffa);
  if (((mdiffa > 1.7) && (diffa > 0)) && (lastdiffa < 1.7)) {
    harsha = harsha + 1;
    add = add + 1;
    
    tone(buzz,1000,500);
  }
  else if (((mdiffa > 1.7) && (diffa > 0)) && (lastdiffa > 1.7)) {
    harsha = harsha;
    add = add;
  }





  if (((mdiffa > 1.7) && (diffa < 0)) && (lastdiffa < 1.7)) {
    harshb = harshb + 1;
    add = add + 1;
    
    tone(buzz,1000,500);
  }

  else if (((mdiffa > 1.7) && (diffa < 0)) && (lastdiffa > 1.7)) {
    harshb = harshb;
    add = add;
  }

  ///////////////////////////////////////////////////////////////////
  turndeg = rotZ;
  if (((turndeg > 30 ) && (mdiffa > 1.2)) && (lastturndeg < 30)) {
    turna = turna + 1;
    add = add + 1;
    
    tone(buzz,1000,500);
  }
  else if (((turndeg > 30 ) && (mdiffa > 1.2)) && (lastturndeg > 30)) {
    turna = turna;
    add = add;
  }


  ////////////////////////////////////////////////////////////////
 /// to check gyro is working:please remove later
  ///////////////////////////////////////////////////////////////
  if(turndeg>30){
    add=add+1;
    tone(buzz,1000,500);
    
  }
  if(turndeg<-30){
    add=add+1;
    tone(buzz,1000,500);
    
  }
  ////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////
  count = count + 1;
  ttime = ttime + 2;
  sum = sum + distance;
  avgd = sum / count;


  if (distance < 10) {
    digitalWrite(ledPin, HIGH);
  }
  else {
    digitalWrite(ledPin, LOW);
  }
//
    //if ( digitalRead(BTpin)==HIGH){

     //  if(flag==0){
    Serial.print("DATA,TIME,");
    Serial.print("totaltime");
    Serial.print(ttime);
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

    Serial.print("curr a");
    Serial.print(curra);
    Serial.print(",");

    Serial.print("last a");
    Serial.print(lasta);
    Serial.print(",");

    Serial.print("m diff a");
    Serial.print(mdiffa);
    Serial.print(",");

    Serial.print("last diff a");
    Serial.print(lastdiffa);
    Serial.print(",");


    Serial.print("turn deg");
    Serial.print(turndeg);
    Serial.print(",");

    Serial.print("last turn deg");
    Serial.print(lastturndeg);
    Serial.print(",");

    Serial.print("turn harsh");
    Serial.print(turna);
    Serial.print(",");

    Serial.print("harsh a");
    Serial.print(harsha);
    Serial.print(",");

    Serial.print("harsh b");
    Serial.print(harshb);
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



    //BTserial.print("DATA,TIME,");
    //BTserial.print("totaltime");
    BTserial.print(ttime);
    BTserial.print(",");
    //BTserial.print("currdist");
    BTserial.print(distcurr);
    BTserial.print(",");
    //BTserial.print("lastdist");
    // BTserial.print(distlast);
    //BTserial.print(",");
    //BTserial.print("avgdist");
    //BTserial.print(avgd);
    //BTserial.print(",");
    //BTserial.print("npd");
    BTserial.print(npd);
    BTserial.print(",");
    /*
       //  BTserial.print("curr a");
        BTserial.print(curra);
        BTserial.print(",");

         //BTserial.print("last a");
        BTserial.print(lasta);
        BTserial.print(",");

         //BTserial.print("m diff a");
        BTserial.print(mdiffa);
        BTserial.print(",");

         BTserial.print("last diff a");
        BTserial.print(lastdiffa);
        BTserial.print(",");


        BTserial.print("turn deg");
         BTserial.print(turndeg);
         BTserial.print(",");

          BTserial.print("last turn deg");
         BTserial.print(lastturndeg);
         BTserial.print(",");

      BTserial.print("turn harsh");
         BTserial.print(turna);
         BTserial.print(",");

      //    BTserial.print("harsh a");
         BTserial.print(harsha);
         BTserial.print(",");

        // BTserial.print("harsh b");
         BTserial.print(harshb);
         BTserial.print(",");

          //BTserial.print("npd");
        BTserial.print(npd);
         BTserial.print(",");
         //BTserial.print("add");
         BTserial.print(add);
      //harsh turning will be a count ... detected by gForceZ value, keeping the box straight.
      //harsh braking count has to be decided manually as the constraint has to be experimented, same with harsh accel
      // add value then have addition of above three as well as npd count
      //score,rank,badges have to be thought out yet
      //ranks will be given once data is in database
      //badges will be given on the basis of ranks
      //come up with algorithm of what to call a harsh turning case, a sudden turn at lower speed, a normal turn at higher speed or both, if any , set constraints.
    */
    // Serial.print("Gyro(deg)");
    //Serial.print(" X=");



    BTserial.print(rotX);
    BTserial.print(",");
    //Serial.print(" Y=");
    BTserial.print(rotY);
    BTserial.print(",");
    //Serial.print(" Z=");
    BTserial.print(rotZ);
    BTserial.print(",");
    //Serial.print(" Accel (g)");
    //Serial.print("X=");
    BTserial.print(gForceX);
    BTserial.print(",");
    //Serial.print("Y=");
    BTserial.print(gForceY);
    BTserial.print(",");
    //Serial.print("Z=");
    BTserial.println(gForceZ);
    BTserial.print(",");
        BTserial.print(add);
    BTserial.print(";");
//}
//flag=1;

// }

//if( digitalRead(BTpin)==LOW){
//flag=0;
  
//}

  lasta = curra;
  distlast = distcurr;
  lastdiffa = mdiffa;
  lastturndeg = turndeg;
  delay(2000);

}


void setupMPU() {
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

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x3B);
  Wire.endTransmission();

  Wire.requestFrom(0b1101000, 6);
  while (Wire.available() < 6);
  accelX = Wire.read() << 8 | Wire.read();
  accelY = Wire.read() << 8 | Wire.read();
  accelZ = Wire.read() << 8 | Wire.read();
  processAcceldata();
}

void processAcceldata() {
  gForceX = accelX / 16384.0;
  gForceY = accelY / 16384.0;
  gForceZ = accelZ / 16384.0;
}




void recordGyroRegisters() {
  Wire.beginTransmission(0b1101000);
  Wire.write(0x43);
  Wire.endTransmission();

  Wire.requestFrom(0b1101000, 6);
  while (Wire.available() < 6);
  gyroX = Wire.read() << 8 | Wire.read();
  gyroY = Wire.read() << 8 | Wire.read();
  gyroZ = Wire.read() << 8 | Wire.read();
  processGyrodata();
}

void processGyrodata() {
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0;
  rotZ = gyroZ / 131.0;
}







