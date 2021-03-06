/**
 * select a pixel and draw all trajectories through this pixel
 * 1. Read files, select pixel(fid,bid),find BDC position,save into a new rootfile
 * 2. open this pixel rootfile and draw the trajectories in 3D
 */

#include <math.h>
#include <fstream>
#include <TFile.h>
#include <TH3D.h>
#include <TTree.h>
#include <TVector3.h>
#include <Math/Functor.h>
#include <Math/Vector3D.h>
#include <TRandom2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TEnv.h>
#include <TF2.h>
#include <TH2D.h>
#include <TView.h>
#include <TH1.h>
#include <Math/Functor.h>
#include <TPolyLine3D.h>
#include <TPolyMarker3D.h>
#include <Math/Vector3D.h>
#include <Fit/Fitter.h>
//using namespace ROOT::Math;

TEnv *env = new TEnv("configCheckBDC2.prm");

class ReadFile{

	public:
		TString inputname;


		ReadFile(int runnum){
			TString inputPath = env->GetValue("inputPath","./rootfile");
			TString runPrefix = env->GetValue("runPrefix","run0");
			TString runSuffix = env->GetValue("runSuffix",".root");
			inputname = inputPath+runPrefix+Form("%d",runnum)+runSuffix;
			cout<<inputname<<endl;
//			inputname=Form("cutWindow/run0%d_analysed_cutWindow.root",runnum);
			//inputname=Form("cutWindow/run0%d_analysed_cutWindow.root",runnum);
			//inputname=Form("test/run0%d_analysed_v2.root",runnum);
			//inputname=Form("analysedrootfiles/run0%d_analysed_v3.root",runnum);
			openFile();
			setBranch();
		}

		// Open file
		TFile *f;
		TTree *AnalysisTree;

		//Declaration of leaves types

		Int_t           RunNumber;
		Long64_t        EventNumber;

		Double_t        BDC1_X;
		Double_t        BDC1_Y;

		Double_t        BDC2_X;
		Double_t        BDC2_Y;

		Double_t        Target_X;
		Double_t        Target_Y;



		Double_t        FDC0_X;
		Double_t        FDC0_Y;

		Double_t        SiLF_E[32]; 
		Double_t        SiLB_E[32]; 
		Double_t        SiRF_E[32]; 
		Double_t        SiRB_E[32];



		void openFile(){
			f = new TFile(inputname,"READ");
			//AnalysisTree=(TTree*)f->Get("AnalysisTree");
			AnalysisTree=(TTree*)f->Get("tree");
		}
		void setBranch(){

			// Set branch addresses.
			AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
			AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);

			AnalysisTree->SetBranchAddress("BDC1_X",&BDC1_X);
			AnalysisTree->SetBranchAddress("BDC1_Y",&BDC1_Y);

			AnalysisTree->SetBranchAddress("BDC2_X",&BDC2_X);
			AnalysisTree->SetBranchAddress("BDC2_Y",&BDC2_Y);

			AnalysisTree->SetBranchAddress("Target_X",&Target_X);
			AnalysisTree->SetBranchAddress("Target_Y",&Target_Y);


			AnalysisTree->SetBranchAddress("FDC0_X",&FDC0_X);
			AnalysisTree->SetBranchAddress("FDC0_Y",&FDC0_Y);

			AnalysisTree->SetBranchAddress("SiLF_E",&SiLF_E);
			AnalysisTree->SetBranchAddress("SiLB_E",&SiLB_E);

			AnalysisTree->SetBranchAddress("SiRF_E",&SiRF_E);
			AnalysisTree->SetBranchAddress("SiRB_E",&SiRB_E);


		}

		void closeFile(){
			f->Close();
		}

};
class TNewSpacePosition{
	private:
	public:
		Double_t X;
		Double_t Y;
		Double_t Z;
		TNewSpacePosition(){
		}
		void setXYZ(Double_t xx,Double_t yy,Double_t zz){
			X = xx;
			Y = yy;
			Z = zz;
		}
		void setXY(Double_t xx,Double_t yy){
			X = xx;
			Y = yy;
		}
		Double_t getX(){
			return X;
		}
		Double_t getY(){
			return Y;
		}
		Double_t getZ(){
			return Z;
		}
		void printXYZ(){
			cout<<"X = "<<X<<" Y = "<<Y<<" Z = "<<Z<<endl;
		}
		virtual void setBranch(TTree *tree){
		}
		virtual void print(){
		}
};
class TNewBDC1SpacePosition:public TNewSpacePosition{
	private: 
	public :
		TNewBDC1SpacePosition(){
			Z = -6666.11;
		}
		void setBranch(TTree *tree){

			tree->Branch("BDC1_X",&X,"BDC1_X/D");
			tree->Branch("BDC1_Y",&Y,"BDC1_Y/D");
			tree->Branch("BDC1_Z",&Z,"BDC1_Z/D");
		}
		void print(){
			cout<<" BDC1: ";
			printXYZ();
		}


};
class TNewBDC2SpacePosition:public TNewSpacePosition{
	private: 
	public :
		TNewBDC2SpacePosition(){
			Z = -5666.67;
		}
		void setBranch(TTree *tree){

			tree->Branch("BDC2_X",&X,"BDC2_X/D");
			tree->Branch("BDC2_Y",&Y,"BDC2_Y/D");
			tree->Branch("BDC2_Z",&Z,"BDC2_Z/D");
		}

