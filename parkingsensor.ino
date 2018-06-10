//project testing vehicle: maruti swift dzire
float legth_vehicle=4160;//units: mm
float door_length=1130;//units: mm

float front_range=length_vehicle/4;//units: mm
float back_range=length_vehicle/6;//uints: mm


float range1_a=door_length/3;//for obstacles on driver's side
float range1_b=door_length/2;//for space for driver's entry in vehicle
float range2=front_range;//for obstacles in front
float range3=door_length/3;//for obstacles in right side
float range4=back_range;//for obstacles behind

int buzz=8;

void setup() {
  // put your setup code here, to run once:
 pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(trigPin4, OUTPUT);
  pinMode(echoPin4, INPUT);
  
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(100);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2; //for driver side ultrasonic sensor

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(100);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2; //for front side ultrasonic sensor

  digitalWrite(trigPin3, LOW);
  delayMicroseconds(100);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3 = duration3 * 0.034 / 2; //for right side ultrasonic sensor

  digitalWrite(trigPin4, LOW);
  delayMicroseconds(100);
  digitalWrite(trigPin4, HIGH);
  delayMicroseconds(100);
  digitalWrite(trigPin4, LOW);
  duration4 = pulseIn(echoPin4, HIGH);
  distance4 = duration4 * 0.034 / 2; //for back side ultrasonic sensor
 

  if(distance1< range1_b){
    tone(buzz,1000,500); //buzzer alert
  }
  else if(dist2<range2 && dist4<range4){
    tone(buzz,1000,500); //buzzer alert
  }
  else if((dist2<range2 &&(dist1<range1_a || dist3 <range 3)
  && (dist4<length_vehicle)){
    tone(buzz,1000,500); //buzzer alert
  }
  else if(dist1<range1 && dist2<range2) {
    tone(buzz,1000,500); //buzzer alert
  }
}
