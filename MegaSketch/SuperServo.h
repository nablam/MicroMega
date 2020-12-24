// SuperServo.h

#ifndef _SUPERSERVO_h
#define _SUPERSERVO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SuperServoClass
{
 protected:


 public:
	void init();
};

extern SuperServoClass SuperServo;

#endif

