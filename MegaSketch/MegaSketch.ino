/*
 Name:		MegaSketch.ino
 Created:	12/4/2020 12:11:56 PM
 Author:	nabmsi
*/


//Sample using LiquidCrystal library
//#include "SrevoII.h"
//#include "TianKongRC20kg.h"
//#include "mylcdbox.h"
#include <Svo.h>

//#define LOGMAster
#define MillisPerLoop 2500
#define MaxStepsPer1KMilli  1685

#define ARMLEN 12
#define CALFLEN 12
float MaxStepsPerLoop;
//Svo ServoOrange;
//Svo ServoYellow;
int baseDelayTime = 800;
int angles[6] = { 45,90,180,270,180,90 };
int anglesMillis[6] = { 849,1186,1860,2500,1860,1186 };
int i_ang = 0;
int tempangle = 90;
int tempDelay = 2000;
 
float speedrate;
float _rateMulitplyer;
int loopCycle = 1000;
 
  
 
unsigned long currentMillis;
unsigned long previousMillis;
unsigned long BaseStartCountMillis;

int testvalue_849_2197 = 2197;
bool printednce = false;

int Specialangles[10] = { 45,90,135,140,150,180,205,225,260,270 };

String StrInputed_MegaSketch;
int linecount_MegaSketch;
int posA_input;
int posB_input;
Svo sv0;
Svo sv1;
Svo sv2;
Svo sv3;
Svo sv4;
Svo sv5;
Svo sv6;
Svo sv7;
Svo sv8;
Svo sv9;
Svo sv10;
Svo sv11;
Svo Arrasvos[12] = { sv0,sv1,sv2,sv3,sv4,sv5,sv6,sv7,sv8,sv9,sv10,sv11 };
int tempPos = 50;
int tempspeed = 0;
void setup()
	{
	MaxStepsPerLoop = (float)(MaxStepsPer1KMilli / 1000) * MillisPerLoop;
	Serial.begin(115200);
	Serial.flush();

	for (int x = 0; x < 12; x++) {
		Arrasvos[x].Attach(x);
		}
 
	Serial.println("all setup");
	 
 

	
	//2197
	//s1.Write(225);
	i_ang = 1;
	randomSeed(analogRead(0));
	int rangle = anglesMillis[i_ang]; //random(900, 2100);
	 
	Serial.println(rangle);
	Serial.print("max steps per loop");


	for (int x = 0; x < 12; x++) {
		 Arrasvos[x].ZeroMe();
		}

//	delay(50);
}

int indxx = -1;


int someangles[4] = { 144,200,248 ,200 };

int TestArray[15][3] = { {0,0,18},{0,2,18},{0,4,18},{0,10,18},{8,0,20},{10,0,20},{12,0,20},{0,0,17},{0,0,16},{0,0,15},{0,0,14},{0,0,13},{0,0,12},{0,4,12},{4,5,12} };
//0.00; 0.00; 180.00
//0.00; -16.60; 146.80
//0.00; -23.56; 132.89
//0.00; -28.96; 122.09
//0.00; -33.56; 112.89
//0.00; -37.66; 104.68
//0.00; -41.41; 97.18
//0.00; -44.90; 90.20
//0.00; -48.19; 83.62
//0.00; -51.32; 77.36
//0.00; -54.31; 71.37
//0.00; -57.20; 65.59
//0.00; -60.00; 60.00
//0.00; -39.76; 63.61
//17.55; -33.91; 69.04
//int someangles[3] = { 110,110,110 };
void loop() {
	
	 currentMillis = millis();
	 if (currentMillis - previousMillis >= MillisPerLoop) {
		 previousMillis = currentMillis;

         indxx++;

         if (indxx == 15)indxx = 0;
		 XYZ_inputConversion(TestArray[indxx][0], TestArray[indxx][1], TestArray[indxx][2]);

       for (int x = 0; x < 12; x++) {
             Arrasvos[x].ZeroMe();
             }
       // Arrasvos[1].Speedmove(someangles[indxx], 30);

       // Arrasvos[4].Speedmove(someangles[indxx], 30 );
      // Arrasvos[7].Speedmove(someangles[indxx], 30);
      //  Arrasvos[10].Speedmove(someangles[indxx], 30);

        // Serial.print(" "); Serial.println(Arrasvos[2]._GlobalZeroAngle);
        //Arrasvos[4].Speedmove(someangles[indxx], 40);
        //Arrasvos[1].Speedmove(someangles[indxx], 40);
        //Arrasvos[7].Speedmove(someangles[indxx], 40);
        //Arrasvos[10].Speedmove(someangles[indxx], 40);
        /* while (Serial.available() > 0) {

             StrInputed_MegaSketch = Serial.readStringUntil('\n');

             SerialInputsForA_Bloop();
             }*/

      
		 } 
 
	}



