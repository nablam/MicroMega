//void ReadPotpins() {
//
//// left JS<----------------------
//	pval8_LS_rot = analogRead(potpin8);//Rotationccw cw 7 -9-10-11 24
//	pval9_LS_dU = analogRead(potpin9); //downup  508+-4 amplitude 170
//	pval10_LS_lR = analogRead(potpin10);//rightleft  mid amplitude 170
//
//   //rightJS-------------------------------->
//	pval11_RS_uD = analogRead(potpin11);//   512 +-6 amplitude 172
//	pval12_RS_lR = analogRead(potpin12); //
//	pval13_RS_rot = analogRead(potpin13);//rot  7-->  14-15-16  --->27
//	}
//void Map01K_update_masterJS() {
//
//// left JS<----------------------
//	pval8_LS_rot = deadzonefilter(map(analogRead(potpin8), 0, 15, 0, PotReadScale), true);
//	pval9_LS_dU = deadzonefilter(map(analogRead(potpin9), 338, 678, 0, PotReadScale), false);
//	pval10_LS_lR = deadzonefilter(map(analogRead(potpin10), 336, 676, 0, PotReadScale), false);
//   //rightJS-------------------------------->
//	pval11_RS_uD = deadzonefilter(map(analogRead(potpin11), 330, 688, 0, PotReadScale), false);
//	pval12_RS_lR = deadzonefilter(map(analogRead(potpin12), 330, 680, 0, PotReadScale), false);
//	pval13_RS_rot = deadzonefilter(map(analogRead(potpin13), 2, 50, 0, PotReadScale), true);
////	Serial.println(pval11_RS_uD);
//
//	_masterjds.LS_rot = pval8_LS_rot;
//	_masterjds.LS_dU = pval9_LS_dU;
//	_masterjds.LS_lR = pval10_LS_lR;
//
//	_masterjds.RS_uD = pval11_RS_uD;
//	_masterjds.RS_lR = pval12_RS_lR;
//	_masterjds.RS_rot = pval13_RS_rot;
//
//	}
//
////{pval8_LS_rot} {pval9_LS_dU} {pval10_LS_lR} {pval11_RS_uD} {pval12_RS_lR} {pval13_RS_rot}
//
//int deadzonefilter(int argval, bool argisRot) {
//
//	if (argisRot) {
//		if ((argval > ((PotReadScale / 2) - (DeadZoneHalfAmplitude / 4))) && (argval < ((PotReadScale / 2) + (DeadZoneHalfAmplitude / 4))))
//			argval = (PotReadScale / 2);
//
//		if (argval < 0)argval = 0;
//		if (argval > PotReadScale)argval = PotReadScale;
//
//		}
//	else
//		{
//		if ((argval > ((PotReadScale / 2) - DeadZoneHalfAmplitude)) && (argval < ((PotReadScale / 2) + DeadZoneHalfAmplitude)))
//			argval = (PotReadScale / 2);
//
//		if (argval < 0)argval = 0;
//		if (argval > PotReadScale)argval = PotReadScale;
//		}
//
//
//	return argval;
//	}
//
//
