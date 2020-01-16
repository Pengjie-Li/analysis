class DssdInput{
	private:
		vector<vector<double>> dssdQPed;
		vector<vector<double>> dssdQPedEnergy;
		
	public:
		DssdInput(){
			dssdQPed.resize(4);	
			dssdQPedEnergy.resize(4);	

			TString inputName = "txt/peak5DssdCalibInput.txt";
			ifstream in;
			in.open(inputName);
			int caseId;
			double hQPed[4];
			double hQPedEnergy;
	
			while (1){
				if(!in.good()) break;
				in>>caseId>>hQPedEnergy;
				for (int i = 0; i < 4; ++i) {
					in>>hQPed[i];
				}

				for (int i = 0; i < 4; ++i){

					if(hQPed[i]!=-9999){
						dssdQPed[i].push_back(hQPed[i]);
						dssdQPedEnergy[i].push_back(hQPedEnergy);
					}
				}
			}
		}
		~DssdInput(){}
		void print(){
			for (int i = 0; i < dssdQPed.size(); ++i) {
				for (int j = 0; j < dssdQPed[i].size(); ++j) {

					cout<<i<<"\t"<<dssdQPedEnergy[i][j]<<"\t"<<dssdQPed[i][j]<<"\t"<<endl;
				}
			}
		}
		vector<double> getQPed(int dssdId){
			return dssdQPed[dssdId];
		}
		vector<double> getEnergy(int dssdId){
			return dssdQPedEnergy[dssdId];
		}





};
class DssdFit{
	private:
		DssdInput *dssdInput;
		TF1 *fitFunction;
	public:
		DssdFit(){
			dssdInput = new DssdInput();
			dssdInput->print();
			fitFunction = new TF1("fit","[0]*x/(1+[1]*x)",0,3000);

		}
		~DssdFit(){}
		void fit(int dssdId){
			
			vector<double> qPed;
			vector<double> energy;
			qPed = dssdInput->getQPed(dssdId);
			energy = dssdInput->getEnergy(dssdId);
			
			qPed.push_back(0);
			energy.push_back(0);
			TGraph *gr = new TGraph(qPed.size(),&qPed[0],&energy[0]);
			//fitFunction->SetParameters(dssdInput->getQPedAlign(teleSide),0);
			//gr->Fit(fitFunction,"Q");
			//fitFunction->SetParameters(0.29,0.01);
			gr->Draw("ap*");
			gr->Fit(fitFunction,"Q");
			cout<<fitFunction->GetParameter(0)<<"\t"<<fitFunction->GetParameter(1)<<endl;
			//fitFunction->Draw("same");
		}
		
};
class DssdCalib{
	private:
		DssdFit *dssdFit;
	public:
		DssdCalib(){
			dssdFit = new DssdFit();
		}
		void calib(){
			TCanvas *cPad = new TCanvas("cPad","cPad",1500,900);
			cPad->Divide(2,2);
			for (int i = 0; i < 4; ++i) {
				cPad->cd(i+1);
				dssdFit->fit(i);// Left
			}
		}
		~DssdCalib(){}
};
void dssdCalib(){
	DssdCalib *dssdAlign = new DssdCalib();	
	dssdAlign->calib();
	//dssdAlign->output();
}
