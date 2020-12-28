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
Svo s0;
Svo s1;
int baseDelayTime = 780;
int angles[6] = { 25,90,180,270,180,90 };
int i_ang = 0;
int tempangle = 90;
int tempDelay = 2000;
int _inputRate = 20;
float _rate = 400.0;
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
	Serial.begin(115200);
	s0.Attach(40, false);
	s1.Attach(38, false);


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
	s1.WriteMicroseconds(testvalue_849_2197);


	delay(baseDelayTime);
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
	//currentMillis = millis();
	//BaseStartCountMillis = currentMillis;
	//if (BaseStartCountMillis > (4010 + baseDelayTime )) {
		/*if (!printednce) {
			Serial.println("STARTED!!!");
			printednce = true;
			
			}*/

		/*if (currentMillis - previousMillis >= 10000) {
			previousMillis = currentMillis;*/

			//ReadInputRate_sweep_noservomove();
			//s1.WriteMicroseconds(_currentValue);
	
	s1.WriteMicroseconds(2197);
	
	delay(baseDelayTime);
	s1.WriteMicroseconds( 849 );

	delay(baseDelayTime);
			//testvalue_849_2197 = testvalue_849_2197 -800;
			
			if (testvalue_849_2197 > 849 && testvalue_849_2197 < 2198)s1.WriteMicroseconds(testvalue_849_2197);
			//testvalue_849_2197 = 849;

			
		//	}
		//}
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

	_stepdiff = (_targetValue - _prevTargetValue) / ( _rate);
	_currentValue = _currentValue + _stepdiff;

	}


int movetoAtRate_giveCurTargpos(   int gotoUs) {

//	_inputRate = map(argInRate, 0, 1000, 1, 10);// pval11_RS_uD;//
	//_rate = _inputRate;

	_targetValue = gotoUs; //lowend
	if (abs(_currentValue - _targetValue) < 1) {
		Serial.println("reached");
		_prevTargetValue = _targetValue;
		_currentValue = _targetValue;
		}


	_stepdiff = (_targetValue - _prevTargetValue) / ( _rate);
	_currentValue = _currentValue + _stepdiff;

	return _currentValue;
	}


float filter(float prevValue, float currentValue, int filter) {
	float lengthFiltered = (prevValue + (currentValue * filter)) / (filter + 1);
	return lengthFiltered;
	}