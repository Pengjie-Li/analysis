class CsiInput{
	private:
		double csiQPed[2][2];
		double csiQPedSigma[2][2];
		double csiQPedEnergy[2][2];
		
	public:
		CsiInput(){
			TString inputName = "teleCsiCalibInput.txt";
			ifstream in;
			in.open(inputName);
			int csiId;
			double hQPed;
			double hQPedSigma;
			double hQPedEnergy;
			double lQPed;
			double lQPedSigma;
			double lQPedEnergy;
	
			while (1){
				in>>csiId>>hQPed>>hQPedSigma>>hQPedEnergy>>lQPed>>lQPedSigma>>lQPedEnergy;
				if(!in.good()) break;
				csiQPed[csiId][0] = hQPed;
				csiQPed[csiId][1] = lQPed;

				csiQPedSigma[csiId][0] = hQPedSigma;
				csiQPedSigma[csiId][1] = lQPedSigma;
				csiQPedEnergy[csiId][0] = hQPedEnergy;
				csiQPedEnergy[csiId][1] = lQPedEnergy;

			}
		}
		~CsiInput(){}
		void print(){
			for (int i = 0; i < 2; ++i) {
				cout<<i<<"\t"<<csiQPed[0][i]<<"\t"<<csiQPed[1][i]<<"\t"<<csiQPedSigma[0][i]<<"\t"<<csiQPedSigma[1][i]<<"\t"<<csiQPedEnergy[0][i]<<"\t"<<csiQPedEnergy[1][i]<<endl;
			}
		}
		double getHQPed(int teleSide){
			return csiQPed[teleSide][0];
		}
		double getLQPed(int teleSide){
			return csiQPed[teleSide][1];
		}
		double getHEnergy(int teleSide){
			return csiQPedEnergy[teleSide][0];
		}
		double getLEnergy(int teleSide){
			return csiQPedEnergy[teleSide][1];
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
		void fit(int teleSide){
			double a[3] = {0};
			double b[3] = {0};
			a[0] = b[0] = 0;
			a[1] = csiInput->getHEnergy(teleSide);
			a[2] = csiInput->getLEnergy(teleSide);
			b[1] = csiInput->getHQPed(teleSide);
			b[2] = csiInput->getLQPed(teleSide);
			
			cout<<a[0]<<":"<<a[1]<<":"<<a[2]<<endl;
			cout<<b[0]<<":"<<b[1]<<":"<<b[2]<<endl;
			TGraph *gr = new TGraph(3,b,a);
			//fitFunction->SetParameters(csiInput->getQPedAlign(teleSide),0);
			//gr->Fit(fitFunction,"Q");
			gr->Draw("apl*");
			gr->Fit(fitFunction);
			cout<<fitFunction->GetParameter(0)<<"\t"<<fitFunction->GetParameter(1)<<endl;
		}
		
};
class CsiCalib{
	private:
		CsiFit *csiFit;
	public:
		CsiCalib(){
			csiFit = new CsiFit();
		}
		void calib(){
			csiFit->fit(0);// Left
			csiFit->fit(1);// Right
		}
		~CsiCalib(){}
};
void csiCalib(){
	CsiCalib *csiAlign = new CsiCalib();	
	csiAlign->calib();
	//csiAlign->output();
}
