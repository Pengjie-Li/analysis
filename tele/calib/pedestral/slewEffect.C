// define a function with 2 parameters
Double_t fitfunc(Double_t *x,Double_t *par) {

	//cout<<par[0]<<":"<<par[1]<<":"<<par[2]<<endl;
	Double_t fitval = par[0]/TMath::Sqrt(x[0]+400)+par[1];

	return fitval;
}

class SlewCorrection{
	private:
		int runNumber;
		TChain *tree;
		TString timeVar;
		TString energyVar;
		TString drawVar;
		TString hName;
		TString drawRange;
		TString draw;
		TString gate;
		TCanvas *cPad;
		TH2F *hDraw;
		TH2F *hDrawCorr;
		TF1 *fitFunction;
		double fitPara[2];
	public:
		SlewCorrection(){
			tree = new TChain("tree");
			fitFunction = new TF1("fit","pol1",0,4000);
		}
		~SlewCorrection(){}
		void loadChain(int runStart,int runStop){
			for (int i = runStart; i < runStop; ++i) {
				//tree->Add(Form("rootfiles/run0%d_analysed.root_1",i));
				tree->Add(Form("rootfiles/run0%d_analysed.root",i));
			}
		}
		void loadRun(int run){
			runNumber = run;
			loadChain(run,run+1);
		}
		void loadRuns(int runStart,int runStop){
			loadChain(runStart,runStop+1);
		}
		void setCanvas(TString cPadName){
			cPad = new TCanvas(cPadName,cPadName,1400,700);
			cPad->Divide(2,1);
		}
		void setVar(TString t,TString q, TString h){
			timeVar = t;
			energyVar = q;
			hName = h;
			drawVar = timeVar+ ":"+ energyVar + ">>" + hName;
		}
		void setRange(int x1, int x2, int x3, int y1, int y2, int y3){
			int xBin = x1;
			int xMin = x2;
			int xMax = x3;
			int yBin = y1;
			int yMin = y2;
			int yMax = y3;
			drawRange = Form("(%d,%d,%d,%d,%d,%d)",xBin,xMin,xMax,yBin,yMin,yMax);
		}
		void setGate(TString g){
			gate = g;
		}
		void drawBeforeCorrection(){
			cPad->cd(1);
			draw = drawVar + drawRange;
			TString color = "colz";
			tree->Draw(draw,gate,color);
			hDraw = (TH2F*)gDirectory->Get(hName);
			hDraw->Write();
			
			profileX(hDraw);
		}

		void profileX(){
			TProfile *hPDEE = hDraw->ProfileX();
			hPDEE->Draw("same");
			hPDEE->Fit(fitFunction,"Q");
		}
		void profileX(TH2F *hTest){
			TProfile *hPDEE = hTest->ProfileX();
			//hPDEE->SetMarkerColor(2);
			hPDEE->Draw("same");
			//TF1 *fit = new TF1("fit",fitfunc,0,4000,2);	
			//fit->SetParameters(-50,550);

			//fit->Draw("same");
			//hPDEE->Fit(fit);
			//hPDEE->Fit("pol1");
			hPDEE->Fit(fitFunction,"Q");

		}
		void getFitPara(){
			fitFunction->GetParameters(fitPara);
			cout<<"Fit Parameters: "<<fitPara[0]<<":"<<fitPara[1]<<endl;
		}
		void drawAfterCorrection(){
			cPad->cd(2);
			getFitPara();	
			timeVar = timeVar + Form("- %f*",fitPara[1])+energyVar;
			TString hNameCorr = hName  + "After";
			drawVar = timeVar+ ":"+ energyVar + ">>" + hNameCorr ;
			draw = drawVar + drawRange;
			TString color = "colz";
			tree->Draw(draw,gate,color);
			hDrawCorr = (TH2F*)gDirectory->Get(hNameCorr);
			hDrawCorr->Write();
	
			profileX(hDrawCorr);
			//getFitPara();
		}
		double getSlopePara(){
			return fitPara[1];
		}
		void printPNG(){
			TString printName ="./png/"+hName+Form("run%d.png",runNumber);
			cPad->Print(printName);
		}
};
class F3Slew0:public SlewCorrection{
	private:
	public:
		F3Slew0(){
			setCanvas("F30Pad");
			setVar("F3TCal[0]","F3QRaw[0]", "hF3Slew0");
			setRange(500,100,1300,500,540,580);
			//gROOT->ProcessLine(".x rootfiles/cutBe10.C");
			//setGate("Trig_DSB&&Be10");

		}
		~F3Slew0(){}
};

