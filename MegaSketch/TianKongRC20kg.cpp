// 
// 
// 
#include "TianKongRC20kg.h"
#pragma region PUB
Servo20kg::Servo20kg(Servo argServo, int argPin, int argIndex, int argMin, int argMid, int argMax, bool argIsReversed) {
	_scaleFactor270 = 1.5f;
	_scaleUS = 0.133f;
	_servo = argServo;
	_pin=argPin;
	_index=argIndex;
	_min=argMin;
	_mid=argMid;
	_max=argMax;
	_isReversed=argIsReversed;
	_CurpositionUs = 1600;
	}
void Servo20kg::AttachMe() {
	_servo.attach(_pin, _min, _max);
//	Serial.print("attached ");Serial.print(_index); Serial.print(" pin ");	Serial.print(_pin); Serial.println(" ");
	}
void Servo20kg::ZeroMe() { _servo.writeMicroseconds(_mid); 
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
	int convertedFor270Scal=(float)argAngle / _scaleFactor270;
	_servo.write(convertedFor270Scal);
	Serial.println("");
	Serial.println(_servo.readMicroseconds());
	};
void Servo20kg::SetAngleDegrees_toUS_noscale(int argAngle) {
	int muConvertedFActor = (float)argAngle * 7.92f;//eek 
	int minOffset = 634 + muConvertedFActor;
	_servo.writeMicroseconds(minOffset);
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
#pragma endregion
