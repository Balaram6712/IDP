#include <Servo.h>
Servo myServo;

int rn = 6;
int rp = 5;
int lp = 10; 
int ln = 9 ; 
int pump = 4;
int mop = 11;
int serv = 3;
int spd = 255;
char incomingByte = '0'; // for incoming serial data

void setup()
{
myServo.attach(3);
myServo.write(0);  
pinMode(rn, OUTPUT);
pinMode(rp, OUTPUT);
pinMode(lp, OUTPUT);
pinMode(ln, OUTPUT);
pinMode(pump, OUTPUT);
pinMode(mop, OUTPUT);
analogWrite(rn, 0);
analogWrite(rp, 0);
analogWrite(lp, 0);
analogWrite(ln, 0);
digitalWrite(pump, LOW);
digitalWrite(mop, HIGH);
Serial.begin(9600);
}


void loop()
{

if(Serial.available())
  incomingByte = Serial.read();

switch(incomingByte)
{

case 'S': // control to stop the robot
analogWrite(rn, 0); 
analogWrite(rp, 0);
analogWrite(lp, 0);
analogWrite(ln, 0);
Serial.println("Stop");
incomingByte='*';
break;

case 'R': //control for right
analogWrite(rn, spd); 
analogWrite(rp, 0);
analogWrite(lp, spd);
analogWrite(ln, 0);
Serial.println("Right");
incomingByte='*';
break;


case 'L': //control for left
analogWrite(rn, 0); 
analogWrite(rp, spd);
analogWrite(lp, 0);
analogWrite(ln, spd);
Serial.println("Left");
incomingByte='*';
break;


case 'F': //control for forward
analogWrite(rp, spd); 
analogWrite(rn, 0);
analogWrite(ln, 0);
analogWrite(lp, spd);
Serial.println("Forward");
incomingByte='*';
break;


case 'B': //control for backward
analogWrite(rp, 0); 
analogWrite(rn, spd);
analogWrite(ln, spd);
analogWrite(lp, 0);
Serial.println("Backward");
incomingByte='*';
break;


case 'P': // pump on
digitalWrite(pump, HIGH);
Serial.println("pump on");
incomingByte='*';
break;

case 'p': // pump off
digitalWrite(pump, LOW); 
Serial.println("pump off");
incomingByte='*';
break;

case 'M':
digitalWrite(mop, HIGH); // mopper on
Serial.println("mop on");
incomingByte='*';
break;

case 'm':
digitalWrite(mop, LOW); // mopper off
Serial.println("mop off");
incomingByte='*';
break;

case 'U': // roller up
myServo.write(0);
Serial.println("roller up");
incomingByte='*';
break;

case 'u': // roller down
myServo.write(135);
Serial.println("roller down");
incomingByte='*';
break;


case '1':
spd = 155;
Serial.println("spd= 10");
incomingByte='*';
break;

case '2':
spd = 185;
Serial.println("spd= 25");
incomingByte='*';
break;

case '3':
spd = 215;
Serial.println("spd= 75");
incomingByte='*';
break;

case '4':
spd = 255;
Serial.println("spd= 100");
incomingByte='*';
break;


delay(1000);
}
}
