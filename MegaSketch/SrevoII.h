// SrevoII.h

#ifndef _SREVOII_h
#define _SREVOII_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#include "Servo.h"

class ServoII : public Servo {
	private:
	int _mymin;
	int _mymax;
	public:

	ServoII();
	void write(int value);
	int read();
	int Get_Base_Min_Pulse_Width();
	int Get_Base_Max_Pulse_Width();
	};

#endif

