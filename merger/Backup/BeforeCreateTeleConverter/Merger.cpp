#include "Merger.h"
#include "constant.h"

Merger::Merger(int runNumber):runNumber(runNumber){
	env = new TEnv("configMerger.prm");
	maxEventNumber = env->GetValue("maxEventNumber",5000);
	inputTree = new TTree("tree","tree");
	if(kMAIN) mergeMAIN =new MergeMAIN(runNumber);
	if(kPLA) mergePLA =new MergePLA(runNumber);
	if(kBDC) mergeBDC =new MergeBDC(runNumber);
	if(kFDC0) mergeFDC0 =new MergeFDC0(runNumber);
//	if(kFDC2) mergeFDC2 =new MergeFDC2(runNumber);
	if(kTELE) mergeTELE =new MergeTELE(runNumber);
	if(kHOD) mergeHOD =new MergeHOD(runNumber);
}

void Merger::eventLoop(){
	nentries = mergeMAIN->inputTree->GetEntries();
	nentries = (nentries > maxEventNumber)?maxEventNumber:nentries;
	cout << "NUMBER OF EVENTS = " << nentries << endl;
	for(Long64_t ientry = 0; ientry<nentries;ientry++){
		//cout<<ientry<<endl;
		//inputTree->GetEntry(ientry);
		if(kMAIN){
			mergeMAIN->init();
			mergeMAIN->getEntry(ientry);
		}

		if(kPLA){
			mergePLA->init();
			mergePLA->getEntry(ientry);
		}
		if(kBDC){
			mergeBDC->init();
			mergeBDC->getEntry(ientry);
		}

		if(kFDC0){
			mergeFDC0->init();
			mergeFDC0->getEntry(ientry);
		}

		if(kTELE){
			mergeTELE->init();
			mergeTELE->getEntry(ientry);
		}
		if(kHOD){
			mergeHOD->init();
			mergeHOD->getEntry(ientry);
		}

		initAnalysedOutput();

		analysingMAIN();
		analysingPLA();
		analysingBDC();
		analysingFDC0();
		analysingTELE();
		analysingHOD();
		
		tree->Fill();
	}
}

void Merger::initAnalysedOutput(){

	/********* Main Trig *********/
		Trig_DSB=-1;
		Trig_BxESPRIxTEL=-1;
		Trig_BxESPRI=-1;
		Trig_BxTEL=-1;
		Trig_BxHODP=-1;
		Trig_BxHODF=-1;
		Trig_BxNEBULA=-1;


	/****** Plastics **********/
		TOF713=NAN;
		Beta713=NAN;
		Gamma713=NAN;
		Ek713=NAN;

		TOF37=NAN;
		Beta37=NAN;
		Gamma37=NAN;
		Ek37=NAN;

		/********* BDC ***************/
		Target_X = NAN;
		Target_Y = NAN;
		Target_ThetaX = NAN;
		Target_ThetaY = NAN;

		/********** TELE ************/


		for(int i = 0;i< 32;i++){
			SiLF_ADC[i] = NAN;
			SiLF_SCM[i] = NAN;
			SiLF_CAL[i] = NAN;

			SiLB_ADC[i] = NAN;
			SiLB_SCM[i] = NAN;
			SiLB_CAL[i] = NAN;

			SiRF_ADC[i] = NAN;
			SiRF_SCM[i] = NAN;
			SiRF_CAL[i] = NAN;

			SiRB_ADC[i] = NAN;
			SiRB_SCM[i] = NAN;
			SiRB_CAL[i] = NAN;
	
	
		}

		CsILL_CAL =NAN;
		CsILRT_CAL=NAN;
		CsILRB_CAL=NAN;
		NAN;
		CsIRLT_CAL=NAN;
		CsIRLB_CAL=NAN;
		CsIRRT_CAL=NAN;
		CsIRRB_CAL=NAN;
		
}
void Merger::analysingPLA(){

	TOF713=getF13Time() - getF7Time() + 570.619; // ns //20181025
	Beta713=Dist_F7F13/TOF713/C_light;
	Gamma713=1/sqrt(1-Beta713*Beta713);
	Ek713=(Gamma713-1)*AMU;

	TOF37=getF7Time() - getF3Time() + 299.091; // ns
	Beta37=Dist_F3F7/TOF37/C_light;
	Gamma37=1/sqrt(1-Beta37*Beta37);
	Ek37=(Gamma37-1)*AMU;
}
void Merger::analysingBDC(){

		Target_X = getBDC1X() + Dist_BDC1Target / Dist_BDC1BDC2 * (getBDC2X() - getBDC1X());
		Target_Y = getBDC1Y() + Dist_BDC1Target / Dist_BDC1BDC2 * (getBDC2Y() - getBDC1Y());
		Target_ThetaX = TMath::ATan( (getBDC2X() - getBDC1X()) / Dist_BDC1BDC2 );
		Target_ThetaY = TMath::ATan( (getBDC2Y() - getBDC1Y()) / Dist_BDC1BDC2 );

		vBeam = new TVector3;
		vBDC1 = new TVector3;
		vBDC2 = new TVector3;

		vBDC1->SetXYZ(getBDC1X(),getBDC1Y(),getBDC1Z());
		vBDC2->SetXYZ(getBDC2X(),getBDC2Y(),getBDC2Z());

		(*vBeam)=(*vBDC2)-(*vBDC1);
		(*vBeam)=(*vBeam).Unit();
		(*vTarget) =(*vBDC1) + getBDC1TargetRatio()*(*vBeam);
}
void Merger::analysingMAIN(){

		Trig_DSB          = getCoincidenceTrigger() & 1;
		Trig_BxESPRIxTEL  = getCoincidenceTrigger() & 2;
		Trig_BxESPRI      = getCoincidenceTrigger() & 4;
		Trig_BxTEL        = getCoincidenceTrigger() & 8;
		Trig_BxHODP       = getCoincidenceTrigger() & 16;
		Trig_BxHODF       = getCoincidenceTrigger() & 32;
		Trig_BxNEBULA     = getCoincidenceTrigger() & 64;
	
}

