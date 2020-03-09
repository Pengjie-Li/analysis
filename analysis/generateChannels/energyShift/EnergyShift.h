class EnergyShift{
	private:
		double protonEnergy_m2;
		double protonEnergy_m4;
		double protonEnergy_m6;
		double protonEnergy_m8;
		double protonEnergy_m10;
		double protonEnergy_p2;
		double protonEnergy_p4;
		double protonEnergy_p6;
		double protonEnergy_p8;
		double protonEnergy_p10;

		double alphaEnergy_m1;
		double alphaEnergy_z1;
		double alphaEnergy_z5;
		double alphaEnergy_1;
		double alphaEnergy_2;

	public:
		EnergyShift(){}
		~EnergyShift(){}
		void init(){
			protonEnergy_m2 = NAN;
			protonEnergy_m4 = NAN;
			protonEnergy_m6 = NAN;
			protonEnergy_m8 = NAN;
			protonEnergy_m10= NAN;

			protonEnergy_p2 = NAN;
			protonEnergy_p4 = NAN;
			protonEnergy_p6 = NAN;
			protonEnergy_p8 = NAN;
			protonEnergy_p10= NAN;

			alphaEnergy_z1 = NAN;
			alphaEnergy_z5 = NAN;
			alphaEnergy_1  = NAN;
			alphaEnergy_2  = NAN;
			alphaEnergy_m1 = NAN;
	
		}
		void shiftProton(double protonEnergy){
			protonEnergy_m2 = protonEnergy*(1-0.002);
			protonEnergy_m4 = protonEnergy*(1-0.004);
			protonEnergy_m6 = protonEnergy*(1-0.006);
			protonEnergy_m8 = protonEnergy*(1-0.008);
			protonEnergy_m10= protonEnergy*(1-0.010);

			protonEnergy_p2 = protonEnergy*(1+0.002);
			protonEnergy_p4 = protonEnergy*(1+0.004);
			protonEnergy_p6 = protonEnergy*(1+0.006);
			protonEnergy_p8 = protonEnergy*(1+0.008);
			protonEnergy_p10= protonEnergy*(1+0.010);

		
		}
		void shiftAlpha(double alphaEnergy){
			alphaEnergy_z1 = alphaEnergy*(1.001);
			alphaEnergy_z5 = alphaEnergy*(1.005);
			alphaEnergy_1  = alphaEnergy*(1.01);
			alphaEnergy_2  = alphaEnergy*(1.02);
			alphaEnergy_m1 = alphaEnergy*(0.99);
	
		}
		void setBranch(TTree* tree){
			tree->Branch("protonEnergy_m2",&protonEnergy_m2,"protonEnergy_m2/D");
			tree->Branch("protonEnergy_m4",&protonEnergy_m4,"protonEnergy_m4/D");
			tree->Branch("protonEnergy_m6",&protonEnergy_m6,"protonEnergy_m6/D");
			tree->Branch("protonEnergy_m8",&protonEnergy_m8,"protonEnergy_m8/D");
			tree->Branch("protonEnergy_m10",&protonEnergy_m10,"protonEnergy_m10/D");


			tree->Branch("protonEnergy_p2",&protonEnergy_p2,"protonEnergy_p2/D");
			tree->Branch("protonEnergy_p4",&protonEnergy_p4,"protonEnergy_p4/D");
			tree->Branch("protonEnergy_p6",&protonEnergy_p6,"protonEnergy_p6/D");
			tree->Branch("protonEnergy_p8",&protonEnergy_p8,"protonEnergy_p8/D");
			tree->Branch("protonEnergy_p10",&protonEnergy_p10,"protonEnergy_p10/D");

		}
};
