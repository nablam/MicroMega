/* 
* acos in radd
* 
* a=8
* b=6
* c=7
* 
* cos A= (b^2+c^2- a^2)/ 2bc
* cos A= (36+49-64) / 84
* cos A=0.25 
* A=cos^-1(0.25)
* A=75.5224
* 
* cos B= (a^2+c^2- b^2)/ 2ac
* cos B=0.68 
* B=cos^-1(0.68)
* B= 46.6
* 
* shoulderanle= sq(armangle) + sg(shinangle)
*
*
*          <--------------------Trabsverse T ---------------------->          
* 
* 
*								front
*				FR0		[0]								FL0   [3]
*				FR1		[1]								FL1   [4]
*				FR2		[2]								FL2   [5]
* 
* 
*				BR0		[6]								BL0	  [9]
*				BR1		[7]								BL1  [10]
*				BR2		[8]								BL2	 [11]
* 
*	front view looing at FR0
* 
*				|\
*				| \
* input H		|  \
* input T		|   \
*			H	|    \  Z'  find Z'   Angle T addjudt for FR[0]
*				|     \      
*				|      \
*				|_      \
*				|_|______\
*					T
* 
*    H^2 + T^2 = H^
* 
*	AngleT = Tan^-1(T/H)
* 
*/


float GetRawAngle(float argOposit, float argAdjascent ) {
	float rads= atan(argOposit / argAdjascent);
	return rads* (180/ PI);
	}

double GetZprime(float arhHeight, float argTransverse) {
	return sqrt((arhHeight * arhHeight) + (argTransverse * argTransverse));
//	return sqrt88x((arhHeight * arhHeight) + (argTransverse * argTransverse));
	}

/* 
* side view looking ar FR0
* 
* *				| \
*				|   \
* input Z'		|     \
* input F		|       \
*		     Z' |         \  Z  find Z
*				|           \      
*				|            \
*				|_            \
*				|_|____________\
*					F
*/

//reuse get z'func

/* 
*                    A
*				---------------
*				\             /
*				  \          /
*				Z   \       /  C
*					  \    /
*					   \  /
*						\/
* 
*   Find angle C  adjust for  FR[1]   ACZ
*   Find angle Z  adjust for  FR[2]   CZA
* 
* 
* */


float AC_i[241] = { 90.0,89.8,89.5,89.3,89.0,88.8,88.6,88.3,88.1,87.9,87.6,87.4,87.1,86.9,86.7,86.4,86.2,85.9,85.7,85.5,85.2,85.0,84.7,84.5,84.3,84.0,83.8,83.5,83.3,83.1,82.8,82.6,82.3,82.1,81.9,81.6,81.4,81.1,80.9,80.6,80.4,80.2,79.9,79.7,79.4,79.2,78.9,78.7,78.5,78.2,78.0,77.7,77.5,77.2,77.0,76.8,76.5,76.3,76.0,75.8,75.5,75.3,75.0,74.8,74.5,74.3,74.0,73.8,73.5,73.3,73.0,72.8,72.5,72.3,72.0,71.8,71.5,71.3,71.0,70.8,70.5,70.3,70.0,69.8,69.5,69.3,69.0,68.7,68.5,68.2,68.0,67.7,67.5,67.2,66.9,66.7,66.4,66.2,65.9,65.6,65.4,65.1,64.8,64.6,64.3,64.1,63.8,63.5,63.3,63.0,62.7,62.5,62.2,61.9,61.6,61.4,61.1,60.8,60.5,60.3,60.0,59.7,59.4,59.2,58.9,58.6,58.3,58.1,57.8,57.5,57.2,56.9,56.6,56.3,56.1,55.8,55.5,55.2,54.9,54.6,54.3,54.0,53.7,53.4,53.1,52.8,52.5,52.2,51.9,51.6,51.3,51.0,50.7,50.4,50.1,49.8,49.5,49.1,48.8,48.5,48.2,47.9,47.5,47.2,46.9,46.6,46.2,45.9,45.6,45.2,44.9,44.6,44.2,43.9,43.5,43.2,42.8,42.5,42.1,41.8,41.4,41.0,40.7,40.3,39.9,39.6,39.2,38.8,38.4,38.0,37.7,37.3,36.9,36.5,36.1,35.7,35.2,34.8,34.4,34.0,33.6,33.1,32.7,32.2,31.8,31.3,30.9,30.4,29.9,29.4,29.0,28.5,28.0,27.4,26.9,26.4,25.8,25.3,24.7,24.1,23.6,23.0,22.3,21.7,21.0,20.4,19.7,18.9,18.2,17.4,16.6,15.7,14.8,13.9,12.8,11.7,10.5,9.1,7.4,5.2,0.0 };
float C_i_A[241] = { 0.0,0.5,1.0,1.4,1.9,2.4,2.9,3.3,3.8,4.3,4.8,5.3,5.7,6.2,6.7,7.2,7.6,8.1,8.6,9.1,9.6,10.0,10.5,11.0,11.5,12.0,12.4,12.9,13.4,13.9,14.4,14.8,15.3,15.8,16.3,16.8,17.3,17.7,18.2,18.7,19.2,19.7,20.2,20.6,21.1,21.6,22.1,22.6,23.1,23.6,24.0,24.5,25.0,25.5,26.0,26.5,27.0,27.5,28.0,28.5,29.0,29.4,29.9,30.4,30.9,31.4,31.9,32.4,32.9,33.4,33.9,34.4,34.9,35.4,35.9,36.4,36.9,37.4,37.9,38.4,38.9,39.4,40.0,40.5,41.0,41.5,42.0,42.5,43.0,43.5,44.0,44.6,45.1,45.6,46.1,46.6,47.2,47.7,48.2,48.7,49.2,49.8,50.3,50.8,51.4,51.9,52.4,53.0,53.5,54.0,54.6,55.1,55.6,56.2,56.7,57.3,57.8,58.4,58.9,59.4,60.0,60.6,61.1,61.7,62.2,62.8,63.3,63.9,64.5,65.0,65.6,66.2,66.7,67.3,67.9,68.5,69.0,69.6,70.2,70.8,71.4,72.0,72.6,73.1,73.7,74.3,74.9,75.5,76.1,76.8,77.4,78.0,78.6,79.2,79.8,80.5,81.1,81.7,82.3,83.0,83.6,84.3,84.9,85.6,86.2,86.9,87.5,88.2,88.9,89.5,90.2,90.9,91.6,92.2,92.9,93.6,94.3,95.0,95.7,96.5,97.2,97.9,98.6,99.4,100.1,100.9,101.6,102.4,103.1,103.9,104.7,105.5,106.3,107.1,107.9,108.7,109.5,110.3,111.2,112.0,112.9,113.8,114.6,115.5,116.4,117.3,118.3,119.2,120.1,121.1,122.1,123.1,124.1,125.1,126.2,127.2,128.3,129.4,130.6,131.7,132.9,134.1,135.3,136.6,137.9,139.3,140.7,142.1,143.6,145.2,146.8,148.5,150.3,152.3,154.3,156.6,159.0,161.9,165.2,169.5,180.0 };



