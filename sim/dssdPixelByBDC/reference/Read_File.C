/**
 * select a pixel and draw all trajectories through this pixel
 * 1. Read files, select pixel(fid,bid),find BDC position,save into a new rootfile
 * 2. open this pixel rootfile and draw the trajectories in 3D
 */

#include <math.h>
#include <TFile.h>
#include <TH3D.h>
#include <TTree.h>
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

class ReadFile{

	public:
		TString inputname;

		ReadFile(int runnum){
			inputname=Form("analysedrootfiles/run0%d_analysed_v3.root",runnum);
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
	

		}
		
		void closeFile(){
			f->Close();
		}

};
class GenerateFile{

	public:
		ReadFile *rf;
		
		TFile *outputFile;
		TTree *tree;
		// SetBranch variables
		Double_t BDC1_X;
		Double_t BDC1_Y;
		Double_t BDC1_Z;

		Double_t BDC2_X;
		Double_t BDC2_Y;
		Double_t BDC2_Z;

		Double_t dBDC2_X;
		Double_t dBDC2_Y;
		Double_t dBDC2_Z;

		Double_t Target_X;
		Double_t Target_Y;
		Double_t Target_Z;



		Double_t FDC0_X;
		Double_t FDC0_Y;
		Double_t FDC0_Z;

		GenerateFile(int runnum){
			rf=new ReadFile(runnum);
			outputFile=new TFile(Form("./rootfiles/Position_Resolution_run%d.root",runnum),"recreate");
			tree=new TTree("tree","tree");
			setBranch();
			setNewDCPosition();
			closeFile();
		}
		void setBranch(){

			tree->Branch("BDC1_X",&BDC1_X,"BDC1_X/D");
			tree->Branch("BDC1_Y",&BDC1_Y,"BDC1_Y/D");
			tree->Branch("BDC1_Z",&BDC1_Z,"BDC1_Z/D");

			tree->Branch("dBDC2_X",&dBDC2_X,"dBDC2_X/D");
			tree->Branch("dBDC2_Y",&dBDC2_Y,"dBDC2_Y/D");
			tree->Branch("dBDC2_Z",&dBDC2_Z,"dBDC2_Z/D");


			tree->Branch("BDC2_X",&BDC2_X,"BDC2_X/D");
			tree->Branch("BDC2_Y",&BDC2_Y,"BDC2_Y/D");
			tree->Branch("BDC2_Z",&BDC2_Z,"BDC2_Z/D");

			tree->Branch("Target_X",&Target_X,"Target_X/D");
			tree->Branch("Target_Y",&Target_Y,"Target_Y/D");
			tree->Branch("Target_Z",&Target_Z,"Target_Z/D");



			tree->Branch("FDC0_X",&FDC0_X,"FDC0_X/D");
			tree->Branch("FDC0_Y",&FDC0_Y,"FDC0_Y/D");
			tree->Branch("FDC0_Z",&FDC0_Z,"FDC0_Z/D");

		}

		void setNewDCPosition(){
			Long64_t nentries=rf->AnalysisTree->GetEntries();
			//nentries=1000;

			for (Long64_t ientry=0; ientry<nentries;ientry++) {
				rf->AnalysisTree->GetEntry(ientry);

				cout<<ientry<<endl;
				//cout<<rf->BDC1_X<<endl;
				BDC1_X=-rf->BDC1_X;
				BDC1_Y=rf->BDC1_Y;
				BDC1_Z=-6666.11;// later check

				BDC2_X=-rf->BDC2_X;
				BDC2_Y=rf->BDC2_Y;
				BDC2_Z=-5666.67;// later check

				Target_X=-rf->Target_X;
				Target_Y=rf->Target_Y;
				Target_Z=2443.77-6666.11;// later check



				FDC0_X=rf->FDC0_X;
				FDC0_Y=rf->FDC0_Y;
				FDC0_Z=-3384.7;// later check

				getBDC2FromtBDC1AndFDC0();
				//printAll();

				tree->Fill();
				
				}


			
		}
		void printAll(){
			cout<<"BDC1_X="<<BDC1_X<<" BDC1_Y="<<BDC1_Y<<" BDC1_Z="<<BDC1_Z<<endl;
			cout<<"BDC2_X="<<BDC2_X<<" BDC2_Y="<<BDC2_Y<<" BDC2_Z="<<BDC2_Z<<endl;
			cout<<"Target_X="<<Target_X<<" Target_Y="<<Target_Y<<" Target_Z="<<Target_Z<<endl;
			cout<<"dBDC2_X="<<dBDC2_X<<" dBDC2_Y="<<dBDC2_Y<<" dBDC2_Z="<<dBDC2_Z<<endl;
			cout<<"FDC0_X="<<FDC0_X<<" FDC0_Y="<<FDC0_Y<<" FDC0_Z="<<FDC0_Z<<endl;


		}
		void getBDC2FromtBDC1AndFDC0(){
			TVector3 vBDC1(BDC1_X,BDC1_Y,BDC1_Z);
			TVector3 vFDC0(FDC0_X,FDC0_Y,FDC0_Z);
			TVector3 vDirection=(vFDC0-vBDC1).Unit();
			// determine k
			double k=getRatio(BDC1_Z,BDC2_Z,vDirection.Z());
			TVector3 vdBDC2=vBDC1+k*vDirection;
			dBDC2_X=vdBDC2.X();
			dBDC2_Y=vdBDC2.Y();
			dBDC2_Z=vdBDC2.Z();
			
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
bool isFileExist(int fid,int bid,int runnum){

	TFile *outputFile=new TFile(Form("pixel%d_%d_run%d.root",fid,bid,runnum),"READ");
	return outputFile->IsOpen();
}
int Read_File(){

	GenerateFile *gf=new GenerateFile(436);		
	//GenerateFile *gf=new GenerateFile(595);		
	return 1;
}

int main(){
	return Read_File();
}

