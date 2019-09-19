class ReadPed{
	private:
		const static int angleNo = 7;
		const static int barNo = 14;

		TString inputName;
		double naiPed[14][7];
		double *naiEnergy;
	public:
		ReadPed(TString input){ 
			inputName = input;
			setNaiEnergy();
		}
		void setNaiEnergy(){
			naiEnergy = new double[7];
			naiEnergy[0]=79.9403;
			naiEnergy[1]=73.4824;
			naiEnergy[2]=67.1986;
			naiEnergy[3]=61.0854;
			naiEnergy[4]=55.1392;
			naiEnergy[5]=49.3552;
			naiEnergy[6]=43.7227;
		}
		void init(){
			for (int i = 0; i < barNo; ++i) {
				for (int j = 0; j < angleNo; ++j) {
					naiPed[i][j] = -1;
				}
			}
		}
		void load(){

			init();
			ifstream in;
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int barID;
			double ped[7];
			double gain[7];
			double gainError[7];
			while(1){
				in >>side>>barID>>ped[0]>>gain[0]>>gainError[0]>>ped[1]>>gain[1]>>gainError[1]>>ped[2]>>gain[2]>>gainError[2]>>ped[3]>>gain[3]>>gainError[3]>>ped[4]>>gain[4]>>gainError[4]>>ped[5]>>gain[5]>>gainError[5]>>ped[6]>>gain[6]>>gainError[6];
				if(!in.good()) break;
				for (int i = 0; i < angleNo; ++i) {

					naiPed[side*7+barID][i] = ped[i];

				}
			}
		}
		void print(){
			for (int i = 0; i < angleNo; ++i) {
				cout<<naiEnergy[i]<<endl;
			}
			for (int i = 0; i < barNo; ++i) {
				for (int j = 0; j < angleNo; ++j) {
					cout<<i/7<<":"<<i%7<<":"<<naiPed[i][j]<<endl;	
				}
			}
		}
		double * getNaiEnergy(){
			return naiEnergy;
		}
		double * getNaiPed(int id){
			return naiPed[id];
		}
};
class DrawGraph{
	private:
		TGraph *gr;
		TF1 *fit;
	public:
		DrawGraph(){}
		~DrawGraph(){}
		DrawGraph(double *ped,double *energy){
			gr = new TGraph(7,ped,energy);
			fit = new TF1("fit","[0]*x+[1]*x*x+[2]*x*x*x");
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
		}
		void print(){
			double p0 = fit->GetParameter(0);                     
			double p1 = fit->GetParameter(1); 
			double p2 = fit->GetParameter(2); 
			cout<<p0<<"\t"<<p1<<"\t"<<p2<<endl;
		}

};
class DrawPedEnergy{
	private:
		ReadPed *inputPed;
		DrawGraph *dg[14];
		TCanvas *cDraw;
	public:
		DrawPedEnergy(){}
		DrawPedEnergy(ReadPed *input){ 
			inputPed = input;
			setDrawPad();
		}
		~DrawPedEnergy(){}
		void setDrawPad(){
			cDraw = new TCanvas("cDraw;","cDraw;",1200,900);
			cDraw->Divide(4,4);
		}
		void draw(){

			double *naiEnergy = inputPed->getNaiEnergy();
			double *naiPed[14];
			for (int i = 0; i < 14; ++i) {
				naiPed[i] = inputPed->getNaiPed(i);
				if(i<7) cDraw->cd(i+1);
				else cDraw->cd(i+2);
				dg[i] = new DrawGraph(naiPed[i],naiEnergy);
			}
		}
		void print(){
			for (int i = 0; i < 14; ++i) {
				cout<<i/7<<"\t"<<i%7<<"\t";
				dg[i]->print();
			}
		}
};
void drawNaiPedEnergy(){
	TString inputText = "naiPedAngle.txt";
	ReadPed *rp = new ReadPed(inputText);
	rp->load();
	rp->print();
	DrawPedEnergy *dpe = new DrawPedEnergy(rp);
	dpe->draw();
	dpe->print();
}
