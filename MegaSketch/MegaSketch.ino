/*
 Name:		MegaSketch.ino
 Created:	12/4/2020 12:11:56 PM
 Author:	nabmsi
*/


//Sample using LiquidCrystal library
#include "TianKongRC20kg.h"
#include "mylcdbox.h"
#include <Servo.h>
#include <LiquidCrystal.h>
#include "mylcdbox.h"
//LiquidCrystal ThelcdTeypad(8, 9, 4, 5, 6, 7);


#pragma region somevars


#define TotalServos 12
#define SERVOMIN 1080
#define SERVOMID 1600
#define SERVOMAX 1800
#define DelaySpeed 50

#define ZEROPOS 1600
Servo myservo_A;
Servo myservo_B;

int linecount = 0;
int posA_input;
int posB_input;
String StrInputed = "";

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
//							FL      FR       
//                          BL		BL
//int ArraServoPINS[12]=  {22,24,26, 23,25,27,
//						28,30,32,  29,31,33}; //so that they are lines up by row of gpio ... idk look at pattern dude

Servo20kg* FL0_22;	Servo20kg* FR0_23;
Servo20kg* FL1_24;	Servo20kg* FR1_25;
Servo20kg* FL2_26;	Servo20kg* FR2_27;

Servo20kg* BL0_28;	Servo20kg* BR0_29;
Servo20kg* BL1_30;	Servo20kg* BR1_31;
Servo20kg* BL2_32;	Servo20kg* BR2_33;

int Mode_fromLcdMenu = 0;
int tempint = 2340;

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

struct JOY_ds {
	int16_t LS_lR; //pin10
	int16_t LS_dU; //pin9
	int16_t RS_lR; //pin12
	int16_t RS_uD; //pin11
	int16_t LS_rot;//pin8
	int16_t RS_rot;//pin13
	};

#pragma endregion

JOY_ds _masterjds;

LcdBoxMenuCtrl* _mulcdDrivenMenu;// = LcdBoxMenuCtrl(8, 9, 4, 5, 6, 7);

Servo20kg* Sv20kgArra[MAXSERVOS] = { FL0_22,FL1_24,FL2_26,FR0_23,FR1_25,FR2_27,BL0_28, BL1_30, BL2_32, BR0_29,BR1_31,BR2_33 };

Servo20kg* Sv20kg_Shoulders_Arra[4] = { FL0_22,FR0_23,BL0_28,BR0_29 };
Servo20kg* Sv20kg_Arms_Top[4] = { FL1_24,FR1_25,BL1_30,BR1_31 };
Servo20kg* Sv20kg_Arms_Low[4] = { FL2_26,FR2_27,BL2_32,BR2_33 };

void setup()
	{
	Serial.begin(115200);
	pinMode(potpin8, INPUT);
	pinMode(potpin9, INPUT);
	pinMode(potpin10, INPUT);
	pinMode(potpin11, INPUT);
	pinMode(potpin12, INPUT);
	pinMode(potpin13, INPUT);
	//2300 2000 1600 1200    //2000 1600 1200  +900
//     2060 1600 1140    //1140  1600 2060
//     1350  1350 2350      2350   1350 850

	 FL0_22= new Servo20kg(servo0,22,0,1200,1600,2000, false);	 FR0_23= new Servo20kg(servo3,23,3,1200,1600,2000,true);
	 FL1_24= new Servo20kg(servo1,24,1,1140,1600,2060,false);	 FR1_25= new Servo20kg(servo4,25,4,1140,1600,2060,true);
	 FL2_26= new Servo20kg(servo2,26,2,850,1350,2350,false);	 FR2_27= new Servo20kg(servo5 ,27,5,850,1350,2350,false);

	 BL0_28= new Servo20kg(servo6,28,6,1200,1600,2000,false);	 BR0_29= new Servo20kg(servo9,29,9,1200,1600,2000,true);
	 BL1_30= new Servo20kg(servo7,30,7,1440,1600,2060,false);	 BR1_31= new Servo20kg(servo10,31,10,1140,1600,2060,true);
	 BL2_32= new Servo20kg(servo8,32,8,850,1350,2350,false);	 BR2_33= new Servo20kg(servo11,33,11,850,1350,2350,false);

	for (int s = 0; s < TotalServos; s++) {
		Sv20kgArra[s]->AttachMe();
		}

	_mulcdDrivenMenu =  new LcdBoxMenuCtrl(8, 9, 4, 5, 6, 7);
	//TIMSK0 = 0;//stop t/c interupt
    
	SetAllServosToMid();

	}


