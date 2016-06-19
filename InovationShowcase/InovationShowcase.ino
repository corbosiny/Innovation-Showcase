#include "StatsPack.h"
#include "ActuatorUnit.h"
#include "Sample.h"


String userInput = "Hello";
int num = 1;

void setup() 
{

  delay(4000);
  Serial.begin(9600); //starts serial connection
  Serial.println("Note: *Command prompts will repeat if faced with invalid input*");
  
  pinMode(10 ,OUTPUT);
  digitalWrite(10, LOW);
  
 
}

void loop() 
{

  ActuatorUnit* actuator = new ActuatorUnit(); //creates instance of the actuator unit for the statspack class
  StatsPack stats(actuator); //creates instance of our statspack class to handle the statistics side of things
  
  while (!(userInput).equals("QUIT")) //runs a while loop to keep the program going and accepting user input and commands until quit is called
  {

      Serial.println("\nWaiting for next command..\n");
      
      while(!Serial.available()) {}

      userInput = String(Serial.read());
      Serial.flush();
      userInput.toUpperCase();
      if(userInput.equals("MAKE ATTEMPT")) //goes for the set target distance 
      {
          stats.makeAttempt();
    
          if(stats.actuatorUnit->getLastTrialDistance() > stats.getTargetDistance() + stats.getSuccessTolerance() || stats.actuatorUnit->getLastTrialDistance() < stats.getTargetDistance() - stats.getSuccessTolerance())
          {
          Serial.print("This trial was not a success...\n\n");
          }
          else {

            Serial.println("This trial was a Success!\n\n");
            stats.successes++;
      
          } 

          Serial.println("Trial is over, getting info for next trial: ");
          stats.setTargetDistance();
          
    }
    //to see a short description of how the functions work or what they do, go below to the help function displays or go to the h files for the respective class
    else if(userInput.equals("CALIBRATE")) {stats.calibrate();}
    else if(userInput.equals("GET NUM TRIALS")) {Serial.print("Number of trials per sample: "); Serial.println(stats.getNumTrials());}
    else if(userInput.equals("SET NUM TRIALS")) {stats.setNumTrials();}
    else if(userInput.equals("GET VOLTAGE STEP")) {Serial.print("Voltage Step: "); Serial.println(stats.getVoltageStep());}
    else if(userInput.equals("SET VOLTAGE STEP")) {stats.setVoltageStep();}
    else if(userInput.equals("GET LAST TRIAL DISTANCE")) {Serial.print("Last Trial Distance: "); Serial.print(stats.actuatorUnit->getLastTrialDistance());}
    else if(userInput.equals("GET SCORE")) {Serial.print("Score: "); Serial.print(stats.getScore());}
    else if(userInput.equals("GET MOVING TOLERANCE")) {Serial.print("Moving Tolerance: "); Serial.println(stats.actuatorUnit->getMovingTolerance());}
    else if(userInput.equals("SET MOVING TOLERANCE")) {stats.actuatorUnit->setMovingTolerance();}
    else if(userInput.equals("GET SUCCESS TOLERANCE")) {Serial.println(stats.getSuccessTolerance());}
    else if(userInput.equals("SET SUCCESS TOLERANCE")) {stats.setSuccessTolerance();}
    else if(userInput.equals("SETUP SENSOR")) {stats.actuatorUnit->setupActuator();}
    else if(userInput.equals("SETUP ACTUATOR")) {stats.actuatorUnit->setupSensor();}
    
    /*else if(userInput.equals("HELP")) //displays all callable user functions and a short description
    {

      Serial.println("List of user commands:");
      Serial.println("--------------------------------\n");
      Serial.println("Calibrate, the program will gather data for all samples");
      Serial.println("Get Num Trials, returns the number of trials run for each sample");
      Serial.println("Set Num Trials, allows the user to change the number of trials run for each sample *allows for more accurate guesses during real trials*");
      Serial.println("Get Voltage Step, returns the voltage step between sampels");
      Serial.println("Set Voltage Step, allows the user to change the voltage step betweens samples *also changes the number of samples*");
      Serial.println("Get Last Trial Distance, reuturns the distance the last ball was hit");
      Serial.println("Get Score, returns the current success rate of the program");
      Serial.println("Get Moving Tolerance, returns the tolerance of when we consider the ball \"stopped\"");
      Serial.println("Set Moving Tolerance, changes the tolerance of when we consider the ball \"Stopped\"");
      Serial.println("Get Success Tolerance, returns the tolerance to which the ball's distance can differ from the target distance to be considered a success");
      Serial.println("Set Success Tolerance, changes the tolerance for which the ball's distance can differ from the target distance to be considered a success");
      Serial.println("Setup sensor, asks user for the analog pin the user will use for setup purposes");
      Serial.println("Setup actuator, asks user the pin the actuator will run on for setup purposes");
      Serial.println("Quit, exits the main program");
      Serial.println("\n--------------------------------");
    
    }
    */
    else{Serial.println("Command not recognized");}
  
  }
  

}
