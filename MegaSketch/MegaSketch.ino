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
#define MillisPerLoop 4000
#define MaxStepsPer1KMilli  1685
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
		//Arrasvos[x].ZeroMe();
		}


	//Arrasvos[0].ZeroMe();
	 

	delay(50);
}

int indxx = -1;


//int someangles[3] = { 110,210,245 };
int someangles[3] = { 110,110,110 };
void loop() {
	
	 currentMillis = millis();
	 if (currentMillis - previousMillis >= MillisPerLoop) {
		 previousMillis = currentMillis;

         indxx++;

         if (indxx == 3)indxx = 0;

        // Arrasvos[0].Speedmove(someangles[indxx], 40);
        /* while (Serial.available() > 0) {

             StrInputed_MegaSketch = Serial.readStringUntil('\n');

             SerialInputsForA_Bloop();
             }*/

		 } 
		
      Arrasvos[0].Speedmove(200, tempspeed);
     Arrasvos[3].Speedmove(200, tempspeed);

     Arrasvos[6].Speedmove(200, tempspeed);
     Arrasvos[9].Speedmove(200, tempspeed); 
      
     Arrasvos[1].Speedmove(200, tempspeed);
     Arrasvos[4].Speedmove(200, tempspeed);

     Arrasvos[7].Speedmove(200, tempspeed);
     Arrasvos[10].Speedmove(200, tempspeed);
      
     Arrasvos[2].Speedmove(someangles[indxx], tempspeed);
     Arrasvos[5].Speedmove(someangles[indxx], tempspeed);

     Arrasvos[8].Speedmove(someangles[indxx], tempspeed);
     Arrasvos[11].Speedmove(someangles[indxx], tempspeed);

   //  Serial.println(Arrasvos[8].Read());
//
	}





void SerialInputsForA_Bloop() {
    String part01 = getValue(StrInputed_MegaSketch, ',', 0);
    String part02 = getValue(StrInputed_MegaSketch, ',', 1);
    //String part03 = getValue(StrInputed,';',2);

    if (part01.equalsIgnoreCase("nogo") && part02.equalsIgnoreCase("nogo")) {
        part01 = String(200);
        part02 = String(200);
        }
    else

        if (part01.equalsIgnoreCase("nogo") || part02.equalsIgnoreCase("nogo")) {
            if (part01.equalsIgnoreCase("nogo")) {
                part01 = part02;
                }
            else
                {
                part02 = part01;
                }
            }

    linecount_MegaSketch++;

    tempPos= posA_input = part01.toInt();
    tempPos = constrain(tempPos, 135, 270);

   tempspeed= posB_input = part02.toInt();
   tempspeed = constrain(tempspeed, 0, 255);
 
    Serial.print(linecount_MegaSketch);
    Serial.print("  |");
    Serial.print("svrA= ");
    Serial.print(posA_input);
    Serial.print("  ");
    Serial.print("svrB= ");
    Serial.print(posB_input);
    Serial.println("-- -- -- ");

    //Sv20kgArra[2]->SetAngleDegrees(posA_input);
    //posA_input= Serial.parseInt();
    //posB_input= Serial.parseInt();

    //myservo_A.writeMicroseconds(posA_input);
    //myservo_B.writeMicroseconds(posB_input);
    //Serial.println(myservo_A.read());
    //Serial.println("-- ");
    }


String getValue(String data, char separator, int index)
    {
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
            }
        }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "nogo";
    }