void Merger::analysingFDC0(){
}
void Merger::analysingTELE(){

	calibrateSilicon();
	getMultiplicity();
	if(maxEventNumber <100) printSilicon();

	calibrateCsI();
	if(maxEventNumber <100) printCsI();
}
void Merger::calibrateCsI(){

		CsILL_CAL =0.464291*getCsILLRawADC()-150.243;
		CsILRT_CAL=0.306815*getCsILRTRawADC()-101.453;
		CsILRB_CAL=0.353228*getCsILRBRawADC()-117.866;

		CsIRLT_CAL=0.357925*getCsIRLTRawADC()-139.651;
		CsIRLB_CAL=0.40584 *getCsIRLBRawADC()-137.378;
		CsIRRT_CAL=0.350254*getCsIRRTRawADC()-105.061;
		CsIRRB_CAL=0.350748*getCsIRRBRawADC()-108.566;
}
Double_t Merger::getCsILLRawADC(){
	return mergeTELE->getCsILLRawADC();
}
Double_t Merger::getCsILRTRawADC(){
	return mergeTELE->getCsILRTRawADC();
}
Double_t Merger::getCsILRBRawADC(){
	return mergeTELE->getCsILRBRawADC();
}
Double_t Merger::getCsIRLTRawADC(){
	return mergeTELE->getCsIRLTRawADC();
}
Double_t Merger::getCsIRLBRawADC(){
	return mergeTELE->getCsIRLBRawADC();
}
Double_t Merger::getCsIRRTRawADC(){
	return mergeTELE->getCsIRRTRawADC();
}
Double_t Merger::getCsIRRBRawADC(){
	return mergeTELE->getCsIRRBRawADC();
}
void Merger::printCsI(){
	cout<<" CsI: Raw Cal"<<endl;
	cout<<"LL Raw = "<<getCsILLRawADC()<<" Cal ="<<CsILL_CAL<<endl;
	cout<<"LRT Raw = "<<getCsILRTRawADC()<<" Cal ="<<CsILRT_CAL<<endl;
	cout<<"LRB Raw = "<<getCsILRBRawADC()<<" Cal ="<<CsILRB_CAL<<endl;
	cout<<"RLT Raw = "<<getCsIRLTRawADC()<<" Cal ="<<CsIRLT_CAL<<endl;
	cout<<"RLB Raw = "<<getCsIRLBRawADC()<<" Cal ="<<CsIRLB_CAL<<endl;
	cout<<"RRT Raw = "<<getCsIRRTRawADC()<<" Cal ="<<CsIRRT_CAL<<endl;
	cout<<"RRB Raw = "<<getCsIRRBRawADC()<<" Cal ="<<CsIRRB_CAL<<endl;
}
void Merger::printSilicon(){
	for(int i =0; i<32;i++){
		cout<<"SiLF: i = "<<i<<" ADC = "<<SiLF_ADC[i]<<" SCM = "<<SiLF_SCM[i]<<" CAL = "<<SiLF_CAL[i]<<endl;
		cout<<"SiLB: i = "<<i<<" ADC = "<<SiLB_ADC[i]<<" SCM = "<<SiLB_SCM[i]<<" CAL = "<<SiLB_CAL[i]<<endl;
		cout<<"SiRF: i = "<<i<<" ADC = "<<SiRF_ADC[i]<<" SCM = "<<SiRF_SCM[i]<<" CAL = "<<SiRF_CAL[i]<<endl;
		cout<<"SiRB: i = "<<i<<" ADC = "<<SiRB_ADC[i]<<" SCM = "<<SiRB_SCM[i]<<" CAL = "<<SiRB_CAL[i]<<endl;

	}
}
void Merger::calibrateSilicon(){
	//side = 0 LF, 1 LB, 2 RF, 3 RB
	for(int side = 0;side<4;side++)
		for(int id=0;id<32;id++)
		{
			calibrateSiliconStrip(side,id);
		}
}
void Merger::calibrateSiliconStrip(int side,int id){

	// raw->SCM->cal
	double raw = getSiliconRawADC(side,id);
	double scm = getSiliconScmSlope(side,id)*raw + getSiliconScmOffset(side,id);
	double cal = getSiliconCalSlope(side)*scm + getSiliconCalOffset(side);
	
	// Some ADC Saturation events
	if(raw>4096){
		raw = -9999;
		scm = -9999;
		cal = -9999;
	}

	setCalibratedSiliconStrip(side,id,raw,scm,cal);
}
double Merger::getSiliconRawADC(int side, int id){
	return mergeTELE->getSiliconRawADC(side,id);
}
double Merger::getSiliconScmSlope(int side, int id){
	return kScmSlope[side][id];
}
double Merger::getSiliconScmOffset(int side, int id){
	return bScmOffset[side][id];
}
double Merger::getSiliconCalSlope(int side){
	return kCalSlope[side/2];
}
double Merger::getSiliconCalOffset(int side){
	return bCalOffset[side/2];
}
void Merger::setCalibratedSiliconStrip(int side,int id,double raw,double scm,double cal){
	
	switch(side){
		case 0: 
			SiLF_ADC[id] = raw;
			SiLF_SCM[id] = scm;
			SiLF_CAL[id] = cal;
			break;
		case 1:
			SiLB_ADC[id] = raw;
			SiLB_SCM[id] = scm;
			SiLB_CAL[id] = cal;
			break;
		case 2: 
			SiRF_ADC[id] = raw;
			SiRF_SCM[id] = scm;
			SiRF_CAL[id] = cal;
			break;
		case 3:
			SiRB_ADC[id] = raw;
			SiRB_SCM[id] = scm;
			SiRB_CAL[id] = cal;
			break;
		default: cout<<"Error! Side of Silicons not exists"<<endl;

	}
}
void Merger::getMultiplicity(){

	multiplicityLF = getMultiplicity(SiLF_CAL);	
	multiplicityLB = getMultiplicity(SiLB_CAL);	

	multiplicityRF = getMultiplicity(SiRF_CAL);	
	multiplicityRB = getMultiplicity(SiRB_CAL);	
	

	if(maxEventNumber <100) printMultiplicity();	

}
void Merger::printMultiplicity(){
	cout<<"Multiplicity: LF= "<<multiplicityLF<<" LB= "<<multiplicityLB<<" RF= "<<multiplicityRF<<" RB= "<<multiplicityRB<<endl;
}
Int_t Merger::getMultiplicity(Double_t *array){
	int nHit = 0;
	for(int i = 0;i<32;i++){
		if(array[i]>siliconHitThreshold) nHit++; 
	}
	return nHit;
}
void Merger::analysingHOD(){
}
Int_t Merger::getCoincidenceTrigger(){
	return mergeMAIN->getCoincidenceTrigger();
}
Double_t Merger::getBDC1TargetRatio(){
	return (Target_Z-(*vBDC1).Z())/(*vBeam).Z();
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

Double_t Merger::getF3Time(){
	return mergePLA->getF3Time();
}
Double_t Merger::getF7Time(){
	return mergePLA->getF7Time();
}
Double_t Merger::getF13Time(){
	return mergePLA->getF13Time();
}

void Merger::createOutput(){

	outputFile = new TFile(Form("./rootfiles/run%04d_analysed.root",runNumber), "recreate"); 
	tree = new TTree("tree","Analysed Tree:raw,cal,analysed");
	setOutputBranch();
}
void Merger::saveOutput(){
	tree->Write();
	outputFile->Close();
}

void Merger::addFriend(){
	if(kPLA){
		inputTree->AddFriend(mergePLA->inputTree);
		//mergePLA->inputTree->Print();
	}
}

void Merger::setBranch(){
	if(kMAIN) mergeMAIN->setBranch();
	if(kPLA) mergePLA->setBranch();
	if(kBDC) mergeBDC->setBranch();
	if(kFDC0) mergeFDC0->setBranch();
	if(kTELE) mergeTELE->setBranch();
	if(kHOD) mergeHOD->setBranch();
}
void Merger::loadInputFiles(){
	if(kMAIN) mergeMAIN->loadInputFiles();
	if(kPLA) mergePLA->loadInputFiles();
	if(kBDC) mergeBDC->loadInputFiles();
	if(kFDC0) mergeFDC0->loadInputFiles();
	if(kTELE) mergeTELE->loadInputFiles();
	if(kHOD) mergeHOD->loadInputFiles();
}
void Merger::loadSiliconCalibrationParameters(){

	siliconHitThreshold = env->GetValue("siliconHitThreshold",500);
        // Silicon
	loadSiliconCalibrationParameters(kScmSlope,bScmOffset,ekScmSlope,ebScmOffset);
	kCalSlope[0] = 7.17797775;
	bCalOffset[0] = -1524.240925;

	kCalSlope[1] = 7.685283145;
	bCalOffset[1] = -1646.273395;

}
void Merger::checkTotalEventNumber(){
	printTotalEventNumber();
}
void Merger::printTotalEventNumber(){
	if(kMAIN)	 mergeMAIN->printTotalEventNumber();
	if(kPLA)	 mergePLA->printTotalEventNumber();
	if(kBDC)	 mergeBDC->printTotalEventNumber();
	if(kFDC0)	 mergeFDC0->printTotalEventNumber();
	if(kTELE)	 mergeTELE->printTotalEventNumber();
	if(kHOD)	 mergeHOD->printTotalEventNumber();
}

bool Merger::isFilesExist(){
	return mergeMAIN->isFileExists()&&mergePLA->isFileExists()&&mergeBDC->isFileExists()&&mergeFDC0->isFileExists()&&mergeTELE->isFileExists()&&mergeHOD->isFileExists();
	//return mergePLA->isFileExists()&&isFileExists("BDC")&&isFileExists("FDC")&&isFileExists("TELE");
}
void Merger::setOutputBranch(){
	if(kMAIN) setMAINOutputBranch();
	if(kPLA) setPLAOutputBranch();
	if(kBDC) setBDCOutputBranch();
	if(kFDC0) setFDC0OutputBranch();
	if(kTELE) setTELEOutputBranch();
	if(kHOD) setHODOutputBranch();
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
void Merger::setBDCOutputBranch(){

	//raw and cal
	mergeBDC->setOutputBranch(tree);

	tree->Branch("Target_X",&Target_X);
	tree->Branch("Target_Y",&Target_Y);
	tree->Branch("Target_ThetaX",&Target_ThetaX);
	tree->Branch("Target_ThetaY",&Target_ThetaY);

	tree->Branch("vBeam","TVector3",&vBeam);
	tree->Branch("vBDC1","TVector3",&vBDC1);
	tree->Branch("vBDC2","TVector3",&vBDC2);
	tree->Branch("vTarget","TVector3",&vTarget);
}
void Merger::setMAINOutputBranch(){
	//raw and cal
	mergeMAIN->setOutputBranch(tree);

	tree->Branch("Trig_DSB"        ,&Trig_DSB        );
	tree->Branch("Trig_BxESPRIxTEL",&Trig_BxESPRIxTEL);
	tree->Branch("Trig_BxESPRI"    ,&Trig_BxESPRI    );
	tree->Branch("Trig_BxTEL"      ,&Trig_BxTEL      );
	tree->Branch("Trig_BxHODP"     ,&Trig_BxHODP     );
	tree->Branch("Trig_BxHODF"     ,&Trig_BxHODF     );
	tree->Branch("Trig_BxNEBULA"   ,&Trig_BxNEBULA   );
}
void Merger::setFDC0OutputBranch(){
	mergeFDC0->setOutputBranch(tree);
}
void Merger::setTELEOutputBranch(){
	mergeTELE->setOutputBranch(tree);

	tree->Branch("multiplicityLF",&multiplicityLF);
	tree->Branch("multiplicityLB",&multiplicityLB);
	tree->Branch("multiplicityRF",&multiplicityRF);
	tree->Branch("multiplicityRB",&multiplicityRB);

	tree->Branch("SiLF_ADC",&SiLF_ADC,"SiLF_ADC[32]/D");
	tree->Branch("SiLB_ADC",&SiLB_ADC,"SiLB_ADC[32]/D");
	tree->Branch("SiRF_ADC",&SiRF_ADC,"SiRF_ADC[32]/D");
	tree->Branch("SiRB_ADC",&SiRB_ADC,"SiRB_ADC[32]/D");

	tree->Branch("SiLF_SCM",&SiLF_SCM,"SiLF_SCM[32]/D");
	tree->Branch("SiLB_SCM",&SiLB_SCM,"SiLB_SCM[32]/D");
	tree->Branch("SiRF_SCM",&SiRF_SCM,"SiRF_SCM[32]/D");
	tree->Branch("SiRB_SCM",&SiRB_SCM,"SiRB_SCM[32]/D");

	tree->Branch("SiLF_CAL",&SiLF_CAL,"SiLF_CAL[32]/D");
	tree->Branch("SiLB_CAL",&SiLB_CAL,"SiLB_CAL[32]/D");
	tree->Branch("SiRF_CAL",&SiRF_CAL,"SiRF_CAL[32]/D");
	tree->Branch("SiRB_CAL",&SiRB_CAL,"SiRB_CAL[32]/D");

	tree->Branch("CsILL_CAL",&CsILL_CAL,"CsILL_CAL/D");
	tree->Branch("CsILRT_CAL",&CsILRT_CAL,"CsILRT_CAL/D");
	tree->Branch("CsILRB_CAL",&CsILRB_CAL,"CsILRB_CAL/D");

	tree->Branch("CsIRLT_CAL",&CsIRLT_CAL,"CsIRLT_CAL/D");
	tree->Branch("CsIRLB_CAL",&CsIRLB_CAL,"CsIRLB_CAL/D");
	tree->Branch("CsIRRT_CAL",&CsIRRT_CAL,"CsIRRT_CAL/D");
	tree->Branch("CsIRRB_CAL",&CsIRRB_CAL,"CsIRRB_CAL/D");

}
void Merger::setHODOutputBranch(){
	mergeHOD->setOutputBranch(tree);
}

void Merger::loadSiliconCalibrationParameters(double k[4][32],double b[4][32],double ek[4][32],double eb[4][32]){
	ifstream in;
	TString par_name;

	par_name="/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/scm/Remove/DSSD_Fit_Whole.txt";

	in.open(par_name);
	//      if(!in.open(par_name))
	//      {
	//              cout<<"Error: parameter file didn't open"<<endl;
	//              cout<<par_name<<endl;
	//      }
	int side;
	int strip;
	double  k0;
	double  b0;
	double ek0;
	double eb0;
	while (1)
	{
		in >>side>>strip>>k0>>b0>>ek0>>eb0;
		//cout<<side<< "  "<<strip<<endl;
		if (!in.good()) break;


		k[side][strip]=k0;
		ek[side][strip]=ek0;

		b[side][strip]=b0;
		eb[side][strip]=eb0;

	}
}

