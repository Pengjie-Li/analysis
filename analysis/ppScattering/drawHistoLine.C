class ReadFile{
	private:
		TString inputName;
		ifstream in;
		vector<double> fragA;
		vector<double> fragQ;
		vector<double> resA;
		vector<double> resQ;

	public:
		ReadFile(TString inputName):inputName(inputName){
			load();
			//print();
		}
		void load(){
			cout<<"Opening "<<inputName<<endl;
			in.open(inputName);
			double fragAngle;
			double fragEnergy;
			double residualAngle;
			double residualEnergy;
			while(1){
				if(!in.good()) break;
				in>>fragAngle>>fragEnergy>>residualAngle>>residualEnergy;
				//cout<<fragAngle<<":"<<fragEnergy<<":"<<residualAngle<<":"<<residualEnergy<<endl;
				fragQ.push_back(fragEnergy);
				fragA.push_back(fragAngle);
				resQ.push_back(residualEnergy);
				resA.push_back(residualAngle);
			}
		}
		void print(){
			for (int i = 0; i < fragQ.size(); ++i) {
				
				cout<<fragA[i]<<":"<<fragQ[i]<<":"<<resA[i]<<":"<<resQ[i]<<endl;
			}
		}
		vector<double> getFragAngle(){
			return fragA;
		}
		vector<double> getFragEnergy(){
			return fragQ;
		}
		vector<double> getResAngle(){
			return resA;
		}
		vector<double> getResEnergy(){
			return resQ;
		}


};
class DefineGraph{
	private:
		ReadFile *inputFile;
		TGraph *gr;
		vector<double> xArray;
		vector<double> yArray;
	public:
		DefineGraph(ReadFile *inputFile):inputFile(inputFile){
			cout<<"In the code, you need to define xArray and yArray from Frag or Res"<<endl;
		}
		void selectXArray(int id){// id = 1, Frag; id = 0, Res
			xArray = id?inputFile->getFragAngle():inputFile->getResAngle();
		}
		void selectYArray(int id){// id = 1, Res; id = 0, Res
			yArray = id?inputFile->getFragEnergy():inputFile->getResEnergy();
		}
		void defineGraph(){
			gr = new TGraph(xArray.size(),&xArray[0],&yArray[0]);
		}
		void draw(){
			setPlotStyle();
			gr->Draw("same");
			//gr->Draw("alsame");
		}
		void setPlotStyle(){
			gr->SetTitle("14Be(p,p)14Be Elastic scattering");
			gr->GetXaxis()->SetTitle("Proton Theta lab(deg)");
			gr->GetYaxis()->SetTitle("Proton Energy(MeV)");
			gr->GetXaxis()->SetRange(400,810);
			gr->SetMinimum(0);
			gr->SetMaximum(150);

			gr->SetLineColor(2);
			gr->SetLineWidth(2);
		}
		void setLineStyle(int color,int width,int style){
			//gr->SetLineColor(2);
			gr->SetLineColor(color);
			gr->SetLineWidth(width);
			gr->SetLineStyle(style);
		}
		void scaleY(double factor){
			for (int i = 0; i < yArray.size(); ++i){
				yArray[i] *= factor;	
				//cout<<factor<<endl;
			}
		}
		TGraph* getTGraph(){
			return gr;
		}

};
void drawProtonCurve(){
	TString fileName = "Be10_150_ec_.txt";
	ReadFile *readFile = new ReadFile(fileName);
	DefineGraph *dg = new DefineGraph(readFile);
	dg->selectXArray(0);// id =1 , Res; id = 0, Res
	dg->selectYArray(0);// id =1 , Res; id = 0, Res
	dg->scaleY(0.9);
	dg->defineGraph();

	dg->setLineStyle(2,3,1);
	dg->draw();
}


void drawHistoLine(){
	TFile *g =new TFile("ppBe10Histo.root","read");
	TCanvas *cPad = new TCanvas("ppBe10L","ppBe10L",1400,900);
	cPad->Divide(4,2);
	TH2F *h[8];
        TString hName[8];
        hName[0] = "h";
        hName[1] = "hP";
        hName[2] = "hT";
        hName[3] = "hPT";
        hName[4] = "hB";
        hName[5] = "hBPT";
        hName[6] = "hH";
        hName[7] = "hBPTH";

	for (int i = 0; i < 8; ++i) {

		cPad->cd(i+1);
		h[i] =(TH2F *)gDirectory->Get(hName[i]);
		h[i]->Draw("colz");
		drawProtonCurve();
	}
}
