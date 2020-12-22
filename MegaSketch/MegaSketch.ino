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
typedef void (*Fptr_int)(int,int);

#pragma region somevars


//#define TotalServos 12
#define TOTALSERVOS 12
#define TOTALLEGS 4
#define ARMLEN 12
#define CALFLEN 12


//#define SERVOMIN 1080
//#define SERVOMID 1600
#define SHPULDERSOFFSET 500
#define DelaySpeed 50

#define ZEROPOS 1600
Servo myservo_A;
Servo myservo_B;

int linecount_MegaSketch = 0;
int posA_input;
int posB_input;
String StrInputed_MegaSketch = "";

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

//Servo20kg* FL0_22;	Servo20kg* FR0_23;
//Servo20kg* FL1_24;	Servo20kg* FR1_25;
//Servo20kg* FL2_26;	Servo20kg* FR2_27;
//
//Servo20kg* BL0_28;	Servo20kg* BR0_29;
//Servo20kg* BL1_30;	Servo20kg* BR1_31;
//Servo20kg* BL2_32;	Servo20kg* BR2_33;

Servo20kg* FL0_22 = new Servo20kg(servo0, 22, 0, 1100, 1600, 2000, true, 205,55,true);	 Servo20kg* FR0_23 = new Servo20kg(servo3, 23, 3, 1200, 1600, 2000, true, 205,55, false);
Servo20kg* FL1_24 = new Servo20kg(servo1, 24, 1, 1140, 1600, 2060, true, 205, 65, true);	 Servo20kg* FR1_25 = new Servo20kg(servo4, 25, 4, 1140, 1600, 2060, false, 205,65, false);
Servo20kg* FL2_26 = new Servo20kg(servo2, 26, 2, 1350, 1850, 2350, false,225,55,false);	 Servo20kg* FR2_27 = new Servo20kg(servo5, 27, 5, 1350, 1850, 2350, false, 225, 55, false);

Servo20kg* BL0_28 = new Servo20kg(servo6, 28, 6, 1100, 1600, 2000, true, 205, 55, false);	 Servo20kg* BR0_29 = new Servo20kg(servo9, 29, 9, 1200, 1600, 2000, true, 205,55, true);
Servo20kg* BL1_30 = new Servo20kg(servo7, 30, 7, 1140, 1600, 2060, false, 205, 65, true);	 Servo20kg* BR1_31 = new Servo20kg(servo10, 31, 10, 1140, 1600, 2060, true, 205, 65, false);
Servo20kg* BL2_32 = new Servo20kg(servo8, 32, 8, 1350, 1850, 2350, false, 225, 55, false);	 Servo20kg* BR2_33 = new Servo20kg(servo11, 33, 11, 1350, 1850, 2350, false, 225, 55, false);


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

Servo20kg* Sv20kgArra[TOTALSERVOS] = { FL0_22,FL1_24,FL2_26,FR0_23,FR1_25,FR2_27,BL0_28, BL1_30, BL2_32, BR0_29,BR1_31,BR2_33 };

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

	// delay(500);
	for (int s = 0; s < TOTALSERVOS; s++) {
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

		
		//TASK 1
		Map01K_update_masterJS();
		//Sv20kgArra[7]->Rotate_Us_RelativeToMid(pval10_LS_lR);
		//TASK 2
		  _mulcdDrivenMenu->HandleKEyPresses();

		//if (testboool) {
		//TASK 3

		  Mode_fromLcdMenu = _mulcdDrivenMenu->Get_cuStatIndex();
		//	}


		  //TASK 4
		DoSwitch(Mode_fromLcdMenu);










	 // ArraServos[11].writeMicroseconds(map(pval10_LS_lR,0,1000,1080,1880));
	  // SetAllServosTo(1440);
		//ReadInputRate_sweep_noservomove();
	 
		}

}

