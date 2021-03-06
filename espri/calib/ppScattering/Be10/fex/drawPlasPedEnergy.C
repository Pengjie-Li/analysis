class ReadPed{
	private:
		const static int angleNo = 8;
		const static int barNo = 2;

		TString inputName;
		double plasPed[barNo][angleNo];
		double *plasEnergy;
	public:
		ReadPed(TString input){ 
			inputName = input;
			setPlasEnergy();
		}
		void setPlasEnergy(){
			plasEnergy = new double[angleNo];
						
			plasEnergy[0]=3.4988;
			plasEnergy[1]=3.7215;
			plasEnergy[2]=3.9755;
			plasEnergy[3]=4.2673;
			plasEnergy[4]=4.6046;
			plasEnergy[5]=4.9948;
			plasEnergy[6]=5.4516;

			plasEnergy[7]=19.8774;

		}
		void init(){
			for (int i = 0; i < barNo; ++i) {
				for (int j = 0; j < angleNo; ++j) {
					plasPed[i][j] = -1;
				}
			}
		}
		void load(){

			init();
			ifstream in;
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			double ped[7];
			double gain[7];
			double gainError[7];
			while(1){
				in >>side>>ped[0]>>gain[0]>>gainError[0]>>ped[1]>>gain[1]>>gainError[1]>>ped[2]>>gain[2]>>gainError[2]>>ped[3]>>gain[3]>>gainError[3]>>ped[4]>>gain[4]>>gainError[4]>>ped[5]>>gain[5]>>gainError[5]>>ped[6]>>gain[6]>>gainError[6];
				if(!in.good()) break;
				for (int i = 0; i < angleNo-1; ++i) {
					plasPed[side][i] = ped[i];
					//cout<<ped[i]<<endl;
				}
			}

		// v1
		//	plasPed[0][7] = 3298.806;
		//	plasPed[1][7] = 2590.814;
		// v2
	//		plasPed[0][7] = 3340;
	//		plasPed[1][7] = 2630;
		// v3
			plasPed[0][7] = 3390;
			plasPed[1][7] = 2650;




		}
		void print(){
			for (int i = 0; i < angleNo; ++i) {
				cout<<plasEnergy[i]<<endl;
			}
			for (int i = 0; i < barNo; ++i) {
				for (int j = 0; j < angleNo; ++j) {
					cout<<i<<":"<<plasPed[i][j]<<endl;	
				}
			}
		}
		double * getPlasEnergy(){
			return plasEnergy;
		}
		double * getPlasPed(int id){
			return plasPed[id];
		}
};
Double_t fitExp(Double_t *x,Double_t *par){
	Double_t fitVal = par[0]*(TMath::Exp(par[1]*x[0])-1);
	return fitVal;
}
class DrawGraph{
	private:
		TGraph *gr;
		TF1 *fit;
	public:
		DrawGraph(){}
		~DrawGraph(){}
		DrawGraph(double *ped,double *energy){
			gr = new TGraph(sizeof(ped),ped,energy);
			//fit = new TF1("fit","[0]*x+[1]*x*x+[2]*x*x*x");
			fit = new TF1("fit","x/([0]+[1]*x)");
			//fit = new TF1("fit",fitExp,0,4000,2);
			//fit->SetParameters(1,0.001);
			setPlotStyle();
			gr->Draw("ap");
			//gr->Fit(fit,"Q");
			gr->Fit(fit);

		}
		void setPlotStyle(){
			gr->SetTitle("Energy vs Ped");
			gr->GetXaxis()->SetTitle("ADC(ch)");
			gr->GetYaxis()->SetTitle("Energy(MeV)");
			gr->SetMarkerStyle(5);
			gr->SetMarkerSize(3);
			gr->SetMarkerColor(1);
			gr->GetXaxis()->SetLimits(0,4000);
			gr->GetYaxis()->SetRangeUser(0,40);
		}
		void print(){
			double p0 = fit->GetParameter(0);                     
			double p1 = fit->GetParameter(1); 
			//cout<<p0<<"\t"<<p1<<"\t"<<fit->GetX(20,2000,3500)<<endl;
			cout<<p0<<"\t"<<p1<<"\t"<<endl;
		}

};
class DrawPedEnergy{
	private:

		const static int barNo = 2;
		ReadPed *inputPed;
		DrawGraph *dg[barNo];
		TCanvas *cDraw;
	public:
		DrawPedEnergy(){}
		DrawPedEnergy(ReadPed *input){ 
			inputPed = input;
			setDrawPad();
		}
		~DrawPedEnergy(){}
		void setDrawPad(){
			cDraw = new TCanvas("cDraw","cDraw",1600,900);
			cDraw->Divide(2,1);
		}
		void draw(){

			double *plasEnergy = inputPed->getPlasEnergy();
			double *plasPed[barNo];
			for (int i = 0; i < barNo; ++i) {
				cDraw->cd(i+1);
				plasPed[i] = inputPed->getPlasPed(i);
				dg[i] = new DrawGraph(plasPed[i],plasEnergy);
			}
		}
		void print(){
			for (int i = 0; i < barNo; ++i) {
				cout<<i<<"\t";
				dg[i]->print();
			}
		}
};
void drawPlasPedEnergy(){
	TString inputText = "plasPedAngle.txt";
	ReadPed *rp = new ReadPed(inputText);
	rp->load();
	rp->print();
	DrawPedEnergy *dpe = new DrawPedEnergy(rp);
	dpe->draw();
	dpe->print();
}
