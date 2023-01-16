{

	//TString Frame="(Target_X+2.13)<30&&(Target_X+2.13)>-30&&(Target_Y+1.1)<25&&(Target_Y+1.1)>-35";
	//TString Neck="((Target_X+2.13)<4&&(Target_X+2.13)>-4&&(Target_Y+1.6)>15&&(Target_Y+1.6)<25)";
	//TString R4="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<20";
	//TString R3="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<21";
	//TString R2="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<13";
	//TString R1="sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<15";

	//TString peak2="!("+R1+")&&"+R3+"&&!("+Neck+")";
	//TString peak5=R2;
	//TString peak1=Frame+"&&!("+R4+")&&!("+Neck+")";
	//TString targetArea="sqrt((Target_X+2.0)*(Target_X+2.0)+(Target_Y+1.1)*(Target_Y+1.1))<13";
	//TString smallTargetArea="sqrt((Target_X+2.0)*(Target_X+2.0)+(Target_Y+1.1)*(Target_Y+1.1))<10";
	TString targetArea="sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<13";
	//TString targetArea="sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<1";

        TString Frame="((targetPosition.X()-2.0)<30&&(targetPosition.X()-2.0)>-30&&(targetPosition.Y()+1.1)<25&&(targetPosition.Y()+1.1)>-35)";
        TString Neck="((targetPosition.X()-2.0)<4&&(targetPosition.X()-2.0)>-4&&(targetPosition.Y()+1.1)>15&&(targetPosition.Y()+1.1)<25)";

        TString R5="(sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<14)";
        TString R4="(sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<17)";
        TString R3="(sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<20)";
        TString R2="(sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<21)";
        TString R1="(sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<15)";

        TString peak[5];
         TString peak3_1="(!"+R5+"&&"+R4+"&&!"+Neck+")";
         TString peak3_2="("+Neck+"&&!"+R2+")";

         peak[0]=targetArea;
         peak[1]="("+Neck+"&&"+R2+")";
         peak[2]="("+peak3_1+"||"+peak3_2+")";
         peak[3]="(!"+R1+"&&"+R2+"&&!"+Neck+")";
         peak[4]="("+Frame+"&&!"+R3+"&&!"+Neck+")";

}
