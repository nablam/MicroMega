// 
// 
// 

#include "SrevoII.h"




ServoII::ServoII() :  Servo() {}
ServoII::ServoII(ServoNames argSn, int argpin, int argmin, int argmax) : Servo() {
    
  // Servo attach(argpin, argmin, argmax);
  // using uint8_t Servo::attach;
    Servo::attach(argpin, argmin, argmax);
    this->_sevoname = argSn;
    }


uint8_t ServoII::attach(int argpin, int argmin, int argmax)
    {
    return  Servo::attach(  argpin,   argmin,   argmax);
    }

void ServoII::write(int value)
    {
    if (value < MIN_PULSE_WIDTH)
        {  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
        if (value < 0) value = 0;
        if (value > 270) value = 270;
        value = map(value, 0, 270, Get_Base_Min_Pulse_Width(), Get_Base_Max_Pulse_Width());
        }
    Servo::writeMicroseconds(value);
    Serial.print(" write to ");
    Serial.print(value);
    Serial.println("  ");
    }

uint8_t ServoII::read()
    {
    return  map(Servo::readMicroseconds() + 1, Get_Base_Min_Pulse_Width(), Get_Base_Max_Pulse_Width(), 0, 270);
    }

int ServoII::Get_Base_Min_Pulse_Width(){
    int tempmin = (MIN_PULSE_WIDTH - _mymin * 4);
    Serial.print(" _mymin= ");
    Serial.print(MIN_PULSE_WIDTH);
    Serial.print(" _mymax= ");
    Serial.print(MAX_PULSE_WIDTH);

    Serial.print(" getmin= ");
    Serial.print(tempmin);
    Serial.println("  ");
    return  (MIN_PULSE_WIDTH - _mymin * 4);
    }

int ServoII::Get_Base_Max_Pulse_Width(){

    int tempmax = (MAX_PULSE_WIDTH - _mymin * 4);
    Serial.print(" _mymin= ");
    Serial.print(MIN_PULSE_WIDTH);
    Serial.print(" _mymax= ");
    Serial.print(MAX_PULSE_WIDTH);

    Serial.print(" getmin= ");
    Serial.print(tempmax);
    Serial.println("  ");
            return  (MAX_PULSE_WIDTH -_mymax * 4);
            }