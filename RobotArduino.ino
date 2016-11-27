float minFactor, midFactor, maxFactor;  //mootori kiiruse faktorid
float minDistance, midDistance, maxDistance;  // erinevad kaugused et panna mootird erineval kiirusel liikuma

const int mot_rightf = 5; // mootorite def
const int mot_leftf = 10;
const int mot_rightb = 6;
const int mot_leftb = 11;

int mot_speed = 255; // mootorite kiirus

int IRVasak = A0;  // sensorite def
int IRParem = A2;
int IRKeskmine = A1;
  
void setup() {
  // put your setup code here, to run once:
pinMode (IRVasak, INPUT); //Määrame, kas see on input või output
pinMode (IRKeskmine, INPUT);
pinMode (IRParem, INPUT);
minDistance = 4;
midDistance = 10;  
maxDistance = 20;
minFactor = 0.3f;
midFactor = 0.65f;
maxFactor = 1.0f;
delay (5000);       //5s viivitust enne mootorite tööle minekut
motors_f(maxFactor);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorLogics();
}

int calculateDistance(int sensorPin){
  float volts = analogRead(sensorPin)*0.00322265625;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
  float distance = 65*pow(volts, -1.10);          // worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk
  Serial.println(distance);                       // print the distance
  delay(100);          // arbitary wait time.
  return distance;
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
void motors_rightb (float factor){//mootorid tagasi paremale
  analogWrite(mot_leftb, 255);
  analogWrite(mot_rightb, 255*factor);
  digitalWrite(mot_leftf, 0);
  digitalWrite(mot_rightf,0);
}
void motors_f(float factor){//mootorid edasi
    analogWrite(mot_rightf, 255*factor);
    analogWrite(mot_leftf, 255*factor);
    digitalWrite(mot_leftb,0);
    digitalWrite(mot_rightb,0);
}
void motors_b(float factor){ //mootorid tagasi
    analogWrite(mot_rightb, 255);
    analogWrite(mot_leftb, 255); 
    digitalWrite(mot_leftf,0);
    digitalWrite(mot_rightf,0);
}

void sensorLogics(){
  int distParem = calculateDistance(IRParem);
  int distKeskmine = calculateDistance(IRKeskmine);
  int distVasak = calculateDistance(IRVasak);
    
  //DISTANCE RIGHT
  if(distParem < midDistance){
    if(distVasak > maxDistance){
    motors_leftf(maxFactor);
    } else if(distVasak < maxDistance && distVasak > midDistance){
      motors_leftf(midFactor);
    } else if(distVasak < midDistance){
      if(distKeskmine > maxDistance){
       motors_f(maxFactor);
      } else if(distKeskmine < maxDistance && distKeskmine > midDistance){
       motors_f(midFactor);
      } else if(distKeskmine < midDistance){
        motors_b(maxFactor);
      }
    }
  }
  else if(distParem > midDistance && distParem < maxDistance) {
        if(distVasak > maxDistance){
        motors_leftf(midFactor);
    } else if(distVasak < maxDistance && distVasak > midDistance){
      if(distKeskmine > maxDistance){
      motors_f(maxFactor);
      } else if(distKeskmine < maxDistance && distKeskmine > midDistance){
        motors_f(midFactor); 
      } else if(distKeskmine < midDistance){
        //Paremale v vasakule
        motors_rightf(minFactor);
    } else if(distVasak < midDistance){
      motors_rightf(midFactor);
    }
  }
  else if(distParem > maxDistance){
    if(distVasak > maxDistance) {
      if(distKeskmine > maxDistance){
        motors_f(maxFactor);
      } else if(distKeskmine > midFactor && distKeskmine < maxFactor){
        motors_f(midFactor);
      } else if(distKeskmine < midDistance){
        motors_rightf(minFactor);
      }
    } else if(distVasak > midDistance && distVasak < maxDistance){
      motors_rightf(midFactor);
    } else if(distVasak < midDistance){
      motors_rightf(minFactor);
    }
  }
     
  
/*
//DISTANCE MID
   if(distKeskmine > minDistance && distKeskmine < midDistance){
  motors_f(minFactor);
  }
  else if(distKeskmine > midDistance && distKeskmine < maxDistance) {
    motors_f(midFactor);
  }
  else if(distKeskmine > maxDistance){
    //motors_f(maxFactor);
  }

//DISTANCE LEFT
    if(distParem > minDistance && distParem < midDistance){
    motors_leftf(minFactor);
  }
  else if(distVasak > midDistance && distVasak <maxDistance) {
    motors_leftf(midFactor);
  }
  else if(distVasak > maxDistance){
    motors_leftf(maxFactor);
  }
} */ 
}
}


