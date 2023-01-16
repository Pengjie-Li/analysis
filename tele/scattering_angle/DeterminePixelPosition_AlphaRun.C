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
TEnv *env = new TEnv("configPixelPosition.prm");

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
			A=0;
			B=0;
			C=1;
			D=3850;
			cfid=31;
			cbid=0;
			calBaseVector();
		}

};
class RightPlane: public Plane{
	public:
		RightPlane(){
			A=0;
			B=0;
			C=1;
			D=3850;
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
			inLeft.open("LeftDSSDPixelPosition.txt");
			inRight.open("RightDSSDPixelPosition.txt");

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
			inputname=Form("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/merger/rootfiles/run0%d_analysed.root",runnum);
			openFile();
			setBranch();
		}

		// Open file
		TFile *f;
		TTree *tree;

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


		Double_t SiLF_CAL[32];
		Double_t SiLB_CAL[32];
		Double_t SiRF_CAL[32];
		Double_t SiRB_CAL[32];

		Int_t	multiplicityLF;	
		Int_t	multiplicityLB;	
		Int_t	multiplicityRF;	
		Int_t	multiplicityRB;	


		Double_t CsILL_CAL;
		Double_t CsILRT_CAL;
		Double_t CsILRB_CAL;
		Double_t CsIRLT_CAL;
		Double_t CsIRLB_CAL;
		Double_t CsIRRT_CAL;
		Double_t CsIRRB_CAL;

		Double_t TOF713;
		Double_t F13_Charge;


