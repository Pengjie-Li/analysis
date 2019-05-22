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
		int fid;
		int bid;
		TString side;
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

		Double_t Target_X;
		Double_t Target_Y;
		Double_t Target_Z;




		GenerateFile(int f,int b){
			fid=f;
			bid=b;
		}



		GenerateFile(int f,int b,int runnum){
			fid=f;
			bid=b;
			rf=new ReadFile(runnum);
			outputFile=new TFile(Form("pixel%d_%d_run%d.root",fid,bid,runnum),"recreate");
			tree=new TTree("tree","tree");
			setBranch();
			findBDCPosition();
			closeFile();
			//cout<<rf->AnalysisTree->GetEntries()<<endl;
		}

		GenerateFile(int f,int b,TString s,int runnum){
			fid=f;
			bid=b;
			side=s;
			rf=new ReadFile(runnum);
			if(side=="left") outputFile=new TFile(Form("lpixel%d_%d_run%d.root",fid,bid,runnum),"recreate");
			if(side=="right") outputFile=new TFile(Form("rpixel%d_%d_run%d.root",fid,bid,runnum),"recreate");
			tree=new TTree("tree","tree");
			setBranch();
			findBDCPosition();
			closeFile();
			//cout<<rf->AnalysisTree->GetEntries()<<endl;
		}

		void setBranch(){

			tree->Branch("BDC1_X",&BDC1_X,"BDC1_X/D");
			tree->Branch("BDC1_Y",&BDC1_Y,"BDC1_Y/D");
			tree->Branch("BDC1_Z",&BDC1_Z,"BDC1_Z/D");

			tree->Branch("BDC2_X",&BDC2_X,"BDC2_X/D");
			tree->Branch("BDC2_Y",&BDC2_Y,"BDC2_Y/D");
			tree->Branch("BDC2_Z",&BDC2_Z,"BDC2_Z/D");

			tree->Branch("Target_X",&Target_X,"Target_X/D");
			tree->Branch("Target_Y",&Target_Y,"Target_Y/D");
			tree->Branch("Target_Z",&Target_Z,"Target_Z/D");


		}

		void findBDCPosition(){
			Long64_t nentries=rf->AnalysisTree->GetEntries();
			//nentries=1000;

			for (Long64_t ientry=0; ientry<nentries;ientry++) {
				rf->AnalysisTree->GetEntry(ientry);

				double rawTarget_X=rf->Target_X;
				double rawTarget_Y=rf->Target_Y;

				int rawFid;
				int rawBid;

				double rawF_Emax;
				double rawB_Emax;

				if(side=="left"){
					rawFid=rf->SiLF_id;
					rawBid=rf->SiLB_id;

					rawF_Emax=rf->SiLF_Emax;
					rawB_Emax=rf->SiLB_Emax;
				}
				else if(side=="right"){
					rawFid=rf->SiRF_id;
					rawBid=rf->SiRB_id;

					rawF_Emax=rf->SiRF_Emax;
					rawB_Emax=rf->SiRB_Emax;
				}else{}

				//cout<<rawFid<<" "<<rawBid<<" "<<rawTarget_X<<" "<<rawTarget_Y<<endl;
				if(rawFid==fid&&rawBid==bid&&rawF_Emax>5000&&rawB_Emax>5000){
				//if(rawFid==fid&&rawBid==bid&&sqrt((rawTarget_X+2.13)*(rawTarget_X+2.13)+(rawTarget_Y+1.6)*(rawTarget_Y+1.6))<13&&rawF_Emax>5000&&rawB_Emax>5000){
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
				//cout<<BDC1_X<<" "<<Target_X<<endl;
				tree->Fill();
				
				}
			}


			
		}
		void closeFile(){
			rf->closeFile();
			tree->Write();
			outputFile->Close();
		}

};

class DrawTrajectory{

	const static double zMin=-50;
	const static double zMax=50;

	const static double yMin=-50;
	const static double yMax=50;

	const static double xMin=-7000;
	const static double xMax=-3000;


	public:
	TFile *inputFile;
	TTree *tree;
	TString side;
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
		TPolyLine3D *l[10000];


		// PolyLine
		TPolyMarker3D *p;


