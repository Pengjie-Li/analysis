#include "scmGenerator.h"

ScmGenerator::ScmGenerator(int runNumber,int maxEventNumber):runNumber(runNumber),maxEventNumber(maxEventNumber){
	env= new TEnv("configScmGenerator.prm");
	rf = new ReadFile(runNumber);
	event = new Event(rf);
}
bool ScmGenerator::isFilesExist(){
	return rf->isFilesExist();
}
void ScmGenerator::loadInputFiles(){
	rf->loadInputFiles();
}
void ScmGenerator::createOutput(){
	TString outputPath = env->GetValue("outputPath","./rootfiles/");
	TString outputPrefix = env->GetValue("outputPrefix","./rootfiles/");
	TString outputSuffix = env->GetValue("outputSuffix","./rootfiles/");
	TString runString = Form("%d",runNumber);
	TString outputFileName = outputPath + outputPrefix + runString+ outputSuffix;
	//cout<<outputFileName<<endl;
	outputFile = new TFile(outputFileName, "recreate");
	tree = new TTree("tree","selected Event");
	setOutputBranch();
}
void ScmGenerator::setOutputBranch(){
	rf->setBranch(tree);
	event->setBranch(tree);
}
void ScmGenerator::saveOutput(){
	tree->Write();
	outputFile->Close();
}
void ScmGenerator::eventLoop(){
	nentries = rf->getEntries();
	nentries = (nentries > maxEventNumber)?maxEventNumber:nentries;
	cout << "NUMBER OF EVENTS = " << nentries << endl;
	//for(Long64_t ientry = 55940; ientry<nentries;ientry++){
	for(Long64_t ientry = 0; ientry<nentries;ientry++){

		rf->getEntry(ientry);

		if(event->selectEvent()){
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
void ScmGenerator::print(){
}
