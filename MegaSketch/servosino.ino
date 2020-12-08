//int x = 0;
//
//int doit() {
//	x++;
//	if (x > TotalServos)x = 0;
//	Print4char0_1(x);
//	return x; }
//
//void SetAllServosTo(int argmilli) {
//	for (int i = 0; i < TotalServos; i++) {
//		ArraServos[i].writeMicroseconds(argmilli);
//		}
//	}


/*



//Sample using LiquidCrystal library
#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);


#pragma region servo


#define TotalServos 12
#define DelaySpeed 50
Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;
Servo servo10;
Servo servo11;
Servo ArraServos[12] = { servo0 ,servo1,servo2,servo3,servo4,servo5,servo6,servo7,servo8,servo9,servo10,servo11 };
int ArraServoPINS[12]=  {22,23,24,25,26,27,28,29,30,31,32,33};
int ArraServoPOSs[12] = {00,00,00,00,00,00,00,00,00,00,00,00};
bool ServosInitialized = false;
int curDelay = 20;
float inputRate;
float rate;
float currentValue;
float targetValue;
float prevTargetValue;
int state = 0;
float stepdiff=0;
#pragma endregion

#pragma region Timers
unsigned long currentMillis;
unsigned long previousMillis;

#pragma endregion



void setup()
    {
    Serial.begin(115200);
    lcd.begin(16, 2);              // start the library
    lcd.setCursor(0, 0);
    lcd.print("RoboDogo V1.0");

    curDelay = DelaySpeed;
    for (int i = 0; i < TotalServos; i++) {
        ArraServos[i].attach(ArraServoPINS[i]);
     }

    }



float filter(float ArgprevValue, float ArgcurrentValue, int filter) {
    float lengthFiltered = (ArgprevValue + (ArgcurrentValue * filter)) / (filter + 1);
    return lengthFiltered;
    }


void TimedLoop() {

    currentMillis = millis();
    if (currentMillis - previousMillis >= 10) {  // start timed event
        previousMillis = currentMillis;
        //Do the loop here
         inputRate = Serial.parseFloat();
        rate == map(inputRate, 0, 1023, 45, 135);
        rate = inputRate;
        if (state == 0) {
            targetValue = 500;
            if (currentValue <= targetValue) {
                state = 1;
                prevTargetValue = targetValue;
                }
            }
        else if(state==1)
            {
            targetValue = 2300;
            if (currentValue >= targetValue) {
                state = 0;
                prevTargetValue = targetValue;
                }
            }

        stepdiff = (targetValue - prevTargetValue) / (20 * rate);
        currentValue = currentValue + stepdiff;
        SetAllServosTo(currentValue);
        Print4char0_1(currentValue);

        Serial.print("cur val= "); Serial.println(currentValue);
        Serial.print("inrate = "); Serial.println(inputRate);
        Serial.print("  rate = "); Serial.println(rate);
        Serial.print(" targV= "); Serial.println(targetValue);
        Serial.print("");
        }//Xtimed
    }//Xloop

void loop_servo0Sweep() {
    for (int i = 0; i < TotalServos; i++) {

        for (ArraServoPOSs[i] = 10; ArraServoPOSs[i] <= 100; ArraServoPOSs[i] += 1) {
            ArraServos[i].write(ArraServoPOSs[i]);
         }
        delay(curDelay);

    }

    for (int i = 0; i < TotalServos; i++) {


        for (ArraServoPOSs[i] = 100; ArraServoPOSs[i] >= 10; ArraServoPOSs[i] -= 1) {
            ArraServos[i].write(ArraServoPOSs[i]);
            }
            delay(curDelay);
        }
}

int p = 1590;
int oldvalue;
int newvalue;
void loop()
    {

    p = Serial.parseInt();



    if (p == 0) {
        p = oldvalue;
        }
   // else
     //   {

       // oldvalue = p;
       // }

currentMillis = millis();
if (currentMillis - previousMillis >= 1000) {  // start timed event
    previousMillis = currentMillis;
    //Do the loop here


    if (p < 830)p = 830;
    if (p > 2350)p = 2350;
    SetAllServosTo(p);
    oldvalue = p;
    }

// TimedLoop();
 //loop_servo0Sweep();
// PrintOn9_1(posservo0);
    }




*/