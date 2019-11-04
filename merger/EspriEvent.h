//#include "PositionESPRI.h"
class CheckEspriEvent{
	private:
		MergeESPRI *calibData;

		int isEspriLR;
		int isEspriPlas;
		int isEspriRdc;

		double dcX;
		double dcY;
		double plasE;
		int naiNHit;
		int naiBarId;
		double naiE; // no considering multiHit on Nai

		double getRdcX(int side){
			return calibData->getRdcX(side);
		}
		double getRdcY(int side){
			return calibData->getRdcY(side);
		}
		double getPlasQ(int side){
			return calibData->getPlasQ(side);
		}
		double getPlasT(int side){
			return calibData->getPlasT(side);
		}
		bool isRdc(int side){
			if(getRdcX(side)>0&&getRdcY(side)>0) return true;
			else return false;
		}
		bool isPlas(int side){
			if(getPlasQ(side)>0.1) return true; // set PlasQ>100KeV
			if(getPlasT(side)>-700&&getPlasT(side)<-500) return true;
			return false;
		}
		int checkLR(bool isESPRIL,bool isESPRIR){
			if(isESPRIL &&!isESPRIR) return 0; 
			else if(!isESPRIL&&isESPRIR) return 1;
			else if(isESPRIL&&isESPRIR){
				cout<<"Left and Right both give effective Hit, check this event"<<endl;
				return 2;
			}
			else return -1;
		}
		void isESPRILR(){
			bool	isESPRIL=false;
			bool	isESPRIR=false;
			bool isRdcL = isRdc(0);
			bool isRdcR = isRdc(1);
			bool isPlasL = isPlas(0);
			bool isPlasR = isPlas(1);

			if(isRdcL&&isPlasL){
				isESPRIL = true;
			}
			if(isRdcR&&isPlasR){
				isESPRIR = true;
			}
			isEspriLR = checkLR(isESPRIL,isESPRIR);
			if(isEspriLR !=-1){
				isEspriRdc = isRdc(isEspriLR);
				isEspriPlas = isPlas(isEspriLR);
			}
			
		//	cout<<"isRdcL:"<<isRdcL<<" isPlasL:"<<isPlasL<<" isESPRIL:"<<isESPRIL<<endl;
		//	cout<<"isRdcR:"<<isRdcR<<" isPlasR:"<<isPlasR<<" isESPRIR:"<<isESPRIR<<endl;
		//	cout<<"isEspriLR:"<<isEspriLR<<endl;
		}
		double getNaiBarQCal(int side,int id){
			return calibData->getNaiBarQCal(side,id);
		}
		void findNaiBarId(){

			for (int i = 0; i < 7; ++i) {
				if(getNaiBarQCal(isEspriLR,i)>1.0){
					naiNHit++;
					naiBarId = i;
				}
			}
		}

		void init(){

			calibData = NULL;
			isEspriLR = -1;
			isEspriRdc = -1;
			isEspriPlas = -1;
			naiNHit = 0;
			naiBarId = -1;
		}


	public:
		CheckEspriEvent(){}
		~CheckEspriEvent(){}
		void setBranch(TTree *tree){

			tree->Branch("isEspriLR",&isEspriLR,"isEspriLR/I");
			tree->Branch("isEspriRdc",&isEspriRdc,"isEspriRdc/I");
			tree->Branch("isEspriPlas",&isEspriPlas,"isEspriPlas/I");
			tree->Branch("naiBarId",&naiBarId,"naiBarId/I");
			tree->Branch("naiNHit",&naiNHit,"naiNHit/I");
		}
		void checkData(MergeESPRI *mergeData){
			init();
			calibData = mergeData;
			isESPRILR();	
			findNaiBarId();
		}
		bool isGoodEvent(){
			if(isEspriLR ==0||isEspriLR ==1) return true;
			else return false;
		}
		int getNaiId(){
			return naiBarId;
		}
		int getSideLR(){
			return isEspriLR;
		}
		void print(){
			cout<<"isEspriRdc = "<<isEspriRdc<<" isEspriPlas = "<<isEspriPlas<<" isEspriLR = "<<isEspriLR<<endl;
			cout<<"naiNHit = "<<naiNHit<<" naiBarId = "<<naiBarId<<endl;
		}


};
class EspriEvent{
	private:


		MergeESPRI *calibData;
		double espriPlasT;
		double espriPlasE;
		double espriNaiE;
		double espriEnergy;

		PositionESPRI *positionESPRI;
		CheckEspriEvent *checkESPRI;
	public:
		void print(){
			if(goodEvent()){
			cout<<"ESPRI Event:"<<endl;
			checkESPRI->print();
			cout<<"espriPlasT = "<<espriPlasT<<endl;
			cout<<"espriPlasE = "<<espriPlasE<<" espriNaiE = "<<espriNaiE<<" espriEnergy = "<<espriEnergy<<endl;
			//positionESPRI->print();
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
		void setESPRIPosition(){
			positionESPRI->loadEvent(checkESPRI);
			//positionESPRI->analysis();
		}

};

