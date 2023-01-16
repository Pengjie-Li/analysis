/**
 * select a pixel and draw all trajectories through this pixel
 * 1. Read files, select pixel(fid,bid),find BDC position,save into a new rootfile
 * 2. open this pixel rootfile and draw the trajectories in 3D
 */

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
#include <TH1.h>
#include <Math/Functor.h>
#include <TPolyLine3D.h>
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

		TVector3        *Beam;
		Int_t           RunNumber;
		Long64_t        EventNumber;

		Double_t        BDC1_X;
		Double_t        BDC1_Y;

		Double_t        BDC2_X;
		Double_t        BDC2_Y;

		Double_t        Target_X;
		Double_t        Target_Y;

		Double_t        Target_ThetaX;
		Double_t        Target_ThetaY;

		Double_t        SiLF_E[32];
		Double_t        SiLB_E[32];
		Double_t        SiRF_E[32];
		Double_t        SiRB_E[32];

		Double_t SiLF_Emax;
		Double_t SiLB_Emax;
		Double_t SiRF_Emax;
		Double_t SiRB_Emax;

		Int_t SiLF_id;
		Int_t SiLB_id;
		Int_t SiRF_id;
		Int_t SiRB_id;


		Double_t        SiLF_SCM[32];
		Double_t        SiLB_SCM[32];
		Double_t        SiRF_SCM[32];
		Double_t        SiRB_SCM[32];



		Double_t        CsI_LL_E;
		Double_t        CsI_LRT_E;
		Double_t        CsI_LRB_E;
		Double_t        CsI_RLT_E;
		Double_t        CsI_RLB_E;
		Double_t        CsI_RRT_E;
		Double_t        CsI_RRB_E;

		Double_t        CsILL_E;
		Double_t        CsILRT_E;
		Double_t        CsILRB_E;
		Double_t        CsIRLT_E;
		Double_t        CsIRLB_E;
		Double_t        CsIRRT_E;
		Double_t        CsIRRB_E;


		void openFile(){
			f = new TFile(inputname,"READ");
			AnalysisTree=(TTree*)f->Get("AnalysisTree");
		}
		void setBranch(){

			Beam=0;
			// Set branch addresses.
			AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
			AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);

			AnalysisTree->SetBranchAddress("BDC1_X",&BDC1_X);
			AnalysisTree->SetBranchAddress("BDC1_Y",&BDC1_Y);

			AnalysisTree->SetBranchAddress("BDC2_X",&BDC2_X);
			AnalysisTree->SetBranchAddress("BDC2_Y",&BDC2_Y);
	
			AnalysisTree->SetBranchAddress("Target_X",&Target_X);
			AnalysisTree->SetBranchAddress("Target_Y",&Target_Y);
			AnalysisTree->SetBranchAddress("Target_ThetaX",&Target_ThetaX);
			AnalysisTree->SetBranchAddress("Target_ThetaY",&Target_ThetaY);

			AnalysisTree->SetBranchAddress("Beam",&Beam);

			AnalysisTree->SetBranchAddress("SiLF_E",SiLF_E);
			AnalysisTree->SetBranchAddress("SiLB_E",SiLB_E);
			AnalysisTree->SetBranchAddress("SiRF_E",SiRF_E);
			AnalysisTree->SetBranchAddress("SiRB_E",SiRB_E);

			AnalysisTree->SetBranchAddress("CsI_LL_E",&CsI_LL_E);
			AnalysisTree->SetBranchAddress("CsI_LRT_E",&CsI_LRT_E);
			AnalysisTree->SetBranchAddress("CsI_LRB_E",&CsI_LRB_E);
			AnalysisTree->SetBranchAddress("CsI_RLT_E",&CsI_RLT_E);
			AnalysisTree->SetBranchAddress("CsI_RLB_E",&CsI_RLB_E);
			AnalysisTree->SetBranchAddress("CsI_RRT_E",&CsI_RRT_E);
			AnalysisTree->SetBranchAddress("CsI_RRB_E",&CsI_RRB_E);

			AnalysisTree->SetBranchAddress("CsILL_E", &CsILL_E);
			AnalysisTree->SetBranchAddress("CsILRT_E",&CsILRT_E);
			AnalysisTree->SetBranchAddress("CsILRB_E",&CsILRB_E);
			AnalysisTree->SetBranchAddress("CsIRLT_E",&CsIRLT_E);
			AnalysisTree->SetBranchAddress("CsIRLB_E",&CsIRLB_E);
			AnalysisTree->SetBranchAddress("CsIRRT_E",&CsIRRT_E);
			AnalysisTree->SetBranchAddress("CsIRRB_E",&CsIRRB_E);

			AnalysisTree->SetBranchAddress("SiLF_Emax",&SiLF_Emax);
			AnalysisTree->SetBranchAddress("SiLB_Emax",&SiLB_Emax);
			AnalysisTree->SetBranchAddress("SiLF_id",&SiLF_id);
			AnalysisTree->SetBranchAddress("SiLB_id",&SiLB_id);

			AnalysisTree->SetBranchAddress("SiRF_Emax",&SiRF_Emax);
			AnalysisTree->SetBranchAddress("SiRB_Emax",&SiRB_Emax);
			AnalysisTree->SetBranchAddress("SiRF_id",&SiRF_id);
			AnalysisTree->SetBranchAddress("SiRB_id",&SiRB_id);



		}
		
		void closeFile(){
			f->Close();
		}

};
class GenerateFile{

