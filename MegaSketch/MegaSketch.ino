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
#define MillisPerLoop 10
#define MaxStepsPer1KMilli  1685
float MaxStepsPerLoop;
Svo s0;
Svo s1;
int baseDelayTime = 800;
int angles[6] = { 45,90,180,270,180,90 };
int anglesMillis[6] = { 849,1186,1860,2500,1860,1186 };
int i_ang = 0;
int tempangle = 90;
int tempDelay = 2000;
int _inputRate = 20;
float _rate = 400.0;
float speedrate;
float _rateMulitplyer;
int loopCycle = 1000;
int _targetValue;
int _currentValue;
int _prevTargetValue;
float _stepdiff;
float servo1PosFiltered;
int state = 0;
unsigned long currentMillis;
unsigned long previousMillis;
unsigned long BaseStartCountMillis;

int testvalue_849_2197 = 2197;
bool printednce = false;
void setup()
	{
	MaxStepsPerLoop = (float)(MaxStepsPer1KMilli / 1000) * MillisPerLoop;
	Serial.begin(115200);
	Serial.flush();
	s0.Attach(40, false);
	s1.Attach(38, false);

	s0.InitPositions();
	s1.InitPositions();


	Serial.print("hi=");
	Serial.println("hoo");
	
	Serial.print("45d=");
	Serial.println(s1.ConvertDegreesToPulsw(45));
    
	Serial.print( "45d=");
	Serial.println(s1.ConvertDegreesToPulsw(45));

	Serial.print("225d=");
	Serial.println(s1.ConvertDegreesToPulsw(225));

	Serial.print("90d=");
	Serial.println(s1.ConvertDegreesToPulsw(90));

	Serial.print("180d=");
	Serial.println(s1.ConvertDegreesToPulsw(180));
	
	//2197
	//s1.Write(225);
	i_ang = 1;
	randomSeed(analogRead(0));
	int rangle = anglesMillis[i_ang]; //random(900, 2100);
	_currentValue = _prevTargetValue=rangle;
	s1.WriteMicroseconds(rangle);
	Serial.println(rangle);
	Serial.print("max steps per loop");
	Serial.println(MaxStepsPerLoop);

	delay(3000);
}



void DoAngle() {

	/*if (currentMillis % 100 == 0){
		if (i_ang > 5) {
			i_ang = 0;
			}

		i_ang++;
		}*/

	/*if (currentMillis % 10 == 0) {
		if (_rate > ratemax) {
			_rate = rateMin;
			}
		else
			if (_rate < rateMin) {
				_rate = rateMin;
				}
		_rate++;
		}*/
		 
	#ifdef LOGMAster
		Serial.println(tempangle);
	#endif

		//int millispuls = s1.ConvertDegreesToPulsw(250);
	

		//int ffflllteredms = movetoAtRate_giveCurTargpos(  _rate, millispuls);

	//	s1.WriteMicroseconds(ffflllteredms);
	
		

	#ifdef LOGMAster
		Serial.print("reading MS"); Serial.print(s1.Read());	Serial.print("reading "); Serial.println(s1.ReadMicroseconds());
	#endif
		//delay(tempDelay);
		//Serial.println(_rate);

		}
void loop() {
	
	 currentMillis = millis();
	 if (currentMillis - previousMillis >= MillisPerLoop) {
		 previousMillis = currentMillis;
		// printednce = !printednce;
		/* if (!printednce)s1.WriteMicroseconds(movetoAtRate_giveCurTargpos(2197,50));
		 else
			 s1.WriteMicroseconds(movetoAtRate_giveCurTargpos(225,100));*/
		 //s1.WriteMicroseconds(movetoAtRate_giveCurTargpos(anglesMillis[i_ang+1], 10));


		 s1.speedmove(200, 200);
		 delay(3000);
		 s1.speedmove(90, 20);
		 delay(3000);
		 }
		 
	}

void ReadInputRate_sweep_noservomove() {
	if (state == 0) {
		_targetValue = 1860; //lowend
		if (_currentValue >= _targetValue) {
			state = 1;
			_prevTargetValue = _targetValue;
		
 Serial.println("on ");
			}
		}
   
	if (state == 1)
		{
		_targetValue = 1160; //highend
		if (_currentValue <= _targetValue) {
			state = 0;
			_prevTargetValue = _targetValue;
			
 			   Serial.print("off");
			}
		}

	_stepdiff = (_targetValue - _prevTargetValue) / ( _rate *   ((float) baseDelayTime /100));
	_currentValue = _currentValue + _stepdiff;

	}

bool lockserial = false;
int movetoAtRate_giveCurTargpos(   int gotoUs, float argspeedPercentage) {
	//100percent speed would be MaxStepsPerLoop
	int stepsToTakeInThisLoop = abs(_currentValue - _targetValue); //prevtargetval is where we are now

	_targetValue = gotoUs; 
	if (stepsToTakeInThisLoop < 4) {
		if (!lockserial) {
			Serial.println("reached");
			_prevTargetValue = _targetValue;
			lockserial = true;
			}
		}
 

	_stepdiff = (_currentValue - _targetValue) / argspeedPercentage;
	Serial.print(" _stepdif ");	Serial.println(_stepdiff);
	_currentValue = _currentValue + _stepdiff;
	return _currentValue;
	}


float filter(float prevValue, float currentValue, int filter) {
	float lengthFiltered = (prevValue + (currentValue * filter)) / (filter + 1);
	return lengthFiltered;
	}