class F3Slew1:public SlewCorrection{
	private:
	public:
		F3Slew1(){
			setCanvas("F31Pad");
			setVar("F3TCal[1]","F3QRaw[1]", "hF3Slew1");
			setRange(500,100,1300,500,540,580);
			//gROOT->ProcessLine(".x rootfiles/cutBe10.C");
			setGate("Trig_DSB");

		}
		~F3Slew1(){}
};

class F7Slew0:public SlewCorrection{
	private:
	public:
		F7Slew0(){
			setCanvas("F70Pad");
			setVar("F7TCal[0]","F7QRaw[0]", "hF7Slew0");
			setRange(500,0,1500,500,540,580);
			setGate("Trig_DSB");
		}
		~F7Slew0(){}
};

class F7Slew1:public SlewCorrection{
	private:
	public:
		F7Slew1(){
			setCanvas("F71Pad");
			setVar("F7TCal[0]","F7QRaw[0]", "hF7Slew0");
			setVar("F7TCal[1]","F7QRaw[1]", "hF7Slew1");
			setRange(500,0,1500,500,540,580);
			setGate("Trig_DSB");
		}
		~F7Slew1(){}
};

class SBT1Slew0:public SlewCorrection{
	private:
	public:
		SBT1Slew0(){
			setCanvas("SBT10Pad");
			setVar("SBT1TCal[0]","SBT1QRaw[0]", "hSBT1Slew0");
			setRange(500,0,1500,500,540,580);
			setGate("Trig_DSB");
		}
		~SBT1Slew0(){}
};

class SBT1Slew1:public SlewCorrection{
	private:
	public:
		SBT1Slew1(){
			setCanvas("SBT11Pad");
			setVar("SBT1TCal[1]","SBT1QRaw[1]", "hSBT1Slew1");
			setRange(500,0,1500,500,540,580);
			setGate("Trig_DSB");
		}
		~SBT1Slew1(){}
};
class SBT2Slew0:public SlewCorrection{
	private:
	public:
		SBT2Slew0(){
			setCanvas("SBT20Pad");
			setVar("SBT2TCal[0]","SBT2QRaw[0]", "hSBT2Slew0");
			setRange(500,0,1500,500,540,580);
			setGate("Trig_DSB");
		}
		~SBT2Slew0(){}
};

class SBT2Slew1:public SlewCorrection{
	private:
	public:
		SBT2Slew1(){
			setCanvas("SBT21Pad");
			setVar("SBT2TCal[1]","SBT2QRaw[1]", "hSBT2Slew1");
			setRange(500,0,1500,500,540,580);
			setGate("Trig_DSB");
		}
		~SBT2Slew1(){}
};
class SBVSlew1:public SlewCorrection{
	private:
	public:
		SBVSlew1(){
			setCanvas("SBV1Pad");
			setVar("SBVTCal[1]","SBVQRaw[1]", "hSBVSlew1");
			setRange(500,0,1500,500,540,580);
			setGate("Trig_DSB");
		}
		~SBVSlew1(){}
};

class BeamPlas{
	private:
		int runNumber;
		Double_t tof37Mean;
		Double_t tof37Width;
		Double_t tof713Mean;
		Double_t tof713Width;
		TString gate;

		SlewCorrection *F30;
		SlewCorrection *F31;
		SlewCorrection *F70;
		SlewCorrection *F71;
		SlewCorrection *SBT10;
		SlewCorrection *SBT11;
		SlewCorrection *SBT20;
		SlewCorrection *SBT21;
		SlewCorrection *SBV1;
	
	
	
		
	public:
		BeamPlas(int run){ runNumber = run;}
		~BeamPlas(){}
		void loadGate(Double_t tof37M,Double_t tof37W,Double_t tof713M,Double_t tof713W){
			tof37Mean = tof37M;
			tof37Width = tof37W;
			tof713Mean = tof713M;
			tof713Width = tof713W;
			gate = Form("Trig_DSB&&abs(TOF37-%f)<%f&&abs(TOF713-%f)<%f",tof37Mean,tof37Width,tof713Mean,tof713Width);
		}

