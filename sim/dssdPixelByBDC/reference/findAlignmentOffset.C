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
#include <TEnv.h>
#include <TVector3.h>
#include <Math/Functor.h>
#include <Math/Vector3D.h>
#include <TRandom2.h>
#include <TStyle.h>
#include <TCanvas.h>
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

// For configuration file
TEnv *env = new TEnv("configAlignment.prm");

class ReadFile{

	public:
		TString inputname;


		ReadFile(){
			inputname=getInputName();
			cout<<inputname<<endl;

			
			//inputname=Form("cutWindow/run0%d_analysed_cutWindow.root",runnum);
			//inputname=Form("test/run0%d_analysed_v2.root",runnum);
			//inputname=Form("analysedrootfiles/run0%d_analysed_v3.root",runnum);
			openFile();
			setBranch();
		}

		TString getInputName(){
			return Form("%s%s%d%s",env->GetValue("inputPath","analysedrootfiles/"),env->GetValue("runPrefix","run0"),env->GetValue("runNumber",595),env->GetValue("runSuffix","_analysed_v3.root"));
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
			AnalysisTree=(TTree*)f->Get("AnalysisTree");
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
	/**
	 * Class Provide Space Position information (X,Y,Z)
	 * Has Functions to set and get XYZ
	 * Generate Branch Tree related with XYZ
	 */
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

			Z = -4222.34;
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

		double xBDC2Offset;
		double yBDC2Offset;

		double xFDC0Offset;
		double yFDC0Offset;



		TFile *outputFile;
		TTree *tree;
		// SetBranch variables
		// Drift Chambers Position
		TNewBDC1SpacePosition *spBDC1;
		TNewBDC2SpacePosition *spBDC2;
		TNewdBDC2SpacePosition *spdBDC2;
		TNewFDC0SpacePosition *spFDC0;
		TNewTargetSpacePosition *spTarget;

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
			rf=new ReadFile();
			TString outputName=getOutputName();
			cout<<outputName<<endl;
			outputFile = new TFile(outputName,"recreate");
			tree=new TTree("tree","tree");
			initSpacePosition();
			setBranch();
			loopTree();
			closeFile();
		}

		TString getOutputName(){
			xBDC2Offset = env->GetValue("xBDC2Offset",100.);
			yBDC2Offset = env->GetValue("yBDC2Offset",100.);

			xFDC0Offset = env->GetValue("xFDC0Offset",100.);
			yFDC0Offset = env->GetValue("yFDC0Offset",100.);
			TString offsetSuffix = Form("BDC2x%04fy%04fFDC0x%04fy%04f",xBDC2Offset,yBDC2Offset,xFDC0Offset,yFDC0Offset);
			TString name = Form("%s%s%d%s",env->GetValue("outputPath","./rootfiles/"),env->GetValue("outputPrefix","Position_Resolution_run"),env->GetValue("runNumber",runNumber),env->GetValue("outputSuffix","_cutWindow_gatedTarget"));

			name = name + offsetSuffix;
			return name;
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

			spBDC2->setXY(-rf->BDC2_X+xBDC2Offset,rf->BDC2_Y+yBDC2Offset);
			spTarget->setXY(-rf->Target_X,rf->Target_Y);
			spFDC0->setXY(rf->FDC0_X+xFDC0Offset,rf->FDC0_Y+yFDC0Offset);

		}
		void setBDC2FromtBDC1AndFDC0(){
			vBDC1.SetXYZ(spBDC1->getX(),spBDC1->getY(),spBDC1->getZ());
			vFDC0.SetXYZ(spFDC0->getX(),spFDC0->getY(),spFDC0->getZ());
			vDirection=(vFDC0-vBDC1).Unit();
			// determine k
			double k=getRatio(spBDC1->getZ(),spBDC2->getZ(),vDirection.Z());
			vdBDC2=vBDC1+k*vDirection;
			spdBDC2->setXY(vdBDC2.X(),vdBDC2.Y());
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

int findAlignmentOffset(){

	int runNumber = env->GetValue("runNumber",595);
	int MaxEventNumber = env->GetValue("MaxEventNumber",5000000);
	GeneratedBDC2 *gf=new GeneratedBDC2(runNumber,MaxEventNumber);		


	return 1;
}
int main(){
	return findAlignmentOffset();
}
