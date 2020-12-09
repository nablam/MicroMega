
    //**************temp page data struct****************
struct PAGEds {
    String title5chars;
    int16_t num;
    bool menuDown;
    bool Select;
    bool menuUp;
    bool toggleBottom;
    bool toggleTop;
    int mode;
    };


//**************Leg servo poses in ms****************
struct LEG_ds {   // slave01 - back
    int16_t hip;
    int16_t shoulder;
    int16_t elbow;
    };
    //**************Body servo angles in ms****************
struct SER_ds {   
    LEG_ds legFR;
    LEG_ds legFL;
    LEG_ds legBR;
    LEG_ds legBL;
    };
 
    //**************Joysticks****************
//struct JOY_ds {
//    int16_t LS_lR; //pin10
//    int16_t LS_dU; //pin9
//    int16_t RS_lR; //pin12
//    int16_t RS_uD; //pin11
//    int16_t LS_rot;//pin8
//    int16_t RS_rot;//pin13
//    };