		void print(){
			cout<<" BDC2: ";
			printXYZ();
		}



};
class TNewFDC0SpacePosition:public TNewSpacePosition{
	private: 
	public :
		TNewFDC0SpacePosition(){
			Z = -3384.7;// later check
		}
		void setBranch(TTree *tree){

			tree->Branch("FDC0_X",&X,"FDC0_X/D");
			tree->Branch("FDC0_Y",&Y,"FDC0_Y/D");
			tree->Branch("FDC0_Z",&Z,"FDC0_Z/D");
		}
		void print(){
			cout<<" FDC0: ";
			printXYZ();
		}



};

class TNewdBDC2SpacePosition:public TNewSpacePosition{
	private: 
	public :
		TNewdBDC2SpacePosition(){

			Z = -5666.67;
		}
		void setBranch(TTree *tree){

			tree->Branch("dBDC2_X",&X,"dBDC2_X/D");
			tree->Branch("dBDC2_Y",&Y,"dBDC2_Y/D");
			tree->Branch("dBDC2_Z",&Z,"dBDC2_Z/D");
		}
		void print(){
			cout<<" dBDC2: ";
			printXYZ();
		}



};
class TNewTargetSpacePosition:public TNewSpacePosition{
	private: 
	public :
		TNewTargetSpacePosition(){

			Z = 2443.77-6666.11;
		}
		void setBranch(TTree *tree){

			tree->Branch("Target_X",&X,"Target_X/D");
			tree->Branch("Target_Y",&Y,"Target_Y/D");
			tree->Branch("Target_Z",&Z,"Target_Z/D");
		}
		void print(){
			cout<<" Target: ";
			printXYZ();
		}



};
class GeneratedBDC2{

	public:
		int MaxEventNumber ;
		int runNumber ;

		ReadFile *rf;
		TVector3 vBDC1;
		TVector3 vdBDC2;
		TVector3 vFDC0;
		TVector3 vDirection;


		TFile *outputFile;
		TTree *tree;
		// SetBranch variables
		// Drift Chambers Position
		TNewBDC1SpacePosition *spBDC1;
		TNewBDC2SpacePosition *spBDC2;
		TNewdBDC2SpacePosition *spdBDC2;
		TNewFDC0SpacePosition *spFDC0;
		TNewTargetSpacePosition *spTarget;
		//		Double_t BDC1_X;
		//		Double_t BDC1_Y;
		//		Double_t BDC1_Z;
		//
		//		Double_t BDC2_X;
		//		Double_t BDC2_Y;
		//		Double_t BDC2_Z;
		//
		//		Double_t dBDC2_X;
		//		Double_t dBDC2_Y;
		//		Double_t dBDC2_Z;
		//
		//		Double_t Target_X;
		//		Double_t Target_Y;
		//		Double_t Target_Z;
		//
		//		Double_t FDC0_X;
		//		Double_t FDC0_Y;
		//		Double_t FDC0_Z;

		GeneratedBDC2(int runnum){
			runNumber = runnum;
			launchGenerator();
		}
		GeneratedBDC2(int runnum, int mevt){
			MaxEventNumber = mevt;
			runNumber = runnum;
			launchGenerator();
		}

		void launchGenerator(){
			rf=new ReadFile(runNumber);
			
			//outputFile = new TFile("sfdlk.root","recreate");
			outputFile = new TFile(getOutputName(),"recreate");
			cout<<getOutputName()<<endl;
			tree=new TTree("tree","tree");
			initSpacePosition();
			setBranch();
			loopTree();
			closeFile();
		}
		TString getOutputName(){
			TString outputPath = env->GetValue("outputPath","./rootfiles/");
			TString outputPrefix = env->GetValue("outputPrefix","Position_Resolution_run");
			TString outputSuffix = env->GetValue("outputSuffix",".root");
			TString result = outputPath+outputPrefix+Form("%d",runNumber)+outputSuffix;
			return result;
		}

		void initSpacePosition(){
			spBDC1 = new TNewBDC1SpacePosition();
			spBDC2 = new TNewBDC2SpacePosition();
			spdBDC2 = new TNewdBDC2SpacePosition();
			spFDC0 = new TNewFDC0SpacePosition();
			spTarget = new TNewTargetSpacePosition();
		}