void DoSwitch(int argFromLcd) {
	


	switch (argFromLcd) {

			case 999:
				break;
				//minmaxes
			case 0:
				SetAllServosToMid();
				break;
			case 1:
				//SetAllServosToMid();

				break;
			case 2:
				SetAllServosToMid();
				break;


				//servos
			case 12:
				Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval10_LS_lR);
				break;
			case 13:
				Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval10_LS_lR);
				break;
			case 14:
				Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval10_LS_lR);
				break;
			case 15:
				Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval10_LS_lR);

				break;
			case 16:
				Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval10_LS_lR);
				break;
			case 17:
				Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval10_LS_lR);
				break;
			case 18:
				Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval10_LS_lR);
				break;
			case 19:
				Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval10_LS_lR);
				break;
			case 20:
				Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval10_LS_lR);
				break;
			case 21:
				Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval10_LS_lR);
				break;
			case 22:
				Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval10_LS_lR);
				break;
			case 23:
				Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval10_LS_lR);
				break;







				//legs
			case 24:
				SetAllServosToMid();
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

				Sv20kgArra[1]->RotateHalf_Us_RelativeToMid(pval9_LS_dU);
				Sv20kgArra[2]->Rotate_Us_RelativeToMid(pval9_LS_dU);

				Sv20kgArra[4]->RotateHalf_Us_RelativeToMid(pval9_LS_dU);
				Sv20kgArra[5]->Rotate_Us_RelativeToMid(pval9_LS_dU);

				Sv20kgArra[7]->RotateHalf_Us_RelativeToMid(pval9_LS_dU);
				Sv20kgArra[8]->Rotate_Us_RelativeToMid(pval9_LS_dU);

				Sv20kgArra[10]->RotateHalf_Us_RelativeToMid(pval9_LS_dU);
				Sv20kgArra[11]->Rotate_Us_RelativeToMid(pval9_LS_dU);
				// Kinematic_Pos_KneesIN_v1(ArraServo_MINS_v1 , ArraServo_MAX_v1);

				Sv20kgArra[0]->RotateHalf_Us_RelativeToMid(pval12_RS_lR - SHPULDERSOFFSET);
				Sv20kgArra[3]->RotateHalf_Us_RelativeToMid(pval12_RS_lR - SHPULDERSOFFSET);
				Sv20kgArra[6]->RotateHalf_Us_RelativeToMid(pval12_RS_lR - SHPULDERSOFFSET);
				Sv20kgArra[9]->RotateHalf_Us_RelativeToMid(pval12_RS_lR - SHPULDERSOFFSET);


				break;
			case 37:
				//use 2 sticks o control front back lift
				Sv20kgArra[1]->RotateHalf_Us_RelativeToMid(pval10_LS_lR);
				Sv20kgArra[2]->Rotate_Us_RelativeToMid(pval10_LS_lR);

				Sv20kgArra[4]->RotateHalf_Us_RelativeToMid(pval10_LS_lR);
				Sv20kgArra[5]->Rotate_Us_RelativeToMid(pval10_LS_lR);

				Sv20kgArra[7]->RotateHalf_Us_RelativeToMid(pval12_RS_lR);
				Sv20kgArra[8]->Rotate_Us_RelativeToMid(pval12_RS_lR);

				Sv20kgArra[10]->RotateHalf_Us_RelativeToMid(pval12_RS_lR);
				Sv20kgArra[11]->Rotate_Us_RelativeToMid(pval12_RS_lR);

				Sv20kgArra[0]->RotateHalf_Us_RelativeToMid(pval11_RS_uD - SHPULDERSOFFSET);
				Sv20kgArra[3]->RotateHalf_Us_RelativeToMid(pval11_RS_uD - SHPULDERSOFFSET);
				Sv20kgArra[6]->RotateHalf_Us_RelativeToMid(pval11_RS_uD - SHPULDERSOFFSET);
				Sv20kgArra[9]->RotateHalf_Us_RelativeToMid(pval11_RS_uD - SHPULDERSOFFSET);
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


	}
	bool ranOnce = false;
	#define SizeTable 241
	
	void loop() {
		while (Serial.available() > 0) {
			StrInputed_MegaSketch = Serial.readStringUntil('\n');
			SerialInputsFor_ServoAB_vomparefuncs(StrInputed_MegaSketch);
			//testMyFuncs(StrInputed_MegaSketch);
			}
		}
	//if (!ranOnce) {
		//unsigned long start = micros();
		//for (int h = 100; h < 200; h++) {
		//	float h_floated = h * (0.1f);
		//	Serial.print("{ ");
		//	for (int i = 0; i < SizeTable; i++) {
		//		float floated_i = i * (0.1f);
		//		float resultat = GetRawAngle( floated_i , h_floated);
		//		if (i < SizeTable - 1) {
		//			Serial.print(resultat, 1);
		//			Serial.print(",");
		//			}
		//		else
		//			{
		//			Serial.print(resultat, 1);
		//			}
		//		}
		//	if (h < SizeTable - 1) {
		//		Serial.println(" },");
		//		}
		//	else
		//		{
		//		Serial.println(" }");
		//		}
		//	}
			//float floated_i = i * (0.1f);
			//float angAC_i = getANgleSSS(ARMLEN, CALFLEN, floated_i);
			//Serial.print(angAC_i, 1);
			//Serial.print(",");
		//	float angC_i_A = getANgleSSS(CALFLEN, floated_i,ARMLEN );
		//	Serial.print(i,1);
		//	Serial.print(",");
		//	Serial.print(floated_i, 1);
		//	Serial.print(",");*/
		//	Serial.println(angAC_i,1);
		//
		//
		//float sq = sqrt(13.5);
		//// Compute the time it took
		//unsigned long end = micros();
		//unsigned long delta = end - start;
	//	Serial.print("ang1=");
	//	Serial.println(ang1, 1);
		//Serial.print("sq=");
		//Serial.println(sq, 1);
		//Serial.print("time=");
		//Serial.println(delta);
		//ranOnce = true;
	//	}


	/*
	int sav = Serial.available();
	//Serial.println(sav);
	while (Serial.available() > 0) {
		StrInputed_MegaSketch = Serial.readStringUntil('\n');
//		SerialInputsFor_ServoAB_vomparefuncs(StrInputed_MegaSketch);

		unsigned long start = micros();
		// Call to your function
		testMyFuncs(StrInputed_MegaSketch);

		// Compute the time it took
		unsigned long end = micros();
		unsigned long delta = end - start;
		Serial.println(delta);
		}
		//processIncomingByte_subEmFuncEm();
	*/
	//RunTasks();
	//while (Serial.available() == 0) {}
	//StrInputed = Serial.readString();
	//SerialInputsForA_Bloop();
	//Serial.println("a");
	//}

