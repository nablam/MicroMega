// 
// 
// 

#include "mylcdbox.h"

LcdBoxMenuCtrl::LcdBoxMenuCtrl(int rs, int rw) : _lcd(8, 9, 4, 5, 6, 7) {
	_lcd.begin(16,2);
	_lcd.setCursor(0, 0);
	_lcd.print("hi");
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(A0, INPUT);
	}

LcdBoxMenuCtrl::LcdBoxMenuCtrl(int rs, int rw, int enable, int d0, int d1, int d2) : _lcd(rs, rw, enable, d0, d1, d2) {
	_lcd.begin(16,2);
	_lcd.setCursor(0, 0);
	_lcd.print("hi");
	pinMode(LED_BUILTIN, OUTPUT);
	pinMode(A0, INPUT);
	Serial.println("inited");
	 }

void LcdBoxMenuCtrl::ON() {
	digitalWrite(LED_BUILTIN, HIGH);
	_lcd.begin(16, 2);
	_lcd.setCursor(3, 0);
	_lcd.print("A");
	Serial.println("on ");
//	delay(_delay);
	}

void LcdBoxMenuCtrl::OFF() {
	digitalWrite(LED_BUILTIN, LOW);
	_lcd.begin(16, 2);
	_lcd.setCursor(1, 1);
	_lcd.print("B");
	Serial.println("off");
//	delay(_delay);
	}

int LcdBoxMenuCtrl::GetCurMenuState() {
 

	return 1;
	}

void LcdBoxMenuCtrl::SetLcd( ) {
	 
	__lcdSet = true;


	}