		void setBranch(){

			spBDC1->setBranch(tree);
			spBDC2->setBranch(tree);
			spdBDC2->setBranch(tree);
			spTarget->setBranch(tree);
			spFDC0->setBranch(tree);
			//	tree->Branch("BDC1_X",&BDC1_X,"BDC1_X/D");
			//	tree->Branch("BDC1_Y",&BDC1_Y,"BDC1_Y/D");
			//	tree->Branch("BDC1_Z",&BDC1_Z,"BDC1_Z/D");

			//		tree->Branch("dBDC2_X",&dBDC2_X,"dBDC2_X/D");
			//		tree->Branch("dBDC2_Y",&dBDC2_Y,"dBDC2_Y/D");
			//		tree->Branch("dBDC2_Z",&dBDC2_Z,"dBDC2_Z/D");


			//		tree->Branch("BDC2_X",&BDC2_X,"BDC2_X/D");
			//		tree->Branch("BDC2_Y",&BDC2_Y,"BDC2_Y/D");
			//		tree->Branch("BDC2_Z",&BDC2_Z,"BDC2_Z/D");

			//		tree->Branch("Target_X",&Target_X,"Target_X/D");
			//		tree->Branch("Target_Y",&Target_Y,"Target_Y/D");
			//		tree->Branch("Target_Z",&Target_Z,"Target_Z/D");



			//		tree->Branch("FDC0_X",&FDC0_X,"FDC0_X/D");
			//		tree->Branch("FDC0_Y",&FDC0_Y,"FDC0_Y/D");
			//		tree->Branch("FDC0_Z",&FDC0_Z,"FDC0_Z/D");

		}

		void loopTree(){
			Long64_t nentries=rf->AnalysisTree->GetEntries();
			//nentries=100000;
			if(nentries > MaxEventNumber) nentries = MaxEventNumber ;

			for (Long64_t ientry=0; ientry<nentries;ientry++) {
				rf->AnalysisTree->GetEntry(ientry);

				if(ientry%1000==0) cout<<ientry<<endl;
				//cout<<ientry<<endl;
				if(isInsideTargetCell()){
					setNewDCPosition();
					setBDC2FromtBDC1AndFDC0();
					tree->Fill();
				}

			}



		}
		bool isInsideTargetCell(){
			return (sqrt((rf->Target_X+2.13)*(rf->Target_X+2.13)+(rf->Target_Y+1.6)*(rf->Target_Y+1.6))<15);
			//return true;
		}
		void printDC(){
			spBDC1->print();
			spBDC2->print();
			spdBDC2->print();
			spFDC0->print();
			spTarget->print();
		}

		void setNewDCPosition(){
			//cout<<rf->BDC1_X<<endl;
			spBDC1->setXY(-rf->BDC1_X,rf->BDC1_Y);
			spBDC2->setXY(-rf->BDC2_X,rf->BDC2_Y);
			spTarget->setXY(-rf->Target_X,rf->Target_Y);
			spFDC0->setXY(rf->FDC0_X,rf->FDC0_Y);

			//	BDC2_X=-rf->BDC2_X;
			//	BDC2_Y=rf->BDC2_Y;
			//	BDC2_Z=-5666.67;// later check

			//	Target_X=-rf->Target_X;
			//	Target_Y=rf->Target_Y;
			//	Target_Z=2443.77-6666.11;// later check



			//	FDC0_X=rf->FDC0_X; // check out why FDC0 positive
			//	FDC0_Y=rf->FDC0_Y;
			//	FDC0_Z=-3384.7;// later check
		}
		void setBDC2FromtBDC1AndFDC0(){
			vBDC1.SetXYZ(spBDC1->getX(),spBDC1->getY(),spBDC1->getZ());
			vFDC0.SetXYZ(spFDC0->getX(),spFDC0->getY(),spFDC0->getZ());
			vDirection=(vFDC0-vBDC1).Unit();
			// determine k
			double k=getRatio(spBDC1->getZ(),spBDC2->getZ(),vDirection.Z());
			vdBDC2=vBDC1+k*vDirection;
			spdBDC2->setXY(vdBDC2.X(),vdBDC2.Y());
			//dBDC2_X=vdBDC2.X();
			//dBDC2_Y=vdBDC2.Y();
			//dBDC2_Z=vdBDC2.Z();

		}
		double getRatio(double z1,double z2,double interval){
			return (z2-z1)/interval;
		}

		void closeFile(){
			rf->closeFile();
			tree->Write();
			outputFile->Close();
		}

};

int CheckBDC2(){

	//int runNumber = 320;
	int runNumber = 310;
	//int runNumber = 340;
	//int MaxEventNumber = 500;
	int MaxEventNumber = 5000000;
	GeneratedBDC2 *gf=new GeneratedBDC2(runNumber,MaxEventNumber);		
	return 1;
}
int main(){
	return CheckBDC2();
}

