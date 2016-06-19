#include "ActuatorUnit.h"

ActuatorUnit::ActuatorUnit()
{

  Serial.println("Actutator Initialized!");
  
}

void ActuatorUnit::setupActuator()
{

    String message = "Enter the signal pin for the actuator: ";
    actuatorPin = getInputInt(message, 2, 13);

    pinMode(actuatorPin, OUTPUT);
    digitalWrite(actuatorPin, LOW); 

    Serial.println("Set to: " + actuatorPin);
    
}

void ActuatorUnit::setupSensor()
{

  String message = "Enter the signal pin for the sensor: ";
  sensorPin = getInputInt(message, 14, 19);
  Serial.println("Set to: " + sensorPin);
  
}

int ActuatorUnit::getLastTrialDistance() {return lastTrialDistance;}

//int ActuatorUnit::getNumTrials() {return numTrials;}
//void ActuatorUnit::setNumTrials(int num) {numTrials = num;}

int ActuatorUnit::getInputInt(String message, int lowBound, int highBound)
{

  char userInput;
  int intInput = 0;
  
   do{

      Serial.println(message);
      while(!Serial.available());
      while(Serial.available() > 0)
      {
    
        userInput = Serial.read(); 
        intInput += userInput - '0';
      
      }
    
    
  } while(!isDigit(userInput) || (intInput > highBound || intInput < lowBound));
  Serial.println("\n");
  
  return intInput;
  
}

void ActuatorUnit::kickBall(float voltage) 
{

  int analogVoltage = 51.2 * voltage;
  if(analogVoltage > 256) {analogVoltage = 256;}
  analogWrite(actuatorPin, analogVoltage);
  delay(4000);
  digitalWrite(actuatorPin, LOW);
 
}

int ActuatorUnit::calcTrialDistance(int reading) {return (6787 / (reading - 3)) - 4;}

int ActuatorUnit::getMovingTolerance() {return movingTolerance;}
void ActuatorUnit::setMovingTolerance() 
{

  String prompt = "Enter in the new moving tolerance: ";
  int newTolerance = getInputInt(prompt, 2, 50);
  Serial.println("Set to: " + newTolerance);
  movingTolerance = newTolerance;
  
}

bool ActuatorUnit::isMoving()
{

  int readings[5];
  readings[0] = analogRead(sensorPin);
  delay(150);
  for(int i = 1; i < 5; i++)
  {

    readings[i] = analogRead(sensorPin);
    if(readings[i] - readings[i - 1] > movingTolerance) {return true;} 
    delay(100);
    
  }

  return false;
   
}

float ActuatorUnit::conductTrial(float voltage)
{

  kickBall(voltage);
  
  while(isMoving());

  int distanceReading = analogRead(sensorPin);
  lastTrialDistance = calcTrialDistance(distanceReading);
  return lastTrialDistance;
  
}

