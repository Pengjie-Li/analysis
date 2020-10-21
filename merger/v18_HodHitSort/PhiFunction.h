class PhiFunction{
	private:
	public:
		PhiFunction(){
		}
		~PhiFunction(){}
		double getPhi(TVector3 zAxis,TVector3 vT){
			TVector3 yAxis;
			//yAxis.SetXYZ(TMath::Sqrt(2)/2,TMath::Sqrt(2)/2,0);
			yAxis.SetXYZ(0,1,0);
			TVector3 xAxis = yAxis.Cross(zAxis);	
			xAxis = xAxis.Unit();
			yAxis = zAxis.Cross(xAxis);
			
			TVector3 vTP	= vT-(vT.Dot(zAxis))*zAxis;
			
			//zAxis.Print();
			//xAxis.Print();
			//vT.Print();
			if(vTP.Dot(yAxis)>=0) return vTP.Angle(xAxis)*TMath::RadToDeg();
			else return (360-vTP.Angle(xAxis)*TMath::RadToDeg());
		
		}

};

