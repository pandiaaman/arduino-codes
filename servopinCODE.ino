#include <Servo.h> 
const int trigPin = 11;
const int echoPin = 12;

long duration;
int distance;


// Declare the Servo pin 
int servoPin = 3; 
// Create a servo object 
Servo Servo1; 

void setup() {
  // put your setup code here, to run once:
pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Servo1.attach(servoPin); 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trigPin, LOW);
  delayMicroseconds(100);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if(distance> 25){
    Servo1.write(0); 
   delay(1000); 
   // Make servo go to 90 degrees 
   Servo1.write(90); 
   delay(1000); 
  }


  
}
