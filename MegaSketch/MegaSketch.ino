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
#define SERVOMIN 1080
#define SERVOMID 1440
#define SERVOMAX 1800
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
int ArraServoValuesBackup[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
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
JOY_ds _masterjds;

//*************needMyservoObjects**********

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


LcdBoxMenuCtrl* _mulcdDrivenMenu;// = LcdBoxMenuCtrl(8, 9, 4, 5, 6, 7);


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
	_mulcdDrivenMenu =  new LcdBoxMenuCtrl(8, 9, 4, 5, 6, 7);
	//TIMSK0 = 0;//stop t/c interupt
	}



 
int p = 1590;
int temp = 1080;




void ReadInputRate_sweep_noservomove() {

	inputRate = map(pval11_RS_uD, 0, 1000, 1, 10);;// pval11_RS_uD;//
	rate = inputRate;


	if (state == 0) {
		targetValue = 1080; //lowend
		if (currentValue <= targetValue) {
			state = 1;
			prevTargetValue = targetValue;
			currentValue = targetValue;
//Serial.println("on ");
			}
		}
   // else 
	if (state == 1)
		{
		targetValue = 1880; //highend
		if (currentValue >= targetValue) {
			state = 0;
			prevTargetValue = targetValue;
			currentValue = targetValue;
//			   Serial.print("off");
			}
		}

	stepdiff = (targetValue - prevTargetValue) / (28 * rate);
	currentValue = currentValue + stepdiff;

	}
bool testboool = false;
int testint = 0;
void loop(){


	currentMillis = millis();
	if (currentMillis - previousMillis >= 20)  {  
		previousMillis = currentMillis;

		//TASK 1
		Map01K_update_masterJS();
   
		//TASK 2
		  _mulcdDrivenMenu->HandleKEyPresses();

		//if (testboool) {
		//TASK 3 

			testint = _mulcdDrivenMenu->Get_cuStatIndex();
		//	}



		switch (testint) {
			
				case 999:
					break;
					//minmaxes
				case 0:
					//Serial.println("zero all");
					SetAllServosTo(SERVOMID);
					break;
				case 1:
				//	Serial.println("min all");
					SetAllServosTo(SERVOMIN + 100);
					break;
				case 2:
					//Serial.println("max all");
					SetAllServosTo(SERVOMAX -100);
					break;



					//servos
				case 12:
					//Serial.println("FRL_22");
					break;
				case 13:
					//Serial.println("FL1_24");
					break;
				case 14:
					//Serial.println("FL2_26");
					break;
				case 15:
					//Serial.println("FR0_23");
					
					break;
				case 16:
					//Serial.println("FR1_25");
					break;
				case 17:
					//Serial.println("FR2_27");
					break;
				case 18:
					//Serial.println("BL0_28");
					break;
				case 19:
					//Serial.println("BL1_30");
					break;
				case 20:
					//Serial.println("BL2_32");
					break;
				case 21:
					//Serial.println("BR0_29");
					break;
				case 22:
					//Serial.println("BR1_31");
					break;
				case 23:
					//Serial.println("BR2_33");
					break;
			
					//legs
				case 24:
					//Serial.println("FL");
					break;
				case 25:
					//Serial.println("FR");
					break;
				case 26:
					//Serial.println("BR");
					break;
				case 27:
					//Serial.println("BL");
					break;
					//kinematics 12*3
				case 36:
					//Serial.println("kine pos");
					break;
				case 37:
					//Serial.println("kine roll");
					break;
					
					//poses 12*4
				case 48:
					//Serial.println("walk");
					break;
				case 49:
					//Serial.println("side");
					break;
				case 50:
					//Serial.println("lay");
					break;
				case 51:
					//Serial.println("ready");
					break;


			
			}

	 // ArraServos[11].writeMicroseconds(map(pval10_LS_lR,0,1000,1080,1880));
	  // SetAllServosTo(1440);
		//ReadInputRate_sweep_noservomove();
	 
		}
}