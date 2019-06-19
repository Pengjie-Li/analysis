{

	TString Frame="(Target_X+2.13)<30&&(Target_X+2.13)>-30&&(Target_Y+1.1)<25&&(Target_Y+1.1)>-35";
	TString Neck="((Target_X+2.13)<4&&(Target_X+2.13)>-4&&(Target_Y+1.6)>15&&(Target_Y+1.6)<25)";
	TString R4="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<20";
	TString R3="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<21";
	TString R2="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<13";
	TString R1="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<15";

	TString peak2="!("+R1+")&&"+R3+"&&!("+Neck+")";
	TString peak5=R2;
	TString peak1=Frame+"&&!("+R4+")&&!("+Neck+")";

}
