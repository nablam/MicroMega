// 
// 
// 
#include "TianKongRC20kg.h"
#pragma region PUB
Servo20kg::Servo20kg(Servo argServo, int argPin, int argIndex, int argMin, int argMid, int argMax, bool argIsReversed) {
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
	}
void Servo20kg::ZeroMe() { _servo.writeMicroseconds(_mid); }


void Servo20kg::Rotate_Us_RelativeToMid(int argPotVal_0_500_1k) {
	//HIgh value 
	// 0.. opens out  .1. stretches down  ..2 stretches open
	//if reversed reverse servo min max
	if (_isReversed) {
		_CurpositionUs = map(argPotVal_0_500_1k, 0, PotReadScale, _max, _min);
		}
	else {
		_CurpositionUs = map(argPotVal_0_500_1k, 0, PotReadScale, _min, _max);

		}
	_servo.writeMicroseconds(_CurpositionUs);
	}
#pragma endregion
