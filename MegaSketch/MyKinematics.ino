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

int GetRawAngle(int argOposit, int argAdjascent ) {
	int rads= atan(argOposit / argAdjascent);
	return rads* (180/ PI);
	}

int GetZprime(int arhHeight, int argTransverse) {
	return sqrt((arhHeight * arhHeight) + (argTransverse * argTransverse));
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
*   Find angle C  adjust for  FR[1] 
*   Find angle Z  adjust for  FR[2]
* 
* */


int getANgleSSS(int argArm, int argOpositEdge, int argthird) {
	
	int rads = acos(  ( (argArm* argArm)+(argthird* argthird)-(argOpositEdge* argOpositEdge)          )/  (argArm* argthird *2));
	
	return rads*(180/PI);
	}

