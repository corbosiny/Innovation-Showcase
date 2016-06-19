#ifndef ActuatorUnit_h
#define ActuatorUnit_h

#include "Arduino.h"

class ActuatorUnit //consist of an actuator and two IR sensors
{

  friend class StatsPack; //so stats can access it

  public:
  ActuatorUnit(); //constructor
  
  void setupActuator(); //Asks user for the active pin number for the motor and sets it up
  void setupSensor(); //Asks user for the signal pin number of the sensor and sets it up
  
  int getLastTrialDistance(); //returns the distance the ball went on the last trial run

  int getMovingTolerance(); //returns the tolerance that if successive readings are within the ball will be considered stopped
  void setMovingTolerance(); //allows the user to set the moving tolerance
  
  private:
  int getInputInt(String message, int lowBound, int highBound); //takes in user input in the form of an int and returns it
  int calcTrialDistance(int reading); //calculates the distance the ball traveled on the last trial based on sensor readings
  
  void kickBall(float voltage); //kicks the ball at the inputed voltage
  bool isMoving(); //checks if the ball is still moving, used to determine if the trial is over

  float conductTrial(float voltage); //handles kicking the ball, running the trial, calculating distance and so forth by calling all necessary functions

  int movingTolerance = 20; //the tolerance of movement, if successive readings fall within this range of the balls distance than the trial is considered over
  
  int actuatorPin; //the active pin of the actuator
  int sensorPin; //the signal pin of the sensor
  int lastTrialDistance; //distance the ball traveled on the last trial
  
};

#endif
