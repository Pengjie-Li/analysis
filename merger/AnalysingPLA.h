void Merger::analysingPLA(){

	initAnalysedPLA();
	if(getF13Time()!=-9999&&getF7Time()!=-9999){
		TOF713=getF13Time() - getF7Time() + 570.619; // ns //20181025
		Beta713=Dist_F7F13/TOF713/C_light;
		Gamma713=1/sqrt(1-Beta713*Beta713);
		Ek713=(Gamma713-1)*AMU;
	}

	if(getF3Time()!=-9999&&getF7Time()!=-9999){
		TOF37=getF7Time() - getF3Time() + 299.091; // ns
		Beta37=Dist_F3F7/TOF37/C_light;
		Gamma37=1/sqrt(1-Beta37*Beta37);
		Ek37=(Gamma37-1)*AMU;
	}
}
void Merger::initAnalysedPLA(){
	/****** Plastics **********/
		TOF713=NAN;
		Beta713=NAN;
		Gamma713=NAN;
		Ek713=NAN;

		TOF37=NAN;
		Beta37=NAN;
		Gamma37=NAN;
		Ek37=NAN;
}
void Merger::setPLAOutputBranch(){

	//raw and cal
	mergePLA->setOutputBranch(tree);
	// analysed 
	tree->Branch("TOF37",&TOF37,"TOF37/D");
	tree->Branch("Beta37",&Beta37,"Beta37/D");
	tree->Branch("Gamma37",&Gamma37,"Gamma37/D");
	tree->Branch("Ek37",&Ek37,"Ek37/D");

	tree->Branch("TOF713",&TOF713,"TOF713/D");
	tree->Branch("Beta713",&Beta713,"Beta713/D");
	tree->Branch("Gamma713",&Gamma713,"Gamma713/D");
	tree->Branch("Ek713",&Ek713,"Ek713/D");
}
Double_t Merger::getF3Time(){
	return mergePLA->getF3Time();
}
Double_t Merger::getF7Time(){
	return mergePLA->getF7Time();
}
Double_t Merger::getF13Time(){
	return mergePLA->getF13Time();
}
