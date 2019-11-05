#include "PositionESPRI.h"
class EspriEvent{
	private:


		MergeESPRI *calibData;
		double espriPlasT;
		double espriPlasE;
		double espriNaiE;
		double espriEnergy;

		PositionESPRI *positionESPRI;
		CheckEspriEvent *checkESPRI;

		// intermediate var
		TVector3 *targetPosition;
		TVector3 *vBeam;
		
	public:
		void print(){
			if(goodEvent()){
			cout<<"ESPRI Event:"<<endl;
			//checkESPRI->print();
			//cout<<"espriPlasT = "<<espriPlasT<<endl;
			//cout<<"espriPlasE = "<<espriPlasE<<" espriNaiE = "<<espriNaiE<<" espriEnergy = "<<espriEnergy<<endl;
			positionESPRI->print();
			}

		}
		EspriEvent(){
			checkESPRI = new CheckEspriEvent();
			positionESPRI = new PositionESPRI();
		}
		~EspriEvent(){
			delete positionESPRI;
		}
		void checkData(MergeESPRI *mergeESPRI){
			calibData = NULL;
			calibData = mergeESPRI;
			checkESPRI->checkData(mergeESPRI);
		}
		void init(){

			espriPlasT= NAN;
			espriPlasE= NAN;
			espriNaiE= NAN;
			espriEnergy = NAN;
			positionESPRI->init();
		}
		void setOutputBranch(TTree *tree){


			positionESPRI->setBranch(tree);
			checkESPRI->setBranch(tree);
			//tree->Branch("naiNHit",&naiNHit,"naiNHit/I");
			//tree->Branch("naiHitIdArray",&hitIdArray,"hitIdArray[naiNHit]/I");
			//tree->Branch("naiId",&naiId,"naiId/I");

			tree->Branch("espriPlasE",&espriPlasE,"espriPlasE/D");
			tree->Branch("espriPlasT",&espriPlasT,"espriPlasT/D");
			tree->Branch("espriNaiE",&espriNaiE,"espriNaiE/D");
			tree->Branch("espriEnergy",&espriEnergy,"espriEnergy/D");


		}
		void setESPRIEvent(){
			init();
			if(goodEvent()){
				setESPRITime();
				setESPRIEnergy();
				setESPRIPosition();
			}
		}
		bool goodEvent(){
			return checkESPRI->isGoodEvent();
		}
		void setESPRIEnergy(){
			espriPlasE = calibData->getPlasQ(checkESPRI->getSideLR());
			if(checkESPRI->getNaiId()!=-1){ espriNaiE  = calibData->getNaiBarQCal(checkESPRI->getSideLR(),checkESPRI->getNaiId());
				espriEnergy = espriPlasE + espriNaiE;
			}else{
				espriEnergy = espriPlasE;
			}
		}
		void setESPRITime(){
			espriPlasT = calibData->getESPRIPlasTime(checkESPRI->getSideLR());
		}
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}
		void setESPRIPosition(){
			positionESPRI->loadTargetPosition(targetPosition);
			positionESPRI->loadBeamVector(vBeam);
			
			positionESPRI->loadEvent(checkESPRI);
			//positionESPRI->loadData(calibData);
			positionESPRI->analysis();
		}

};

