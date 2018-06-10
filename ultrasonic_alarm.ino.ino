const int trigPin = 11;
const int echoPin =12;
const int ledPin = 2;
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
  Serial.println("CLEARDATA");
  Serial.println("LABEL,current time,total time,distance,current dist,last dist,avg distance,non precise dist,add");
}
void loop(){
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
    Serial.print(ttime);
    Serial.print(",");
    Serial.print(distance);
    Serial.print(",");
    Serial.print(distcurr);
    Serial.print(",");
    Serial.print(distlast);
    Serial.print(",");
    Serial.print(avgd);
    Serial.print(",");
    Serial.print(npd);
    Serial.print(",");
    Serial.println(add);
 


    distlast=distcurr;
  
  delay(2000);

}

