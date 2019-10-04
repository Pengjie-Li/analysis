class CsiInput{
	private:
		double csiQPed[2][7];
		double csiQPedSigma[2][7];
		double csiQPedAlign[2][7];
		
	public:
		CsiInput(){
			TString inputName = "csiAlphaRunQPed.txt";
			ifstream in;
			in.open(inputName);
			int csiId;
			double hQPed;
			double hQPedSigma;
			double hQPedAlign;
			double lQPed;
			double lQPedSigma;
			double lQPedAlign;
	
			while (1){
				in>>csiId>>hQPed>>hQPedSigma>>hQPedAlign>>lQPed>>lQPedSigma>>lQPedAlign;
				if(!in.good()) break;
				csiQPed[0][csiId] = hQPed;
				csiQPed[1][csiId] = lQPed;

				csiQPedSigma[0][csiId] = hQPedSigma;
				csiQPedSigma[1][csiId] = lQPedSigma;
				csiQPedAlign[0][csiId] = hQPedAlign;
				csiQPedAlign[1][csiId] = lQPedAlign;

			}
		}
		~CsiInput(){}
		void print(){
			for (int i = 0; i < 7; ++i) {
				cout<<i<<"\t"<<csiQPed[0][i]<<"\t"<<csiQPed[1][i]<<"\t"<<csiQPedSigma[0][i]<<"\t"<<csiQPedSigma[1][i]<<"\t"<<csiQPedAlign[0][i]<<"\t"<<csiQPedAlign[1][i]<<endl;
			}
		}
		double getNormHQPed(int csiId){
			if(csiId>3) return csiQPed[0][4];
			else return csiQPed[0][2];
		}
		double getNormLQPed(int csiId){
			if(csiId>3) return csiQPed[1][4];
			else return csiQPed[1][2];
		}
		double getHQPed(int csiId){
			return csiQPed[0][csiId];
		}
		double getLQPed(int csiId){
			return csiQPed[1][csiId];
		}
		double getQPedAlign(int csiId){
			return csiQPedAlign[0][csiId];
		}


};
class CsiFit{
	private:
		CsiInput *csiInput;
		TF1 *fitFunction;
	public:
		CsiFit(){
			csiInput = new CsiInput();
			csiInput->print();
			fitFunction = new TF1("fit","[0]*x/(1+[1]*x)",0,3000);

		}
		~CsiFit(){}
		void fit(int csiId){
			double a[3] = {0};
			double b[3] = {0};
			a[0] = b[0] = 0;
			a[1] = csiInput->getNormHQPed(csiId);
			a[2] = csiInput->getNormLQPed(csiId);
			b[1] = csiInput->getHQPed(csiId);
			b[2] = csiInput->getLQPed(csiId);
			
			TGraph *gr = new TGraph(3,b,a);
			fitFunction->SetParameters(csiInput->getQPedAlign(csiId),0);
			gr->Fit(fitFunction,"Q");
			cout<<fitFunction->GetParameter(0)<<"\t"<<fitFunction->GetParameter(1)<<endl;
		}
		
};
class CsiAlign{
	private:
		CsiFit *csiFit;
	public:
		CsiAlign(){
			csiFit = new CsiFit();

		}
		void analysing(){
			for (int i = 0; i < 7; ++i) {
				csiFit->fit(i);	
			}
		}
		void output(){
		}
		~CsiAlign(){}
};
void csiAlignment(){
	CsiAlign *csiAlign = new CsiAlign();	
	csiAlign->analysing();
	//csiAlign->output();
}
