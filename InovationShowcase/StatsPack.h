#ifndef StatsPack_h
#define StatsPack_h

#include "Arduino.h"
#include "Sample.h"
#include "ActuatorUnit.h"

class StatsPack
{

  public:
  StatsPack(ActuatorUnit* actuator); //constructor takes in a pointer of type ActuatorUnit

  ActuatorUnit* actuatorUnit; //holds the address of the actuator unit

  //all the functions below handle the statistics side of things, the names are pretty self explanatory
  float calcMean(int sampleNum); 
  float calcStandardDeviation(int sampleNum);
  float calcTScore(int sampleNum);
  float calcProb(int sampleNum);

  //basic getters and setters
  float getTargetDistance(); 
  void setTargetDistance(); 
  
  int getNumTrials(); 
  void setNumTrials(); 

  float getVoltageStep(); 
  void setVoltageStep();

  int getSuccessTolerance();
  void setSuccessTolerance();

  void takeSample(int i); //runs through a number of trials to take a sample of data at a voltage step
  void calibrate(); //takes a whole new batch of samples to recallibrate itself
  void calcAllProbs(); //calculates the probability of hitting the target distance when hitting the ball at each voltage level

  void makeAttempt(); //attempts to hit the target distance the user specified

  float getScore(); //returns successes divided by the number of trials
  float successes = 0; //number of successful trials
  
  private:
  float voltageStep; //determined by the user, the difference in voltage between samples, can only be from 4 to 5 volts
  int numSamples; //number of samples that will be taken, determined by the voltage step
  int numTrials; //number of trials run for each sample
  float targetDistance; //the user defines this, it is the distance the ball wants to reach

  int successTolerance;
  
  Sample samples[25]; //each sample class holds all the statistical data relating to each sample
  /* ignore this
  float samples[100][100];
  float means[100];
  float stdDevs[100]; //standard deviations
  
  float tScores[100]; 
  float probs[100]; //calculated probability of hitting target distance
  */
  float referenceTProbs[8] = {.4, .3, .2, .15, .10, .05, .025, .02}; //reference probabilities for a t table, and below are all the reference scores for the first eight rows
  float referenceTScores[7][8] =  {{.325, .727, 1.376, 1.963, 3.078, 6.314, 12.706, 15.895}, 
                                   {.289, .617, 1.061, 1.386, 1.886, 2.920, 4.303, 4.849}, 
      
                                   
                                   
                                   
                                   {.277, .584, .978, 1.250, 1.638, 2.353, 3.182, 3.482}, 
                                   {.271, .569, .941, 1.190, 1.533, 2.132, 2.776, 3.0}, 
                                   {.267, .559, .920, 1.156, 1.476, 2.015, 2.571, 2.757}, 
                                   {.265, .553, .906, 1.134, 1.440, 1.943, 2.447, 2.612}, 
                                   {.263, .549, .896, 1.119, 1.415, 1.895, 2.365, 2.517}};
                                   

};

#endif