	public:
		ReadFile *rf;
		
		Double_t BDC1_X;
		Double_t BDC1_Y;
		Double_t BDC1_Z;

		Double_t BDC2_X;
		Double_t BDC2_Y;
		Double_t BDC2_Z;

		Double_t Target_X;
		Double_t Target_Y;
		Double_t Target_Z;




		GenerateFile(int f,int b){
			fid=f;
			bid=b;
		}



		GenerateFile(int runnum){
			rf=new ReadFile(runnum);
			checkBDCVector();
			closeFile();
			//cout<<rf->AnalysisTree->GetEntries()<<endl;
		}
		

		void checkBDCVector(){
			Long64_t nentries=rf->AnalysisTree->GetEntries();
			nentries=100;

			for (Long64_t ientry=0; ientry<nentries;ientry++) {
				rf->AnalysisTree->GetEntry(ientry);
				BDC1_X=-rf->BDC1_X;
				BDC1_Y=rf->BDC1_Y;
				BDC1_Z=-6666.11;// later check

				BDC2_X=-rf->BDC2_X;
				BDC2_Y=rf->BDC2_Y;
				BDC2_Z=-5666.67;// later check

				Target_X=rf->Target_X;
				Target_Y=rf->Target_Y;
				Target_Z=2443.77-6666.11;// later check



				//cout<<BDC1_X<<" "<<Target_X<<endl;
				tree->Fill();
				
				}
			}


			
		}
		void closeFile(){
			rf->closeFile();
		}

};

class DrawTrajectory{

	const static double xMin=-50;
	const static double xMax=50;

	const static double yMin=-50;
	const static double yMax=50;

	const static double zMin=-7000;
	const static double zMax=-3000;


	public:
	TFile *inputFile;
	TTree *tree;
		// Branch variables
		//
		Double_t BDC1_X;
		Double_t BDC1_Y;
		Double_t BDC1_Z;

		Double_t BDC2_X;
		Double_t BDC2_Y;
		Double_t BDC2_Z;

		Double_t Target_X;
		Double_t Target_Y;
		Double_t Target_Z;


		// PolyLine
		TPolyLine3D *l[500];

