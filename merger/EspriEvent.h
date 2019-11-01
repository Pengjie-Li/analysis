//#include "PositionESPRI.h"
class EspriEvent{
	private:

		int naiNHit;
		int hitIdArray[5];
		int naiId;

		MergeESPRI *calibData;
		double espriPlasT;
		double espriPlasE;
		double espriNaiE;
		double espriEnergy;

		PositionESPRI *positionESPRI;
	public:
		void print(){
			if(naiId !=-1){
				cout<<"ESPRI Event:"<<endl;
				cout<<"naiNHit = "<<naiNHit<<" naiId = "<<endl;
				cout<<"T = "<<espriPlasT<<endl;
				cout<<"dE = "<<espriPlasE<<" E ="<<espriNaiE<<" TotalE = "<<espriEnergy<<endl;
				positionESPRI->print();
			}

		}
		EspriEvent(){
			positionESPRI = new PositionESPRI();
		}
		~EspriEvent(){
			delete positionESPRI;
		}
		void loadData(MergeESPRI *mergeESPRI){
			calibData = mergeESPRI;
		}
		void init(){

			naiNHit = 0;
			for (int i = 0; i < 5; ++i) {
				hitIdArray[i] = -1;
			}
			naiId = -1;

			espriPlasT= NAN;
			espriPlasE= NAN;
			espriNaiE= NAN;
			espriEnergy = NAN;
		}
		void setOutputBranch(TTree *tree){


			positionESPRI->setBranch(tree);
			tree->Branch("naiNHit",&naiNHit,"naiNHit/I");
			tree->Branch("naiHitIdArray",&hitIdArray,"hitIdArray[naiNHit]/I");
			tree->Branch("naiId",&naiId,"naiId/I");

			tree->Branch("espriPlasE",&espriPlasE,"espriPlasE/D");
			tree->Branch("espriPlasT",&espriPlasT,"espriPlasT/D");
			tree->Branch("espriNaiE",&espriNaiE,"espriNaiE/D");
			tree->Branch("espriEnergy",&espriEnergy,"espriEnergy/D");


		}
		void setESPRIEvent(){
			init();
			selectGoodEvent();
			//if(naiId!=-1){ // don't consider loew energy proton
			//}
			setESPRIEnergy();
			setESPRIPosition();
			setESPRITime();

		}
		void selectGoodEvent(){
			findNaiMultHit();
			deterimineNaiId();
		}
		void setESPRIEnergy(){
			espriPlasE = getPlasBarQCal((int)naiId/7);
			espriNaiE = getNaiBarQCal(naiId);
			espriEnergy = espriPlasE + espriNaiE;
		}
		void setESPRITime(){
			espriPlasT = calibData->getESPRIPlasTime();
		}
		void setESPRIPosition(){
			positionESPRI->loadTargetPosition();
			positionESPRI->loadBeamVector();
			positionESPRI->analysis();
		}
		void findNaiMultHit(){
			for (int i = 0; i < 14; ++i) {
				//cout<<getNaiBarQCal(i)<<endl;
				if(getNaiBarQCal(i)>1&&getPlasBarQCal((int)i/7)>0.5){
					hitIdArray[naiNHit] = i;
					naiNHit++; 
				}
			}
			if(naiNHit>3) cout<<naiNHit<<endl;
			//cout<<naiNHit<<endl;
		}
		void deterimineNaiId(){
			if(naiNHit == 1){
				naiId = hitIdArray[0];
			}

			if(naiNHit > 1){
				for (int i = 0; i < naiNHit; ++i) {
					if(checkNaiRange(i)&&checkRdcHit(i)) naiId = hitIdArray[i];
				}
				if(naiId == -1) naiId = hitIdArray[0];
			}
			//cout<<"naiNHit = "<<naiNHit<<" naiId = "<<naiId<<endl;
		}
		bool checkNaiRange(int iHit){
			int barId = hitIdArray[iHit];
			if(getNaiBarQCal(barId)<150&&getNaiBarQCal(barId)>5) return true; 
			return false;
		}
		bool checkRdcHit(int iHit){
			int barId = hitIdArray[iHit];
			if(getRdcX(barId)>0&&getRdcY(barId)>0) return true;
			else return false;
		}
		double getNaiBarQCal(int i){
			int side = i/7;
			int id = i%7;
			return calibData->getNaiBarQCal(side,id);
		}
		double getPlasBarQCal(int i){
			return calibData->getPlasBarQCal(i);
		}
		double getRdcX(int i){
			return calibData->getRdcX((int)i/7);
		}
		double getRdcY(int i){
			return calibData->getRdcY((int)i/7);
		}

			double dcX = getRdcX(naiId);
			double dcY = getRdcY(naiId);
			int sideLR = (naiId > 6)? 1: 0;
			//cout<<sideLR<<":"<<dcX<<":"<<dcY<<endl;
	
};

