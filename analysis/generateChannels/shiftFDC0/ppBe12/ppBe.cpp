#include "ppBe.h"

PPBe::PPBe(int runNumber,int maxEventNumber):runNumber(runNumber),maxEventNumber(maxEventNumber){
	env= new TEnv("configPPBe.prm");
	rf = new ReadFile(runNumber);
	event = new Event(rf);
	fdc0Event = new Fdc0Event();
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
	fdc0Event->setOutputBranch(tree);
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
			setFdc0Event();
			tree->Fill();

			cout<<"Event Number = "<<ientry<<endl;
			//print();
			//if(nentries<1000) {
			//	cout<<endl;
			//	cout<<"Event Number = "<<ientry<<endl;

			//	print();
			//}
		}

	}
}

void PPBe::setFdc0Event(){
		fdc0Event->init();
        fdc0Event->load(rf);
        fdc0Event->setEvent();
}
void PPBe::print(){
	fdc0Event->print();
}
