// mylcdbox.h

#ifndef _MYLCDBOX_h
#define _MYLCDBOX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <LiquidCrystal.h>


class LcdBoxMenuCtrl {
	public:
	LcdBoxMenuCtrl(int rs, int rw);
	LcdBoxMenuCtrl(int rs, int rw, int enable, int d0, int d1, int d2);
	void SetLcd( );
	bool __lcdSet;
	void ON();
	void OFF();
	int GetCurMenuState();
	int _pin;
	int _delay;
	LiquidCrystal _lcd;
	};

#endif

