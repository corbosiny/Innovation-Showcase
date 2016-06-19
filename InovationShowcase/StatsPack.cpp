#include "StatsPack.h"
#include "ActuatorUnit.h"

StatsPack::StatsPack(ActuatorUnit* actuator)
{

 actuatorUnit = actuator;

 setTargetDistance();
 setNumTrials();
 setVoltageStep();
 
 numSamples = (1 / voltageStep);

 for(int i = 1; i <= 1 / voltageStep; i++) {samples[i].voltage = 4 + (voltageStep * i);}
 
}

float StatsPack::calcMean(int sampleNum)
{

  int total = 0;
  for(int i = 0; i < numTrials; i++) {total += samples[sampleNum].distanceResults[i];}

  return total / numTrials;
  
}

float StatsPack::calcStandardDeviation(int sampleNum)
{

  int total = 0;
  for(int i = 0; i < numTrials; i++) {total += pow(samples[sampleNum].distanceResults[i] - samples[sampleNum].mean, 2);}

  return sqrt(total);
  
}

float StatsPack::calcTScore(int sampleNum) {return (samples[sampleNum].mean - targetDistance) / (samples[sampleNum].stdDev / sqrt(numTrials));}

float StatsPack::calcProb(int sampleNum)
{

  int df = numTrials - 2;
  for(int i = 0; i < 8; i++)
  {

    if (referenceTScores[df][i] == samples[sampleNum].tScore)
    {return referenceTProbs[i];}
    else if(referenceTScores[df][i] > samples[sampleNum].tScore) {return (referenceTProbs[i] + referenceTProbs[i+1]) / 2;}
    
  }

  return 0;
  
}

float StatsPack::getTargetDistance() {return targetDistance;}
void StatsPack::setTargetDistance()
{

  String prompt = "Enter the target distance in centimeters: ";
  float newDistance = (float) actuatorUnit->getInputInt(prompt, 0, 72);
  Serial.println("Set to: " + String(newDistance));
  targetDistance = newDistance;

}

int StatsPack::getNumTrials() {return numTrials;}
void StatsPack::setNumTrials() 
{

  String prompt = "Enter the number of trials for each sample: ";
  int trialNum = actuatorUnit->getInputInt(prompt, 0, 7);
  Serial.println("Set to: " + trialNum);
  numTrials = trialNum;
  
}

float StatsPack::getVoltageStep() {return voltageStep;}
void StatsPack::setVoltageStep() 
{

  String prompt1 = "Enter the first digit of the voltage step: ";
  String prompt2 = "Enter the second digit number of the voltage step: ";
  
  int firstNum = actuatorUnit->getInputInt(prompt1, 0, 9);
  int secondNum = actuatorUnit->getInputInt(prompt2, 0, 9);
  
  float newVoltageStep = (firstNum / 10.0) + (secondNum / 100.0);
  
  Serial.println("Set to: " + String(newVoltageStep));  
  voltageStep = newVoltageStep;
  numSamples = 2 / voltageStep;
  
}

int StatsPack::getSuccessTolerance() {return successTolerance;}
void StatsPack::setSuccessTolerance()
{

  String prompt = "Enter the success tolerance: ";
  int newSuccessTolerance = actuatorUnit->getInputInt(prompt, 0, 80);
  Serial.println("Set to: " + newSuccessTolerance);
  successTolerance = newSuccessTolerance;
  
}

void StatsPack::takeSample(int i)
{

     Serial.println("Beginning trial one..");
     for(int j = 0; j < numTrials; j++) 
     {
     
      samples[i].distanceResults[j] = actuatorUnit->conductTrial(samples[i].voltage);
      Serial.println("Sample " + String(i + 1) + " trial " + String(j + 1) + " is complete\n");
      while(!Serial.available());
      Serial.read();
      Serial.flush();
      if(j < numTrials - 1) {Serial.println("Beginning trial " + String(i + 2) + "..");}
     
     }
     
     samples[i].mean = calcMean(i);
     samples[i].stdDev = calcStandardDeviation(i);
     samples[i].tScore = calcTScore(i);      
     samples[i].prob = calcProb(i);
  
}

void StatsPack::calibrate()
{

  for(int i = 0; i < numSamples; i++) 
  {
  
    takeSample(i);
    Serial.println("Sample " + String(i + 1) + " is complete");
    while(!Serial.available());
    Serial.read();
    Serial.flush();
    if(i < numSamples - 1) {Serial.println("Beginning sample " + String(i + 2) + "..");}
  
  }

}

void StatsPack::calcAllProbs()
{

  for(int i = 0; i < numSamples; i++) {samples[i].prob = calcProb(i);}
  
}

float StatsPack::getScore() { return (float) successes / getNumTrials(); }

void StatsPack::makeAttempt()
{

  float largestProb = 0;
  float voltage = 0;
  
  for(int i = 0; i < numSamples; i++) 
  {
    
    if(samples[i].prob > largestProb) 
    {

      largestProb = samples[i].prob;
      voltage = samples[i].voltage;
      
    }
      
  }

  actuatorUnit->conductTrial(voltage);
  numTrials++;
  
}

