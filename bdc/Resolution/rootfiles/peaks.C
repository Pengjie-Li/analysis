{
TString R1="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<15";
TString peak5=R1;

TString Neck="((Target_X+2.13)<4&&(Target_X+2.13)>-4&&(Target_Y+1.6)>15&&(Target_Y+1.6)<25)";
TString R3="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<21";
TString peak4=Neck+"&&"+R3;

TString R5="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<17";
TString R6="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<14";
TString peak3_1="!("+R6+")&&"+R5+"&&!("+Neck+")";

TString peak3_2=Neck+"&&!("+R3+")";

TString peak2="!("+R1+")&&"+R3+"&&!("+Neck+")";

TString R4="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<20";
TString Frame="(Target_X+2.13)<30&&(Target_X+2.13)>-30&&(Target_Y+1.6)<25&&(Target_Y+1.6)>-35";
TString peak1=Frame+"&&!("+R4+")&&!("+Neck+")";

}
