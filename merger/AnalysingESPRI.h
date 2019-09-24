void Merger::analysingESPRI(){
	initAnalysedESPRI();
	//analysisESPRI->input(mergeESPRI);
	setESPRIEvent();

	espriEvent->loadData(mergeESPRI);
	espriEvent->analysing();
}
void Merger::initAnalysedESPRI(){
	/************* ESPRI *****************/
	espriNaiEnergy = NAN;
	espriPlasTime = NAN;
	espriPlasDeltaE = NAN;
	protonTheta = NAN;
	flightLengthTargetESPRI = NAN;
//	vESPRI->SetXYZ(0,0,0);
//	vProton->SetXYZ(0,0,0);
	vESPRI->SetXYZ(NAN,NAN,NAN);
	vProton->SetXYZ(NAN,NAN,NAN);

}
void Merger::setESPRIOutputBranch(){
	vESPRI = new TVector3;
	vProton = new TVector3;
	mergeESPRI->setOutputBranch(tree);
	tree->Branch("vESPRI","TVector3",&vESPRI);
	tree->Branch("vProton","TVector3",&vProton);

	tree->Branch("espriNaiEnergy",&espriNaiEnergy,"espriNaiEnergy/D");
	tree->Branch("espriPlasTime",&espriPlasTime,"espriPlasTime/D");
	tree->Branch("espriPlasDeltaE",&espriPlasDeltaE,"espriPlasDeltaE/D");
	tree->Branch("protonTheta",&protonTheta,"protonTheta/D");
	tree->Branch("flightLengthTargetESPRI",&flightLengthTargetESPRI,"flightLengthTargetESPRI/D");
}
void Merger::setESPRIEvent(){
	mergeESPRI->selfAnalysis();
	(*vESPRI) = getESPRIPosition();
	//setESPRITime();
	espriNaiEnergy = getESPRINaiEnergy();
	espriPlasTime = getESPRIPlasTime();
	espriPlasDeltaE = getESPRIPlasDeltaE();
	setProtonAngle();
}
void Merger::setProtonAngle(){
	(*vProton) = (*vESPRI)-(*vTarget);
	flightLengthTargetESPRI = (*vProton).Mag();
	//vBeam->Print();
	//vTarget->Print();
	//vProton->Print();
	protonTheta = vProton->Angle((*vBeam))*TMath::RadToDeg();
	//cout<<"FL Target ESPRI="<<flightLengthTargetESPRI<<":protonTheta="<<protonTheta<<endl;
}
TVector3 Merger::getESPRIPosition(){
	return mergeESPRI->getESPRIPosition();
}
double Merger::getESPRINaiEnergy(){
	return mergeESPRI->getESPRINaiEnergy();
}
double Merger::getESPRIPlasTime(){
	return mergeESPRI->getESPRIPlasTime();
}
double Merger::getESPRIPlasDeltaE(){
	return mergeESPRI->getESPRIPlasDeltaE();
}