float getANgleSSS(float argArm, float argOpositEdge, float argthird) {
	
	float rads = acos(  ( (argArm* argArm)+(argthird* argthird)-(argOpositEdge* argOpositEdge)          )/  (argArm* argthird *2));
	
	return rads*(180/PI);
	}




void XYZ_inputConversion(int argT, int argD, int argH ) {
		float Zprime = GetZprime(argH, argT);
		float S0Angle = GetRawAngle(argT, Zprime);

		float z = GetZprime(argD, Zprime);
		float S1AnglePlus = GetRawAngle(argD, Zprime);
		float S1Angle = getANgleSSS(ARMLEN, CALFLEN, z);

		S1Angle = abs( S1AnglePlus - S1Angle);
		float S2Angle = 180 - getANgleSSS(CALFLEN, z, ARMLEN);

		//normalize 
		
		String pl = ";";
		Serial.println( S0Angle +pl+ S1Angle + pl + S2Angle );
	}

void testMyFuncs(String argDatas) {
	linecount_MegaSketch++;
	float A = 0;
	float B = 0;
	float C = 0;

	String subStr0 = getSubStringz(argDatas, ',', 0); //servo index
	String subStr1 = getSubStringz(argDatas, ',', 1); //what function to use : write , write angle , convertedd angle ...
	String subStr2 = getSubStringz(argDatas, ',', 2); // angle aorwhatever


	A = subStr0.toInt();
	B = subStr1.toInt();

	if (subStr2.equalsIgnoreCase("***")) {
			//Do pithagor  
		}
	else
		{    //do cos
		C = subStr2.toInt();
		}




	Serial.print(formatLineCountPrint(linecount_MegaSketch));  Serial.print("  |");
	Serial.print("trans= ");
	Serial.print(A);
	Serial.print("  ");
	Serial.print(" disp= ");
	Serial.print(B);
	Serial.print("  ");
	Serial.print("height ");
	Serial.print(C);
	Serial.println(" .");


	//use Disp and HEight to get Z'
	float Zprime = GetZprime(C, A);
	Serial.print("Z'= ");
	Serial.print(Zprime);
	Serial.print("  ");


	float S0Angle = GetRawAngle(A, Zprime);
	//Serial.print("S0Angle= ");
	//Serial.print(S0Angle);
	//Serial.print("  ");


	float z = GetZprime(B, Zprime);





	Serial.print("Z= ");
	Serial.print(z);
	Serial.println("  ");


	Serial.print("S0Angle= ");
	Serial.print(S0Angle);
	Serial.print("  ");

	float S1AnglePlus = GetRawAngle(B, Zprime);
	float S1Angle = getANgleSSS(ARMLEN, CALFLEN, z);
	S1Angle = S1AnglePlus- S1Angle;
	float S2Angle = getANgleSSS( CALFLEN, z,ARMLEN);


	Serial.print("S1Angle= ");
	Serial.print(S1Angle);
	Serial.print("  ");

	Serial.print("S2Angle= ");
	Serial.print(S2Angle);
	Serial.println("  ");

	//Sv20kgArra[0]->WriteNormalDegrees_convert_writeMilis(S0Angle);
	//Sv20kgArra[3]->WriteNormalDegrees_convert_writeMilis(S0Angle);
	//Sv20kgArra[6]->WriteNormalDegrees_convert_writeMilis(S0Angle);
	//Sv20kgArra[9]->WriteNormalDegrees_convert_writeMilis(S0Angle);

 //  

 //  Sv20kgArra[1]->WriteNormalDegrees_convert_writeMilis(S1Angle);
	//Sv20kgArra[4]->WriteNormalDegrees_convert_writeMilis(S1Angle);
	//Sv20kgArra[7]->WriteNormalDegrees_convert_writeMilis(S1Angle);
	//Sv20kgArra[10]->WriteNormalDegrees_convert_writeMilis(S1Angle);

	//Sv20kgArra[2]->WriteNormalDegrees_convert_writeMilis(S2Angle);
	//Sv20kgArra[5]->WriteNormalDegrees_convert_writeMilis(S2Angle);
	//Sv20kgArra[8]->WriteNormalDegrees_convert_writeMilis(S2Angle);
	//Sv20kgArra[11]->WriteNormalDegrees_convert_writeMilis(S2Angle);


	}
