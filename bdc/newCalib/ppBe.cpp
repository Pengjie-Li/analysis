#include "ppBe.h"

void PPBe::loadChain(int rSt,int rSp){

	env= new TEnv("configPPBe.prm");
	rf = new ReadFile();
	event = new Event(rf);

	runStart = rSt;
	runStop  = rSp;
	rf->loadChain(runStart,runStop);

}
bool PPBe::isFilesExist(){
	return true;
}
void PPBe::loadInputFiles(){
	//rf->loadInputFiles();
}
void PPBe::createOutput(){
	TString outputPath = env->GetValue("outputPath","./rootfiles/");
	TString outputPrefix = env->GetValue("outputPrefix","./rootfiles/");
	TString outputSuffix = env->GetValue("outputSuffix","./rootfiles/");
	TString runString = Form("%d_%d",runStart, runStop);
	TString outputFileName = outputPath + outputPrefix + runString+ outputSuffix;
	cout<<outputFileName<<endl;
	outputFile = new TFile(outputFileName, "recreate");
	tree = new TTree("tree","selected Event");
	setOutputBranch();
}
void PPBe::setOutputBranch(){
	//rf->setBranch(tree);
	//event->setBranch(tree);
}
void PPBe::saveOutput(){
	outputFile->cd();
	//outputFile->Write();
	event->write();
	outputFile->Close("R");
	//tree->Write();
	//outputFile->Close();
}
void PPBe::eventLoop(){

	Long64_t nentries = rf->getTotalEntries();
	//nentries = 10000;
	cout << "NUMBER OF EVENTS = " << nentries << endl;
	for (Long64_t i = 0; i < nentries; ++i) {
		rf->getEntry(i);
		if(event->selectEvent()){
			if(event->goodBDC1Gate()) event->fillBDC1();
			if(event->goodBDC2Gate()) event->fillBDC2();
			if(event->goodFDC0Gate()) event->fillFDC0();
			//rf->print();
		}
		if(i%10000==0) cout<<i*100/nentries<<"%"<<endl;
	}
}
void PPBe::print(){
}
