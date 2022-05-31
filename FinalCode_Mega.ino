#include <AccelStepper.h>
#include <MultiStepper.h>
#include "max6675.h"
#include <SPI.h>
#include <SD.h>
//temp 

int chipSelect = 53;
File myFile;
byte NTCPin = A15;
#define SERIESRESISTOR 1000
#define NOMINAL_RESISTANCE 100000
#define NOMINAL_TEMPERATURE 25
#define BCOEFFICIENT 3950


int heaterPin = 9;
int ThermistorPin = 15;
int Vo;
float R1 = 100000;
float logR2, R2, T, Tc, Tf;
float c1=6.66082410500E-004, c2 = 2.23928204100E-004, c3 = 7.19951882000E-008;

// pid
float  temp_Value = 0.0;
float set_Temp = 0;

float PID_error = 0;
float prev_Error = 0;
float elapsedTime,Time,timePrev;
int PID_Value = 0;

//pid const
int kp = 25; int ki = 0.01; int kd = 12;
int PID_p = 0; int PID_i = 0; int PID_d = 0;



#define dirPin 2
#define dirPin2 3
#define dirPin3 4
#define dirPin4 13
#define stepPin 5
#define stepPin2 6
#define stepPin3 7
#define stepPin4 12
#define motorInterfaceType 2
//
//long bigArmStepsFor180 = 20000;
//long SmallArmStepsFor303 = 32600;

//long bigArmStepsFor180 = 19200;
//long SmallArmStepsFor320 = 34133;

float bigArmStepsFor180 = 19200.0;
float SmallArmStepsFor180 = 19200.0;



//long bigArmStepsPerDeg = bigArmStepsFor180/180;
//long smallArmStepsPerDeg = SmallArmStepsFor303/303;

float bigArmStepsPerDeg = bigArmStepsFor180/180;
float smallArmStepsPerDeg = SmallArmStepsFor180/180;
float zStepsPerMM  = 3333;

float currentBigArmAngle = 0;
float currentSmallArmAngle = 180;
float currentZpos = 0;




AccelStepper smallStepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
AccelStepper bigStepper = AccelStepper(motorInterfaceType, stepPin2, dirPin2);
AccelStepper zStepper = AccelStepper(2, stepPin3, dirPin3);
AccelStepper extStepper = AccelStepper(2, stepPin4, dirPin4);

MultiStepper both;
MultiStepper extruder;

void setup() {
Serial.begin(9600);
  pinMode(chipSelect,OUTPUT);

   if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }

  myFile = SD.open("test.txt",FILE_READ);



  
  pinMode(heaterPin, OUTPUT);
  Time = millis();
  
  Serial.begin(9600);
  // put your setup code here, to run once:
   bigStepper.setMaxSpeed(1000);
  smallStepper.setMaxSpeed(1000);
    zStepper.setMaxSpeed(5000); 
    extStepper.setMaxSpeed(50000); 
   
  
  
  both.addStepper(bigStepper);
  both.addStepper(smallStepper);
  both.addStepper(zStepper);
  both.addStepper(extStepper);
  
  
  bigStepper.setCurrentPosition(0);
  smallStepper.setCurrentPosition(19200);
  zStepper.setCurrentPosition(0);
  extStepper.setCurrentPosition(0);
  
}

void moveTo(float bigAngle,float smallAngle, float zPos,float ext){

float bigAngleDifference = bigAngle - currentBigArmAngle;
float bigStepsForAngle = bigAngleDifference * bigArmStepsPerDeg;
currentBigArmAngle = bigAngle;

float smallAngleDifference = smallAngle - currentSmallArmAngle;
float smallStepsForAngle = (smallAngleDifference * smallArmStepsPerDeg)+ bigStepsForAngle;
currentSmallArmAngle = smallAngle;

float zPosDifference= zPos - currentZpos;
float zStepsForPos = zPosDifference * zStepsPerMM;
currentZpos = zPos;
//
// Serial.print("SmallAngle: ");
//  Serial.print(smallAngle);
// Serial.print(":::: ");
// 
// Serial.print("currentSmallAngle ");
// Serial.print(currentSmallArmAngle);
// Serial.print(":::: ");
// Serial.print("StepsSmallAngleDiff ");
// Serial.print("StepsSmallAngleDiff ");
//  Serial.print(smallAngleDifference);
// Serial.print("StepsSmall ");
// Serial.print(smallStepsForAngle);
// 
//
//  Serial.print("--- ");
//  Serial.print("StepsBig ");
// Serial.print(bigStepsForAngle);
//  Serial.println();
Serial.print("Big Stepper:  ");
Serial.println(bigStepsForAngle);
Serial.println("-------- ");
Serial.print("small Stepper:  ");
Serial.println(smallStepsForAngle);

Serial.println("################################### ");

long firstMove[] = {bigStepsForAngle,smallStepsForAngle,zStepsForPos,ext}; 
  bigStepper.setCurrentPosition(0);
  smallStepper.setCurrentPosition(0);
  zStepper.setCurrentPosition(0);
  extStepper.setCurrentPosition(0);
  both.moveTo(firstMove);

//both.runSpeedToPosition();
both.run();
}




