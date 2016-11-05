float minFactor, midFactor, maxFactor;
float minDistance, midDistance, maxDistance;
float int motorPinRight, motorPinCentre, motorPinLeft;

const int mot_rightf = 5; // mootorite def
const int mot_leftf = 10;
const int mot_rightb = 6;
const int mot_leftb = 11;

int mot_speed = 255 // mootorite kiirus

int irSensorVasak = A0;
int irSensorParem = A2;
int irSensorKeskmine = A1;
  
void setup() {
  // put your setup code here, to run once:
pinMode (irSensorVasak, INPUT); //Määrame, kas see on input või output
pinMode (irSensorKeskmine, INPUT);
pinMode (irSensorParem, INPUT);
  
delay (5000);       //5s viivitust enne mootorite tööle minekut
motors_forward(maxFactor);
}

void loop() {
  // put your main code here, to run repeatedly:

}

int calculateDistance(int sensorPin){
  float volts = analogRead(sensorPin)*0.00322265625;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
  float distance = 65*pow(volts, -1.10);          // worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk
  Serial.println(distance);                       // print the distance
  delay(100);          // arbitary wait time.
  return distance;
  }

void sensorLogics(){
  //DISTANCE RIGHT
  if(calculateDistance(right) > minDistance && calculateDistance(right) < midDistance){
    motors_right(minFactor);
  }
  else if(calculateDistance(right) > midDistance && calculateDistance(right) <maxDistance) {
    motors_right(midFactor);
  }
  else if(calculateDistance(right) > maxDistance){
    motors_right(maxFactor);
  }

//DISTANCE MID
   if(calculateDistance(centre) > minDistance && calculateDistance(right) < midDistance){
    motors_forward(minFactor);
  }
  else if(calculateDistance(centre) > midDistance && calculateDistance(right) <maxDistance) {
    motors_forward(midFactor);
  }
  else if(calculateDistance(centre) > maxDistance){
    motors_forward(maxFactor);
  }

//DISTANCE LEFT
    if(calculateDistance(left) > minDistance && calculateDistance(right) < midDistance){
    motors_left(minFactor);
  }
  else if(calculateDistance(left) > midDistance && calculateDistance(right) <maxDistance) {
    motors_left(midFactor);
  }
  else if(calculateDistance(left) > maxDistance){
    motors_left(maxFactor);
  }
}
// motor factors
void motors_rightf(float factor){
  analogWrite(mot_rightf, 255*factor);//mootorid edasi paremale
  analogWrite (mot_leftf, 255);
  digitalWrite(mot_leftb,0);
  digitalWrite(mot_rightb,0);
}
void motors_leftf(float factor){// mootorid edasi vasakule
  analogWrite(mot_leftf, 255*factor);
  analogWrite(mot_rightf, 255);
  digitalWrite(mot_leftb, 0);
  digitalWrite(mot_rightb,0);
}
void motors_leftb (float factor){//mootorid tagasi vasakule
  analogWrite(mot_leftb, 255*factor);
  analogWrite(mot_rightb, 255);
  digitalWrite(mot_leftf, 0);
  digitalWrite(mot_rightf,0);
}
void motors_rightb ( float factor){//mootorid tagasi paremale
  analogWrite(mot_leftb, 255);
  analogWrite(mot_rightb, 255*factor);
  digitalWrite(mot_leftf, 0);
  digitalWrite(mot_rightf,0);
}
void motors_f(  float factor){//mootorid edasi
    analogWrite(mot_rightf, 255*factor);
    analogWrite(mot_leftf, 255*factor);
    digitalWrite(mot_leftb,0);
    digitalWrite(mot_rightb,0);
}
void motors_b(  float factor){ //mootorid tagasi
    analogWrite(mot_rightb, 255*factor);
    analogWrite(mot_leftb, 255*factor); 
    digitalWrite(mot_leftf,0);
    digitalWrite(mot_rightf,0);
}
  