		void checkF3Slew(){

			F30 = new F3Slew0();
			F30->loadRun(runNumber);
			F30->setGate(gate);
			F30->setRange(2000,0,4000,1000,540,580);
			F30->drawBeforeCorrection();
			//F30->profileX();
			F30->drawAfterCorrection();

			F31 = new F3Slew1();
			F31->loadRun(runNumber);
			F31->setGate(gate);
			F31->setRange(2000,0,4000,1000,540,580);
			F31->drawBeforeCorrection();
			//F31->profileX();
			F31->drawAfterCorrection();
		}
		void checkF7Slew(){

			F70 = new F7Slew0();
			F70->loadRun(runNumber);
			F70->setGate(gate);
			F70->setRange(2000,0,4000,1000,540,580);
			F70->drawBeforeCorrection();
			F70->drawAfterCorrection();

			F71 = new F7Slew1();
			F71->loadRun(runNumber);
			F71->setGate(gate);
			F71->setRange(2000,0,4000,1000,540,580);
			F71->drawBeforeCorrection();
			F71->drawAfterCorrection();
		}
		void checkSBT1Slew(){

			SBT10 = new SBT1Slew0();
			SBT10->loadRun(runNumber);
			SBT10->setGate(gate);
			SBT10->setRange(2000,0,4000,1000,200,240);
			SBT10->drawBeforeCorrection();
			SBT10->drawAfterCorrection();

			SBT11 = new SBT1Slew1();
			SBT11->loadRun(runNumber);
			SBT11->setGate(gate);
			SBT11->setRange(2000,0,4000,1000,200,240);
			SBT11->drawBeforeCorrection();
			SBT11->drawAfterCorrection();
		}
		void checkSBT2Slew(){

			SBT20 = new SBT2Slew0();
			SBT20->loadRun(runNumber);
			SBT20->setGate(gate);
			SBT20->setRange(2000,0,4000,1000,200,240);
			SBT20->drawBeforeCorrection();
			SBT20->drawAfterCorrection();

			SBT21 = new SBT2Slew1();
			SBT21->loadRun(runNumber);
			SBT21->setGate(gate);
			SBT21->setRange(2000,0,4000,1000,200,240);
			SBT21->drawBeforeCorrection();
			SBT21->drawAfterCorrection();
		}
	
		void checkSBVSlew(){

			SBV1 = new SBVSlew1();
			SBV1->loadRun(runNumber);
			SBV1->setGate(gate);
			SBV1->setRange(2000,0,4000,1000,210,250);
			SBV1->drawBeforeCorrection();
			SBV1->drawAfterCorrection();
		}
                void outputTxt(){

                        TString outputName=Form("./txt/SlewParaRun%d.txt",runNumber);
                        //ofstream fout(outputName,ios_base::app | ios_base::out);
                        ofstream fout(outputName, ios_base::out);
			fout<<F30->getSlopePara()<<endl;
			fout<<F31->getSlopePara()<<endl;
			fout<<F70->getSlopePara()<<endl;
			fout<<F71->getSlopePara()<<endl;
			fout<<SBT10->getSlopePara()<<endl;
			fout<<SBT11->getSlopePara()<<endl;
			fout<<SBT20->getSlopePara()<<endl;
			fout<<SBT21->getSlopePara()<<endl;
			fout<<SBV1->getSlopePara()<<endl;
        
                        fout.close();
                }
		void printPNG(){

			F30->printPNG();
			F31->printPNG();
			F70->printPNG();
			F71->printPNG();
			SBT10->printPNG();
			SBT11->printPNG();
			SBT20->printPNG();
			SBT21->printPNG();
			SBV1->printPNG();

		}


};
void slewEffect(){

	//int runNumber = 310;
	int runNumber = 320;
	double tof37Mean = 299.2;
	double tof37Width = 0.5;
	double tof713Mean = 236.6;
	double tof713Width = 0.5;
	//int runNumber = 340;
	//int runNumber = 360;
	//double tof37Mean = 300.6;
	//double tof37Width = 0.5;
	//double tof713Mean = 236.1;
	//double tof713Width = 0.5;
	
	//int runNumber = 380;
	//int runNumber = 595;
	TString fileName = Form("correctSlewEffect%d.root",runNumber);


	TFile *outputFile = new TFile(fileName,"RECREATE");

	BeamPlas *bp = new BeamPlas(runNumber);
	bp->loadGate(tof37Mean,tof37Width,tof713Mean,tof713Width);
	bp->checkF3Slew();
	bp->checkF7Slew();
	bp->checkSBT1Slew();
	bp->checkSBT2Slew();
	bp->checkSBVSlew();
	bp->outputTxt();	
	bp->printPNG();	
	//checkF3Slew(runNumber,tof37Mean,tof37Width,tof713Mean,tof713Width);
	//checkF7Slew(runNumber);
	//	checkSBT1Slew(runNumber);
	//	checkSBT2Slew(runNumber);
	//	checkSBVSlew(runNumber);

	//Test
	//	SlewCorrection *sc = new SlewCorrection();
	//	//sc->loadRuns(runStart,runStop);
	//	sc->loadRun(runNumber);
	//	sc->setVar("F3TCal[0]","F3QRaw[0]", "hF3Slew0");
	//	sc->setRange(500,0,1500,500,540,580);
	//	//sc->setRange(350,250,600,500,540,580);//320
	//	//sc->setRange(250,250,500,500,540,580);//360
	//	sc->setGate("Trig_DSB");
	//	sc->drawBeforeCorrection();
	//	sc->profileX();
}
