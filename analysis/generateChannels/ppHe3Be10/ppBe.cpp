#include "ppBe.h"

PPBe::PPBe(int runNumber,int maxEventNumber):runNumber(runNumber),maxEventNumber(maxEventNumber){
	env= new TEnv("configPPBe.prm");
	rf = new ReadFile(runNumber);
	event = new Event(rf);

	he3Event = new He3Event();
}
bool PPBe::isFilesExist(){
	return rf->isFilesExist();
}
void PPBe::loadInputFiles(){
	rf->loadInputFiles();
}
void PPBe::createOutput(){
	TString outputPath = env->GetValue("outputPath","./rootfiles/");
	TString outputPrefix = env->GetValue("outputPrefix","./rootfiles/");
	TString outputSuffix = env->GetValue("outputSuffix","./rootfiles/");
	TString runString = Form("%d",runNumber);
	TString outputFileName = outputPath + outputPrefix + runString+ outputSuffix;
	cout<<outputFileName<<endl;
	outputFile = new TFile(outputFileName, "recreate");
	tree = new TTree("tree","selected Event");
	setOutputBranch();
}
void PPBe::setOutputBranch(){
	rf->setBranch(tree);
	event->setBranch(tree);
	he3Event->setOutputBranch(tree);
}
void PPBe::saveOutput(){
	tree->Write();
	outputFile->Close();
}
void PPBe::eventLoop(){
	nentries = rf->getEntries();
	nentries = (nentries > maxEventNumber)?maxEventNumber:nentries;
	cout << "NUMBER OF EVENTS = " << nentries << endl;
	//for(Long64_t ientry = 55940; ientry<nentries;ientry++){
	for(Long64_t ientry = 0; ientry<nentries;ientry++){

		rf->getEntry(ientry);

		if(event->selectEvent()){
			setHe3Event();
			tree->Fill();

			//cout<<"Event Number = "<<ientry<<endl;
			//print();
			//if(nentries<100000) {
			//	cout<<endl;
			//	cout<<"Event Number = "<<ientry<<endl;

			//	print();
			//}
		}

	}
}
void PPBe::setHe3Event(){
        he3Event->init();

        he3Event->load(rf);
        he3Event->setEvent();
}

void PPBe::print(){
	he3Event->print();
}
