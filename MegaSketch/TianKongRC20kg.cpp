// 
// 
// 
#include "TianKongRC20kg.h"
#pragma region PUB
Servo20kg::Servo20kg(Servo argServo, int argPin, int argIndex, int argMin, int argMid, int argMax, bool argIsReversed, int argneutral, int argrange, bool positiveIncreaseMovesCorrectly) {
	_scaleFactor270 = 1.5f;

	_scaleUS = (float)(argMax- argMin)/ (float)(argrange *2);
	_servo = argServo;
	_pin=argPin;
	_index=argIndex;
	_min=argMin;
	_mid=argMid;
	_max=argMax;
	_isReversed=argIsReversed;
	_CurpositionUs = _mid;

	  _ANG_sv_neutral= argneutral;
	  _ANG_sv_range= argrange;
	  _ANG_sv_movesCorrectly= positiveIncreaseMovesCorrectly;

	  //if (positiveIncreaseMovesCorrectly) {
		 // _ANG_Corrected_whenLowVal = _ANG_sv_neutral;
		 // 
		 // }
	  //else {
		 // _ANG_Corrected_whenLowVal = _ANG_sv_neutral;
		 // }
	  ////add range to calfs
	  //if (_index % 3 == 2) {
		 // 
		 // 
		 // }
	  //else
		 // {
		 // _ANG_Corrected_whenLowVal;
		 // _ANG_Corrected_whenHighVal;

		 // }

	 

	}
void Servo20kg::AttachMe() {
	_servo.attach(_pin, _min, _max);
//	Serial.print("attached ");Serial.print(_index); Serial.print(" pin ");	Serial.print(_pin); Serial.println(" ");
	}
void Servo20kg::ZeroMe() {
	_servo.writeMicroseconds(_mid); _CurpositionUs = _servo.readMicroseconds();
//Serial.println("set to mid ");
//Serial.print(_mid);
	}


void Servo20kg::Rotate_Us_RelativeToMid(int argPotVal_0_500_1k) {
	//HIgh value 
	// 0.. opens out  .1. stretches down  ..2 stretches open
	//if reversed reverse servo min max
	if (_isReversed) {
		//_CurpositionUs = map(argPotVal_0_500_1k, 0, PotReadScale, _max, _min);
		_CurpositionUs = map(argPotVal_0_500_1k, 1000, 0, _min, _max);
		}
	else {
		//_CurpositionUs = map(argPotVal_0_500_1k, 0, PotReadScale, _min, _max);
		_CurpositionUs = map(argPotVal_0_500_1k, 0, 1000, _min, _max);

		}
	_servo.writeMicroseconds(_CurpositionUs);
	//_servo.writeMicroseconds(argPotVal_0_500_1k);
	}

void Servo20kg::RotateHalf_Us_RelativeToMid(int argPotVal_0_500_1k) {
	//HIgh value 
	// 0.. opens out  .1. stretches down  ..2 stretches open
	//if reversed reverse servo min max
	if (_isReversed) {
		//_CurpositionUs = map(argPotVal_0_500_1k, 0, PotReadScale, _max, _min);
		_CurpositionUs = map(argPotVal_0_500_1k, 1000, 0, _min, _mid);
		}
	else {
		//_CurpositionUs = map(argPotVal_0_500_1k, 0, PotReadScale, _min, _max);
		_CurpositionUs = map(argPotVal_0_500_1k, 0, 1000, _mid, _max);

		}
	_servo.writeMicroseconds(_CurpositionUs);
	//_servo.writeMicroseconds(argPotVal_0_500_1k);
	}

void Servo20kg::SetUs(int argPulse) {
	_servo.writeMicroseconds(argPulse);
	}

void Servo20kg::SetAngleDegrees_ScaleFactor1p5(int argAngle) {
	float newAng;//based ofset 205
	if (_ANG_sv_movesCorrectly) {
		Serial.print(" I movecorrectly ");
		newAng = _ANG_sv_neutral + argAngle;
		if (_index % 3 == 2) { newAng = _ANG_sv_neutral + argAngle-90; }
		}
	else
		{
		newAng = _ANG_sv_neutral - argAngle;
		if (_index % 3 == 2) { newAng = _ANG_sv_neutral - argAngle+90; }
		}

	int convertedFor270Scal=(float)newAng / _scaleFactor270;
	
	_CurpositionUs = _servo.readMicroseconds();
	_cur_Ang_sv = convertedFor270Scal;
	
	//90and = 1529
	//0 ang =2000
	
		//_servo.write(_cur_Ang_sv);
	Serial.print("/--["); Serial.print(_index); Serial.println("]-/--");
	Serial.print("InputANG = "); Serial.print(argAngle); Serial.print(" cur_Ang720="); Serial.print(_cur_Ang_sv); Serial.print(" svUs= ");	Serial.print(_CurpositionUs); Serial.print("new ang= "); Serial.print(newAng); Serial.println("--/");

	int newUS = WriteCorrectMillisFromInputangle(argAngle);
	Serial.print("US shouldbe = "); Serial.print(newUS);


	_CurpositionUs = newUS;
	_servo.writeMicroseconds(_CurpositionUs);
	};
void Servo20kg::SetAngleDegrees_toUS_noscale(int argAngle) {
	//int muConvertedFActor = (float)argAngle * 7.92f;//eek 
	//int minOffset = 634 + muConvertedFActor;
	//_servo.writeMicroseconds(minOffset);
	//TO DO 
	//SetUs(muConvertedFActor);
	}

void Servo20kg::Dispatch_TestFunc_value(int argFuncIndex, int argVal) {
	
	switch (argFuncIndex) {
			case 0:
				ZeroMe();
				break;
			case 1:
				if (argVal < 500)argVal = 900;
				if (argVal > 2000)argVal = 1300;
				SetUs(argVal);
				break;
			case 2:
				SetAngleDegrees_ScaleFactor1p5(argVal);
				break;
			case 3:
				SetAngleDegrees_toUS_noscale(argVal);
				break;
			
		
		}//Xswitch

	}

int  Servo20kg::WriteCorrectMillisFromInputangle(int argInputANG) {

	int US_output;

	if (_index % 3 != 2) {
		if (_ANG_sv_movesCorrectly == true) {
			US_output = _mid + (argInputANG * _scaleUS);
			}
		else
			{
			US_output = _mid - (argInputANG * _scaleUS);
			}
		}
	else
	if (_index % 3 == 2) {

		US_output = map(abs(argInputANG), 180, 45 , _min, _max);

		
		
		}

	return US_output;
	}

#pragma endregion