void moveTo2(float bigAngle,float smallAngle, float zPos,float ext){

float bigStepsForAngle = bigAngle * bigArmStepsPerDeg;

float smallStepsForAngle = (smallAngle * smallArmStepsPerDeg)+ bigStepsForAngle;

float zPosDifference= zPos - currentZpos;
float zStepsForPos = zPosDifference * zStepsPerMM;
currentZpos = zPos;
//Serial.println("----------------------------------");
//Serial.print("Big Stepper");
//Serial.println(bigStepsForAngle);
//
//Serial.print("small Stepper");
//Serial.println(smallStepsForAngle);
//
//Serial.print("z Stepper");
//Serial.println(zStepsForPos);
//Serial.println("----------------------------------");
long firstMove[] = {bigStepsForAngle,smallStepsForAngle,zStepsForPos,ext}; 

  zStepper.setCurrentPosition(0);
  extStepper.setCurrentPosition(0);
  both.moveTo(firstMove);

both.runSpeedToPosition();
}





double readTemp(){
float ADCvalue;
float Resistance;
ADCvalue = analogRead(NTCPin);

//convert value to resistance
Resistance = (1023 / ADCvalue) - 1;
Resistance = SERIESRESISTOR / Resistance;


float steinhart;
steinhart = Resistance / NOMINAL_RESISTANCE; // (R/Ro)
steinhart = log(steinhart); // ln(R/Ro)
steinhart /= BCOEFFICIENT; // 1/B * ln(R/Ro)
steinhart += 1.0 / (NOMINAL_TEMPERATURE + 273.15); // + (1/To)
steinhart = 1.0 / steinhart; // Invert
steinhart -= 273.15; // convert to C

//Serial.print("Temperature ");
//Serial.print(steinhart);
//Serial.println(" oC");

return steinhart;
}

void PID(){
   temp_Value = readTemp();
 // Serial.print("Current temp: ");
Serial.println(temp_Value); 
 // Serial.print("Set temperature: ");
//Serial.println(set_Temp); 
 PID_error = (set_Temp - temp_Value);
 //Serial.print("Error temp: ");
//Serial.println(PID_error);  
 
 // Calc p value
  PID_p = kp * PID_error;

 // Serial.print("P:  ");
//Serial.println(PID_p);  

  //calc pid I value in range +-3
  if(-3<PID_error<3){
    PID_i = PID_i + (ki+PID_error);
  }

PID_i = 0;
 // Serial.print("I: ");
//Serial.println(PID_i);  

  // derivative
 timePrev = Time;
 Time = millis();
 elapsedTime = (Time - timePrev) / 1000;

 //calculating PID D value
 PID_d = kd*((PID_error - prev_Error)/elapsedTime);
 //Serial.print("d ");
//Serial.println(PID_d);  

 //calculate total PID value
 PID_Value = PID_p + PID_i + PID_d;
 //Serial.print("PID_Value: ");
//Serial.println(PID_Value);  


 if(PID_Value < 0){
  PID_Value = 0;
 }
 if(PID_Value > 255){
  PID_Value = 255;
 }

analogWrite(heaterPin,PID_Value);
//Serial.print("current PWm: ");
//Serial.println(PID_Value);  
prev_Error = PID_error;
//Serial.println("---------------");
}

void readSd(){
 float x;
 float y;
 float z;
 float e;
 
 String line = myFile.readStringUntil('\n');

  int i1 = line.indexOf(',');
  int i2 = line.indexOf(',', i1+1);
  int i3 = line.indexOf(',', i2+1);


  String firstValue = line.substring(0, i1);
  String secondValue = line.substring(i1 + 1, i2);
  String thirdValue = line.substring(i2 + 1,i3);
  String fourthValue = line.substring(i3 + 1);

  x = firstValue.toFloat();
  y = secondValue.toFloat();
  z = thirdValue.toFloat();
  e = fourthValue.toFloat();

  //Serial.println(e);
 

  moveTo2(x,y,z,e);


//  Serial.println(thirdValue);
//  Serial.println(fourthValue);


  


}
void loop() {

   


//

//extStepper.setCurrentPosition(0);

//
//
//
//
//long firstMove2[] = {0,0,20000,0}; 
//long firstMove3[] = {0,0,0,0}; 
//
//both.moveTo(firstMove2);
//both.runSpeedToPosition();
//delay(2000);
//both.moveTo(firstMove3);
//both.runSpeedToPosition();
//both.moveTo(firstMove);
//
//both.runSpeedToPosition();
//delay(2000);
//both.moveTo(firstMove2);
//
//both.runSpeedToPosition();
//delay(2000);
//
//both.moveTo(firstMove3);
//
//both.runSpeedToPosition();
//delay(2000);
//

//
delay(1000);
PID();
if(readTemp() > 220){
for(int i=0; i < 20000; i++){
PID();
readSd();
readSd();
readSd();



}
}




  // put your main code here, to run repeatedly:

}