		void print(){
			tree->Print();
		}
		void openFile(){
			f = new TFile(inputname,"READ");
			tree=(TTree*)f->Get("tree");
		}
		void setBranch(){

			// Set branch addresses.
			tree->SetBranchAddress("RunNumber",&RunNumber);
			tree->SetBranchAddress("EventNumber",&EventNumber);


			tree->SetBranchAddress("Trig_DSB",&Trig_DSB);
			tree->SetBranchAddress("Trig_BxESPRIxTEL",&Trig_BxESPRIxTEL);
			tree->SetBranchAddress("Trig_BxESPRI",&Trig_BxESPRI);
			tree->SetBranchAddress("Trig_BxTEL",&Trig_BxTEL);
			tree->SetBranchAddress("Trig_BxHODP",&Trig_BxHODP);
			tree->SetBranchAddress("Trig_BxHODF",&Trig_BxHODF);
			tree->SetBranchAddress("Trig_BxNEBULA",&Trig_BxNEBULA);

			tree->SetBranchAddress("BDC1_X",&BDC1_X);
			tree->SetBranchAddress("BDC1_Y",&BDC1_Y);

			tree->SetBranchAddress("BDC2_X",&BDC2_X);
			tree->SetBranchAddress("BDC2_Y",&BDC2_Y);

			tree->SetBranchAddress("Target_X",&Target_X);
			tree->SetBranchAddress("Target_Y",&Target_Y);


			tree->SetBranchAddress("FDC0_X",&FDC0_X);
			tree->SetBranchAddress("FDC0_Y",&FDC0_Y);

			tree->SetBranchAddress("multiplicityLF",&multiplicityLF);
			tree->SetBranchAddress("multiplicityLB",&multiplicityLB);
			tree->SetBranchAddress("multiplicityRF",&multiplicityRF);
			tree->SetBranchAddress("multiplicityRB",&multiplicityRB);

			tree->SetBranchAddress("SiLF_CAL",&SiLF_CAL);
			tree->SetBranchAddress("SiLB_CAL",&SiLB_CAL);
			tree->SetBranchAddress("SiRF_CAL",&SiRF_CAL);
			tree->SetBranchAddress("SiRB_CAL",&SiRB_CAL);


			tree->SetBranchAddress("F13_Charge",&F13_Charge);
			tree->SetBranchAddress("TOF713",&TOF713);

			tree->SetBranchAddress("CsILL_CAL",&CsILL_CAL);
			tree->SetBranchAddress("CsILRT_CAL",&CsILRT_CAL);
			tree->SetBranchAddress("CsILRB_CAL",&CsILRB_CAL);
			tree->SetBranchAddress("CsIRRT_CAL",&CsIRRT_CAL);
			tree->SetBranchAddress("CsIRRB_CAL",&CsIRRB_CAL);
			tree->SetBranchAddress("CsIRLT_CAL",&CsIRLT_CAL);
			tree->SetBranchAddress("CsIRLB_CAL",&CsIRLB_CAL);


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

class PixelPosition{
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

		Double_t Target_X;
		Double_t Target_Y;
		Double_t Target_Z;

		Double_t siEnergyFront;
		Double_t siEnergyBack;

		Double_t TOF713;
		Double_t F13_Charge;

		Int_t	multiplicityLF;	
		Int_t	multiplicityLB;	
		Int_t	multiplicityRF;	
		Int_t	multiplicityRB;	


		Double_t CsILL_CAL;
		Double_t CsILRT_CAL;
		Double_t CsILRB_CAL;
		Double_t CsIRLT_CAL;
		Double_t CsIRLB_CAL;
		Double_t CsIRRT_CAL;
		Double_t CsIRRB_CAL;



		PixelPosition(int par1,int par2,int par3,int par4,int par5){
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

		PixelPosition(){
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
			if(isLR == 0) outputFile=new TFile(Form("./rootfiles/PixelL%d_%d_run%d.root",fid,bid,runNumber),"recreate");
			else outputFile=new TFile(Form("./rootfiles/PixelR%d_%d_run%d.root",fid,bid,runNumber),"recreate");
			tree=new TTree("tree","tree");
			setBranch();

		}
		void setBranch(){

			tree->Branch("runNumber",&runNumber,"runNumber/I");
			tree->Branch("fid",&fid,"fid/I");
			tree->Branch("bid",&bid,"bid/I");

			tree->Branch("BDC1_X",&BDC1_X,"BDC1_X/D");
			tree->Branch("BDC1_Y",&BDC1_Y,"BDC1_Y/D");
			tree->Branch("BDC1_Z",&BDC1_Z,"BDC1_Z/D");

			tree->Branch("BDC2_X",&BDC2_X,"BDC2_X/D");
			tree->Branch("BDC2_Y",&BDC2_Y,"BDC2_Y/D");
			tree->Branch("BDC2_Z",&BDC2_Z,"BDC2_Z/D");

			tree->Branch("Target_X",&Target_X,"Target_X/D");
			tree->Branch("Target_Y",&Target_Y,"Target_Y/D");
			tree->Branch("Target_Z",&Target_Z,"Target_Z/D");



			tree->Branch("pixelX",&pixelX,"pixelX/D");
			tree->Branch("pixelY",&pixelY,"pixelY/D");
			tree->Branch("pixelZ",&pixelZ,"pixelZ/D");

			tree->Branch("siEnergyFront",&siEnergyFront,"siEnergyFront/D");
			tree->Branch("siEnergyBack",&siEnergyBack,"siEnergyBack/D");

			tree->Branch("F13_Charge",&F13_Charge,"F13_Charge/D");
			tree->Branch("TOF713",&TOF713,"TOF713/D");

			tree->Branch("multiplicityLF",&multiplicityLF,"multiplicityLF/I");
			tree->Branch("multiplicityLB",&multiplicityLB,"multiplicityLB/I");
			tree->Branch("multiplicityRF",&multiplicityRF,"multiplicityRF/I");
			tree->Branch("multiplicityRB",&multiplicityRB,"multiplicityRB/I");


			tree->Branch("CsILL_CAL",&CsILL_CAL);
			tree->Branch("CsILRT_CAL",&CsILRT_CAL);
			tree->Branch("CsILRB_CAL",&CsILRB_CAL);
			tree->Branch("CsIRRT_CAL",&CsIRRT_CAL);
			tree->Branch("CsIRRB_CAL",&CsIRRB_CAL);
			tree->Branch("CsIRLT_CAL",&CsIRLT_CAL);
			tree->Branch("CsIRLB_CAL",&CsIRLB_CAL);



		}

		void eventLoop(){
			Long64_t nentries = rf->tree->GetEntries();
			nentries = (nentries>maxEventNumber)?maxEventNumber:nentries;
			for(Long64_t ientry = 0; ientry< nentries; ientry++){
				rf->tree->GetEntry(ientry);
				setNewDCPosition();
				if(selectGoodPixelEvent()){
					//cout<<"CsI_RLT_E = "<<rf->CsI_RLT_E<<" CsI_RLB_E ="<<rf->CsI_RLB_E<<endl;;
					//cout<<"CsI_LRT_E = "<<rf->CsI_LRT_E<<" CsI_LRB_E ="<<rf->CsI_LRB_E<<endl;;

					getBDC1BDC2Position();
					calDSSDPlaneIntersectPoint();
					tree->Fill();
				}
				if(ientry%10000 ==0) cout<<ientry<<endl;

			}
		}

		void setNewDCPosition(){

			BDC1_X=-rf->BDC1_X;
			BDC1_Y=rf->BDC1_Y;
			BDC1_Z=-6666.11;// later check

			BDC2_X=-rf->BDC2_X;
			BDC2_Y=rf->BDC2_Y;
			BDC2_Z=-5666.67;// later check

			Target_X=-rf->Target_X;
			Target_Y=rf->Target_Y;
			Target_Z=-4222.23;// later check

			TOF713    = rf->TOF713;
			F13_Charge = rf->F13_Charge;

			multiplicityLF = rf->multiplicityLF;
			multiplicityLB = rf->multiplicityLB;
			multiplicityRF = rf->multiplicityRF;
			multiplicityRB = rf->multiplicityRB;

			CsILL_CAL = rf->CsILL_CAL;
			CsILRT_CAL = rf->CsILRT_CAL;
			CsILRB_CAL = rf->CsILRB_CAL;

			CsIRLT_CAL = rf->CsIRLT_CAL;
			CsIRLB_CAL = rf->CsIRLB_CAL;
			CsIRRT_CAL = rf->CsIRRT_CAL;
			CsIRRB_CAL = rf->CsIRRB_CAL;
	
	
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
			//return isSiEnergyGood();
			//return isTrigDSB()&&isSiEnergyGood();
			//return isTrigDSB()&&isSiEnergyGood()&&(!isInsideTargetArea());
			//return isSiEnergyGood()&&isInsideTargetArea();
			//return isTrigDSB()&&isInsideTargetArea();
			return isTrigDSB()&&isSiEnergyGood();
			//return isTrigDSB()&&isSiEnergyGood()&&isCsIEnergyGood();
		}
		bool isTrigDSB(){
			return (rf->Trig_DSB>0);
		}
		bool isSiMultiplicityGood(){
			// DSSD 1 hit
			int fmul = isLR?rf->multiplicityLF:rf->multiplicityRF;	
			int bmul = isLR?rf->multiplicityLB:rf->multiplicityRB;	
			return (fmul ==1)&&(bmul ==1);
		}
		bool isSiEnergyGood(){
			siEnergyFront = isLR?rf->SiRF_CAL[fid]:rf->SiLF_CAL[fid];
			siEnergyBack = isLR?rf->SiRB_CAL[bid]:rf->SiLB_CAL[bid];
			double siEnergy = 0.5*(siEnergyFront+siEnergyBack);
			if(abs(siEnergyFront-siEnergyBack)<3000&&siEnergy>5000){
				//cout<<"front:"<<siEnergyFront<<" back:"<<siEnergyBack<<endl;
				return true;
			}
			else return false;
		}
//		bool isCsIEnergyGood(){
//			double CsIEnergy = -1;
//			if(isLR){
//				CsIEnergy = (rf->CsI_RLT_E>rf->CsI_RLB_E)?rf->CsI_RLT_E:rf->CsI_RLB_E;
//			}else{
//				CsIEnergy = (rf->CsI_LRT_E>rf->CsI_LRB_E)?rf->CsI_LRT_E:rf->CsI_LRB_E;
//			}
//			cout<<"CsI Energy = "<<CsIEnergy<<endl;
//			return (CsIEnergy>200);
//		}
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


int yDeterminePixelPosition(){ //  
	//PixelPosition *pixelPosition = new PixelPosition();
	PixelPosition *pixelPosition[8];
		int isLR = 1;
		int fid = 16;
		int bid = 31;
		int maxEventNumber = 5000000;
		int runNumber[8]={310,312,314,316,318,320,322,324}; // Be10
//		int runNumber[8]={334,335,336,338,339,340,341,342}; // Be12
//		int runNumber[8]={429,430,433,434,435,436,437,438}; // Be14
	//	int runNumber[8]={587,588,589,590,591,592,593,594}; // Be14
//
		for(int i=0;i<1;i++){
			pixelPosition[i] = new PixelPosition(runNumber[i],maxEventNumber,isLR,fid,bid);
		}
	
	return 1;
}
int xDeterminePixelPosition(){ // run 595

	//PixelPosition *pixelPosition = new PixelPosition();
	PixelPosition *pixelPosition[16];
		int isLR = 1;
		int fid = -1;
		int bid = -1;
		int maxEventNumber = 5000000;
//		int runNumber[8]={595,312,314,316,318,320,322,324}; // Be10
//		int runNumber[8]={334,335,336,338,339,340,341,342}; // Be12
//		int runNumber[8]={429,430,433,434,435,436,437,438}; // Be14
	//	int runNumber[8]={587,588,589,590,591,592,593,594}; // Be14
//
		int pixelId =-1;
		for(int i=14;i<18;i++){
		for(int j=28;j<32;j++){
			pixelId++;
			pixelPosition[pixelId] = new PixelPosition(595,maxEventNumber,isLR,i,j);
		}
		}
	
	return 1;

}
int DeterminePixelPosition_AlphaRun(){ //  

	//PixelPosition *pixelPosition = new PixelPosition();
	PixelPosition *pixelPosition[16];
	int isLR = 0;
	int maxEventNumber = 5000000;
	//		int runNumber[8]={595,312,314,316,318,320,322,324}; // Be10
	//		int runNumber[8]={334,335,336,338,339,340,341,342}; // Be12
	//		int runNumber[8]={429,430,433,434,435,436,437,438}; // Be14
	//	int runNumber[8]={587,588,589,590,591,592,593,594}; // Be14
	//
	int runNumber = 599;
	int pixelId =-1;
	for(int i=12;i<19;i++){
		for(int j=12;j<19;j++){
//	for(int i=15;i<16;i++){
//		for(int j=15;j<16;j++){
	
			pixelId++;
			pixelPosition[pixelId] = new PixelPosition(runNumber,maxEventNumber,isLR,i,j);
		}
	}

	return 1;



}
int main(){
	//for(int i=332;i<339;i++) Generate_File(i);
	//return 1;
	//return DeterminePixelPosition();
	//return DeterminePixelPosition();
}

