#include <Sparkfun_DRV2605L.h>

int triggerFront = 6;
int triggerRight = 9;
int triggerLeft = 13;
int triggerBack= 10;
int echoFront = 7;
int echoRight=8;
int echoLeft= 12;
int echoBack= 11 ;
int led_pin = LED_BUILTIN; 
int timeFront;
int timeRight;
int timeLeft;
int timeBack;
int distanceFront=0; 
int distanceRight=0;
int distanceLeft=0;
int distanceBack=0;
int motorRight=4;
int motorLeft=3 ;
int dist= 10;


void setup ( ) {
  Serial.begin (9600);
  pinMode (triggerFront, OUTPUT); 
  pinMode (triggerRight, OUTPUT); 
  pinMode (triggerLeft, OUTPUT); 
  pinMode (triggerBack, OUTPUT); 
  pinMode (echoFront, INPUT);
  pinMode (echoRight, INPUT);
  pinMode (echoLeft, INPUT);
  pinMode (echoBack, INPUT);
  pinMode (led_pin, OUTPUT);
  pinMode (motorLeft, OUTPUT);
  pinMode (motorRight, OUTPUT);
}


void loop ( ) {
   detect();
}

void detect(){
    digitalWrite (triggerFront, HIGH);
    delayMicroseconds (10);
    digitalWrite (triggerFront, LOW);
    timeFront = pulseIn(echoFront, HIGH); 
    digitalWrite (triggerRight, HIGH);
    delayMicroseconds (10);
    digitalWrite (triggerRight, LOW);
    timeRight = pulseIn(echoRight, HIGH);
    digitalWrite (triggerLeft, HIGH);
    delayMicroseconds (10);
    digitalWrite (triggerLeft, LOW);
    timeLeft = pulseIn(echoLeft, HIGH); 
    digitalWrite (triggerBack, HIGH);
    delayMicroseconds (10);
    digitalWrite (triggerBack, LOW);
    timeBack = pulseIn(echoBack, HIGH); 
    
    distanceFront = (timeFront * 0.034) / 2;
    distanceRight = (timeRight * 0.034) / 2; 
    distanceLeft = (timeLeft * 0.034) / 2;
    distanceBack = (timeBack * 0.034) / 2; 
    
    distanceFront= distanceFront<0 ? 0:distanceFront;
    distanceRight= distanceRight<0 ? 0:distanceRight;
    distanceLeft= distanceLeft<0 ? 0:distanceLeft;
    distanceBack= distanceBack<0 ? 0:distanceBack;
    
    Serial.print("Front ");
    Serial.println(distanceFront);
    Serial.print("Right ");
    Serial.println(distanceRight);
    Serial.print("Left ");
    Serial.println(distanceLeft);
    Serial.print("Back ");
    Serial.println(distanceBack);
    if (distanceFront || distanceRight || distanceLeft || distanceBack ){
        if(obstacleFront()){
          //GO FRONT
          digitalWrite(led_pin, HIGH);
          digitalWrite(motorRight,250);
          digitalWrite(motorLeft,250);
        }
        else if (obstacleRight()){
          //GO RIGHT
          digitalWrite(led_pin, HIGH);
          digitalWrite(motorRight,200);
          digitalWrite(motorLeft,250);
        }
        else if (obstacleLeft()){
          //GO LEFT
          digitalWrite(led_pin, HIGH);
          digitalWrite(motorRight,250);
          digitalWrite(motorLeft,200);
        }
        else if (obstacleBack()){
          //TURN 180 DEGREES
          digitalWrite(led_pin, HIGH);
          digitalWrite(motorRight,0);
          digitalWrite(motorLeft,0);
        }
    }
  
    else{   
        
        // TURN Around until you detect something
        digitalWrite(led_pin, LOW);
        digitalWrite(motorRight,0);
        digitalWrite(motorLeft,0);
    } 
}
bool obstacleFront(){
  return (distanceFront > distanceLeft) && (distanceFront > distanceRight) && (distanceFront > distanceBack) && (distanceFront <= dist);
}

bool obstacleRight(){
  return (distanceRight > distanceLeft) && (distanceRight > distanceFront) && (distanceRight > distanceBack) && (distanceRight <= dist);
}

bool obstacleLeft(){
  return (distanceLeft > distanceRight) && (distanceLeft > distanceFront) && (distanceLeft > distanceBack) && (distanceLeft <= dist);
}

bool obstacleBack(){
  return (distanceBack > distanceRight) && (distanceBack > distanceFront) && (distanceBack > distanceLeft) && (distanceBack <= dist);
}
