#include "Merger.h"
#include "constant.h"
#include "AnalysingMAIN.h"
#include "AnalysingPLA.h"
#include "AnalysingBDC.h"
#include "AnalysingFDC0.h"
#include "AnalysingTELE.h"
#include "AnalysingHOD.h"
#include "AnalysingESPRI.h"


Merger::Merger(int runNumber,int maxEventNumber):runNumber(runNumber),maxEventNumber(maxEventNumber){
	env = new TEnv("configMerger.prm");
	//maxEventNumber = env->GetValue("maxEventNumber",5000);
	inputTree = new TTree("tree","tree");
	if(kMAIN) mergeMAIN =new MergeMAIN(runNumber);
	if(kPLA){
		mergePLA =new MergePLA(runNumber);
		plaEvent = new PlaEvent();
	}
	if(kBDC) {
		mergeBDC =new MergeBDC(runNumber);
		bdcEvent = new BdcEvent();
	}
	if(kFDC0){
		mergeFDC0 =new MergeFDC0(runNumber);
		fdc0Event = new Fdc0Event();
	}
//	if(kFDC2) mergeFDC2 =new MergeFDC2(runNumber);
	if(kHOD) mergeHOD =new MergeHOD(runNumber);
	if(kTELE) {
		mergeTELE =new MergeTELE(runNumber);
		teleEvent = new TeleEvent();
	}
	if(kESPRI) { 
		mergeESPRI =new MergeESPRI(runNumber);
		espriEvent = new EspriEvent();
	}
}
void Merger::eventLoop(){
	nentries = mergeMAIN->inputTree->GetEntries();
	nentries = (nentries > maxEventNumber)?maxEventNumber:nentries;
	cout << "NUMBER OF EVENTS = " << nentries << endl;
	for(Long64_t ientry = 0; ientry<nentries;ientry++){

		//inputTree->GetEntry(ientry);
		getEntry(ientry);

		//initAnalysedOutput();

		if(kMAIN)	 analysingMAIN();
		if(kPLA)	 analysingPLA();
		if(kBDC)	 analysingBDC();
		if(kFDC0)	 analysingFDC0();
		if(kTELE)	 analysingTELE();
		if(kHOD)	 analysingHOD();
		if(kESPRI)	 analysingESPRI();

		//cout<<"Event Number = "<<ientry<<endl;
		//print();
		if(nentries<1000) {
			cout<<endl;
			cout<<"Event Number = "<<ientry<<endl;

			print();
		}

		tree->Fill();
	}
}
void Merger::print(){
	//printPLA();	
	//printBDC();	
	printESPRI();
	//printFDC0();
}
void Merger::getEntry(Long64_t ientry){
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
		if(kESPRI){
			mergeESPRI->init();
			mergeESPRI->getEntry(ientry);
		}
}

void Merger::createOutput(){

	TString outputPath = env->GetValue("outputPath","./rootfiles/");
	TString outputPrefix = env->GetValue("outputPrefix","./rootfiles/");
	TString outputSuffix = env->GetValue("outputSuffix","./rootfiles/");
	TString runString = Form("%d",runNumber);
	TString outputFileName = outputPath + outputPrefix + runString+ outputSuffix;
	cout<<outputFileName<<endl;
	outputFile = new TFile(outputFileName, "recreate"); 
	//outputFile = new TFile(Form("./rootfiles/run%04d_analysed.root_2",runNumber), "recreate"); 
	tree = new TTree("tree","Analysed Tree:raw,cal,analysed");
	setOutputBranch();
}
void Merger::saveOutput(){
	tree->Write();
	outputFile->Close();
}

void Merger::addFriend(){
	if(kPLA){
		//inputTree->AddFriend(mergePLA->inputTree);
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
	if(kESPRI) mergeESPRI->setBranch();
}
void Merger::loadInputFiles(){
	if(kMAIN) mergeMAIN->loadInputFiles();
	if(kPLA) mergePLA->loadInputFiles();
	if(kBDC) mergeBDC->loadInputFiles();
	if(kFDC0) mergeFDC0->loadInputFiles();
	if(kTELE) mergeTELE->loadInputFiles();
	if(kHOD) mergeHOD->loadInputFiles();
	if(kESPRI) mergeESPRI->loadInputFiles();
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
	if(kESPRI)	 mergeESPRI->printTotalEventNumber();
}

bool Merger::isFilesExist(){
	//return mergeMAIN->isFileExists()&&mergePLA->isFileExists()&&mergeBDC->isFileExists()&&mergeFDC0->isFileExists()&&mergeTELE->isFileExists()&&mergeHOD->isFileExists();
	//return mergeMAIN->isFileExists()&&mergePLA->isFileExists()&&mergeBDC->isFileExists()&&mergeFDC0->isFileExists()&&mergeTELE->isFileExists()&&mergeESPRI->isFileExists();
	return mergeMAIN->isFileExists()&&mergePLA->isFileExists()&&mergeBDC->isFileExists()&&mergeFDC0->isFileExists()&&mergeTELE->isFileExists()&&mergeESPRI->isFileExists()&&mergeHOD->isFileExists();
	//return mergePLA->isFileExists()&&isFileExists("BDC")&&isFileExists("FDC")&&isFileExists("TELE");
}
void Merger::setOutputBranch(){
	if(kMAIN)	 setMAINOutputBranch();
	if(kPLA)	 setPLAOutputBranch();
	if(kBDC)	 setBDCOutputBranch();
	if(kFDC0)	 setFDC0OutputBranch();
	if(kTELE)	 setTELEOutputBranch();
	if(kHOD)	 setHODOutputBranch();
	if(kESPRI)	 setESPRIOutputBranch();
}
