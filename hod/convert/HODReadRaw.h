class PlasticRaw{
	private:
	public:
		int ID;
		int timeUpRaw ;
		int timeDownRaw ;
		int energyUpRaw ;
		int energyDownRaw;

		PlasticRaw(){
		}
		void initialize(){
			ID            = -1;
			timeUpRaw     = -1;
			timeDownRaw   = -1;
			energyUpRaw   = -1;
			energyDownRaw = -1;
		}
		void print(){
			cout<<"\t ID ="<< ID<<"\t timeUpRaw ="<< timeUpRaw<<"\t timeDownRaw = "<<timeDownRaw<<" \t energyUpRaw = "<<energyUpRaw<<"\t energyDownRaw = "<<energyDownRaw<<endl;

		}
		void load(TArtHODPla *HODPla){
			if(HODPla->GetID()>=1 && HODPla->GetID()<=NUMBER_OF_HOD) { 
				ID = HODPla->GetID();
				//check which HOD fired: HODP:24~40, HODF:24~1
				//define the intraID as 1~40, 1 from the lower momentum side one by one (HODF No.24 as intraID 1)
				//
				if(ID<25){   //HODF
					ID=24-ID; //1~24 			 
				} else {
					ID=64-ID;
				}
				timeUpRaw = HODPla->GetTURaw();
				timeDownRaw = HODPla->GetTDRaw();
				energyUpRaw = HODPla->GetQURaw();
				energyDownRaw = HODPla->GetQDRaw();

			}
		}
		int getID(){
			return ID;

		}
		int getTimeUpRaw(){
			return timeUpRaw;
		}
		int getTimeDownRaw(){
			return timeDownRaw;
		}
		int getEnergyUpRaw(){
			return energyUpRaw;
		}
		int getEnergyDownRaw(){
			return energyDownRaw;
		}
};
class HODPlasticRaw{

	private:
	public:

		int hodNHit;
		int hodTRaw[2][40];
		int hodQRaw[2][40];

		HODPlasticRaw(){
			initialize();
		}
		void setBranch(TTree *tree){
			tree->Branch("hodNHit",&hodNHit,"hodNHit/I");
			tree->Branch("hodTRaw",hodTRaw,"hodTRaw[2][40]/I");
			tree->Branch("hodQRaw",hodQRaw,"hodQRaw[2][40]/I");
		}
		void initialize(){
			hodNHit = 0;
			for (int i = 0; i < 2; ++i) {
				for(int j=0;j<NUMBER_OF_HOD;j++){
					hodTRaw[i][j] = -1;
					hodQRaw[i][j] = -1;
				}
			}
		}
		void readRaw(TClonesArray *HODPlaHit){

			initialize(); // init by function itself
			hodNHit = HODPlaHit->GetEntriesFast();

			//cout<<"HOD Plastic nHit = "<<HODPlaHit->GetEntriesFast()<<endl;
			if(hodNHit != 0)
			{
				PlasticRaw *plastic =new PlasticRaw();
				for(Int_t i=0; i<hodNHit; i++)
				{
					plastic->initialize();
					TArtHODPla *HODPla = (TArtHODPla*)HODPlaHit->At(i);
					plastic->load(HODPla);
					//plastic->print();
					readOneHit(plastic);
				}
				delete plastic;
			}

		}

		void readOneHit(PlasticRaw *plastic){
			int ID = plastic->getID();
			hodTRaw[0][ID] = plastic->getTimeUpRaw();
			hodTRaw[1][ID] = plastic->getTimeDownRaw();
			hodQRaw[0][ID] = plastic->getEnergyUpRaw();
			hodQRaw[1][ID] = plastic->getEnergyDownRaw();


		}
		int getEnergyRaw(int side, int ID){
			return hodQRaw[side][ID];
		}
		int getTimeRaw(int side, int ID){
			return hodTRaw[side][ID];
		}


};

