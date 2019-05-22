#include "PositionESPRI.h"
class MergeESPRI:public Convert{
	private:
		// Analysis of ESPRI 
		int isLR;
		int isESPRIL;
		int isRdcL;
		int isNaiL;
		int isPlasL;

		int isESPRIR;
		int isRdcR;
		int isNaiR;
		int isPlasR;
		PositionESPRI *positionESPRI;



		//Declaration of leaves types
		Int_t           EventNumber;
		Int_t           RunNumber;
		vector<int>     *rdcTDC;
		vector<int>     *rdcPlaneID;
		vector<int>     *rdcWireID;
		vector<int>     *rdcPlaneNHit;
		Int_t           naiQRaw[4][7];
		Int_t           plasQRaw[4];
		Int_t           plasTRaw[4];
		Int_t           plasTimeRef;
		Int_t           rdcMult;
		Double_t        rdcX[2];
		Double_t        rdcY[2];
		Double_t        rdcA[2];
		Double_t        rdcB[2];
		Double_t        rdcChi2[2];
		Double_t        rdcDL[2][7];
		Double_t        rdcTch[2][7];
		Double_t        rdcRes[2][7];
		Double_t        naiQCal[4][7];
		Double_t        naiQ[2][7];
		Double_t        naiQL;
		Double_t        naiQR;
		Double_t        naiQLId;
		Double_t        naiQRId;
		Double_t        plasQCal[4];
		Double_t        plasTCal[4];
		Double_t        plasQL;
		Double_t        plasQR;
		Double_t        plasTL;
		Double_t        plasTR;

	public:

