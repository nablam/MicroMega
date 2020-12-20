

//void setup() {
//  myservo_A.attach(22,500,2500);
//  myservo_B.attach(23,2000,1000);
//  posA_input = ZEROPOS;
//  posB_input = ZEROPOS;
//  Serial.begin(115200);
//  }

String getValue(String data, char separator, int index)
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
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "nogo";
    }



void SerialInputsForA_Bloop() {
    String part01 = getValue(StrInputed_MegaSketch, ',', 0);
    String part02 = getValue(StrInputed_MegaSketch, ',', 1);
    //String part03 = getValue(StrInputed,';',2);

    if (part01.equalsIgnoreCase("nogo") && part02.equalsIgnoreCase("nogo")) {
        part01 = String(ZEROPOS);
        part02 = String(ZEROPOS);
        }
    else

        if (part01.equalsIgnoreCase("nogo") || part02.equalsIgnoreCase("nogo")) {
            if (part01.equalsIgnoreCase("nogo")) {
                part01 = part02;
                }
            else
                {
                part02 = part01;
                }
            }

    linecount_MegaSketch++;

    posA_input = part01.toInt();


    posB_input = part02.toInt();

    //Serial.print(part01);
    //Serial.print(part02);
    //Serial.print(posA_input+posB_input);
    //Serial.println("-- ");
    Serial.print(linecount_MegaSketch);
    Serial.print("  |");
    Serial.print("svrA= ");
    Serial.print(posA_input);
    Serial.print("  ");
    Serial.print("svrB= ");
    Serial.print(posB_input);
    Serial.println("-- -- -- ");

    //Sv20kgArra[2]->SetAngleDegrees(posA_input);
    //posA_input= Serial.parseInt();
    //posB_input= Serial.parseInt();

    //myservo_A.writeMicroseconds(posA_input);
    //myservo_B.writeMicroseconds(posB_input);
    //Serial.println(myservo_A.read());
    //Serial.println("-- ");
    }
//
//void loop() {
//    while (Serial.available() == 0) {}
//    StrInputed = Serial.readString();
//
//    SerialInputsForA_Bloop();
//
//    }

