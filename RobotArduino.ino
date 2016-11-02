float minFactor, midFactor, maxFactor;
float minDistance, midDistance, maxDistance;
float int motorPinRight, motorPinCentre, motorPinLeft;

void setup() {
  // put your setup code here, to run once:
pinMode             //Määrame, kas see on input või output
pinMode
pinMode
  
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

