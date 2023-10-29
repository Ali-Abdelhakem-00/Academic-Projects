#include <PID_v1.h>

#define echoPin 2
#define trigPin 3
#define fan 9
#define in1 6
#define in2 7
#define pwr 152
double e=0;
double Kp=22, Ki=0.5, Kd=0;
unsigned long T=0;
double Setpoint, Input,Output;

int pulsetime = 1000;
unsigned long Signaltime =0;

PID myfan(&Input, &Output, &Setpoint, Kp,Ki,Kd, DIRECT);

unsigned long SignalBegin;

void setup() {

  Signaltime = millis();
  Setpoint =15;
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(fan,OUTPUT);
 
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);

  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);

  Serial.begin(9600);
  myfan.SetOutputLimits(0,pulsetime);

  myfan.SetMode(AUTOMATIC);
  T = millis();

}

void loop(){

  Input = readDistance();

  

  myfan.Compute();
  if((millis()-SignalBegin)>pulsetime){
    
    SignalBegin += pulsetime;
    }

    if((Output)>(millis()-SignalBegin)){
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
  for(int i=pwr;i>0;i--)
      {
      analogWrite(fan,i);
      }
     
      
     }


     else if((Output)<(millis()-SignalBegin)){
      digitalWrite(in1,LOW);
     digitalWrite(in2,HIGH);
      for(int i=0;i<pwr;i++)
      {
      analogWrite(fan,i);
      }

      }
      else
      {
        digitalWrite(in1,LOW);
        digitalWrite(in2,LOW);

      for(int i=pwr;i>0;i--)
      {
      analogWrite(fan,i);
      }
     
      
        }


    Serial.println(readDistance());   
  }
  
long readDistance(){

  long duration;
  long distance;
  digitalWrite (trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
    delayMicroseconds(2);
    digitalWrite(trigPin, LOW);
   duration = pulseIn(echoPin,HIGH);
   distance = duration * 0.034 / 2;
   return distance;

  }
