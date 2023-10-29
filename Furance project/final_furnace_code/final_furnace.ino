#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 10 
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/
double sensed_output, control_signal;
double setpoint;
double Kp; //proportional gain
double Ki; //integral gain
double Kd; //derivative gain
int T; //sample time in milliseconds
unsigned long last_time;
double total_error, last_error;
int max_control;
int min_control;
int heater = 9;
int fan=8;

int pwm=2;

int val;
int cel;



void setup() {
  //Serial.println("Dallas Temperature IC Control Library Demo");
 // Start up the library 
 sensors.begin();
T = 500;
Kd=0;
Ki = 0.5;
Kp=5;

setpoint = 40;

Serial.begin (9600) ;
pinMode (heater, OUTPUT) ; // set pin as output for relay 
digitalWrite (heater, HIGH) ;
pinMode(fan, OUTPUT);

  

}

void loop() {

  // call sensors.requestTemperatures() to issue a global temperature 
 // request to all devices on the bus 
/********************************************************************/
 sensors.requestTemperatures(); // Send the command to get temperature readings 
/********************************************************************/

sensed_output=sensors.getTempCByIndex(0);
 //Serial.print("Temperature is: "); 
 Serial.println(sensors.getTempCByIndex(0));
 //Serial.print("       "); // Why "byIndex"?  
 




sensed_output = sensors.getTempCByIndex(0);
PID_Control ();
/*Serial.println ("control_signal:");
Serial.print (control_signal);*/
//Serial.print ("sensed_output: ");
//Serial.println (sensed_output) ;
if (control_signal > 0.5) {
digitalWrite (heater, LOW );// turn relay 1 ON
   digitalWrite(fan, HIGH);
 
}
else if (control_signal < -0.5 ){
digitalWrite (heater, HIGH) ;// turn relay 1 ON
digitalWrite(fan, LOW);

}
delay (100) ;
}

void PID_Control() {
unsigned long current_time = millis () ; //returns the number of milliseconds passed since the Arduino started running the program
int delta_time = current_time - last_time; //delta time interval
if (delta_time >= T){
double error = setpoint - sensed_output;

total_error += error; //accuma lates the error - integral term
if (total_error >= max_control) total_error = max_control;
else if (total_error <= min_control) total_error = min_control;
double delta_error = error - last_error; //difference of error for derivative term
control_signal = Kp*error + (Ki*T) *total_error + (Kd/T) *delta_error; //PID control compute
last_error= error;
last_time = current_time;
}}


   
