#include <Servo.h>

//objects 
Servo horizontal;
Servo vertical;
//set pins 
const int left = A0;
const int down = A1;

const int right = A5;
const int up = A4;

//const int motor = 10;
//set variables 
int rin = 0;
int lin = 0;
int uin = 0;
int din = 0;

int ravg = 0;
int lavg = 0;
int uavg = 0;
int bavg = 0;
//set limits 
int maximum = 150;
int minimum = 30;
int angleh = 0;
int anglev = 0;

int rlOut = 0;
int ubOut = 0;
void setup() {

  horizontal.attach(10);
  horizontal.write(100);
  vertical.attach(9);
  vertical.write(100);

  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(down, INPUT);
  pinMode(up, INPUT);

  horizontal.write(30);
  vertical.write(30);

}

void loop() {
  Serial.begin(9600);

  rin = analogRead(right);
  lin = analogRead(left);

  uin = analogRead(up);
  din = analogRead(down);
//take averages for control 
  ravg = (rin + uin) / 2;
  lavg = (lin + din) / 2;

  uavg = (uin + lin) / 2;
  bavg = (din + rin) / 2;


  rlOut = ravg - lavg;
  ubOut = uavg - bavg;

  angleh = horizontal.read();
  anglev = vertical.read();
//movement and calibation (+200 due to non ideal sensors) 
  if (ravg > lavg + 200) {

    horizontal.write(angleh - 1 );
    if (angleh < minimum) {
      angleh = minimum;
    }
    //delay(10)(10);
  }

  else if ( lavg > ravg - 200) {

    horizontal.write(angleh + 1);

    if (angleh > maximum) {
      angleh = maximum;
    }
    //delay(10)(10);
  }

  else {

    horizontal.write(angleh);
  }

  if (uavg > bavg -200  ) {
    vertical.write(anglev + 1);
    if (anglev > maximum) {
      anglev = maximum;
    }
    //delay(10)(10);
  }

  else if (bavg > uavg + 200) {
    vertical.write(anglev - 1);
    if (anglev < minimum) {
      anglev = minimum;
    }
    //delay(10)(10);
  }

  else {
    vertical.write(angleh);
  }
//test of output values 
  /*Serial.print(lavg);
  Serial.print(" ");
  Serial.print(ravg);
  Serial.print("    ");
  Serial.print(uavg);
  Serial.print(" ");
  Serial.println(bavg);*/


  
  //delay(10);
//test of range below 
  /*for (int i = 20; i < 160; i++) {
    horizontal.write(i);
    vertical.write(i);
    //delay(10)(50);
    }
    for (int j = 160; j > 20; j--) {
    horizontal.write(j);
    vertical.write(j);
    //delay(10)(50);*/
}
