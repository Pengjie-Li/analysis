class CsiInput{
	private:
		vector<vector<double>> csiQPed;
		vector<vector<double>> csiQPedSigma;
		vector<vector<double>> csiQPedEnergy;
		
	public:
		CsiInput(){
			csiQPed.resize(7);	
			csiQPedSigma.resize(7);	
			csiQPedEnergy.resize(7);	

			TString inputName = "txt/peak5CsiCalibInput.txt";
			ifstream in;
			in.open(inputName);
			int caseId;
			double hQPed[7];
			double hQPedSigma[7];
			double hQPedEnergy;
	
			while (1){
				if(!in.good()) break;
				in>>caseId>>hQPedEnergy;
				for (int i = 0; i < 7; ++i) {
					in>>hQPed[i]>>hQPedSigma[i];
				}
				if(caseId != 0) continue;
				for (int i = 0; i < 7; ++i){

					if(hQPed[i]!=-9999){
						csiQPed[i].push_back(hQPed[i]);
						csiQPedSigma[i].push_back(hQPedSigma[i]);
						csiQPedEnergy[i].push_back(hQPedEnergy);
					}
				}
			}
		}
		~CsiInput(){}
		void print(){
			for (int i = 0; i < csiQPed.size(); ++i) {
				for (int j = 0; j < csiQPed[i].size(); ++j) {

					cout<<i<<"\t"<<csiQPedEnergy[i][j]<<"\t"<<csiQPed[i][j]<<"\t"<<csiQPedSigma[i][j]<<"\t"<<endl;
				}
			}
		}
		vector<double> getQPed(int csiId){
			return csiQPed[csiId];
		}
		vector<double> getEnergy(int csiId){
			return csiQPedEnergy[csiId];
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
			
			vector<double> qPed;
			vector<double> energy;
			qPed = csiInput->getQPed(csiId);
			energy = csiInput->getEnergy(csiId);
			
			qPed.push_back(0);
			energy.push_back(0);
			TGraph *gr = new TGraph(qPed.size(),&qPed[0],&energy[0]);
			//fitFunction->SetParameters(csiInput->getQPedAlign(teleSide),0);
			//gr->Fit(fitFunction,"Q");
			fitFunction->SetParameters(0.29,0.01);
			gr->Draw("ap*");
			gr->Fit(fitFunction,"Q");
			cout<<fitFunction->GetParameter(0)<<"\t"<<fitFunction->GetParameter(1)<<endl;
			//fitFunction->Draw("same");
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
			TCanvas *cPad = new TCanvas("cPad","cPad",1500,900);
			cPad->Divide(4,2);
			for (int i = 0; i < 7; ++i) {
				cPad->cd(i+1);
				csiFit->fit(i);// Left
			}
		}
		~CsiCalib(){}
};
void csiCalib(){
	CsiCalib *csiAlign = new CsiCalib();	
	csiAlign->calib();
	//csiAlign->output();
}
