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
#define MAXFunctions 5
#define MAXCALIBS 3
#define MAXSERVOS 12
#define MAXLEGS 4
#define MAXKINEMATICS 2
#define MAXPOSES 4

#define btnRIGHT 0
#define btnRIGHT 0
#define btnUP 1
#define btnDOWN 2
#define btnLEFT 3
#define btnSELECT 4
#define btnNONE 5

	LcdBoxMenuCtrl(int rs, int rw);
	LcdBoxMenuCtrl(int rs, int rw, int enable, int d0, int d1, int d2);
	bool HandleKEyPresses();
	int Get_cuStatIndex();
	void OutputServoPOS(int argServoPos);

	private:
	LiquidCrystal _lcd;
	int lcd_key = 0;
	int adc_key_in = 0;
	int _CurFunction = 0; //noting , the next states are explained bellow
	bool _lock;
	bool _selectPressed;
	int ReadKeysNonBlock();

 

#pragma region menus
	int IndeciesOfSubFunctionSelections[MAXFunctions] = { 0,0,0,0,0 };
	int MaxIndeciesOfSubFunctionSelections[MAXFunctions] = { MAXCALIBS,MAXSERVOS,MAXLEGS,MAXKINEMATICS,MAXPOSES };
	int _curStateIndex; //= (_CurFunction*12) + index
	String PageTites[MAXFunctions] = {
//  "________________"	
	"0-zero all      ",
	"1-single manual ",
	"2-leg manual    ",
	"3-FULL Knematic ",
	"4-poses         "
		};

	String Functions2DTable[MAXFunctions][13] =
		{
			{
				"All zero        ",
				"All min         ",
				"All max         ",
				"!..outofbounds.!"
			},
			{
				"FRL_22  0.. xxxx",
				"FL1_24  .1. XXXX",
				"FL2_26  ..2 XXXX",
				"FR0_23  0.. XXXX",
				"FR1_25  .1. XXXX",
				"FR2_27  ..2 XXXX",
				"BL0_28  0.. XXXX",
				"BL1_30  .1. XXXX",
				"BL2_32  ..2 XXXX",
				"BR0_29  0.. XXXX",
				"BR1_31  .1. XXXX",
				"BR2_33  ..2 XXXX",
				"!..outofbounds.!"
			},
			 {
				"FLz=.. x=.. y=..",
				"FRz=.. x=.. y=..",
				"BRz=.. x=.. y=..",
				"BLz=.. x=.. y=..",
				"!..outofbounds.!",
			},
		   {
				"pos  Z.. X.. Y..",
				"rol  Z.. X.. Y..",
				"!..outofbounds.!",
		   },
		   {
				"walk forward    ",
				"side-step       ",
				"lawdown         ",
				"silly           ",
				"!..outofbounds.!",
			}

		};

#pragma endregion
	};

#endif