		DrawTrajectory(int fid,int bid,int runnum){

			inputFile=new TFile(Form("pixel%d_%d_run%d.root",fid,bid,runnum),"READ");
			tree=(TTree*)inputFile->Get("tree");
			setBranch();
			fillPolyLine();
		}
		void setBranch(){
			tree->SetBranchAddress("BDC1_X",&BDC1_X);
			tree->SetBranchAddress("BDC1_Y",&BDC1_Y);
			tree->SetBranchAddress("BDC1_Z",&BDC1_Z);

			tree->SetBranchAddress("BDC2_X",&BDC2_X);
			tree->SetBranchAddress("BDC2_Y",&BDC2_Y);
			tree->SetBranchAddress("BDC2_Z",&BDC2_Z);

			tree->SetBranchAddress("Target_X",&Target_X);
			tree->SetBranchAddress("Target_Y",&Target_Y);
			tree->SetBranchAddress("Target_Z",&Target_Z);

		}
		void fillPolyLine(){
			//	TPolyLine3D *l = new TPolyLine3D(n);
			//	for (int i = 0; i <n;++i) {
			//		double t = t0+ dt*i/n;
			//		double x,y,z;
			//		line(t,parFit,x,y,z);
			//		l->SetPoint(i,x,y,z);
			//	}
			int n=tree->GetEntries();
			cout<<"We got "<<n<<" trajectories to draw"<<endl;
			

			TH3D *hdummy = new TH3D("hdummy", "", 2, xMin, xMax, 2, yMin, yMax, 2, zMin, zMax);
			hdummy->GetXaxis()->SetRangeUser(xMin, xMax);
			hdummy->GetYaxis()->SetRangeUser(yMin, yMax);
			hdummy->GetZaxis()->SetRangeUser(zMin, zMax);
			hdummy->SetLineColor(kWhite);
			hdummy->Draw();

			for (int i = 0; i <10;i++){

				l[i] = new TPolyLine3D(2);
				tree->GetEntry(i);
				l[i]->SetPoint(0,BDC1_X,BDC1_Y,BDC1_Z);
				l[i]->SetPoint(1,BDC2_X,BDC2_Y,BDC2_Z);
				l[i]->SetPoint(2,Target_X,Target_Y,Target_Z);


				TVector3* vBDC1 = new TVector3;
				TVector3* vBDC2 = new TVector3;
				TVector3* vTarget = new TVector3;

				vBDC1->SetXYZ(BDC1_X,BDC1_Y,BDC1_Z);
				vBDC2->SetXYZ(BDC2_X,BDC2_Y,BDC2_Z);
				vTarget->SetXYZ(Target_X,Target_Y,Target_Z);

				
				TVector3 *u1= new TVector3;
				TVector3 *u2= new TVector3;
                                (*u1)=((*vBDC2)-(*vBDC1)).Unit();
                                (*u2)=((*vTarget)-(*vBDC1)).Unit();

				cout<<u1->X()<<" "<<u1->Y()<<" "<<u1->Z()<<endl;
				cout<<u2->X()<<" "<<u2->Y()<<" "<<u2->Z()<<endl;
				//	cout<<u2.x<<u2.y<<u2.z<<endl;
				//   XYZVector x0(p[0], p[2], 0. );
				//   XYZVector x1(p[0] + p[1], p[2] + p[3], 1. );
				//   XYZVector u = (x1-x0).Unit();

				l[i]->SetLineColor(kBlue);
				l[i]->Draw();

			}

		}

};
bool isFileExist(int fid,int bid,int runnum){

	TFile *outputFile=new TFile(Form("pixel%d_%d_run%d.root",fid,bid,runnum),"READ");
	return outputFile->IsOpen();
}
int Check_BDC2Target(){
	//cout<<isFileExist(24,31,595)<<endl;
	if(isFileExist(24,31,595)) {}
	else new GenerateFile(24,31,595);
	new DrawTrajectory(24,31,595);
	return 1;
}

int main(){
	return Check_BDC2Target();
}

