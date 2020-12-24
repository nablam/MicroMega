// 
// 
// 

#include "SrevoII.h"




ServoII::ServoII() : Servo() {}
void ServoII::write(int value)
    {
    if (value < MIN_PULSE_WIDTH)
        {  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
        if (value < 0) value = 0;
        if (value > 270) value = 270;
        value = map(value, 0, 270, Get_Base_Min_Pulse_Width(), Get_Base_Max_Pulse_Width());
        }
    Servo::writeMicroseconds(value);
    }

int ServoII::read()
    {
    return  map(Servo::readMicroseconds() + 1, Get_Base_Min_Pulse_Width(), Get_Base_Max_Pulse_Width(), 0, 270);
    }

int ServoII::Get_Base_Min_Pulse_Width(){
    return  (MIN_PULSE_WIDTH - _mymin * 4);
    }

int ServoII::Get_Base_Max_Pulse_Width(){
            return  (MIN_PULSE_WIDTH - _mymax * 4);
            }