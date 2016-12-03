float minFactor, midFactor, maxFactor, oneFactor;  //mootori kiiruse faktorid
float minDistance, midDistance, maxDistance;  // erinevad kaugused et panna mootird erineval kiirusel liikuma

const int mot_rightf = 5; // mootorite def
const int mot_leftf = 9;
const int mot_rightb = 6;
const int mot_leftb = 10;

int mot_speed = 100; // mootorite kiirus

int IRVasak = A0;  // sensorite def
int IRParem = A5;
int IRKeskmine = A2;
  
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
pinMode (IRVasak, INPUT); //Määrame, kas see on input või output
pinMode (IRKeskmine, INPUT);
pinMode (IRParem, INPUT);
minDistance = 4;
midDistance = 70;  
maxDistance = 100;
minFactor = 0.3f;
midFactor = 0.45f;
maxFactor = 0.7f;
oneFactor = 1.0f;
delay (5000);       //5s viivitust enne mootorite tööle minekut
//motors_f(maxFactor);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorLogics();
}

int calculateDistance(int sensorPin){
  float volts = analogRead(sensorPin)*0.00322265625;   // value from sensor * (5/1024) - if running 3.3.volts then change 5 to 3.3
  float distance = 65*pow(volts, -1.10);          // worked out from graph 65 = theretical distance / (1/Volts)S - luckylarry.co.uk
  //Serial.println(distance);                       // print the distance
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
  //delay (500);
  int distKeskmine = calculateDistance(IRKeskmine);
  //delay (500);
  int distVasak = calculateDistance(IRVasak);
  //delay (500);
    
  //DISTANCE RIGHT
  //parem lähedal
  if(distParem < midDistance){
    //vasak kaugel
    if(distVasak > maxDistance){
      //keskel lähedal
      if(distKeskmine < midDistance){
    motors_rightb(maxFactor);
    Serial.println("vasakule min - palju");
    Serial.println(distVasak);
    Serial.println(distKeskmine);
    Serial.println(distParem);
    //keskel mid
      } else if (distKeskmine < maxDistance && distKeskmine > midDistance){
          motors_leftf(midFactor);
      //keskel kaugel
      } else if (distKeskmine > maxDistance){
          motors_leftf(maxFactor);
        }
      }
     //vasak mid
     else if(distVasak < maxDistance && distVasak > midDistance){
      //keskel lähedal
      if(distKeskmine < midDistance){
              motors_leftf(midFactor);
      //keskel mid
      } else if (distKeskmine < maxDistance && distKeskmine > midDistance){
          motors_leftf(midFactor);
        //keskel kaugel
        } else if (distKeskmine > maxDistance){
          motors_leftf(maxFactor);
        }
    //vasakul lähedal
    } else if(distVasak < midDistance){
      //keskel kaugel
      if(distKeskmine > maxDistance){
       motors_f(maxFactor);
       Serial.println("edasi max");
           Serial.println(distVasak);
    Serial.println(distKeskmine);
    Serial.println(distParem);
    //keskel mid
      } else if(distKeskmine < maxDistance && distKeskmine > midDistance){
       motors_f(midFactor);
        Serial.println("edasi mid");
            Serial.println(distVasak);
    Serial.println(distKeskmine);
    Serial.println(distParem);
    //keskel lähedal
      } else if(distKeskmine < midDistance){
        motors_b(minFactor);
        Serial.println("tagasi max");
            Serial.println(distVasak);
    Serial.println(distKeskmine);
    Serial.println(distParem);
      }
    }
  }
  //parem mid
  else if(distParem > midDistance && distParem < maxDistance) {
    //vasak kaugel
        if(distVasak > maxDistance){
         //keskel lähedal
      if(distKeskmine < midDistance){
      motors_rightb(maxFactor);
      //keskel mid
      } else if (distKeskmine < maxDistance && distKeskmine > midDistance){
          motors_leftf(midFactor);
      //keskel kaugel
      } else if (distKeskmine > maxDistance){
          motors_leftf(maxFactor);
        }
    //vasak mid
    } else if(distVasak < maxDistance && distVasak > midDistance){
      //keskmine kaugel
      if(distKeskmine > maxDistance){
      motors_f(maxFactor);
        Serial.println("edasi max");
            Serial.println(distVasak);
    Serial.println(distKeskmine);
    Serial.println(distParem);
    //keskmine mid
      } else if(distKeskmine < maxDistance && distKeskmine > midDistance){
        motors_f(midFactor); 
        Serial.println("edasi mid");
            Serial.println(distVasak);
    Serial.println(distKeskmine);
    Serial.println(distParem);
    //keskmine lähedal
      } else if(distKeskmine < midDistance){
        //Paremale v vasakule
        motors_rightf(maxFactor);
        Serial.println("paremale min - järsult");
            Serial.println(distVasak);
    Serial.println(distKeskmine);
    Serial.println(distParem);
      }
    //vasakul lähedal
    } else if(distVasak < midDistance){
         //keskel lähedal
      if(distKeskmine < midDistance){
      motors_leftb(maxFactor);
      //keskel mid
      } else if (distKeskmine < maxDistance && distKeskmine > midDistance){
          motors_rightf(midFactor);
      //keskel kaugel
      } else if (distKeskmine > maxDistance){
          motors_rightf(maxFactor);
        }
    }
  }
  
  //parem kaugel
  else if(distParem > maxDistance){
    //vasak kaugel
    if(distVasak > maxDistance) {
      //keskmine kaugel
      if(distKeskmine > maxDistance){
        motors_f(maxFactor);
        Serial.println("edasi max");
            Serial.println(distVasak);
    Serial.println(distKeskmine);
    Serial.println(distParem);
    //keskmine mid
      } else if(distKeskmine > midFactor && distKeskmine < maxFactor){
        motors_f(midFactor);
        Serial.println("edasi mid");
            Serial.println(distVasak);
    Serial.println(distKeskmine);
    Serial.println(distParem);
    //keskmine lähedal
      } else if(distKeskmine < midDistance){
        motors_b(minFactor);
        Serial.println("paremale min - järsult");
            Serial.println(distVasak);
    Serial.println(distKeskmine);
    Serial.println(distParem);
      }
      //vasak mid
    } else if(distVasak > midDistance && distVasak < maxDistance){
         //keskel lähedal
      if(distKeskmine < midDistance){
      motors_leftb(maxFactor);
      //keskel mid
      } else if (distKeskmine < maxDistance && distKeskmine > midDistance){
          motors_rightf(midFactor);
      //keskel kaugel
      } else if (distKeskmine > maxDistance){
          motors_rightf(maxFactor);
        }
    //vasak lähedal
    } else if(distVasak < midDistance){
         //keskel lähedal
      if(distKeskmine < midDistance){
      motors_rightb(minFactor);
      //keskel mid
      } else if (distKeskmine < maxDistance && distKeskmine > midDistance){
          motors_rightf(minFactor);
      //keskel kaugel
      } else if (distKeskmine > maxDistance){
          motors_rightf(midFactor);
        }
    }
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


//hampster out
