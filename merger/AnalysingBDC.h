void Merger::analysingBDC(){

		initAnalysedBDC();

		Target_X = getBDC1X() + Dist_BDC1Target / Dist_BDC1BDC2 * (getBDC2X() - getBDC1X());
		Target_Y = getBDC1Y() + Dist_BDC1Target / Dist_BDC1BDC2 * (getBDC2Y() - getBDC1Y());
		Target_ThetaX = TMath::ATan( (getBDC2X() - getBDC1X()) / Dist_BDC1BDC2 );
		Target_ThetaY = TMath::ATan( (getBDC2Y() - getBDC1Y()) / Dist_BDC1BDC2 );

		vBDC1->SetXYZ(-getBDC1X(),getBDC1Y(),getBDC1Z());
		vBDC2->SetXYZ(-getBDC2X(),getBDC2Y(),getBDC2Z());

		(*vBeam)=(*vBDC2)-(*vBDC1);
		(*vBeam)=(*vBeam).Unit();
		(*vTarget) =(*vBDC1) + getBDC1TargetRatio()*(*vBeam);
		(*vSBT) =(*vBDC1) + getBDC1SBTRatio()*(*vBeam);
		flightLengthBeamTarget =((*vTarget)-(*vSBT)).Mag();
		//cout<<"FL Beam Target:"<<flightLengthBeamTarget<<endl;
		//vBDC1->Print();
		//vSBT->Print();
}
void Merger::initAnalysedBDC(){

		/********* BDC ***************/
		Target_X = NAN;
		Target_Y = NAN;
		Target_ThetaX = NAN;
		Target_ThetaY = NAN;
		flightLengthBeamTarget = NAN;
		
		vBDC1->SetXYZ(NAN,NAN,NAN);
		vBDC2->SetXYZ(NAN,NAN,NAN);
		vTarget->SetXYZ(NAN,NAN,NAN);
		vSBT->SetXYZ(NAN,NAN,NAN);
		vBeam->SetXYZ(NAN,NAN,NAN);

}

void Merger::setBDCOutputBranch(){

	vBeam = new TVector3;
	vTarget = new TVector3;
	vSBT = new TVector3;
	vBDC1 = new TVector3;
	vBDC2 = new TVector3;


	//raw and cal
	mergeBDC->setOutputBranch(tree);

	tree->Branch("flightLengthBeamTarget",&flightLengthBeamTarget);
	tree->Branch("Target_X",&Target_X);
	tree->Branch("Target_Y",&Target_Y);
	tree->Branch("Target_ThetaX",&Target_ThetaX);
	tree->Branch("Target_ThetaY",&Target_ThetaY);

	tree->Branch("vBeam","TVector3",&vBeam);
	tree->Branch("vBDC1","TVector3",&vBDC1);
	tree->Branch("vBDC2","TVector3",&vBDC2);
	tree->Branch("vTarget","TVector3",&vTarget);
	tree->Branch("vSBT","TVector3",&vSBT);
}
Double_t Merger::getBDC1TargetRatio(){
	return (Target_Z-(*vBDC1).Z())/(*vBeam).Z();
}
Double_t Merger::getBDC1SBTRatio(){
	return (SBT_Z-(*vBDC1).Z())/(*vBeam).Z();
}
Double_t Merger::getBDC1X(){
	return mergeBDC->getBDC1X();
}
Double_t Merger::getBDC1Y(){
	return mergeBDC->getBDC1Y();
}
Double_t Merger::getBDC1Z(){
	return BDC1_Z;
}
Double_t Merger::getBDC2X(){
	return mergeBDC->getBDC2X();
}
Double_t Merger::getBDC2Y(){
	return mergeBDC->getBDC2Y();
}
Double_t Merger::getBDC2Z(){
	return BDC2_Z; 
}