#pragma region teststuff
void betterSwitch() {
	  //case 0 1 2   allzero allmin allmax
	if (Mode_fromLcdMenu < 3) {
		switch (Mode_fromLcdMenu) {

					//minmaxes
				case 0:
					SetAllServosToMid();
					break;
				case 1:
					SetAllServosToMid();
					break;
				case 2:
					SetAllServosToMid();
					break;
			}


		}
	else
	//case 12 -> 23 
	// use index 0 -12
		if (Mode_fromLcdMenu >= TOTALSERVOS && Mode_fromLcdMenu < (TOTALSERVOS + TOTALSERVOS)) {

			Sv20kgArra[Mode_fromLcdMenu - TOTALSERVOS]->Rotate_Us_RelativeToMid(pval11_RS_uD);
			}
		else
		  // 24 25 26 27
		  // FL FR BL BR
			if (Mode_fromLcdMenu >= (TOTALSERVOS + TOTALSERVOS) && Mode_fromLcdMenu < (TOTALSERVOS + TOTALSERVOS + TOTALLEGS)) {
				if (Mode_fromLcdMenu % 3 == 0) {
					}
				else if (Mode_fromLcdMenu % 3 == 1) {
					}
				else if (Mode_fromLcdMenu % 3 == 2) {
					}
				else
					{
					}

				}


	}


typedef void (*GenericFP)(int); //function pointer prototype to a function which takes an 'int' an returns 'void'

void Page1(int foo)
	{
	Serial.print("Page1=");
	Serial.println(foo);
	}

void Page2(int foo)
	{
	Serial.print("Page2=");
	Serial.println(foo);
	}

void Page3(int foo)
	{
	Serial.print("Page3=");
	Serial.println(foo);
	}
GenericFP MenuFP[3] = { &Page1, &Page2, &Page3 }; //create an array of 'GenericFP' function pointers. Notice the '&' operator

void daloop()
	{
	MenuFP[0](1); //call MenuFP element 0 with the parameter 1.  This is equivalent to: Page1(1)
	MenuFP[1](5); //call MenuFP element 1 with the parameter 5.  This is equivalent to: Page2(5)
	MenuFP[2](7); //and so on.                                   This is equivalent to: Page3(7)
	}

#pragma endregion
