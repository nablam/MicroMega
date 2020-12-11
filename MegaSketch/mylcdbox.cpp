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
	_lcd.print("  Robodogo v0  ");
	_lcd.setCursor(0, 1);
	_lcd.print("Select to start");

	//pinMode(LED_BUILTIN, OUTPUT);
	pinMode(A0, INPUT);
	Serial.println("lcd object inited");

	}

void LcdBoxMenuCtrl::ON() {
	//digitalWrite(LED_BUILTIN, HIGH);
	//_lcd.begin(16, 2);
	_lcd.clear();
	_lcd.setCursor(3, 0);
	_lcd.print("Aon");
	Serial.println("on ");
//	delay(_delay);
	}

void LcdBoxMenuCtrl::OFF() {
	//digitalWrite(LED_BUILTIN, LOW);
	_lcd.clear();
	_lcd.setCursor(1, 1);
	_lcd.print("Boff");
	Serial.println("off");
//	delay(_delay);
	}

void LcdBoxMenuCtrl::ONOFF() {
	//digitalWrite(LED_BUILTIN, LOW);
	//_lcd.begin(16, 2);
	_lcd.setCursor(0, 5);
	_lcd.print("conoff");
	Serial.println("conoff");
//	delay(_delay);
	}

int LcdBoxMenuCtrl::ReadKeysNonBlock() {
		adc_key_in = analogRead(0);      // read the value from the sensor
		// my buttons when read are centered at these valies: 0, 144, 329, 504, 741
		// we add approx 50 to those values and check to see if we are close
		if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
		// For V1.1 us this threshold
		if (adc_key_in < 50)   return btnRIGHT;
		if (adc_key_in < 250)  return btnUP;
		if (adc_key_in < 450)  return btnDOWN;
		if (adc_key_in < 650)  return btnLEFT;
		if (adc_key_in < 850)  return btnSELECT;

		// For V1.0 comment the other threshold and use the one below:

	  //  if (adc_key_in < 50)   return btnRIGHT;
	  //  if (adc_key_in < 195)  return btnUP;
	  //  if (adc_key_in < 380)  return btnDOWN;
	   // if (adc_key_in < 555)  return btnLEFT;
	  //  if (adc_key_in < 790)  return btnSELECT;



		return btnNONE;  // when all others fail, return this...
	}

void LcdBoxMenuCtrl::StartLcd( ) {
	 
	__lcdSet = true;
	_lcd.begin(16,2);
	_lcd.setCursor(0, 0);

	}