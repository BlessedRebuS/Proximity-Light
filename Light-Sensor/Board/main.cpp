#include <Arduino.h>

#define TRIG_DISTANCE 17

const int relayPin1 = 7;
const int relayPin2 = 8;

const int trigPin = 5;
const int echoPin = 6;

const int buttonPin = 3;

bool status1 = false;
bool status2 = false;

byte mode = 0;

void switchStatus1(bool status) {
  if (!status) {
    digitalWrite(relayPin1, LOW);
    status1 = false;
  } else {
    digitalWrite(relayPin1, HIGH);
    status1 = true;
  }
}

void switchStatus2(bool status) {
  if (!status) {
    digitalWrite(relayPin2, LOW);
    status2 = false;
  } else {
    digitalWrite(relayPin2, HIGH);
    status2 = true;
  }
}

void switchMode() {
  mode = ++mode % 3;
}

//roba sensore ultrasuoni

int getDistance() {
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
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

bool checkDistance(int distance) {

  if (distance <= TRIG_DISTANCE) return true;

  return false;
}

void setup() {

  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);

  digitalWrite(relayPin1, LOW);
  digitalWrite(relayPin2, LOW);

  attachInterrupt(digitalPinToInterrupt(buttonPin), switchMode, RISING);

  Serial.begin(9600);
}

void loop() {

  int distance = getDistance();

  if (checkDistance(distance)) {
    switch (mode) {
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

    delay(800);
  }

  delay(5);
}
