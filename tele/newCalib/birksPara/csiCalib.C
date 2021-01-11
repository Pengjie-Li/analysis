class CsiInput{
	private:
		vector<vector<double>> csiQPed;
		vector<vector<double>> csiQPedSigma;
		vector<vector<double>> csiQPedEnergy;
		vector<vector<double>> csiQPedEnergyErr;

	public:
		CsiInput(){
			csiQPed.resize(7);	
			csiQPedSigma.resize(7);	
			csiQPedEnergy.resize(7);	
			csiQPedEnergyErr.resize(7);	

			TString inputName = "txt/peak5CsiCalibInput.txt";
			ifstream inputFile;
			inputFile.open(inputName);
			int cid;
			double hQPed[2];
			double hQPedSigma[2];
			//double hQPedEnergy[2] = {500.22, 318.27};
			double hQPedEnergy[2] = {499.45, 317.74};
			double hQPedEnergyErr[2] = {0,0 };

			while (1){
				if(!inputFile.good()) break;
				inputFile>>cid>>hQPed[0]>>hQPedSigma[0]>>hQPed[1]>>hQPedSigma[1];

				for (int i = 0; i < 2; ++i) {

					csiQPed[cid].push_back(hQPed[i]);
					csiQPedSigma[cid].push_back(hQPedSigma[i]);
					csiQPedEnergy[cid].push_back(hQPedEnergy[i]);
					csiQPedEnergyErr[cid].push_back(hQPedEnergyErr[i]);

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
		vector<double> getQPedErr(int csiId){
			return csiQPedSigma[csiId];
		}
		vector<double> getEnergyErr(int csiId){
			return csiQPedEnergyErr[csiId];
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
			vector<double> qPedErr;
			vector<double> energy;
			vector<double> energyErr;
			qPed = csiInput->getQPed(csiId);
			qPedErr = csiInput->getQPedErr(csiId);
			energy = csiInput->getEnergy(csiId);
			energyErr = csiInput->getEnergyErr(csiId);

			qPed.push_back(0);
			qPedErr.push_back(0);
			energy.push_back(0);
			energyErr.push_back(0);

			//cout<<qPedErr[0]<<endl;
			TGraphErrors *gr = new TGraphErrors(qPed.size(),&qPed[0],&energy[0],&qPedErr[0],&energyErr[0]);

			fitFunction->SetParameters(0.29,0.01);
			gr->SetTitle(Form("Bar%d",csiId));
			gr->SetMarkerColor(4);
			gr->Draw("AP");
			gr->Fit(fitFunction,"Q");
			gr->Fit(fitFunction,"Q");
			cout<<csiId<<"  "<<fitFunction->GetParameter(0)<<"\t"<<fitFunction->GetParameter(1)<<endl;

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
