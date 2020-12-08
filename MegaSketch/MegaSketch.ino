/*
 Name:		MegaSketch.ino
 Created:	12/4/2020 12:11:56 PM
 Author:	nabmsi
*/


//Sample using LiquidCrystal library
#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


#pragma region servo


#define TotalServos 12
#define DelaySpeed 50
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;
Servo servo10;
Servo servo11;
Servo ArraServos[12] = { servo0 ,servo1,servo2,servo3,servo4,servo5,servo6,servo7,servo8,servo9,servo10,servo11 };
int ArraServoPINS[12]=  {22,23,24,25,26,27,28,29,30,31,32,33};
int ArraServoPOSs[12] = {00,00,00,00,00,00,00,00,00,00,00,00};
bool ServosInitialized = false;
int curDelay = 20;
float inputRate;
float rate;
float currentValue;
float targetValue;
float prevTargetValue;
int state = 0;
float stepdiff=0;
#pragma endregion

#pragma region Timers
unsigned long currentMillis;
unsigned long previousMillis;

#pragma endregion


#pragma region pots

#define PotReadScale 1000
#define DeadZoneHalfAmplitude 16

int potpin8 = 8;
int potpin9 = 9;
int potpin10 = 10;

int potpin11 = 11;
int potpin12 = 12;
int potpin13 = 13;

int pval8 =0; //valu of the potpin
int pval9 = 0;
int pval10 = 0;

int pval11 = 0;
int pval12 = 0;
int pval13 = 0;
#pragma endregion


void setup()
    {
    Serial.begin(115200);
    pinMode(potpin8, INPUT);
    pinMode(potpin9, INPUT);
    pinMode(potpin10, INPUT);
    pinMode(potpin11, INPUT);
    pinMode(potpin12, INPUT);
    pinMode(potpin13, INPUT);
    pinMode(A0, INPUT);
    }

void ReadPotpins() {
// left JS<----------------------
// pval8 =analogRead(potpin8);//Rotationccw cw 7 -9-10-11 24
pval8 = map(analogRead(potpin8),5,17 , 0, 128);
 

 //pval9 =analogRead(potpin9); //downup  508+-4 amplitude 170
 pval9 = deadzonefilter(map(analogRead(potpin9), 338, 678, 0, PotReadScale));
 

 // pval10 =analogRead(potpin10);//rightleft  mid amplitude 170
 pval10 = deadzonefilter(map(analogRead(potpin10),336  , 676 , 0, PotReadScale));
 

//rightJS-------------------------------->
// pval11 =analogRead(potpin11);//   512 +-6 amplitude 172
 pval11 = deadzonefilter(map(analogRead(potpin11), 330, 680, 0, PotReadScale));
 

//  pval12 =analogRead(potpin12); //
   pval12 = deadzonefilter(map(analogRead(potpin12),330  , 680 , 0, PotReadScale));
 

// pval13 =analogRead(potpin13);//rot  7-->  14-15-16  --->27
   pval13 = map(analogRead(potpin13),8 , 21 , 0, 100); 
 

    }
 
int deadzonefilter(int argval) {


    if ((argval > ((PotReadScale / 2) - DeadZoneHalfAmplitude)) && (argval < ((PotReadScale / 2) + DeadZoneHalfAmplitude)))
        argval = (PotReadScale / 2) ;
 
    if (argval < 0)argval = 0;
    if (argval > PotReadScale)argval = PotReadScale;

    return argval;
    }

 
void loop(){
   

    ReadPotpins();
   /* currentMillis = millis();
    if (currentMillis - previousMillis >= 10)  {  
        previousMillis = currentMillis;
        
        ReadPotpins();
         
        }*/
}