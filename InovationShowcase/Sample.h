#ifndef Sample_h
#define Sample_h

class Sample
{

  friend class StatsPack;

  public:
  Sample();

  private:
  float distanceResults[100]; //holds each trial distance result for the entire sample

  float voltage; //holds voltage
  
  float mean; //holds mean
  float stdDev; //holds standard deviation
  float tScore; //holds t score
  float prob; //holds probability
  
};


#endif
