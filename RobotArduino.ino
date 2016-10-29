void setup() {
  // put your setup code here, to run once:
pinMode             //Määrame, kas see on input või output
pinMode
pinMode
  
delay (5000);       //5s viivitust enne mootorite tööle minekut
motors_forward();
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

 
}