		MergeESPRI(int run){
			env = new TEnv("configMerger.prm");
			detector = "ESPRI";
			treeName = "CalTreeESPRI";
			runNumber = run;
			positionESPRI = new PositionESPRI();
		}
		void init(){
		}
		void setBranch(){

			// when you have vector in your tree
			rdcTDC		= 0;
			rdcPlaneID	= 0;
			rdcWireID	= 0;
			rdcPlaneNHit	= 0;

			// Set branch addresses.
			inputTree->SetBranchAddress("EventNumber",&EventNumber);
			inputTree->SetBranchAddress("RunNumber",&RunNumber);
			inputTree->SetBranchAddress("rdcTDC",&rdcTDC);
			inputTree->SetBranchAddress("rdcPlaneID",&rdcPlaneID);
			inputTree->SetBranchAddress("rdcWireID",&rdcWireID);
			inputTree->SetBranchAddress("rdcPlaneNHit",&rdcPlaneNHit);
			inputTree->SetBranchAddress("naiQRaw",naiQRaw);
			inputTree->SetBranchAddress("plasQRaw",plasQRaw);
			inputTree->SetBranchAddress("plasTRaw",plasTRaw);
			inputTree->SetBranchAddress("plasTimeRef",&plasTimeRef);
			inputTree->SetBranchAddress("rdcMult",&rdcMult);
			inputTree->SetBranchAddress("rdcX",rdcX);
			inputTree->SetBranchAddress("rdcY",rdcY);
			inputTree->SetBranchAddress("rdcA",rdcA);
			inputTree->SetBranchAddress("rdcB",rdcB);
			inputTree->SetBranchAddress("rdcChi2",rdcChi2);
			inputTree->SetBranchAddress("rdcDL",rdcDL);
			inputTree->SetBranchAddress("rdcTch",rdcTch);
			inputTree->SetBranchAddress("rdcRes",rdcRes);
			inputTree->SetBranchAddress("naiQCal",naiQCal);
			inputTree->SetBranchAddress("naiQ",naiQ);
			inputTree->SetBranchAddress("naiQL",&naiQL);
			inputTree->SetBranchAddress("naiQR",&naiQR);
			inputTree->SetBranchAddress("naiIdQL",&naiQLId);
			inputTree->SetBranchAddress("naiIdQR",&naiQRId);
			inputTree->SetBranchAddress("plasQCal",plasQCal);
			inputTree->SetBranchAddress("plasTCal",plasTCal);
			inputTree->SetBranchAddress("plasQL",&plasQL);
			inputTree->SetBranchAddress("plasQR",&plasQR);
			inputTree->SetBranchAddress("plasTL",&plasTL);
			inputTree->SetBranchAddress("plasTR",&plasTR);

		}
		void setOutputBranch(TTree *tree){
			tree->Branch("isLR",&isLR,"isLR/I");
			tree->Branch("isESPRIL",&isESPRIL,"isESPRIL/I");
			tree->Branch("isESPRIR",&isESPRIR,"isESPRIR/I");
			// Set branch addresses.
			tree->Branch("EventNumber",&EventNumber);
			tree->Branch("RunNumber",&RunNumber);
			tree->Branch("rdcTDC",&rdcTDC);
			tree->Branch("rdcPlaneID",&rdcPlaneID);
			tree->Branch("rdcWireID",&rdcWireID);
			tree->Branch("rdcPlaneNHit",&rdcPlaneNHit);
			tree->Branch("naiQRaw",naiQRaw,"naiQRaw[4][7]/I");
			tree->Branch("plasQRaw",plasQRaw);
			tree->Branch("plasTRaw",plasTRaw);
			tree->Branch("plasTimeRef",&plasTimeRef);
			tree->Branch("rdcMult",&rdcMult);
			tree->Branch("rdcX",rdcX);
			tree->Branch("rdcY",rdcY);
			tree->Branch("rdcA",rdcA);
			tree->Branch("rdcB",rdcB);
			tree->Branch("rdcChi2",rdcChi2);
			tree->Branch("rdcDL",rdcDL,"rdcDL[2][7]/D");
			tree->Branch("rdcTch",rdcTch,"rdcTch[2][7]/D");
			tree->Branch("rdcRes",rdcRes,"rdcRes[2][7]/D");
			tree->Branch("naiQCal",naiQCal,"naiQCal[4][7]/D");
			tree->Branch("naiQ",naiQ,"naiQ[2][7]/D");
			tree->Branch("naiQL",&naiQL);
			tree->Branch("naiQR",&naiQR);
			tree->Branch("naiIdQL",&naiQLId);
			tree->Branch("naiIdQR",&naiQRId);
			tree->Branch("plasQCal",plasQCal);
			tree->Branch("plasTCal",plasTCal);
			tree->Branch("plasQL",&plasQL);
			tree->Branch("plasQR",&plasQR);
			tree->Branch("plasTL",&plasTL);
			tree->Branch("plasTR",&plasTR);

		}
		void selfAnalysis(){
			isESPRILR();
		}
		void isESPRILR(){
			isLR=isRdcL=isRdcR=isPlasL=isPlasR=isNaiL=isNaiR = -1;
			isESPRIL=isESPRIR=-1;
			if(rdcX[0]>0&&rdcY[0]>0) isRdcL = 1;
			if(rdcX[1]>0&&rdcY[1]>0) isRdcR = 1;
			if(plasQL>0&&plasTL!=0) isPlasL = 1;
			if(plasQR>0&&plasTR!=0) isPlasR = 1;
			if(naiQL>0) isNaiL = 1;
			if(naiQR>0) isNaiR = 1;

			if(isRdcL==1){
				if(isNaiL ==1||isPlasL ==1){
					isESPRIL =1;
				}else{
					isESPRIL = -1;
				}
			}
			if(isRdcR==1){
				if(isNaiR ==1||isPlasR ==1){
					isESPRIR =1;
				}else{
					isESPRIR = -1;
				}
			}
			
			if(isESPRIL==1 &&isESPRIR ==-1) isLR = 0;
			else if(isESPRIL==-1 &&isESPRIR ==1) isLR = 1;
			else if(isESPRIL==1 &&isESPRIR ==1) isLR = largerEnergySide();
			else isLR = -1;

		}
		int largerEnergySide(){
			// compare E total
			if(naiQL>naiQR) return 0;
			else return 1;
		}
		TVector3 getESPRIPosition(){
			if(isLR>=0){
				//cout<<"isLR="<<isLR<<":"<<rdcX[isLR]<<":"<<rdcY[isLR]<<endl;
				TVector3 result = getESPRIPosition(isLR,rdcX[isLR],rdcY[isLR]);
				//result.Print();
				return getESPRIPosition(isLR,rdcX[isLR],rdcY[isLR]);
			}else{
				TVector3 result; result.SetXYZ(0,0,0);
				return result;
			}
		}
		TVector3 getESPRIPosition(int lr,double X,double Y){
			return positionESPRI->getESPRIPosition(lr,X,Y);
		}
		double getESPRINaiEnergy(){
			return isLR>0?naiQR:naiQL;
		}
		double getESPRIPlasTime(){
			return isLR>0?plasTR:plasTL;
		}
		double getESPRIPlasDeltaE(){
			return isLR>0?plasQR:plasQL;
		}
		~MergeESPRI(){
			delete positionESPRI;
		}
};
