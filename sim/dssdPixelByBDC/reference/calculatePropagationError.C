void calculatePropagationError(){
// 1. Input sigma of BDC1, BDC2, FDC0
// 2. Function of response equation 
// 3. Output result

	double sigmaBDC1 = 0.113;
	double sigmaBDC2 = 0.113;
	double sigmaFDC0 = 0.117;
	double C0 = 999.44/3281.41 ;
	double sigma_dBDC2MinusBDC2 = sqrt((1-C0)*(1-C0)*sigmaBDC1*sigmaBDC1 + C0*C0*sigmaFDC0*sigmaFDC0 + sigmaBDC2*sigmaBDC2);
	cout<< " Propagation of Error with sigmaBDC1 = "<<sigmaBDC1<<" sigmaBDC2 = "<< sigmaBDC2<<" sigmaFDC0 = "<<sigmaFDC0<<endl;
	cout<< " Sigma of dBDC2 - BDC2 = "<<sigma_dBDC2MinusBDC2<<endl;
}
