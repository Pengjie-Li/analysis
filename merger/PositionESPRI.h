class PositionESPRI{
	private:
		TVector3 leftPedal;
		TVector3 leftBaseX;
		TVector3 leftBaseY;
		TVector3 rightPedal;
		TVector3 rightBaseX;
		TVector3 rightBaseY;
		double centerX;
		double centerY;

	public:
		PositionESPRI(){
			leftPedal.SetXYZ(-878.501926,-4.057746,-3715.121798);
			leftBaseX.SetXYZ(0.500011,0.000000,0.866019);
			leftBaseY.SetXYZ(-0.003464,0.999992,0.002000);
			rightPedal.SetXYZ(882.276111,0.000000,-3719.777658);
			rightBaseX.SetXYZ(0.494954,0.000000,-0.868919);
			rightBaseY.SetXYZ(0.000000,1.000000,-0.000000);
			centerX = 227.5;
			centerY = 227.5;
		}
		TVector3 getESPRIPosition(int lr,double X,double Y){
			X = X -centerX;
			Y = Y -centerY;
			TVector3 pedal;
			TVector3 baseX;
			TVector3 baseY;
			if(lr ==0 ){
				pedal = leftPedal;
				baseX = leftBaseX;
				baseY = leftBaseY;
			}
			else{
				pedal = rightPedal;
				baseX = rightBaseX;
				baseY = rightBaseY;
			}
			return (pedal + X*baseX + Y*baseY);
		}
		~PositionESPRI(){}
};
