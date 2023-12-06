/***************************************************************************
  This is the code snippet used to simulate butterfly wing movements while basking
  during a behavioural trials.

  The used device had these parts:
  - An Arduino Nano Every.
  - Two 2g Ultra-Micro servo (3V-5V) with linear turning element.
  - A battery holder with on/off switch.
  - 4 1.2 Volt 2400 mAh in series.

  Written by Matteo Marcantonio.
 ***************************************************************************/


#include <Servo.h>

int posR = 0;
int posL = 0;
int topR = 110;
int bottomR = 40;
int topL = topR + 60;
int bottomL = bottomR + 60;
int previousMillis = millis();
int currentMillis = millis();
int diffL;
int interval = 10000;
int repeat = 0;
bool start = true;

Servo wingR;  // create servo object to control a servo
Servo wingL;  // create servo object to control a servo

void setup() {
  Serial.begin(9600);
  wingL.attach(12, 400, 2600);  // (pin, min, max)
  wingR.attach(10, 400, 2600);  // (pin, min, max)
}

void loop() {

  /* initial test flaps */
  if (start) {
    while (repeat < 5) {
      fly();
      repeat++;
      start = false;
      Serial.println(repeat);
    }
  }

  repeat = 0;
  long currentMillis = millis();
  if (currentMillis - previousMillis >= 10000) {
    /* Twice fast flap like if just landed */
    while (repeat < 2) {
      fastFlap();
      repeat++;
    }
    delay(1000);
    /*slow flap while basking */
    slowFlap();
  }
}

/* this is to simulate wings during flight */
// Beware may overheat servos if run for long time
void fly() {
  int diffL = 0;
  for (posR = bottomR; posR <= topR; posR += 10) {
    diffL = diffL + 10;
    posL = topL;
    wingR.write(posR);
    wingL.write(posL - diffL);
    delay(20);
  }
  diffL = 0;
  for (posR = topR; posR >= bottomR; posR -= 10) {
    diffL = diffL + 10;
    posL = bottomL;
    wingR.write(posR);
    wingL.write(posL + diffL);
    delay(20);
  }
}

/* this is to simulate fast wing movement while landed */
void fastFlap() {
  int diffL = 0;
  for (posR = bottomR; posR <= topR; posR += 1) {
    diffL++;
    wingR.write(posR);
    posL = topL;
    wingL.write(posL - diffL);
    delay(15);
  }
  diffL = 0;
  for (posR = topR; posR >= bottomR; posR -= 1) {
    diffL++;
    wingR.write(posR);
    posL = bottomL;
    wingL.write(posL + diffL);
    delay(20);
  }
}

/* this is to simulate slow wing movement while basking */
void slowFlap() {
  int diffL = 0;
  for (posR = bottomR; posR <= topR; posR += 1) {
    diffL++;
    wingR.write(posR);
    posL = topL;
    wingL.write(posL - diffL);
    delay(50);
  }
  wingR.write(topR);
  wingL.write(bottomL);
  delay(5000);

  diffL = 0;
  for (posR = topR; posR >= bottomR; posR -= 1) {
    diffL++;
    wingR.write(posR);
    posL = bottomL;
    wingL.write(posL + diffL);
    delay(40);
  }
  wingR.write(bottomR);
  wingL.write(topL);
  delay(5000);
  previousMillis = currentMillis + 50000;
}
