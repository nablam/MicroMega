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


	void WriteNormalDegrees_convert_writeMilis(int argAngle);
	void SetUs(int argPuls);
	void General_ServoWalkCycle( int argRateMultiplier,  int argInRate);
		
	void Dispatch_TestFunc_value(int argFuncIndex, int argVal);
	int  WriteCorrectMillisFromInputangle(int argInputANG);
	void LoadStatesUs(int argus);
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

	int _state;
	float _inputRate;
	float _rate;
	int _currentValue;
	int _targetValue;
	int _prevTargetValue;
	float _stepdiff = 0;

	float _ANG_Corrected_whenLowVal;
	float _ANG_Corrected_whenHighVal;

	int _CurpositionUs;
	float _curStandardizedAngle;
	float _cur_Ang_sv;



	int States_Us[4]{1300,1300,1300,1300};
	int _i_stateUs;

	//int WalkCycle0_T = 0;
	//int WalkCycle0_D = 5;
	//int WalkCycle0_H = 13;

	//int WalkCycle1_T = 0;
	//int WalkCycle1_D = -5;
	//int WalkCycle1_H = 13;

	//int WalkCycle2_T = 0;
	//int WalkCycle2_D = -5;
	//int WalkCycle2_H = 9;

	//int WalkCycle3_T = 0;
	//int WalkCycle3_D = 5;
	//int WalkCycle3_H = 9;
	
	};



#endif