//
//double inline __declspec (naked) __fastcall sqrtt(double n) {
//	_asm fld qword ptr [esp+4]
//	_asm fsqrt
//	_asm ret 8
//	}

float sqrt88x(const float x)
	{
	union {
		int i;
		float x;
		} u;

	u.x = x;
	u.i = (1 << 29) + (u.i >> 1) - (1 << 22);
	return u.x;
	}

















//void UsePotinputsForLegKine() {
//	int inputX = map(pval10_LS_lR, 0, 1000, -12, 12);
//
//	int inputRevY= map(pval9_LS_dU, 0, 1000, 12, -12);
//	int inputY = map(pval9_LS_dU, 0, 1000, -12, 12);
//	int inputZ = map(pval11_RS_uD, 0, 1000, 6, 24);
//	
//
//	SetLeg(inputX, inputY, inputZ, inputRevY, 0, 1, 2);
//	SetLeg(inputX, inputY, inputZ, inputRevY ,3, 4, 5);
//	SetLeg(inputX, inputY, inputZ, inputRevY, 6, 7, 8);
//	SetLeg(inputX, inputY, inputZ, inputRevY,9, 10, 11);
//	}
//
//void SetLeg(int argT, int argD, int argH, int argRevPot, int argIndexshoulder, int argIndexarm, int argIndexcaf) {
//
//	if (argIndexarm != 10 && argIndexarm != 7) {
//			//use Disp and HEight to get Z'
//		float Zprime = GetZprime(argH, argT);
//		float S0Angle = GetRawAngle(argT, Zprime);
//
//		float z = GetZprime(argD, Zprime);
//		float S1AnglePlus = GetRawAngle(argD, Zprime);
//		float S1Angle = getANgleSSS(ARMLEN, CALFLEN, z);
//
//		S1Angle = S1AnglePlus - S1Angle;
//		float S2Angle = getANgleSSS(CALFLEN, z, ARMLEN);
//
//	//	Sv20kgArra[argIndexshoulder]->WriteNormalDegrees_convert_writeMilis(S0Angle);
//	//	Sv20kgArra[argIndexarm]->WriteNormalDegrees_convert_writeMilis(S1Angle);
//	//	Sv20kgArra[argIndexcaf]->WriteNormalDegrees_convert_writeMilis(S2Angle);
//		}
//
//	else
//		{
//
//			//use Disp and HEight to get Z'
//		float Zprime = GetZprime(argH, argT);
//		float S0Angle = GetRawAngle(argT, Zprime);
//
//		float z = GetZprime(argRevPot, Zprime);
//		float S1AnglePlus = GetRawAngle(argRevPot, Zprime);
//		float S1Angle = getANgleSSS(ARMLEN, CALFLEN, z);
//
//		S1Angle = S1AnglePlus - S1Angle;
//		float S2Angle = getANgleSSS(CALFLEN, z, ARMLEN);
//
//	//	Sv20kgArra[argIndexshoulder]->WriteNormalDegrees_convert_writeMilis(S0Angle);
//	//	Sv20kgArra[argIndexarm]->WriteNormalDegrees_convert_writeMilis(S1Angle);
//	//	Sv20kgArra[argIndexcaf]->WriteNormalDegrees_convert_writeMilis(S2Angle);
//		}
//
//	}