		DrawTrajectory(int fid,int bid,int runnum){

			inputFile=new TFile(Form("pixel%d_%d_run%d.root",fid,bid,runnum),"READ");
			tree=(TTree*)inputFile->Get("tree");
			setBranch();
			//fillPolyLine();
		}

		DrawTrajectory(int fid,int bid,TString s,int runnum){

			side=s;
			if(s=="left") inputFile=new TFile(Form("lpixel%d_%d_run%d.root",fid,bid,runnum),"READ");
			if(s=="right") inputFile=new TFile(Form("rpixel%d_%d_run%d.root",fid,bid,runnum),"READ");
			tree=(TTree*)inputFile->Get("tree");
			setBranch();
			//fillPolyLine();
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
		void drawPolyLine(){
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

			for (int i = 0; i <n;i++){

				l[i] = new TPolyLine3D(2);
				tree->GetEntry(i);

				if(isnan(BDC1_X)||isnan(BDC1_Y)||isnan(BDC2_X)||isnan(BDC2_Y)) { cout<<"points"<<endl;continue;}
			
				TVector3* vBDC1 = new TVector3;
				TVector3* vBDC2 = new TVector3;
				TVector3* vTarget = new TVector3;
				TVector3* vVirtual = new TVector3;

				vBDC1->SetXYZ(BDC1_X,BDC1_Y,BDC1_Z);
				vBDC2->SetXYZ(BDC2_X,BDC2_Y,BDC2_Z);
				vTarget->SetXYZ(Target_X,Target_Y,Target_Z);

				
				TVector3 *u1= new TVector3;
                                (*u1)=((*vBDC2)-(*vBDC1)).Unit();
				(*vVirtual)=(*vBDC1)+4000*(*u1);

			//	l[i]->SetPoint(0,BDC1_X,BDC1_Y,BDC1_Z);
			//	l[i]->SetPoint(1,BDC2_X,BDC2_Y,BDC2_Z);
			//	l[i]->SetPoint(2,Target_X,Target_Y,Target_Z);
			//	l[i]->SetPoint(3,vVirtual->X(),vVirtual->Y(),vVirtual->Z());
			//
				l[i]->SetPoint(0,BDC1_Z,BDC1_X,BDC1_Y);
				l[i]->SetPoint(1,BDC2_Z,BDC2_X,BDC2_Y);
				l[i]->SetPoint(2,Target_Z,Target_X,Target_Y);
				l[i]->SetPoint(3,vVirtual->Z(),vVirtual->X(),vVirtual->Y());
				//cout<<BDC1_X<<" "<<BDC1_Y<<" "<<BDC1_Z<<endl;
				//cout<<vVirtual->Z()<<" "<<vVirtual->X()<<" "<<vVirtual->Y()<<endl;



				l[i]->SetLineColor(kBlue);
				l[i]->Draw();

			}

		}


		void drawIntersectPoint(){
			// 1. define plane
			// 2. get loop of line
			// 3. inside loop, calculate intersect points
			// 4. draw 3D points



			TCanvas *cMarker3D=new TCanvas("cMarker3D","cMarker3D");
			cMarker3D->cd();

			TCanvas *cProjection=new TCanvas("Projection2D","Projection2D");
			TH2D *hProjection=new TH2D("hProjection","hProjection",500,-50,50,500,-50,50);

			TH3D *hdummy = new TH3D("hdummy", "", 2, xMin, xMax, 2, yMin, yMax, 2, zMin, zMax);
			hdummy->GetXaxis()->SetRangeUser(xMin, xMax);
			hdummy->GetYaxis()->SetRangeUser(yMin, yMax);
			hdummy->GetZaxis()->SetRangeUser(zMin, zMax);
			hdummy->SetLineColor(kWhite);
			hdummy->Draw();


			const static double leftPlane[4]={0.147,0.004,0.989,3820.259};
			const static double rightPlane[4]={-0.154,-0.002,0.988,3816.409};


			double planeVector[3];
			double planePoint[3];
			planePoint[0]=0;
			planePoint[1]=0;

			if(side=="left"){
				planeVector[0]=leftPlane[0];
				planeVector[1]=leftPlane[1];
				planeVector[2]=leftPlane[2];
				planePoint[2]=-leftPlane[3]/leftPlane[2];
			}else{
				planeVector[0]=rightPlane[0];
				planeVector[1]=rightPlane[1];
				planeVector[2]=rightPlane[2];
				planePoint[2]=-rightPlane[3]/rightPlane[2];
			}

			int n=tree->GetEntries();

			p=new TPolyMarker3D[n];
			cout<<"We got "<<n<<" lines to calculate intersection"<<endl;
			for (int i = 0; i <n;i++){

				tree->GetEntry(i);
			
				TVector3* vBDC1 = new TVector3;
				TVector3* vBDC2 = new TVector3;
				TVector3* vTarget = new TVector3;
				TVector3* vVirtual = new TVector3;

				vBDC1->SetXYZ(BDC1_X,BDC1_Y,BDC1_Z);
				vBDC2->SetXYZ(BDC2_X,BDC2_Y,BDC2_Z);
				vTarget->SetXYZ(Target_X,Target_Y,Target_Z);

				TVector3 *u1= new TVector3;
                                (*u1)=((*vBDC2)-(*vBDC1)).Unit();

				double lineVector[3];
				double linePoint[3];
				lineVector[0]=u1->X();
				lineVector[1]=u1->Y();
				lineVector[2]=u1->Z();
				linePoint[0]=BDC1_X;
				linePoint[1]=BDC1_Y;
				linePoint[2]=BDC1_Z;

				double vVirtualPoint[3];
				calPlaneLineIntersectPoint(vVirtualPoint,planeVector,planePoint,lineVector,linePoint);
				vVirtual->SetX(vVirtualPoint[0]);
				vVirtual->SetY(vVirtualPoint[1]);
				vVirtual->SetZ(vVirtualPoint[2]);
				p->SetPoint(i,vVirtualPoint[2],vVirtualPoint[0],vVirtualPoint[1]);
				hProjection->Fill(vVirtualPoint[0],vVirtualPoint[1]);

			}
			p->SetMarkerSize(1);
			p->SetMarkerColor(1);
			//p->SetMarkerStyle(8);
			p->Draw();
			
			cProjection->cd();
			hProjection->Draw("colz");



		}	
		//double[] calPlaneLineIntersectPoint(double[] planeVector, double[] planePoint, double[] lineVector, double[] linePoint){  
		void calPlaneLineIntersectPoint(double *returnResult,double *planeVector, double *planePoint, double *lineVector, double *linePoint){  
			double vp1, vp2, vp3, n1, n2, n3, v1, v2, v3, m1, m2, m3, t,vpt;  
			vp1 = planeVector[0];  
			vp2 = planeVector[1];  
			vp3 = planeVector[2];  
			n1 = planePoint[0];  
			n2 = planePoint[1];  
			n3 = planePoint[2];  
			v1 = lineVector[0];  
			v2 = lineVector[1];  
			v3 = lineVector[2];  
			m1 = linePoint[0];  
			m2 = linePoint[1];  
			m3 = linePoint[2];  
			vpt = v1 * vp1 + v2 * vp2 + v3 * vp3;  
			//首先判断直线是否与平面平行  
			if (vpt == 0)  
			{  
				cout<<"Plane Parallel, not good!"<<endl;
			}  
			else  
			{  
				t = ((n1 - m1) * vp1 + (n2 - m2) * vp2 + (n3 - m3) * vp3) / vpt;  
				returnResult[0] = m1 + v1 * t;  
				returnResult[1] = m2 + v2 * t;  
				returnResult[2] = m3 + v3 * t;  
			}  
		}  

};
bool isFileExist(int fid,int bid,int runnum){

	TFile *outputFile=new TFile(Form("pixel%d_%d_run%d.root",fid,bid,runnum),"READ");
	return outputFile->IsOpen();
}
int Draw_trajectory(){
	//cout<<isFileExist(24,31,595)<<endl;
	int fid=16;
	int bid=31;
	TString side="right";
	int runnum=600;

//	new GenerateFile(fid,bid,runnum);
//	new DrawTrajectory(fid,bid,runnum);

      //new GenerateFile(fid,bid,side,runnum);

	DrawTrajectory *dt=new DrawTrajectory(fid,bid,side,runnum);
	//dt->drawPolyLine();
	dt->drawIntersectPoint();
	
	return 1;
}

int main(){
	return Draw_trajectory();
}

