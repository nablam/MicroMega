/*
 Name:		MegaSketch.ino
 Created:	12/4/2020 12:11:56 PM
 Author:	nabmsi
*/


//Sample using LiquidCrystal library
#include "mylcdbox.h"
#include <Servo.h>
#include <LiquidCrystal.h>
#include "mylcdbox.h"
//LiquidCrystal ThelcdTeypad(8, 9, 4, 5, 6, 7);


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
int ArraServoPINS[12]=  {22,24,26,23,25,27,28,30,32,29,31,33}; //so that they are lines up by row of gpio ... idk look at pattern dude
int ArraServoPOSs[12] = {00,00,00,00,00,00,00,00,00,00,00,00};
bool ServosInitialized = false;
int curDelay = 20;
float inputRate;
float rate;
int currentValue=500;
int targetValue;
int prevTargetValue;
int state = 0;
float stepdiff=0;
#pragma endregion

#pragma region Timers
unsigned long currentMillis;
unsigned long previousMillis;
#define KNEEACTANGLE 15.8L
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

int pval8_LS_rot =0; //valu of the potpin
int pval9_LS_dU = 0;
int pval10_LS_lR = 0;

int pval11_RS_uD = 0;
int pval12_RS_lR = 0;
int pval13_RS_rot = 0;
#pragma endregion

struct JOY_ds {
	int16_t LS_lR; //pin10
	int16_t LS_dU; //pin9
	int16_t RS_lR; //pin12
	int16_t RS_uD; //pin11
	int16_t LS_rot;//pin8
	int16_t RS_rot;//pin13
	};
JOY_ds localjds;

//**************Leg servo poses in ms****************
struct LEG_ds {
	int16_t hip;
	int16_t shoulder;
	int16_t elbow;
	};

LEG_ds Leg_FR;
LEG_ds Leg_FL;
LEG_ds Leg_BR;
LEG_ds Leg_BL;

void setup()
	{
	Serial.begin(115200);
	pinMode(potpin8, INPUT);
	pinMode(potpin9, INPUT);
	pinMode(potpin10, INPUT);
	pinMode(potpin11, INPUT);
	pinMode(potpin12, INPUT);
	pinMode(potpin13, INPUT);
	

	for (int s = 0; s < TotalServos; s++) {
		ArraServos[s].attach(ArraServoPINS[s]);
		}

	}
LcdBoxMenuCtrl _mulcdDrivenMenu =  LcdBoxMenuCtrl(8, 9, 4, 5, 6, 7);
void ReadPotpins() {
 
// left JS<----------------------
	 pval8_LS_rot =analogRead(potpin8);//Rotationccw cw 7 -9-10-11 24
	 pval9_LS_dU =analogRead(potpin9); //downup  508+-4 amplitude 170
	 pval10_LS_lR =analogRead(potpin10);//rightleft  mid amplitude 170
 
	//rightJS-------------------------------->
	 pval11_RS_uD =analogRead(potpin11);//   512 +-6 amplitude 172
	 pval12_RS_lR =analogRead(potpin12); //
	 pval13_RS_rot =analogRead(potpin13);//rot  7-->  14-15-16  --->27
	}
void MapPotpins() {

// left JS<----------------------
	pval8_LS_rot = deadzonefilter(map(analogRead(potpin8), 0, 15, 0, PotReadScale),true);
	pval9_LS_dU = deadzonefilter(map(analogRead(potpin9), 338, 678, 0, PotReadScale),false);
	pval10_LS_lR = deadzonefilter(map(analogRead(potpin10), 336, 676, 0, PotReadScale), false);
   //rightJS-------------------------------->
	pval11_RS_uD = deadzonefilter(map(analogRead(potpin11), 330, 688, 0, PotReadScale), false);
	pval12_RS_lR = deadzonefilter(map(analogRead(potpin12), 330, 680, 0, PotReadScale), false);
	pval13_RS_rot = deadzonefilter(map(analogRead(potpin13), 2, 50, 0, PotReadScale),true);
//	Serial.println(pval11_RS_uD);
	}

//{pval8_LS_rot} {pval9_LS_dU} {pval10_LS_lR} {pval11_RS_uD} {pval12_RS_lR} {pval13_RS_rot}
 
int deadzonefilter(int argval, bool argisRot) {

	if (argisRot) {
		if ((argval > ((PotReadScale / 2) - (DeadZoneHalfAmplitude/4))) && (argval < ((PotReadScale / 2) + (DeadZoneHalfAmplitude / 4))))
			argval = (PotReadScale / 2);

		if (argval < 0)argval = 0;
		if (argval > PotReadScale)argval = PotReadScale;

		}
	else
		{
		if ((argval > ((PotReadScale / 2) - DeadZoneHalfAmplitude)) && (argval < ((PotReadScale / 2) + DeadZoneHalfAmplitude)))
			argval = (PotReadScale / 2);

		if (argval < 0)argval = 0;
		if (argval > PotReadScale)argval = PotReadScale;
		}
  

	return argval;
	}





 
void SetAllServosTo(int argmilli) {
	for (int i = 0; i < TotalServos; i++) {
		ArraServos[i].writeMicroseconds(argmilli);
		}
	}
 
 
int p = 1590;
int temp = 1080;
void loop(){


	currentMillis = millis();
	if (currentMillis - previousMillis >= 20)  {  
		previousMillis = currentMillis;
	   MapPotpins();
   //   ReadPotpins();
	  // p=map(pval11_RS_uD,0,1000,830,2350);

	 
	   //SetAllServosTo(p);
	   inputRate = map(pval11_RS_uD, 0, 1000, 1, 10);;// pval11_RS_uD;//
	  // rate == map(inputRate, 0, 1023, 45, 135);
	   rate = inputRate;
	  /* if (rate > 10)rate = 10;
	   if (rate < 1)rate = 1;*/

	   if (state == 0) {
		   targetValue = 720; //lowend
		   if (currentValue <= targetValue) {
			   state = 1;
			   prevTargetValue = targetValue;
			   currentValue = targetValue;
			   _mulcdDrivenMenu.ON();
//Serial.println("on ");
			   }
		   }
	  // else 
		   if (state == 1)
		   {
		   targetValue = 1440; //highend
		   if (currentValue >= targetValue) {
			   state = 0;
			   prevTargetValue = targetValue;
			   currentValue = targetValue;
			   _mulcdDrivenMenu.OFF();
//			   Serial.print("off");
			   }
		   }

	   stepdiff = (targetValue - prevTargetValue) / (28* rate);
	   currentValue = currentValue + stepdiff;
	  SetAllServosTo(currentValue);

	 
		}
}