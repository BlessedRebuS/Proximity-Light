#include <Arduino.h>

//--------------------------------------
//-----CONFIGURATION PARAMETERS---------
#define TRIG_DISTANCE 17 // cm
#define SWITCH_DELAY 800 // ms
//--------------------------------------

//--------------------------------------
//-----ARDUINO PIN----------------------
const int trigPin = 9;  //default D9
const int echoPin = 8;  //default D8
const int relayPin = 7; //default D7
//--------------------------------------

//--------------------------------------
//------------FUNCTIONS-----------------
bool status = false;

void switchStatus()
{
  if (status)
  {
    digitalWrite(relayPin, LOW);
    status = false;
  }
  else
  {
    digitalWrite(relayPin, HIGH);
    status = true;
  }
}

int getDistance()
{
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  unsigned long duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

bool checkDistance(int distance)
{
  if (distance <= TRIG_DISTANCE)
    return true;
  return false;
}

void setup()
{
  pinMode(relayPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  digitalWrite(relayPin, LOW);

  Serial.begin(9600);
}

void loop()
{

  int distance = getDistance();

  if (checkDistance(distance))
  {
    switchStatus();
    delay(SWITCH_DELAY);
  }

  delay(5);
}