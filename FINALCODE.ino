#include <Servo.h>
Servo myServo;

int rn = 6;
int rp = 5;
int lp = 10; 
int ln = 9 ; 
int pump = 4;
int mop = 13;
int serv = 3;
int spd = 255;
int usfront_trigpin = 7;
int usfront_echopin = 8;
int usback_trigpin = 11;
int usback_echopin = 12;
int usleft_trigpin = A1;                          
int usleft_echopin = A2;                           
int usright_trigpin = A3;                          
int usright_echopin = A4;                           
int durationleft;
int distanceleft;
int durationright;
int distanceright;
int durationfront;
int distancefront;
int durationback;
int distanceback;
char incomingByte = '0';

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
pinMode(usfront_trigpin, OUTPUT);
pinMode(usfront_echopin, INPUT);
pinMode(usback_trigpin, OUTPUT);
pinMode(usback_echopin, INPUT);
pinMode(usleft_trigpin, OUTPUT);
pinMode(usleft_echopin, INPUT);
pinMode(usright_trigpin, OUTPUT);
pinMode(usright_echopin, INPUT);
pinMode(2, INPUT);
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

static int a;
static int  b = 0;

if(Serial.available())
  incomingByte = Serial.read();

digitalWrite(usfront_trigpin, LOW);
delayMicroseconds(5);
digitalWrite(usfront_trigpin, HIGH);
delayMicroseconds(10);
digitalWrite(usfront_trigpin, LOW);

durationfront = pulseIn(usfront_echopin, HIGH);
distancefront = (durationfront/2)*0.0343;

digitalWrite(usback_trigpin, LOW);
delayMicroseconds(5);
digitalWrite(usback_trigpin, HIGH);
delayMicroseconds(10);
digitalWrite(usback_trigpin, LOW);

durationback = pulseIn(usback_echopin, HIGH);
distanceback = (durationback/2)*0.0343;


int l = digitalRead(2);

if(l == 1)
{  
digitalWrite(usleft_trigpin, LOW);
delayMicroseconds(5);
digitalWrite(usleft_trigpin, HIGH);
delayMicroseconds(10);
digitalWrite(usleft_trigpin, LOW);

durationleft = pulseIn(usleft_echopin, HIGH);
distanceleft = (durationleft/2)*0.0343;

digitalWrite(usright_trigpin, LOW);
delayMicroseconds(5);
digitalWrite(usright_trigpin, HIGH);
delayMicroseconds(10);
digitalWrite(usright_trigpin, LOW);

durationright = pulseIn(usright_echopin, HIGH);
distanceright = (durationright/2)*0.0343;

if(b == 0)
  if(distanceright <= distanceleft)
   b = 0;
  else
   b = 1; 

if((distancefront < 20)&&(a == 1))
  {
    if(b%2 != 0)
    {
      analogWrite(rn, spd); 
      analogWrite(rp, 0);
      analogWrite(lp, spd);
      analogWrite(ln, 0);
    }
   else
    {
      analogWrite(rn, 0); 
      analogWrite(rp, spd);
      analogWrite(lp, 0);
      analogWrite(ln, spd);
    }
    delay(2000);
    analogWrite(rn, 0); 
    analogWrite(rp, spd);
    analogWrite(lp, spd);
    analogWrite(ln, 0);
    delay(1500);
    if(b%2 != 0)
    {
      analogWrite(rn, spd); 
      analogWrite(rp, 0);
      analogWrite(lp, spd);
      analogWrite(ln, 0);
    }
    else
    {
      analogWrite(rn, 0); 
      analogWrite(rp, spd);
      analogWrite(lp, 0);
      analogWrite(ln, spd);
    }
    delay(2000);
    analogWrite(rn, 0); 
    analogWrite(rp, 0);
    analogWrite(lp, 0);
    analogWrite(ln, 0);
    incomingByte = 'F';
    b++;
  }
else
if((distanceback < 12)&&(a == 2))
  incomingByte = 'S';
}  //l == 1 
else
{
  if((distancefront < 12)&&(a == 1))
    incomingByte = 'S';
  else
  if((distanceback < 12)&&(a == 2))
    incomingByte = 'S';  
}

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
a = 3;
break;


case 'L': //control for left
analogWrite(rn, 0); 
analogWrite(rp, spd);
analogWrite(lp, 0);
analogWrite(ln, spd);
Serial.println("Left");
incomingByte='*';
a = 4;
break;


case 'F': //control for forward
analogWrite(rp, spd); 
analogWrite(rn, 0);
analogWrite(ln, 0);
analogWrite(lp, spd);
Serial.println("Forward");
a = 1;
break;


case 'B': //control for backward
analogWrite(rp, 0); 
analogWrite(rn, spd);
analogWrite(ln, spd);
analogWrite(lp, 0);
Serial.println("Backward");
a = 2;
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

}
}