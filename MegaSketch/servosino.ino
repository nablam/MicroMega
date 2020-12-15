

void SetAllServosTo(int argmilli) {
    for (int i = 0; i < TotalServos; i++) {
        int correctedPos = argmilli + ArraServoOffsets[i];
        ArraServos[i].writeMicroseconds(correctedPos);
        ArraServoPOSs[i] = correctedPos;
        }
    }

void SetServoToMilis(int argservo, int argmilis) {
    ArraServos[argservo].writeMicroseconds(argmilis);
    
    }

void PosCrouch_IN() {}
void PosCrouchOut() {}

//void MoveServoWithJS(int argPval, int argservoNumber, bool argrev, int(&argArraMin)[12], int(&argArraMax)[12], int(&argArraMid)[12]) {

void MoveServoWithJS(int argPval,int argservoNumber, bool argrev ) {
    

    int potmilis = 500;
    if (argrev == false) {
        potmilis = map(argPval, 0, PotReadScale, SERVOMIN, SERVOMAX);
        }
    else {
        potmilis = map(argPval, 0, PotReadScale, SERVOMAX, SERVOMIN);

        }

    int correctedPos = potmilis + ArraServoOffsets[argservoNumber];
    ArraServos[argservoNumber].writeMicroseconds(correctedPos);
    ArraServoPOSs[argservoNumber] = correctedPos;
    _mulcdDrivenMenu->OutputServoPOS(correctedPos);
    }
//FL FR BR BL
void MoveShoulderWithJS(int argLegNumber) {
    //22       23
    //
    //
    //28       29   rev these

    switch (argLegNumber) {
            case 0:     //FL22
                MoveServoWithJS(pval10_LS_lR, 0, false);
                MoveServoWithJS(pval9_LS_dU,1 , true);
                MoveServoWithJS(pval9_LS_dU, 2, true);

                break;
            case 1:     //FR23
                MoveServoWithJS(pval10_LS_lR, 3, false);
                MoveServoWithJS(pval9_LS_dU, 4, false);
                MoveServoWithJS(pval9_LS_dU, 5, false);
                break;
            case 2:     //BR29 rev
                MoveServoWithJS(pval10_LS_lR, 9, true);
                MoveServoWithJS(pval9_LS_dU, 10, false);
                MoveServoWithJS(pval9_LS_dU, 11, false);
                break;
            case 3:     //BL28 rev
                MoveServoWithJS(pval10_LS_lR, 6, true);
                MoveServoWithJS(pval9_LS_dU, 7, true);
                MoveServoWithJS(pval9_LS_dU, 8, true);
                break;
        }
    
    }

//using rightstick
void Kinematic_Pos_KneesIN() {
        
    MoveServoWithJS(pval10_LS_lR, 0, false);
            MoveServoWithJS(pval11_RS_uD, 1, true);
            MoveServoWithJS(pval11_RS_uD, 2, false);

    MoveServoWithJS(pval10_LS_lR, 3, true);
            MoveServoWithJS(pval11_RS_uD, 4, false);
            MoveServoWithJS(pval11_RS_uD, 5, true);

        MoveServoWithJS(pval10_LS_lR, 9, false);
            MoveServoWithJS(pval11_RS_uD, 10, true);
            MoveServoWithJS(pval11_RS_uD, 11, false);

        MoveServoWithJS(pval10_LS_lR, 6, true);
            MoveServoWithJS(pval11_RS_uD, 7, false);
            MoveServoWithJS(pval11_RS_uD, 8, true);
    
    }

void Kinematic_Pos_KneesOUT() {

    MoveServoWithJS(pval12_RS_lR, 0, false);
    MoveServoWithJS(pval11_RS_uD, 1, false);
    MoveServoWithJS(pval11_RS_uD, 2, true);

    MoveServoWithJS(pval12_RS_lR, 3, true);
    MoveServoWithJS(pval11_RS_uD, 4, true);
    MoveServoWithJS(pval11_RS_uD, 5, false);

    MoveServoWithJS(pval12_RS_lR, 9, false);
    MoveServoWithJS(pval11_RS_uD, 10, false);
    MoveServoWithJS(pval11_RS_uD, 11, true);

    MoveServoWithJS(pval12_RS_lR, 6, true);
    MoveServoWithJS(pval11_RS_uD, 7, true);
    MoveServoWithJS(pval11_RS_uD, 8, false);

    }
