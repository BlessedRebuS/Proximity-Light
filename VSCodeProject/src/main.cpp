#include <Arduino.h>

//--------------------------------------
//-----CONFIGURATION PARAMETERS---------
#define TRIG_DISTANCE 17 // cm
#define SWITCH_DELAY 800 // ms

#define DEBUG_MODE false // If 'true' enables Serial communication for better debugging
//--------------------------------------

//--------------------------------------
//--------LIGHTS CONFIGURATION----------
#include <FastLED.h>
#define LIGHTS_ON false // Enables lights, set to true or false

#define DATA_PIN 4
//#define CLK_PIN   4
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB
#define NUM_LEDS 64
CRGB leds[NUM_LEDS];
uint8_t gHue;
#define FRAMES_PER_SECOND 60
#define BRIGHTNESS 80

void rainbow()
{
  gHue++;
  fill_rainbow(leds, NUM_LEDS, gHue, 7);
  FastLED.show();

  FastLED.delay(1000 / FRAMES_PER_SECOND);
}
//--------------------------------------

//--------------------------------------
//-----ARDUINO PIN----------------------
const int trigPin = 5; //default D5
const int echoPin = 6; //default D6

const int buttonPin = 3; //default D3
const int relayPin1 = 7; //default D7
const int relayPin2 = 8; //default D8
//--------------------------------------

//--------------------------------------
//------------FUNCTIONS-----------------
bool status;
int distance;

byte mode = 0;
void switchStatus1(bool value)
{
  if (!value)
  {
    digitalWrite(relayPin1, LOW);
  }
  else
  {
    digitalWrite(relayPin1, HIGH);
  }
}

void switchStatus2(bool value)
{
  if (!value)
  {
    digitalWrite(relayPin2, LOW);
  }
  else
  {
    digitalWrite(relayPin2, HIGH);
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

  if (DEBUG_MODE)
  {
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  return distance;
}

bool checkDistance(int distance)
{

  if (distance <= TRIG_DISTANCE)
    return true;

  return false;
}

void switchMode()
{
  mode = ++mode % 3;

  switch (mode)
  {
  case 0:
    switchStatus1(true);
    switchStatus2(true);
    break;
  case 1:
    switchStatus1(true);
    switchStatus2(false);
    break;
  case 2:
    switchStatus1(false);
    switchStatus2(true);
    break;
  }

  if(DEBUG_MODE){
    Serial.print("Mode: ");
    Serial.println(mode);
  }
}

void turnOff()
{
  switchStatus1(false);
  switchStatus2(false);
}

void setup()
{

  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(relayPin1, LOW);
  digitalWrite(relayPin2, LOW);

  attachInterrupt(digitalPinToInterrupt(buttonPin), switchMode, RISING);

  // Lights setup
  if (LIGHTS_ON)
  {
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    gHue = 0;
  }

  if (DEBUG_MODE)
    Serial.begin(9600);

  mode = 0;
  status = false;
}

void loop()
{
  distance = getDistance();

  if (checkDistance(distance))
  {
    if (status)
    {
      turnOff();
      status=false;
    }
    else{
      switchMode();
      status=true;
    }
    delay(SWITCH_DELAY);
  }

  if (LIGHTS_ON)
    rainbow();
}