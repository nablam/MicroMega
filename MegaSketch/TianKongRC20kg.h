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
	Servo20kg(Servo argServo, int argPin, int argIndex, int argMin, int argMid, int argMax, bool argIsReversed, int argneutral, int range, bool positiveIncreaseMovesCorrectly);
	void AttachMe();
	void ZeroMe();//0
	void Rotate_Us_RelativeToMid(int agPotValue);//Pot outputs 0 -500- 1000
	void RotateHalf_Us_RelativeToMid(int agPotValue);//Pot outputs 0 -500- 1000


	void SetAngleDegrees_ScaleFactor1p5(int argAngle);
	void SetUs(int argPuls);
	void SetAngleDegrees_toUS_noscale(int argAngle);
		
	void Dispatch_TestFunc_value(int argFuncIndex, int argVal);
	private:
	Servo _servo;
	float _scaleFactor270;  //input 180 degrees -> /_scalefactor720 = 120
	float _scaleUS; //
	int _pin;
	int _index;
	int _min;
	int _mid;
	int _max;
	bool _isReversed;

	int _ANG_sv_neutral;
	int _ANG_sv_range;
	bool _ANG_sv_movesCorrectly;

	float _ANG_Corrected_whenLowVal;
	float _ANG_Corrected_whenHighVal;

	int _CurpositionUs;
	float _curStandardizedAngle;
	float _cur_Ang_sv;
	
	};



#endif

