//#include "PositionESPRI.h"
class EspriEvent{
	private:

		int naiNHit;
		int hitIdArray[5];
		int naiId;

		MergeESPRI *calibData;
		double espriPlasE;
		double espriNaiE;
		double espriEnergy;
		double espriAngle;
		TVector3 *espriPosition;
		TVector3 *targetPosition;
		TVector3 *vBeam;
		PositionESPRI *positionESPRI;
	public:
		void print(){
			if(naiId !=-1){
				cout<<"ESPRI Event:"<<endl;
				cout<<"naiNHit = "<<naiNHit<<" naiId = "<<endl;
				cout<<"dE = "<<espriPlasE<<" E ="<<espriNaiE<<" TotalE = "<<espriEnergy<<endl;
				cout<<"Angle = "<<espriAngle<<endl;
				espriPosition->Print();
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
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}
		void init(){

			naiNHit = 0;
			for (int i = 0; i < 5; ++i) {
				hitIdArray[i] = -1;
			}
			naiId = -1;

			espriPlasE= NAN;
			espriNaiE= NAN;
			espriEnergy = NAN;
			espriAngle = NAN;
			espriPosition->SetXYZ(NAN,NAN,NAN);
		}
		void setOutputBranch(TTree *tree){

			espriPosition = new TVector3;

			tree->Branch("naiNHit",&naiNHit,"naiNHit/I");
			tree->Branch("naiHitIdArray",&hitIdArray,"hitIdArray[naiNHit]/I");
			tree->Branch("naiId",&naiId,"naiId/I");

			tree->Branch("espriPlasE",&espriPlasE,"espriPlasE/D");
			tree->Branch("espriNaiE",&espriNaiE,"espriNaiE/D");
			tree->Branch("espriEnergy",&espriEnergy,"espriEnergy/D");
			tree->Branch("espriAngle",&espriAngle,"espriAngle/D");
			tree->Branch("espriPosition","TVector3",&espriPosition);
		}
		void setESPRIEvent(){
			init();
			selectGoodEvent();
			if(naiId!=-1){
				setESPRIEnergy();
				setESPRIAngle();
			}
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
		void setESPRIAngle(){
			//loadPos
			setESPRIPosition();
			espriAngle = ((*espriPosition)-(*targetPosition)).Angle((*vBeam))*TMath::RadToDeg();
			//cout<<espriAngle<<endl;
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
		void setESPRIPosition(){
			double dcX = getRdcX(naiId);
			double dcY = getRdcY(naiId);
			int sideLR = (naiId > 6)? 1: 0;
			//cout<<sideLR<<":"<<dcX<<":"<<dcY<<endl;
			if(dcX>0&&dcY>0){
				(*espriPosition) = positionESPRI->getESPRIPosition(sideLR,dcX,dcY);
				//espriPosition->Print();
			}
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

};

