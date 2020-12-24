// how much serial data we expect before a newline
const unsigned int MAX_INPUT = 50;

  // here to process incoming serial data after a terminator received
void process_data(const char* data)
    {
    // for now just display it
    // (but you could compare it to some value, convert to an integer, etc.)
   // Serial.println(data);
  //  SerialInputsFor_LcdFunctions(data);

    }  // end of process_data

void processIncomingByte_subEmFuncEm(const byte inByte)
    {
    static char input_line[MAX_INPUT];
    static unsigned int input_pos = 0;

    switch (inByte)
        {

            case '\n':   // end of text
                input_line[input_pos] = 0;  // terminating null byte

                // terminator reached! process input_line here ...
                process_data(input_line);

                // reset buffer for next time
                input_pos = 0;
                break;

            case '\r':   // discard carriage return
                break;

            default:
              // keep adding if not full ... allow for terminating null byte
                if (input_pos < (MAX_INPUT - 1))
                    input_line[input_pos++] = inByte;
                break;
        }  //Xswitch

    } //XprocessIncomingByte  



String getSubStringz(String data, char separator, int index)
    {
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
            }
        }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "***";
    }


void SerialInputsFor_LcdFunctions_i_f_v(String argDatas) {
    linecount_MegaSketch++;
    int ServoIndex = 0;
    int functionIndex = 0;
    int NumericInput = 0;
   
    String subStr0 = getSubStringz(argDatas, ',', 0); //servo index
    String subStr1 = getSubStringz(argDatas, ',', 1); //what function to use : write , write angle , convertedd angle ...
    String subStr2 = getSubStringz(argDatas, ',', 2); // angle aorwhatever

    if (subStr0.equalsIgnoreCase("***")) {
        subStr0 = "0";
        }
    if (subStr1.equalsIgnoreCase("***")) {
        subStr1 = "0";//  zero me function
        }
    if (subStr2.equalsIgnoreCase("***")) {
        subStr1 = "1600";// String(ZEROPOS);
        }

    ServoIndex = subStr0.toInt();
    if (ServoIndex < 0 || ServoIndex >= TOTALSERVOS) { ServoIndex = 0; }

    functionIndex = subStr1.toInt();
    if (functionIndex < 0 || functionIndex >= 4) { functionIndex = 0; } //  zerome, rotateUs, RotateAngle, rotateAngle270, RotateAngleUsconversion

    NumericInput = subStr2.toInt();
    if (NumericInput < 0 || NumericInput >= 2500) { functionIndex = 0; } 

    Serial.print(formatLineCountPrint(linecount_MegaSketch));  Serial.print("  |");
    Serial.print("svr i= ");
    Serial.print(ServoIndex);
    Serial.print("  ");
    Serial.print("func ");
    Serial.print(functionIndex);
    Serial.print("  ");
    Serial.print("input ");
    Serial.print(NumericInput);
    Serial.println(" .");

   Sv20kgArra[ServoIndex]->Dispatch_TestFunc_value(functionIndex, NumericInput);
   
    }

int SerialInputsFor_ServoAB_vomparefuncs(String argDatas) {
   // linecount_MegaSketch++;

    int theval= argDatas.toInt();
  
 //   Serial.print(formatLineCountPrint(linecount_MegaSketch));  Serial.print("  |");
 //   Serial.print("theval= ");
//    Serial.print(theval);
    return (theval);
   // delay(1000);
  //  Sv20kgArra[0]->SetAngleDegrees_ScaleFactor1p5(theval);
  /*  Sv20kgArra[0]->SetAngleDegrees_ScaleFactor1p5(theval);
    Sv20kgArra[3]->SetAngleDegrees_ScaleFactor1p5(theval);
    Sv20kgArra[6]->SetAngleDegrees_ScaleFactor1p5(theval);*/
    //Sv20kgArra[9]->SetAngleDegrees_ScaleFactor1p5(theval);

   /* Sv20kgArra[1]->SetAngleDegrees_ScaleFactor1p5(theval);
    Sv20kgArra[4]->SetAngleDegrees_ScaleFactor1p5(theval);
    Sv20kgArra[7]->SetAngleDegrees_ScaleFactor1p5(theval);
    Sv20kgArra[10]->SetAngleDegrees_ScaleFactor1p5(theval);*/

   // Sv20kgArra[2]->SetAngleDegrees_ScaleFactor1p5(theval);
  //  Sv20kgArra[5]->SetAngleDegrees_ScaleFactor1p5(theval);
   // Sv20kgArra[8]->SetAngleDegrees_ScaleFactor1p5(theval);
   // Sv20kgArra[11]->SetAngleDegrees_ScaleFactor1p5(theval);

  //  Sv20kgArra[0]->SetUs(theval);
    //Sv20kgArra[6]->SetAngleDegrees_ScaleFactor1p5(theval);
    //Sv20kgArra[9]->SetAngleDegrees_ScaleFactor1p5(theval);


    }




String formatLineCountPrint(int number)
    {
    String temp = "";
    if (number < 10)
        {
        temp = "00" + number;

        }
    else
        temp = number;

    return temp;
    }

void loop_ReadSerialInputs()
    {
    while (Serial.available() > 0)
        processIncomingByte_subEmFuncEm(Serial.read());

      // dostuffs

    }  // end of loop
