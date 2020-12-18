
void SetAllServosToMid() {   
    for (int s = 0; s < TotalServos; s++) {
        Sv20kgArra[s]->ZeroMe();
        }
    }
void SetAllServosTo_RelativeMax() {}
void SetAllServosTo_RelativeMin() {}

/*
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





void MoveServoWithJS_v1(int argPval, int argservoNumber, bool argrev, int *argArraMin, int *argArraMax) {

//void MoveServoWithJS(int argPval,int argservoNumber, bool argrev ) {
    int potmilis = 500;
    if (argrev == false) {
        potmilis = map(argPval, 0, PotReadScale, argArraMin[argservoNumber], argArraMax[argservoNumber]);
        }
    else {
        potmilis = map(argPval, 0, PotReadScale, argArraMax[argservoNumber], argArraMin[argservoNumber]);

        }

    int correctedPos = potmilis + ArraServoOffsets[argservoNumber];
    ArraServos[argservoNumber].writeMicroseconds(correctedPos);
    ArraServoPOSs[argservoNumber] = correctedPos;
    _mulcdDrivenMenu->OutputServoPOS(correctedPos);
    }
//FL FR BR BL
void MoveShoulderWithJS_v1(int argLegNumber, int *argArraMin, int *argArraMax) {
    //22       23
    //
    //
    //28       29   rev these

    switch (argLegNumber) {
            case 0:     //FL22
                MoveServoWithJS_v1(pval10_LS_lR, 0, false, &argArraMax[0], &argArraMin[0]);
                MoveServoWithJS_v1(pval9_LS_dU,1 , true, &argArraMax[1], &argArraMin[1]);
                MoveServoWithJS_v1(pval9_LS_dU, 2, true, &argArraMax[2], &argArraMin[2]);

                break;
            case 1:     //FR23
                MoveServoWithJS_v1(pval10_LS_lR, 3, false, &argArraMax[3], &argArraMin[3]);
                MoveServoWithJS_v1(pval9_LS_dU, 4, false, &argArraMax[4], &argArraMin[4]);
                MoveServoWithJS_v1(pval9_LS_dU, 5, false, &argArraMax[5], &argArraMin[5]);
                break;
            case 2:     //BR29 rev
                MoveServoWithJS_v1(pval10_LS_lR, 9, true, &argArraMax[9], &argArraMin[9]);
                MoveServoWithJS_v1(pval9_LS_dU, 10, false, &argArraMax[10], &argArraMin[10]);
                MoveServoWithJS_v1(pval9_LS_dU, 11, false, &argArraMax[11], &argArraMin[11]);
                break;
            case 3:     //BL28 rev
                MoveServoWithJS_v1(pval10_LS_lR, 6, true, &argArraMax[6], &argArraMin[6]);
                MoveServoWithJS_v1(pval9_LS_dU, 7, true, &argArraMax[7], &argArraMin[7]);
                MoveServoWithJS_v1(pval9_LS_dU, 8, true, &argArraMax[8], &argArraMin[8]);
                break;
        }

    }

//using rightstick
void Kinematic_Pos_KneesIN_v1(int(&argArraMax)[12], int(&argArraMin)[12]) {

    MoveServoWithJS_v1(pval10_LS_lR, 0, false, &argArraMax[0], &argArraMin[0]);
    MoveServoWithJS_v1(pval11_RS_uD, 1, true, &argArraMax[1], &argArraMin[1]);
    MoveServoWithJS_v1(pval11_RS_uD, 2, false, &argArraMax[2], &argArraMin[2]);

    MoveServoWithJS_v1(pval10_LS_lR, 3, true, &argArraMax[3], &argArraMin[3]);
    MoveServoWithJS_v1(pval11_RS_uD, 4, false, &argArraMax[4], &argArraMin[4]);
    MoveServoWithJS_v1(pval11_RS_uD, 5, true, &argArraMax[5], &argArraMin[5]);

    MoveServoWithJS_v1(pval10_LS_lR, 9, false, &argArraMax[9], &argArraMin[9]);
    MoveServoWithJS_v1(pval11_RS_uD, 10, true, &argArraMax[10], &argArraMin[10]);
    MoveServoWithJS_v1(pval11_RS_uD, 11, false, &argArraMax[11], &argArraMin[11]);

    MoveServoWithJS_v1(pval10_LS_lR, 6, true, &argArraMax[6], &argArraMin[6]);
    MoveServoWithJS_v1(pval11_RS_uD, 7, false, &argArraMax[7], &argArraMin[7]);
    MoveServoWithJS_v1(pval11_RS_uD, 8, true, &argArraMax[8], &argArraMin[8]);

    }

void Kinematic_Pos_KneesOUT_v1(int(&argArraMax)[12], int(&argArraMin)[12]) {




    MoveServoWithJS_v1(pval10_LS_lR, 0, false, &argArraMax[0], &argArraMin[0]);
    MoveServoWithJS_v1(pval11_RS_uD, 1, false, &argArraMax[1], &argArraMin[1]);
    MoveServoWithJS_v1(pval11_RS_uD, 2, true, &argArraMax[2], &argArraMin[2]);

    MoveServoWithJS_v1(pval10_LS_lR, 3, true, &argArraMax[3], &argArraMin[3]);
    MoveServoWithJS_v1(pval11_RS_uD, 4, true, &argArraMax[4], &argArraMin[4]);
    MoveServoWithJS_v1(pval11_RS_uD, 5, false, &argArraMax[5], &argArraMin[5]);

    MoveServoWithJS_v1(pval10_LS_lR, 9, false, &argArraMax[9], &argArraMin[9]);
    MoveServoWithJS_v1(pval11_RS_uD, 10, false, &argArraMax[10], &argArraMin[10]);
    MoveServoWithJS_v1(pval11_RS_uD, 11, true, &argArraMax[11], &argArraMin[11]);

    MoveServoWithJS_v1(pval10_LS_lR, 6, true, &argArraMax[6], &argArraMin[6]);
    MoveServoWithJS_v1(pval11_RS_uD, 7, true, &argArraMax[7], &argArraMin[7]);
    MoveServoWithJS_v1(pval11_RS_uD, 8, false, &argArraMax[8], &argArraMin[8]);



    }


*/