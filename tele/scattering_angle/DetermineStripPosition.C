/**
 * select a pixel and draw all trajectories through this pixel
 * 1. Read files,
 * 2. select pixel(fid,bid),find BDC position,
 * 3. extrapolation to DSSD plane,get X,Y
 * 4. save into a new rootfile
 */

#include <math.h>
#include <fstream>
#include <TFile.h>
#include <TH3D.h>
#include "TEnv.h"
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
TEnv *env = new TEnv("configStripPosition.prm");

class Plane{
	public:
		double A;
		double B;
		double C;
		double D;
		// corner pixel for calculating base vector
		int cfid;
		int cbid;
		TVector3 e1;
		TVector3 e2;
		TVector3 e3;

		Plane(){};
		Plane(double a,double b,double c,double d){
			A=a;
			B=b;
			C=c;
			D=d;
		}
		double getX(double y,double z){
			return (-B*y-C*z-D)/A;
		}
		double getY(double x,double z){
			return (-A*x-C*z-D)/B;
		}
		double getZ(double x,double y){
			return (-A*x-B*y-D)/C;
		}
		void calBaseVector(){
			e3.SetXYZ(A,B,C);
			e3=e3.Unit();

			e1.SetXYZ(1,0,-e3.X()/e3.Z());
			e1=e1.Unit();
			e2 = e1.Cross(e3);
			if(e2.Y()<0) e2=-e2;
		}
		

};
class LeftPlane: public Plane{
	public:
		LeftPlane(){
			A=-0.147;
			B=0.004;
			C=0.989;
			D=3820.259;
			cfid=31;
			cbid=0;
			calBaseVector();
		}

};
class RightPlane: public Plane{
	public:
		RightPlane(){
			A=0.154;
			B=-0.002;
			C=0.988;
			D=3816.409;
			cfid=31;
			cbid=31;
			calBaseVector();
		}

};
class DSSDPoistion{
	private:
		double Table[2048][6];
	public:
		TVector3 getPoistion(int isLR,int fid,int bid){
			int line=findLine(isLR,fid,bid);
			return TVector3(Table[line][3],Table[line][4],Table[line][5]);
		}
		int findLine(int isLR,int fid,int bid){
			int line=-1;
			for(int i=0;i<2048;i+=1024){
				line=i;
				if(Table[line][0]==isLR){
					for(int j=0;j<1024;j+=32){
						line=i+j;	
						if(Table[line][1]==fid){
							for(int k=0;k<32;k++){
								line=i+j+k;
								if(Table[line][2]==bid) return line;
							}
						}
					}

				}
			}
			return -1;
		}
		DSSDPoistion(){
			readFile();
		}
		void readFile(){
			ifstream inLeft;
			ifstream inRight;
			inLeft.open("LeftDSSDStripPosition.txt");
			inRight.open("RightDSSDStripPosition.txt");

			int line=0;

			int side;
			int fid;
			int bid;
			double  x;
			double  y;
			double z;
			while (1)
			{
				inLeft >>fid>>bid>>x>>y>>z;
				if (!inLeft.good()) break;
				Table[line][0]=0;
				Table[line][1]=fid;
				Table[line][2]=bid;
				Table[line][3]=x;
				Table[line][4]=y;
				Table[line][5]=z;
				line++;
			}
			inLeft.close();
			while (1)
			{
				inRight >>fid>>bid>>x>>y>>z;
				//cout<<x<<" "<<y<<" "<<z<<endl;
				
				if (!inRight.good()) break;
				Table[line][0]=1;
				Table[line][1]=fid;
				Table[line][2]=bid;
				Table[line][3]=x;
				Table[line][4]=y;
				Table[line][5]=z;

				line++;
			}
			inRight.close();

		}

};
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

		Int_t           Trig_DSB;                                                  
		Int_t           Trig_BxESPRIxTEL;                                          
		Int_t           Trig_BxESPRI;                                              
		Int_t           Trig_BxTEL;                                                
		Int_t           Trig_BxHODP;                                               
		Int_t           Trig_BxHODF;                                               
		Int_t           Trig_BxNEBULA;

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



		void print(){
			AnalysisTree->Print();
		}
		void openFile(){
			f = new TFile(inputname,"READ");
			AnalysisTree=(TTree*)f->Get("AnalysisTree");
		}
		void setBranch(){

			// Set branch addresses.
			AnalysisTree->SetBranchAddress("RunNumber",&RunNumber);
			AnalysisTree->SetBranchAddress("EventNumber",&EventNumber);


			AnalysisTree->SetBranchAddress("Trig_DSB",&Trig_DSB);
			AnalysisTree->SetBranchAddress("Trig_BxESPRIxTEL",&Trig_BxESPRIxTEL);
			AnalysisTree->SetBranchAddress("Trig_BxESPRI",&Trig_BxESPRI);
			AnalysisTree->SetBranchAddress("Trig_BxTEL",&Trig_BxTEL);
			AnalysisTree->SetBranchAddress("Trig_BxHODP",&Trig_BxHODP);
			AnalysisTree->SetBranchAddress("Trig_BxHODF",&Trig_BxHODF);
			AnalysisTree->SetBranchAddress("Trig_BxNEBULA",&Trig_BxNEBULA);

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
class GenerateFile{

	public:
		ReadFile *rf;
		DSSDPoistion *dp;
		Plane *pl;
		TVector3 vBDC1;
		TVector3 vdBDC2;
		TVector3 vFDC0;
		TVector3 vDirection;

		TVector3 vDSSD;
		TVector3 vdDSSD;

		
		TFile *outputFile;
		TTree *tree;
		// SetBranch variables
		// Drift Chambers Position
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

		Int_t isLR;
		Int_t fid;
		Int_t bid;
		Double_t pixelX;
		Double_t pixelY;
		Double_t pixelZ;

		Double_t vdDSSDX;
		Double_t vdDSSDY;
		Double_t vdDSSDZ;

		Double_t vDSSDX;
		Double_t vDSSDY;
		Double_t vDSSDZ;


		Double_t siEnergy;
		

		GenerateFile(int runnum){
			dp=new DSSDPoistion();
			rf=new ReadFile(runnum);
			outputFile=new TFile(Form("./rootfiles/Position_Resolution_run%d.root",runnum),"recreate");
			tree=new TTree("tree","tree");
			setBranch();
			loopTree();
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

			
			tree->Branch("isLR",&isLR,"isLR/I");
			tree->Branch("fid",&fid,"fid/I");
			tree->Branch("bid",&bid,"bid/I");

			tree->Branch("pixelX",&pixelX,"pixelX/D");
			tree->Branch("pixelY",&pixelY,"pixelY/D");
			tree->Branch("pixelZ",&pixelZ,"pixelZ/D");

			tree->Branch("vdDSSDX",&vdDSSDX,"vdDSSDX/D");
			tree->Branch("vdDSSDY",&vdDSSDY,"vdDSSDY/D");
			tree->Branch("vdDSSDZ",&vdDSSDZ,"vdDSSDZ/D");

			tree->Branch("vDSSDX",&vDSSDX,"vDSSDX/D");
			tree->Branch("vDSSDY",&vDSSDY,"vDSSDY/D");
			tree->Branch("vDSSDZ",&vDSSDZ,"vDSSDZ/D");

			tree->Branch("siEnergy",&siEnergy,"siEnergy/D");

		}

		void loopTree(){
			Long64_t nentries=rf->AnalysisTree->GetEntries();
			//nentries=10000;

			for (Long64_t ientry=0; ientry<nentries;ientry++) {
				rf->AnalysisTree->GetEntry(ientry);

				if(ientry%1000==0) cout<<ientry<<endl;
				//cout<<ientry<<endl;
				setNewDCPosition();
				setBDC2FromtBDC1AndFDC0();
				if(isDCGood()){
					//printDC();
					setDSSDEvent();
					if(isDSSDGood()){
						//printDSSDEvent();
						setDSSDFromtDC();
						if(isGoodGuess()){
							tree->Fill();
							printAll();
						}
					}
				}

			}


			
		}
		bool isDSSDGood(){
		//左右不分的事件去除
			return (isLR>-1)?true:false;
		}
		bool isDCGood(){
			return (sqrt((dBDC2_Y-BDC2_Y)*(dBDC2_Y-BDC2_Y)+(dBDC2_X-BDC2_X)*(dBDC2_X-BDC2_X))<1)? true:false;	
		}
		void setDSSDFromtDC(){
			// trajectory in DC
			// hit on plane on DSSD
			// get (x,y,z)

			if(isLR==0) pl=new LeftPlane();
			else pl=new RightPlane();


			double planeVector[3];
			double planePoint[3];
			setPlaneVP(planeVector,planePoint);

			double lineVector[3];
			double linePoint[3];
			setLineVP(lineVector,linePoint);

			double vVirtualPoint[3];
			calPlaneLineIntersectPoint(vVirtualPoint,planeVector,planePoint,lineVector,linePoint);
			vdDSSD.SetX(vVirtualPoint[0]);
			vdDSSD.SetY(vVirtualPoint[1]);
			vdDSSD.SetZ(vVirtualPoint[2]);

			vdDSSDX=vdDSSD.X();
			vdDSSDY=vdDSSD.Y();
			vdDSSDZ=vdDSSD.Z();

			// for test use
			 //  vDSSD.SetXYZ(pixelX,pixelY,pixelZ);
			// determine k
			double k=getRatio(BDC1_Z,pixelZ,vDirection.Z());
			vDSSD=vBDC1+k*vDirection;

			vDSSDX=vDSSD.X();
			vDSSDY=vDSSD.Y();
			vDSSDZ=vDSSD.Z();

		}
		bool isGoodGuess(){
			return (abs(vDSSDX-pixelX)<5&&abs(vDSSDY-pixelY)<5)? true:false;
		}

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

		void printDeducedDSSD(){
			cout<<" Deduced DSSD Position from DC: x="<<vdDSSD.X()<<" y="<<vdDSSD.Y()<<" x="<<vdDSSD.Z()<<endl;


		}
		void setLineVP(double *lineVector,double *linePoint){

			lineVector[0]=vDirection.X();
			lineVector[1]=vDirection.Y();
			lineVector[2]=vDirection.Z();
			linePoint[0]=BDC1_X;
			linePoint[1]=BDC1_Y;
			linePoint[2]=BDC1_Z;
		}


		void setPlaneVP(double *planeVector, double *planePoint){

			planePoint[0]=0;
			planePoint[1]=0;
			planePoint[2]=pl->getZ(0,0);

			planeVector[0]=pl->A;
			planeVector[1]=pl->B;
			planeVector[2]=pl->C;

		}
		void printAll(){
			printDC();
			printDSSDEvent();
			//printDeducedDSSD();
			cout<<endl;
		}
		void setDSSDEvent(){
			isLR=-1;
			fid=-1;
			bid=-1;
			pixelX=0;
			pixelY=0;
			pixelZ=0;
			siEnergy=0;
			findPixel();//fid,bid,siEnergy,isLR will be set
			if(isLR>-1){
				TVector3 pixel=dp->getPoistion(isLR,fid,bid);
				pixelX=pixel.X();
				pixelY=pixel.Y();
				pixelZ=pixel.Z();
			}
		}
		void printDSSDEvent(){
			cout<<"isLR="<<isLR<<" fid="<<fid<<" bid="<<bid<<" siEnergy="<<siEnergy<<endl;
			cout<<"Rawfully position from txt file: pixelX="<<pixelX<<" pixelY="<<pixelY<<" pixelZ="<<pixelZ<<endl;
			cout<<"Deduced DSSS from Drift Chamber : x="<<vdDSSD.X()<<" y="<<vdDSSD.Y()<<" z="<<vdDSSD.Z()<<endl;
			cout<<"Test DSSS from Drift Chamber : x="<<vDSSD.X()<<" y="<<vDSSD.Y()<<" z="<<vDSSD.Z()<<endl;
		}
		void findPixel(){
			double SiLF_Emax=3000;
			double SiRF_Emax=3000;
			double SiLB_Emax=3000;
			double SiRB_Emax=3000;

			int SiLF_id=3000;
			int SiRF_id=3000;
			int SiLB_id=3000;
			int SiRB_id=3000;

			for(int i=0;i<32;i++){
				if(rf->SiLF_E[i]>SiLF_Emax){
					SiLF_Emax=rf->SiLF_E[i];		
					SiLF_id=i;		
				}
				if(rf->SiLB_E[i]>SiLB_Emax){
					SiLB_Emax=rf->SiLB_E[i];		
					SiLB_id=i;
				}

				if(rf->SiRF_E[i]>SiRF_Emax){
					SiRF_Emax=rf->SiRF_E[i];		
					SiRF_id=i;		
				}
				if(rf->SiRB_E[i]>SiRB_Emax){
					SiRB_Emax=rf->SiRB_E[i];		
					SiRB_id=i;
				}

			}

			if(SiLF_Emax!=3000&&SiLB_Emax!=3000&&abs(SiLF_Emax-SiLB_Emax)<3000&&SiLF_Emax>SiRF_Emax&&SiLB_Emax>SiRB_Emax){
				siEnergy=0.5*(SiLF_Emax+SiLB_Emax);
				isLR=0;
				fid=SiLF_id;
				bid=SiLB_id;
			}

			if(SiRF_Emax!=3000&&SiRB_Emax!=3000&&abs(SiRF_Emax-SiRB_Emax)<3000&&SiLF_Emax<SiRF_Emax&&SiLB_Emax<SiRB_Emax){
				siEnergy=0.5*(SiRF_Emax+SiRB_Emax);
				isLR=1;
				fid=SiRF_id;
				bid=SiRB_id;
			}

			//if(isLR>-1) cout<<"SiLF_Emax="<<SiLF_Emax<<" SiLB_Emax＝"<<SiLB_Emax<<" SiRF_Emax="<<SiRF_Emax<<" SiRB_Emax="<<SiRB_Emax<<endl;
			//if(isLR>-1) cout<<" isLR="<<isLR<<" fid="<<fid<<" bid="<<bid<<" siEnergy="<<siEnergy<<endl;

		}
		void printDC(){
			cout<<"BDC1_X="<<BDC1_X<<" BDC1_Y="<<BDC1_Y<<" BDC1_Z="<<BDC1_Z<<endl;
			cout<<"Target_X="<<Target_X<<" Target_Y="<<Target_Y<<" Target_Z="<<Target_Z<<endl;
			cout<<"FDC0_X="<<FDC0_X<<" FDC0_Y="<<FDC0_Y<<" FDC0_Z="<<FDC0_Z<<endl;
			cout<<"BDC2_X="<<BDC2_X<<" BDC2_Y="<<BDC2_Y<<" BDC2_Z="<<BDC2_Z<<endl;
			cout<<"dBDC2_X="<<dBDC2_X<<" dBDC2_Y="<<dBDC2_Y<<" dBDC2_Z="<<dBDC2_Z<<endl;
		}

		void setNewDCPosition(){
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
		}
		void setBDC2FromtBDC1AndFDC0(){
			vBDC1.SetXYZ(BDC1_X,BDC1_Y,BDC1_Z);
			vFDC0.SetXYZ(FDC0_X,FDC0_Y,FDC0_Z);
			vDirection=(vFDC0-vBDC1).Unit();
			// determine k
			double k=getRatio(BDC1_Z,BDC2_Z,vDirection.Z());
			vdBDC2=vBDC1+k*vDirection;
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
void testDSSDPosition(){
	DSSDPoistion *dp=new DSSDPoistion();
	TVector3 temp=dp->getPoistion(1,15,26);
	cout<<"this is vector: "<<temp.X()<<" "<<temp.Y()<<" "<<temp.Z()<<" "<<endl;
}
int Generate_File(){
	//GenerateFile *gf=new GenerateFile(333);		
	//GenerateFile *gf=new GenerateFile(334);		
	GenerateFile *gf=new GenerateFile(436);		
	//GenerateFile *gf=new GenerateFile(595);		

	return 1;
}
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
		TVector3 getVector(){
			TVector3 v(X,Y,Z);
			return v;
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

class StripPosition{
	public :
		int runNumber;
		int maxEventNumber;
		int isLR;
		int fid;
		int bid;

		ReadFile *rf;
		TNewBDC1SpacePosition *spBDC1;
		TNewBDC2SpacePosition *spBDC2;
		Plane *DSSDPlane;

		//Output
		TFile *outputFile;
		TTree *tree;
		Double_t BDC1_X;
		Double_t BDC1_Y;
		Double_t BDC1_Z;

		Double_t BDC2_X;
		Double_t BDC2_Y;
		Double_t BDC2_Z;


		double pixelX;
		double pixelY;
		double pixelZ;
	
		StripPosition(int par1,int par2,int par3,int par4,int par5){
			runNumber = par1;
			maxEventNumber =  par2;
			isLR = par3 ;
			fid = par4;
			bid = par5;

			openInputFile();
			createOutput();
			eventLoop();
			saveOutput();
		}

		StripPosition(){
			runNumber = env->GetValue("runNumber",595);
			maxEventNumber = env->GetValue("maxEventNumber",2000);
			isLR = env->GetValue("isLR",-1);
			fid = env->GetValue("fid",15);
			bid = env->GetValue("bid",15);

			openInputFile();
			createOutput();
			eventLoop();
			saveOutput();
		}
		void createOutput(){
			if(isLR == 0) outputFile=new TFile(Form("./rootfiles/StripL%d_%d_run%d.root",fid,bid,runNumber),"recreate");
			else outputFile=new TFile(Form("./rootfiles/StripR%d_%d_run%d.root",fid,bid,runNumber),"recreate");
			tree=new TTree("tree","tree");
			setBranch();

		}
		void setBranch(){

			tree->Branch("BDC1_X",&BDC1_X,"BDC1_X/D");
			tree->Branch("BDC1_Y",&BDC1_Y,"BDC1_Y/D");
			tree->Branch("BDC1_Z",&BDC1_Z,"BDC1_Z/D");

			tree->Branch("BDC2_X",&BDC2_X,"BDC2_X/D");
			tree->Branch("BDC2_Y",&BDC2_Y,"BDC2_Y/D");
			tree->Branch("BDC2_Z",&BDC2_Z,"BDC2_Z/D");

			tree->Branch("pixelX",&pixelX,"pixelX/D");
			tree->Branch("pixelY",&pixelY,"pixelY/D");
			tree->Branch("pixelZ",&pixelZ,"pixelZ/D");
		}

		void eventLoop(){
			Long64_t nentries = rf->AnalysisTree->GetEntries();
			nentries = (nentries>maxEventNumber)?maxEventNumber:nentries;
			for(Long64_t ientry = 0; ientry< nentries; ientry++){
				rf->AnalysisTree->GetEntry(ientry);
				setNewDCPosition();
				if(selectGoodPixelEvent()){
					getBDC1BDC2Position();
					calDSSDPlaneIntersectPoint();
					tree->Fill();
				}

			}
		}

		void setNewDCPosition(){

			BDC1_X=-rf->BDC1_X;
			BDC1_Y=rf->BDC1_Y;
			BDC1_Z=-6666.11;// later check

			BDC2_X=-rf->BDC2_X;
			BDC2_Y=rf->BDC2_Y;
			BDC2_Z=-5666.67;// later check

	
		}
		void openInputFile(){
			rf = new ReadFile(runNumber);
			//rf->print();
		}
		bool selectGoodPixelEvent(){
			/**
			 * is Pixel Si Energy good: E>5MeV
			 * is Inside Target Area
			 * if so, get the BDC1, BDC2
			 */
			return isSiEnergyGood();
			//return isTrigDSB()&&isSiEnergyGood();
			//return isTrigDSB()&&isSiEnergyGood()&&(!isInsideTargetArea());
			//return isSiEnergyGood()&&isInsideTargetArea();
		}
		bool isTrigDSB(){
			return (rf->Trig_DSB>0);
		}
		bool isSiEnergyGood(){
			double siEnergy = -9999;

			if(fid!=-1) siEnergy = isLR?rf->SiRF_E[fid]:rf->SiLF_E[fid];
			if(bid!=-1) siEnergy = isLR?rf->SiRB_E[bid]:rf->SiLB_E[bid];

			if(siEnergy>5000){
				//cout<<"front:"<<frontSiEnergy<<" back:"<<backSiEnergy<<endl;
				return true;
			}
			else return false;
		}
                bool isInsideTargetArea(){
                        return (sqrt((rf->Target_X+2.13)*(rf->Target_X+2.13)+(rf->Target_Y+1.6)*(rf->Target_Y+1.6))<15);
		}
		void getBDC1BDC2Position(){

			//cout<<"This is good event"<<endl;
			spBDC1 = new TNewBDC1SpacePosition();
			spBDC2 = new TNewBDC2SpacePosition();

			spBDC1->setXY(-rf->BDC1_X,rf->BDC1_Y);
			spBDC2->setXY(-rf->BDC2_X,rf->BDC2_Y);
			//spBDC1->print();
			//spBDC2->print();
		}

		void calDSSDPlaneIntersectPoint(){
			if(isLR==0) DSSDPlane=new LeftPlane();
			else DSSDPlane=new RightPlane();

			TVector3 planeVector = getDSSDPlaneVector();
			TVector3 planePoint = getDSSDPlanePoint();
			TVector3 lineVector = getTrajectoryLineVector();
			TVector3 linePoint = getTrajectoryLinePoint();

			TVector3 intersectPoint = calPlaneLineIntersectPoint(planeVector,planePoint,lineVector,linePoint);
			//intersectPoint.Print();
			pixelX = intersectPoint.X();
			pixelY = intersectPoint.Y();
			pixelZ = intersectPoint.Z();
		}
		TVector3 getDSSDPlaneVector(){
			TVector3 vResult;
			vResult.SetXYZ(DSSDPlane->A,DSSDPlane->B,DSSDPlane->C);
			return vResult;
		}
		TVector3 getDSSDPlanePoint(){
			TVector3 vResult;
			vResult.SetXYZ(0,0,DSSDPlane->getZ(0,0));
			return vResult;

		}
		TVector3 getTrajectoryLineVector(){
			TVector3 vBDC1 = spBDC1->getVector();
			TVector3 vBDC2 = spBDC2->getVector();
			TVector3 vResult = vBDC2-vBDC1;
			return vResult;
		}
		TVector3 getTrajectoryLinePoint(){
			return spBDC1->getVector();
		}
		TVector3 calPlaneLineIntersectPoint(TVector3 planeVector,TVector3 planePoint,TVector3 lineVector,TVector3 linePoint){
			double planeVectorArray[3];
			vector2Array(planeVector,planeVectorArray);

			double planePointArray[3];
			vector2Array(planePoint,planePointArray);

			double lineVectorArray[3];
			vector2Array(lineVector,lineVectorArray);

			double linePointArray[3];
			vector2Array(linePoint,linePointArray);

			double returnResult[3];
			calPlaneLineIntersectPoint(returnResult,planeVectorArray,planePointArray,lineVectorArray,linePointArray);
			TVector3 vResult;
			vResult.SetXYZ(returnResult[0],returnResult[1],returnResult[2]);
			return vResult;

		}
		void vector2Array(TVector3 vector,double *array){
			array[0] = vector.X();
			array[1] = vector.Y();
			array[2] = vector.Z();
		}

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

		void saveOutput(){
			tree->Write();
			outputFile->Close();
		}
};
int DetermineStripPosition(){
	//StripPosition *pixelPosition = new StripPosition();
	StripPosition *pixelPosition[8];
		int isLR = 1;
		int fid = -1;
		int bid = 27;
		int maxEventNumber = 5000000;
		int runNumber[8]={310,312,314,316,318,320,322,324};
		for(int i=0;i<8;i++){
			pixelPosition[i] = new StripPosition(runNumber[i],maxEventNumber,isLR,fid,bid);
		}
	
	return 1;
}

int main(){
	//for(int i=332;i<339;i++) Generate_File(i);
	//return 1;
	return DetermineStripPosition();
}

