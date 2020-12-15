

void SetAllServosTo(int argmilli) {
    for (int i = 0; i < TotalServos; i++) {
        int correctedPos = argmilli + ArraServoOffsets[i];
        ArraServos[i].writeMicroseconds(correctedPos);
        ArraServoPOSs[i] = correctedPos;
        }
    }

void PosCrouch_IN() {}
void PosCrouchOut() {}

void MoveServoWithJS(int argservoNumber, bool argrev) {
    

    int potmilis = 500;
    if (argrev == false) {
        potmilis = map(pval10_LS_lR, 0, PotReadScale, SERVOMIN, SERVOMAX);
        }
    else {
        potmilis = map(pval10_LS_lR, 0, PotReadScale, SERVOMAX, SERVOMIN);

        }

    int correctedPos = potmilis + ArraServoOffsets[argservoNumber];
    ArraServos[argservoNumber].writeMicroseconds(correctedPos);
    ArraServoPOSs[argservoNumber] = correctedPos;
    _mulcdDrivenMenu->OutputServoPOS(correctedPos);
    }
