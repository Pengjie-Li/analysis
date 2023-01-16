class EnergyShift{
	private:
		double protonEnergy_m1;
		double protonEnergy_z1;
		double protonEnergy_z5;
		double protonEnergy_1;
		double protonEnergy_2;

		double alphaEnergy_m1;
		double alphaEnergy_z1;
		double alphaEnergy_z5;
		double alphaEnergy_1;
		double alphaEnergy_2;

	public:
		EnergyShift(){}
		~EnergyShift(){}
		void init(){
			protonEnergy_z1 = NAN;
			protonEnergy_z5 = NAN;
			protonEnergy_1  = NAN;
			protonEnergy_2  = NAN;
			protonEnergy_m1 = NAN;

			alphaEnergy_z1 = NAN;
			alphaEnergy_z5 = NAN;
			alphaEnergy_1  = NAN;
			alphaEnergy_2  = NAN;
			alphaEnergy_m1 = NAN;
	
		}
		void shiftProton(double protonEnergy){
			
			protonEnergy_z1 = protonEnergy*(1.001);
			protonEnergy_z5 = protonEnergy*(1.005);
			protonEnergy_1  = protonEnergy*(1.01);
			protonEnergy_2  = protonEnergy*(1.02);
			protonEnergy_m1 = protonEnergy*(0.99);
		}
		void shiftAlpha(double alphaEnergy){
			alphaEnergy_z1 = alphaEnergy*(1.001);
			alphaEnergy_z5 = alphaEnergy*(1.005);
			alphaEnergy_1  = alphaEnergy*(1.01);
			alphaEnergy_2  = alphaEnergy*(1.02);
			alphaEnergy_m1 = alphaEnergy*(0.99);
	
		}
		void setBranch(TTree* tree){
			tree->Branch("protonEnergy_m1",&protonEnergy_m1,"protonEnergy_m1/D");
			tree->Branch("protonEnergy_z1",&protonEnergy_z1,"protonEnergy_z1/D");
			tree->Branch("protonEnergy_z5",&protonEnergy_z5,"protonEnergy_z5/D");
			tree->Branch("protonEnergy_1",&protonEnergy_1,"protonEnergy_1/D");
			tree->Branch("protonEnergy_2",&protonEnergy_2,"protonEnergy_2/D");

			tree->Branch("alphaEnergy_m1",&alphaEnergy_m1,"alphaEnergy_m1/D");
			tree->Branch("alphaEnergy_z1",&alphaEnergy_z1,"alphaEnergy_z1/D");
			tree->Branch("alphaEnergy_z5",&alphaEnergy_z5,"alphaEnergy_z5/D");
			tree->Branch("alphaEnergy_1",&alphaEnergy_1,"alphaEnergy_1/D");
			tree->Branch("alphaEnergy_2",&alphaEnergy_2,"alphaEnergy_2/D");

		}
};
