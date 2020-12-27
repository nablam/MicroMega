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

	
	public:
	enum ServoNames { FL0, FL1, FL2, FR0, FR1, FR2, BL0, BL1, BL2, BR0, BR1, BR2, NONE };
	ServoII();
	ServoII(ServoNames arg_sevoname , int argpin, int argmin, int argmax);

	uint8_t attach();
	uint8_t attach(int argpin, int argmin, int argmax);
	void write(int value);
	uint8_t read();
	int Get_Base_Min_Pulse_Width();
	int Get_Base_Max_Pulse_Width();


	private:
	int _mymin;
	int _mymax;


	ServoNames _sevoname;
	};

#endif

