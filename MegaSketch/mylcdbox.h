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
	void StartLcd( );
	bool __lcdSet;
	void ON();
	void OFF();
	void ONOFF();
	int ReadKeysNonBlock();
	int _pin;
	int _delay;
	LiquidCrystal _lcd;


#pragma region menus



	int STATE_MENU = -1; //noting , the next states are explained bellow

	// define some values used by the panel and buttons
	int lcd_key = 0;
	int adc_key_in = 0;
	const int btnRIGHT = 0;
	const int btnUP   =  1;
	const int btnDOWN =  2;
	const int btnLEFT  = 3;
	const int btnSELECT =4;
	const int btnNONE  = 5;
	const int menuHOME =10;
	const int menuSingleServo =11;
	int menuContext = menuHOME;


	//0-zero all          
	//-lcd lr_select
	// ________________
	// zero>  
	// <min>
	// <max

	// 1-single manual	 test with RS_lR
	// "________________"
	// "FRL_22  0.. xxxx"
	// "FL1_24  .1. XXXX"
	// "FL2_26  ..2 XXXX"

	// "FR0_23  0.. XXXX"
	// "FR1_25  .1. XXXX"
	// "FR2_27  ..2 XXXX"

	// "BL0_28  0.. XXXX"
	// "BL1_30  .1. XXXX"
	// "BL2_32  ..2 XXXX"

	// "BR0_29  0.. XXXX"
	// "BR1_31  .1. XXXX"
	// "BR2_33  ..2 XXXX"

	//2 single leg manual test inverse kinematics
	// "FLz=.. x=.. y=.."
	// "FRz=.. x=.. y=.."
	// "BRz=.. x=.. y=.."
	// "BLz=.. x=.. y=.."


	//3 all legs manual invers kinematics
	// "pos  Z.. X.. Y.."
	// "rol  Z.. X.. Y.."
	// "

	//4 walk forward cycle
	// "forward         "
	// "side step       "
	// "laydown         "
	// "silly           "


#pragma endregion

	};

#endif

