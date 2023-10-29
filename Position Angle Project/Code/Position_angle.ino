#define ENCA 2 
#define ENCB 3 
#define IN1 8 
#define IN2 9
#define PWM 10

volatile int pos= 0;
long prevt = 0;
double eprev = 0; 
double eintegral = 0;
double Kp =20;
double Kd = 0.1, Ki = 0.5, setpoint = 180;


void setMotor (int dir, int pwmval ,int pwm, int inl ,int in2)
{
analogWrite (pwm, pwmval);
if (dir == 1)
{
digitalWrite(inl, HIGH);
digitalWrite(in2, LOW);
}
else if (dir == -1)
{
digitalWrite(inl, LOW);
digitalWrite(in2, HIGH);
}
else
{
digitalWrite(inl, LOW);
digitalWrite(in2, LOW);
}
}
void readencoder(){
int b = digitalRead(ENCB);
if (b>0)
{ 
  pos++;
}

else
{
  pos--;
}
}



void setup() {
Serial.begin(9600); 
pinMode (ENCA, INPUT);
pinMode (ENCB, INPUT);
attachInterrupt (digitalPinToInterrupt (ENCA), readencoder, RISING);

}
void loop() { 
  int dir = 1; 
  int target = setpoint* 405/360;
long currt = micros();
double deltat = ((double) (currt-prevt))/(1.0e6);
prevt = currt;
int e = pos - target;
double dedt = (e-eprev) / (deltat);
eintegral = eintegral + e*deltat;

float u = Kp + Kd*dedt + Ki*eintegral;
float pwr = fabs(u) ;
if (pwr>255) 
{
  pwr=255;
}
if (u<0) 
{
dir = -1;
}
setMotor (dir, pwr, PWM, IN1, IN2); 
eprev=e;
Serial.print (target);
Serial.print(" "); 
Serial.print (pos); 
Serial.println();
}
