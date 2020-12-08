// mylcdbox.h

#ifndef _MYLCDBOX_h
#define _MYLCDBOX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class LED_Controls {
	public:
	LED_Controls(int pin, int delay);
	void ON();
	void OFF();
	int _pin;
	int _delay;
	};

#endif