void RunTasks(){


	currentMillis = millis();
	if (currentMillis - previousMillis >= 20)  {  
		
		previousMillis = currentMillis;


		//servo0 min 900
		//
		//          +540
		//
		//   mid 1440
		//
		//           +540
		//
		//servo0 max 1980

		
		
		//servo1 min 952
		//
		//          +488
		//
		//   mid 1440
		//
		//           +488
		//
		//servo1 max 1936


		//servo2 min 240
		//
		//          +1200
		//
		//   mid 1440
		//
		//           +1200
		//
		//servo2 max 2640


		//SetServoToMilis(0, 1980);


		
		//TASK 1
		Map01K_update_masterJS();

		//TASK 2
		  _mulcdDrivenMenu->HandleKEyPresses();

		//if (testboool) {
		//TASK 3

		  Mode_fromLcdMenu = _mulcdDrivenMenu->Get_cuStatIndex();
		//	}



		switch (Mode_fromLcdMenu) {

				case 999:
					break;
					//minmaxes
				case 0:
					// // SetAllServosTo(SERVOMID);
					break;
				case 1:
					// // SetAllServosTo(SERVOMIN + 100);
					break;
				case 2:
					// // SetAllServosTo(SERVOMAX -100);
					break;



					//servos
				case 12:
					// MoveeServoWithJS_v1(pval10_LS_lR, Mode_fromLcdMenu - 12,false,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;
				case 13:
					// MoveeServoWithJS_v1(pval10_LS_lR, Mode_fromLcdMenu - 12,true,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;
				case 14:
					// MoveeServoWithJS_v1(pval10_LS_lR, Mode_fromLcdMenu - 12,true,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;
				case 15:
					// MoveeServoWithJS_v1(pval10_LS_lR, Mode_fromLcdMenu - 12, false,ArraServo_MINS_v1 , ArraServo_MAX_v1);

					break;
				case 16:
					// MoveeServoWithJS_v1(pval10_LS_lR, Mode_fromLcdMenu - 12,false,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;
				case 17:
					// MoveeServoWithJS_v1(pval10_LS_lR, Mode_fromLcdMenu - 12, false,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;
				case 18:
					// MoveeServoWithJS_v1(pval10_LS_lR, Mode_fromLcdMenu - 12, true,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;
				case 19:
					// MoveeServoWithJS_v1(pval10_LS_lR, Mode_fromLcdMenu - 12, true,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;
				case 20:
					// MoveeServoWithJS_v1(pval10_LS_lR, Mode_fromLcdMenu - 12, true,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;
				case 21:
					// MoveeServoWithJS_v1(pval10_LS_lR, Mode_fromLcdMenu - 12,true,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;
				case 22:
					// MoveeServoWithJS_v1(pval10_LS_lR, Mode_fromLcdMenu - 12, false,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;
				case 23:
					// MoveeServoWithJS_v1(pval10_LS_lR, Mode_fromLcdMenu - 12, false,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;

					//legs
				case 24:
					// MoveeShoulderWithJS_v1(Mode_fromLcdMenu - 24,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;
				case 25:
					// MoveeShoulderWithJS_v1(Mode_fromLcdMenu - 24,ArraServo_MINS_v1 , ArraServo_MAX_v1);

					break;
				case 26:
					// MoveeShoulderWithJS_v1(Mode_fromLcdMenu - 24,ArraServo_MINS_v1 , ArraServo_MAX_v1);

					break;
				case 27:
					// MoveeShoulderWithJS_v1(Mode_fromLcdMenu - 24,ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;


					//// Kinematics 12*3
				case 36:
					// Kinematic_Pos_KneesIN_v1(ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;
				case 37:
					// Kinematic_Pos_KneesOUT_v1(ArraServo_MINS_v1 , ArraServo_MAX_v1);
					break;

					//poses 12*4
				case 48:
					break;
				case 49:
					break;
				case 50:
					break;
				case 51:
					break;



			}















		/*
		//TASK 1
		Map01K_update_masterJS();
   
		//TASK 2
		  _mulcdDrivenMenu->HandleKEyPresses();

		//if (testboool) {
		//TASK 3 

		  Mode_fromLcdMenu = _mulcdDrivenMenu->Get_cuStatIndex();
		//	}



		switch (Mode_fromLcdMenu) {
			
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
					MoveServoWithJS(pval10_LS_lR, Mode_fromLcdMenu - 12,false);
					break;
				case 13:
					//Serial.println("FL1_24");
					MoveServoWithJS(pval10_LS_lR, Mode_fromLcdMenu - 12,true);
					break;
				case 14:
					//Serial.println("FL2_26");
					MoveServoWithJS(pval10_LS_lR, Mode_fromLcdMenu - 12,true);
					break;
				case 15:
					//Serial.println("FR0_23");
					MoveServoWithJS(pval10_LS_lR, Mode_fromLcdMenu - 12, false);
					
					break;
				case 16:
					//Serial.println("FR1_25");
					MoveServoWithJS(pval10_LS_lR, Mode_fromLcdMenu - 12,false);
					break;
				case 17:
					//Serial.println("FR2_27");
					MoveServoWithJS(pval10_LS_lR, Mode_fromLcdMenu - 12, false);
					break;
				case 18:
					//Serial.println("BL0_28");
					MoveServoWithJS(pval10_LS_lR, Mode_fromLcdMenu - 12, true);
					break;
				case 19:
					//Serial.println("BL1_30");
					MoveServoWithJS(pval10_LS_lR, Mode_fromLcdMenu - 12, true);
					break;
				case 20:
					//Serial.println("BL2_32");
					MoveServoWithJS(pval10_LS_lR, Mode_fromLcdMenu - 12, true);
					break;
				case 21:
					//Serial.println("BR0_29");
					MoveServoWithJS(pval10_LS_lR, Mode_fromLcdMenu - 12,true);
					break;
				case 22:
					//Serial.println("BR1_31");
					MoveServoWithJS(pval10_LS_lR, Mode_fromLcdMenu - 12, false);
					break;
				case 23:
					//Serial.println("BR2_33");
					MoveServoWithJS(pval10_LS_lR, Mode_fromLcdMenu - 12, false);
					break;
			
					//legs
				case 24:
					//Serial.println("FL");
					MoveShoulderWithJS(Mode_fromLcdMenu - 24);
					break;
				case 25:
					//Serial.println("FR");
					MoveShoulderWithJS(Mode_fromLcdMenu - 24);

					break;
				case 26:
					//Serial.println("BR");
					MoveShoulderWithJS(Mode_fromLcdMenu - 24);

					break;
				case 27:
					//Serial.println("BL");
					MoveShoulderWithJS(Mode_fromLcdMenu - 24);
					break;


					//kinematics 12*3
				case 36:
					//Serial.println("kine pos");
					Kinematic_Pos_KneesIN();
					break;
				case 37:
					//Serial.println("kine roll");
					Kinematic_Pos_KneesOUT();
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
			*/

	 // ArraServos[11].writeMicroseconds(map(pval10_LS_lR,0,1000,1080,1880));
	  // SetAllServosTo(1440);
		//ReadInputRate_sweep_noservomove();
	 
		}

}



void loop() {


	}