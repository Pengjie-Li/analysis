class PhiFunction{
	private:
		TVector3 yAxis;
	public:
		PhiFunction(){
			yAxis.SetXYZ(0,1,0);
		}
		~PhiFunction(){}
		double getPhi(TVector3 zAxis,TVector3 vT){
			TVector3 xAxis = yAxis.Cross(zAxis);	
			TVector3 vTP	= vT-(vT.Dot(zAxis))*zAxis;
			
			//zAxis.Print();
			//xAxis.Print();
			//vT.Print();
			if(vTP.Y()>=0) return vTP.Angle(xAxis)*TMath::RadToDeg();
			else return -vTP.Angle(xAxis)*TMath::RadToDeg();
		
		}

};

