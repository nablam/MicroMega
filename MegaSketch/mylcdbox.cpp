// 
// 
// 

#include "mylcdbox.h"

#pragma region publicregion
//PUBLIC
LcdBoxMenuCtrl::LcdBoxMenuCtrl(int rs, int rw) : _lcd(8, 9, 4, 5, 6, 7) {
	_lcd.begin(16,2);
	_lcd.setCursor(0, 0);
	pinMode(A0, INPUT);
	}

LcdBoxMenuCtrl::LcdBoxMenuCtrl(int rs, int rw, int enable, int d0, int d1, int d2) : _lcd(rs, rw, enable, d0, d1, d2) {
	_lcd.begin(16,2);
	_lcd.setCursor(0, 0);
	_lcd.print("  Robodogo v0  ");
	_lcd.setCursor(0, 1);
	_lcd.print("Select to start");

	pinMode(A0, INPUT);
	Serial.println("lcd object inited");
	}

void LcdBoxMenuCtrl::HandleKEyPresses() {
	_lcd.setCursor(0, 1);            // move to the begining of the second line
	if (_CurFunction < 0)_CurFunction = MAXFunctions - 1;
	if (_CurFunction >= MAXFunctions) _CurFunction = 0;

	lcd_key = this->ReadKeysNonBlock();  // read the buttons

	switch (lcd_key)               // depending on which button was pushed, we perform an action
		{

			case btnUP:
				{

				if (_lock) break;_lock = true;

				_CurFunction++;
				if (_CurFunction >= MAXFunctions) { _CurFunction = 0; } //rollback
				if (_CurFunction < 0) { _CurFunction = MAXFunctions - 1; } //rollforward

				this->_lcd.clear();
				this->_lcd.setCursor(0, 0);
				this->_lcd.print(this->PageTites[_CurFunction]);
				this->_lcd.setCursor(0, 1);
				this->_lcd.print(this->Functions2DTable[_CurFunction][IndeciesOfSubFunctionSelections[_CurFunction]]);


				break;
				}
			case btnDOWN:
				{
				if (_lock) break;_lock = true;

				_CurFunction--;
				if (_CurFunction < 0) { _CurFunction = MAXFunctions - 1; } //rollback
				this->_lcd.clear();
				this->_lcd.setCursor(0, 0);
				this->_lcd.print(this->PageTites[_CurFunction]);
				this->_lcd.setCursor(0, 1);
				this->_lcd.print(this->Functions2DTable[_CurFunction][IndeciesOfSubFunctionSelections[_CurFunction]]);

				break;
				}
			case btnSELECT:
				{
				if (_lock) break;_lock = true;
				break;
				}
			case btnRIGHT:
				{
				if (_lock) break;_lock = true;
				if (_CurFunction >= MAXFunctions) { _CurFunction = 0; } //rollback
				if (_CurFunction < 0) { _CurFunction = MAXFunctions - 1; } //rollforward
				IndeciesOfSubFunctionSelections[_CurFunction]++;
				if (IndeciesOfSubFunctionSelections[_CurFunction] >= MaxIndeciesOfSubFunctionSelections[_CurFunction]) {
					IndeciesOfSubFunctionSelections[_CurFunction] = 0;
					}
				this->_lcd.clear();
				this->_lcd.setCursor(0, 1);
				this->_lcd.print(this->Functions2DTable[_CurFunction][IndeciesOfSubFunctionSelections[_CurFunction]]);
				break;
				}
			case btnLEFT:
				{
				if (_lock) break;_lock = true;
				if (_CurFunction >= MAXFunctions) { _CurFunction = 0; } //rollback
				if (_CurFunction < 0) { _CurFunction = MAXFunctions - 1; } //rollforward
				IndeciesOfSubFunctionSelections[_CurFunction]--;
				if (IndeciesOfSubFunctionSelections[_CurFunction] < 0 ) {
					IndeciesOfSubFunctionSelections[_CurFunction] = MaxIndeciesOfSubFunctionSelections[_CurFunction]-1;
					}
				this->_lcd.clear();
				this->_lcd.setCursor(0, 1);
				this->_lcd.print(this->Functions2DTable[_CurFunction][IndeciesOfSubFunctionSelections[_CurFunction]]);



				break;

				}
			case btnNONE:
				{
				_lock = false;

				break;
				}
		}//xswitch
	}

#pragma endregion

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


	void LcdBoxMenuCtrl::ProcessSelctionSubMenu_0_zeroing() {
		this->_lcd.setCursor(0, 1);
		this->_lcd.print(" zeroing  in:   ");
		}

	void LcdBoxMenuCtrl::ProcessSelectionSubMenu_1_servos() {
		//if (_IsSelectedServo == false) { this->_lcd.print("<-SelectServo->"); }
		//else
			//{
			this->_lcd.print("       ok       ");
			//}
		}


	void LcdBoxMenuCtrl::ProcessSelectionSubMenu_2_legs() {
		
		}


	void LcdBoxMenuCtrl::ProcessSelectionSubMenu_3_kinematic() {
		}


	void LcdBoxMenuCtrl::ProcessSelectionSubMenu_4_poses() {
		
		}
