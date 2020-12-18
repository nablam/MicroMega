// TianKongRC20kg.h

#ifndef _TIANKONGRC20KG_h
#define _TIANKONGRC20KG_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Servo.h>

class Servo20kg {

	public:
	Servo20kg(Servo argServo, int argPin, int argIndex, int argMin, int argMid, int argMax, bool argIsReversed);
	void AttachMe();
	void ZeroMe();
	void Rotate_Us_RelativeToMid(int agPotValue);//Pot outputs 0 -500- 1000

	private:
	Servo _servo;
	int _pin;
	int _index;
	int _min;
	int _mid;
	int _max;
	bool _isReversed;
	int _CurpositionUs;
	
	};



#endif