//
//void QuickAndDirtyLoad() {
//	int inputX = 0;
//	int inputRevY =0;
//	int inputY = 0;
//	int inputZ = 13;
//
//
//	SetupLegUS(inputX, inputY, inputZ, inputRevY, 0, 1, 2);
//	SetupLegUS(inputX, inputY, inputZ, inputRevY, 3, 4, 5);
//	SetupLegUS(inputX, inputY, inputZ, inputRevY, 6, 7, 8);
//	SetupLegUS(inputX, inputY, inputZ, inputRevY, 9, 10, 11);
//
//
//	 inputX = 0;
//	 inputRevY = -8;
//	 inputY = 8;
//	 inputZ = 13;
//
//
//
//	 SetupLegUS(inputX, inputY, inputZ, inputRevY, 0, 1, 2);
//	 SetupLegUS(inputX, inputY, inputZ, inputRevY, 3, 4, 5);
//	 SetupLegUS(inputX, inputY, inputZ, inputRevY, 6, 7, 8);
//	 SetupLegUS(inputX, inputY, inputZ, inputRevY, 9, 10, 11);
//
//
//
//	 inputX = 0;
//	 inputRevY = 0;
//	 inputY = 0;
//	 inputZ = 7;
//
//
//
//	 SetupLegUS(inputX, inputY, inputZ, inputRevY, 0, 1, 2);
//	 SetupLegUS(inputX, inputY, inputZ, inputRevY, 3, 4, 5);
//	 SetupLegUS(inputX, inputY, inputZ, inputRevY, 6, 7, 8);
//	 SetupLegUS(inputX, inputY, inputZ, inputRevY, 9, 10, 11);
//
//
//
//	 inputX = 0;
//	 inputRevY = 8;
//	 inputY = -8;
//	 inputZ = 7;
//
//
//
//	 SetupLegUS(inputX, inputY, inputZ, inputRevY, 0, 1, 2);
//	 SetupLegUS(inputX, inputY, inputZ, inputRevY, 3, 4, 5);
//	 SetupLegUS(inputX, inputY, inputZ, inputRevY, 6, 7, 8);
//	 SetupLegUS(inputX, inputY, inputZ, inputRevY, 9, 10, 11);
//
//
//
//	}
//void SetupLegUS(int argT, int argD, int argH, int argRevPot, int argIndexshoulder, int argIndexarm, int argIndexcaf) {
//
//	if (argIndexarm != 10 && argIndexarm != 7) {
//			//use Disp and HEight to get Z'
//		float Zprime = GetZprime(argH, argT);
//		float S0Angle = GetRawAngle(argT, Zprime);
//
//		float z = GetZprime(argD, Zprime);
//		float S1AnglePlus = GetRawAngle(argD, Zprime);
//		float S1Angle = getANgleSSS(ARMLEN, CALFLEN, z);
//
//		S1Angle = S1AnglePlus - S1Angle;
//		float S2Angle = getANgleSSS(CALFLEN, z, ARMLEN);
//
//		//Sv20kgArra[argIndexshoulder]->LoadStatesUs(S0Angle);
//		//Sv20kgArra[argIndexarm]->LoadStatesUs(S1Angle);
//		//Sv20kgArra[argIndexcaf]->LoadStatesUs(S2Angle);
//		}
//
//	else
//		{
//
//			//use Disp and HEight to get Z'
//		float Zprime = GetZprime(argH, argT);
//		float S0Angle = GetRawAngle(argT, Zprime);
//
//		float z = GetZprime(argRevPot, Zprime);
//		float S1AnglePlus = GetRawAngle(argRevPot, Zprime);
//		float S1Angle = getANgleSSS(ARMLEN, CALFLEN, z);
//
//		S1Angle = S1AnglePlus - S1Angle;
//		float S2Angle = getANgleSSS(CALFLEN, z, ARMLEN);
//
//	//	Sv20kgArra[argIndexshoulder]->LoadStatesUs(S0Angle);
//	//	Sv20kgArra[argIndexarm]->LoadStatesUs(S1Angle);
//	//	Sv20kgArra[argIndexcaf]->LoadStatesUs(S2Angle);
//		}
//
//	}
//

