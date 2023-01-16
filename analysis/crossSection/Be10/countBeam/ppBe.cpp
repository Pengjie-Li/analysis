#include "ppBe.h"

PPBe::PPBe(int runNumber,int maxEventNumber):runNumber(runNumber),maxEventNumber(maxEventNumber){
	env= new TEnv("configPPBe.prm");
	rf = new ReadFile(runNumber);
	event = new Event(rf);
	ppAlpha = new PPAlphaKinetics(rf);
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
	ppAlpha->setBranch(tree);
}
void PPBe::saveOutput(){
	tree->Write();
	outputFile->Close();
}
void PPBe::eventLoop(){
	dsbTotal = 0;
	nentries = rf->getEntries();
	nentries = (nentries > maxEventNumber)?maxEventNumber:nentries;
	cout << "NUMBER OF EVENTS = " << nentries << endl;
	//for(Long64_t ientry = 55940; ientry<nentries;ientry++){
	for(Long64_t ientry = 0; ientry<nentries;ientry++){

		rf->getEntry(ientry);

		if(event->selectEvent()){
			dsbTotal++;
			//ppAlpha->calculate();
			//tree->Fill();
			//cout<<"Event Number = "<<ientry<<endl;
			//print();
			//if(nentries<1000) {
			//	cout<<endl;
			//	cout<<"Event Number = "<<ientry<<endl;

			//	print();
			//}
		}

	}
	output();

}
void PPBe::output(){
	TString outputName = "runDSBSummary.txt";
	ofstream out(outputName,ios_base::app | ios_base::out);
	out.flags (ios::left);
	out<<setw(20)<<rf->getRunNumber()<<setw(20)<<dsbTotal<<endl;
	out.close();
}
void PPBe::print(){
	//ppAlpha->print();
}
