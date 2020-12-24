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

	  _state = 0;
	  _stepdiff = 0;
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
	//_servo.writeMicroseconds(argPulse);
	_servo.write(argPulse);
	_CurpositionUs = argPulse;
	}

void Servo20kg::LoadStatesUs(int argus) {
	float newAng;//based ofset 205
	if (_ANG_sv_movesCorrectly) {
		newAng = _ANG_sv_neutral + argus;
		if (_index % 3 == 2) {
			newAng = _ANG_sv_neutral + argus - 90;
			}
		}
	else
		{
		newAng = _ANG_sv_neutral - argus;
		if (_index % 3 == 2) { newAng = _ANG_sv_neutral - argus + 90; }
		}
	int convertedFor270Scal = (float)newAng / _scaleFactor270;
	_cur_Ang_sv = convertedFor270Scal;
	int newUS = WriteCorrectMillisFromInputangle(argus);

	if (_i_stateUs >= 4)_i_stateUs = 0;
	States_Us[_i_stateUs] = newUS;
	_i_stateUs++;
	
	}


void Servo20kg::General_ServoWalkCycle( int argRateMultiplier, int argInRate) {

	_inputRate = map(argInRate, 0, 1000, 1, 10);// pval11_RS_uD;//
	_rate = _inputRate;


	switch (_state) {
			case 0:
				_targetValue = States_Us[_state]; //lowend
				if (abs(_currentValue - _targetValue) < 3) {
					_state = 1;
					_prevTargetValue = _targetValue;
					_currentValue = _targetValue;
					}
				break;
			case 1:
				_targetValue = States_Us[_state]; //lowend
				if (abs(_currentValue - _targetValue) < 3) {
					_state = 2;
					_prevTargetValue = _targetValue;
					_currentValue = _targetValue;
					}
					break;
			case 2:
				_targetValue = States_Us[_state]; //lowend
				if (abs(_currentValue - _targetValue) < 3) {
					_state = 3;
					_prevTargetValue = _targetValue;
					_currentValue = _targetValue;
					}
					break;
			case 3:
				_targetValue = States_Us[_state]; //lowend
				if (abs(_currentValue - _targetValue) < 3) {
					_state = 0;
					_prevTargetValue = _targetValue;
					_currentValue = _targetValue;
					}
					break;
		}
	

				_stepdiff = (_targetValue - _prevTargetValue) / (argRateMultiplier * _rate);
				_currentValue = _currentValue + _stepdiff;

				SetUs(_currentValue);
	}
					

void Servo20kg::WriteNormalDegrees_convert_writeMilis(int argAngle_base180) {
	float newAng;//based ofset 205
	if (_ANG_sv_movesCorrectly) {
		//Serial.print(" I movecorrectly ");
		newAng = _ANG_sv_neutral + argAngle_base180;
		if (_index % 3 == 2) {
			newAng = _ANG_sv_neutral + argAngle_base180-90; }
		}
	else
		{
		newAng = _ANG_sv_neutral - argAngle_base180;
		if (_index % 3 == 2) { newAng = _ANG_sv_neutral - argAngle_base180+90; }
		}

	int convertedFor270Scal=(float)newAng / _scaleFactor270;
	
	//_CurpositionUs = _servo.readMicroseconds();
	_cur_Ang_sv = convertedFor270Scal;
	
	//90and = 1529
	//0 ang =2000
	
//_servo.write(_cur_Ang_sv);
//	Serial.print("/--["); Serial.print(_index); Serial.println("]-/--");
//	Serial.print("InputANG = "); Serial.print(argAngle); Serial.print(" cur_Ang720="); Serial.print(_cur_Ang_sv); Serial.print(" svUs= ");	Serial.print(_CurpositionUs); Serial.print("new ang= "); Serial.print(newAng); Serial.println("--/");

	int newUS = WriteCorrectMillisFromInputangle(argAngle_base180);
	//Serial.print("US shouldbe = "); Serial.print(newUS);


	_CurpositionUs = newUS;
	_servo.writeMicroseconds(_CurpositionUs);
	};


//void Servo20kg::Dispatch_TestFunc_value(int argFuncIndex, int argVal) {
//	
//	switch (argFuncIndex) {
//			case 0:
//				ZeroMe();
//				break;
//			case 1:
//				if (argVal < 500)argVal = 900;
//				if (argVal > 2000)argVal = 1300;
//				SetUs(argVal);
//				break;
//			case 2:
//				SetAngleDegrees_ScaleFactor1p5(argVal);
//				break;
//			case 3:
//				General_ServoSetAngle(argVal);
//				break;
//			
//		
//		}//Xswitch
//
//	}

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

