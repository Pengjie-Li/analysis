//#include "constant.h"
class PlaEvent{
	private:
		MergePLA *plaData;
		Double_t TOF713;
		Double_t Beta713;
		Double_t Gamma713;
		Double_t Ek713;

		Double_t TOF37;
		Double_t Beta37;
		Double_t Gamma37;
		Double_t Ek37;


		void init(){
			/****** Plastics **********/
			TOF713=NAN;
			Beta713=NAN;
			Gamma713=NAN;
			Ek713=NAN;

			TOF37=NAN;
			Beta37=NAN;
			Gamma37=NAN;
			Ek37=NAN;
		}

	public:
		PlaEvent(){}
		~PlaEvent(){}
		void analysing(MergePLA *mergePLA){
			plaData = mergePLA;
			init();
			Double_t Dist_F7F13=36014.1; // mm
			Double_t Dist_F3F7=46976; // mm

			Double_t C_light = 299.792458; // mm/ns

			Double_t AMU = 931.494; // Atomic Mass Unit (MeV/c²)
			if(getF13Time()!=-9999&&getF7Time()!=-9999){
				TOF713=getF13Time() - getF7Time() + 570.387; // 20191016  570.619; // ns //20181025
				Beta713=Dist_F7F13/TOF713/C_light;
				Gamma713=1/sqrt(1-Beta713*Beta713);
				Ek713=(Gamma713-1)*AMU;
			}

			if(getF3Time()!=-9999&&getF7Time()!=-9999){
				TOF37=getF7Time() - getF3Time() + 299.091; // ns
				Beta37=Dist_F3F7/TOF37/C_light;
				Gamma37=1/sqrt(1-Beta37*Beta37);
				Ek37=(Gamma37-1)*AMU;
			}
			//print();

		}
		void setOutputBranch(TTree *tree){

			tree->Branch("TOF37",&TOF37,"TOF37/D");
			tree->Branch("Beta37",&Beta37,"Beta37/D");
			tree->Branch("Gamma37",&Gamma37,"Gamma37/D");
			tree->Branch("Ek37",&Ek37,"Ek37/D");

			tree->Branch("TOF713",&TOF713,"TOF713/D");
			tree->Branch("Beta713",&Beta713,"Beta713/D");
			tree->Branch("Gamma713",&Gamma713,"Gamma713/D");
			tree->Branch("Ek713",&Ek713,"Ek713/D");
		}
		Double_t getF3Time(){
			return plaData->getF3Time();
		}
		Double_t getF7Time(){
			return plaData->getF7Time();
		}
		Double_t getF13Time(){
			return plaData->getF13Time();
		}
		void print(){
			cout<<"PLA Analysed Event:"<<endl;
			cout<<"TOF37  = "<<setw(8)<<TOF37<<" Beta37  = "<<setw(8)<<Beta37<<" Gamma37  = "<<setw(8)<<Gamma37<<" Ek37  = "<<setw(8)<<Ek37<<endl;
			cout<<"TOF713 = "<<setw(8)<<TOF713<<" Beta713 = "<<setw(8)<<Beta713<<" Gamma713 = "<<setw(8)<<Gamma713<<" Ek713 = "<<setw(8)<<Ek713<<endl;
		}

};

