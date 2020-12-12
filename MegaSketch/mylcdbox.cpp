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
	_IsSelectedPage=false;
	_IsSelectedServo = false;
	_isSelectedLeg = false;
	_isSelectedKinematics = false;
	_isSelectedPose = false;
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
	_IsSelectedPage = false;
	_IsSelectedServo = false;
	_isSelectedLeg = false;
	_isSelectedKinematics = false;
	_isSelectedPose = false;

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

void LcdBoxMenuCtrl::DoSwitchContext() {
	_lcd.setCursor(0, 1);            // move to the begining of the second line
	if (STATE_MENU < 0)STATE_MENU = 0;
	lcd_key = this->ReadKeysNonBlock();  // read the buttons

	switch (lcd_key)               // depending on which button was pushed, we perform an action
		{

			case btnUP:
				{
				STATE_MENU++;
				if (STATE_MENU > TotalSTATESmenue) { STATE_MENU = 0; } //rollback
				this->_lcd.clear();
				this->_lcd.setCursor(0, 0);
				this->_lcd.print(this->PageTites[STATE_MENU]);
				_IsSelectedPage = false;
				_IsSelectedServo = false;
				_isSelectedLeg = false;
				_isSelectedKinematics = false;
				_isSelectedPose = false;

				break;
				}
			case btnDOWN:
				{
				STATE_MENU--;
				if (STATE_MENU < 0) { STATE_MENU = TotalSTATESmenue; } //rollback
				this->_lcd.clear();
				this->_lcd.setCursor(0, 0);
				this->_lcd.print(this->PageTites[STATE_MENU]);
				_IsSelectedPage = false;
				_IsSelectedServo = false;
				_isSelectedLeg = false;

				break;
				}
			case btnSELECT:
				{
				if (_IsSelectedPage == false) {
					_IsSelectedPage = true;
					_IsSelectedServo = false;
					_isSelectedLeg = false;
					}
				else {

					//***************************process correct selection//
					this->_lcd.setCursor(0, 1);
					switch (STATE_MENU) {
							case 0:
								ProcessSelctionSubMenu_0_zeroing();
								break;
							case 1:
								ProcessSelectionSubMenu_1_servos();
								break;
							case 2:
								ProcessSelectionSubMenu_2_legs();
								break;
							case 3:
								ProcessSelectionSubMenu_3_kinematic();
								break;
							case 4:
								ProcessSelectionSubMenu_4_poses();
								break;

						}//xSubSwitch
					}//xpageselceted or not
				break;
				}
			case btnRIGHT:
				{
				this->_lcd.setCursor(0, 1);
				if (_IsSelectedPage) {
					


					switch (STATE_MENU) {
							case 0:
								Browse_0_zeroing(true);
								break;
							case 1:
								Browse_1_servos(true);
								break;
							case 2:
								Browse_2_legs(true);
								break;
							case 3:
								Browse_3_kinematics(true);
								break;
							case 4:
								Browse_4_poses(true);
								break;

						}//xSubSwitch




					
					}
				else
					{
					this->_lcd.print("page.not.slctd..");
					}
				break;
				}
			case btnLEFT:
				{
				this->_lcd.setCursor(0, 1);
				if (_IsSelectedPage) {


					switch (STATE_MENU) {
							case 0:
								Browse_0_zeroing(false);
								break;
							case 1:
								Browse_1_servos(false);
								break;
							case 2:
								Browse_2_legs(false);
								break;
							case 3:
								Browse_3_kinematics(false);
								break;
							case 4:
								Browse_4_poses(false);
								break;

						}//xSubSwitch
					
					
					}
				else
					{
					this->_lcd.print("page.not.slctd..");
					}

				break;

				}
			case btnNONE:
				{
		//		lcd.print("nada  ");
				break;
				}
		}//xswitch
	}



	void LcdBoxMenuCtrl::ProcessSelctionSubMenu_0_zeroing() {
		this->_lcd.setCursor(0, 1);
		this->_lcd.print(" zeroing  in:   ");
		}


	void LcdBoxMenuCtrl::ProcessSelectionSubMenu_1_servos() {
		if (_IsSelectedServo == false) { this->_lcd.print("<-SelectServo->"); }
		else
			{
			this->_lcd.print("       ok       ");
			_IsSelectedServo = true;
			}
		}


	void LcdBoxMenuCtrl::ProcessSelectionSubMenu_2_legs() {
		if (_isSelectedLeg == false) { this->_lcd.print("<-Select Leg ->"); }
		else
			{
			this->_lcd.print("       ok       ");
			_isSelectedLeg = true;
			}
		}


	void LcdBoxMenuCtrl::ProcessSelectionSubMenu_3_kinematic() {
		if (_isSelectedKinematics == false) { this->_lcd.print("<-Select Kinem->"); }
		else
			{
			this->_lcd.print("       ok       ");
			_isSelectedKinematics = true;
			}
		}


	void LcdBoxMenuCtrl::ProcessSelectionSubMenu_4_poses() {
		if (_isSelectedPose == false) { this->_lcd.print("<-Select pose->"); }
		else
			{
			this->_lcd.print("       ok       ");
			_isSelectedPose = true;
			}
		}

	void LcdBoxMenuCtrl::Browse_0_zeroing(bool argRightbtn) {
		if (argRightbtn) {
			}
		else
			{
			}
		}

	void LcdBoxMenuCtrl::Browse_1_servos(bool argRightbtn) {
		if (argRightbtn) {
			this->_curServoSelced++;
			if (this->_curServoSelced >= TotalSERVOS) {
				this->_curServoSelced = 0;
				}
			}
		else
			{
			this->_curServoSelced--;
			if (this->_curServoSelced < 0) {
				this->_curServoSelced = TotalSERVOS -1;
				}
			}
		this->_lcd.print(Servo12Titles[_curServoSelced]);
		}

	void LcdBoxMenuCtrl::Browse_2_legs(bool argRightbtn) {
		if (argRightbtn) {
			this->_curLegSelecetde++;
			if (this->_curLegSelecetde >= TotalLEGS) {
				this->_curLegSelecetde = 0;
				}
			}
		else
			{
			this->_curLegSelecetde--;
			if (this->_curLegSelecetde < 0) {
				this->_curLegSelecetde = TotalLEGS - 1;
				}
			}
		this->_lcd.print(Legs4Titles[_curLegSelecetde]);
		}
	void LcdBoxMenuCtrl::Browse_3_kinematics(bool argRightbtn) {
		if (argRightbtn) {
			this->_curKineSelected++;
			if (this->_curKineSelected >= TotalKINEMATICS) {
				this->_curKineSelected = 0;
				}
			}
		else
			{
			this->_curKineSelected--;
			if (this->_curKineSelected < 0) {
				this->_curKineSelected = TotalKINEMATICS - 1;
				}
			}
		this->_lcd.print(Kinematics2Titles[_curKineSelected]);
		}
	void LcdBoxMenuCtrl::Browse_4_poses(bool argRightbtn) {
		if (argRightbtn) {
			this->_curPoseSelected++;
			if (this->_curPoseSelected >= TotalPOSES) {
				this->_curPoseSelected = 0;
				}
			}
		else
			{
			this->_curPoseSelected--;
			if (this->_curPoseSelected < 0) {
				this->_curPoseSelected = TotalPOSES - 1;
				}
			}
		this->_lcd.print(Poses4Titles[_curPoseSelected]);
		}

	void dtryme() {}

