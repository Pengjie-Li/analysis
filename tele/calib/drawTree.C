class DrawCurve{
	private:
        TGraph *gCurve[4];
		
	public:
		DrawCurve(){

			TFile *fCurve;

			fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/ppaKinematic/ppAlphaCurve.root","READ");
			gCurve[0] = (TGraph *)gDirectory->Get("ProtonEnergyAngle");
			gCurve[1] = (TGraph *)gDirectory->Get("AlphaEnergyAngle");
			gCurve[2] = (TGraph *)gDirectory->Get("angle");
			gCurve[3] = (TGraph *)gDirectory->Get("energy");

			fCurve->Close();
		}
		void drawProtonEA(){
			
			gCurve[0]->Draw("plsame");
		}
		void drawAlphaEA(){
			gCurve[1]->Draw("plsame");
		}
		void drawAA(){
			gCurve[2]->Draw("plsame");
		}
		void drawEE(){
			gCurve[3]->Draw("plsame");
		}

		~DrawCurve(){}
};

class TCalibPara{
	private:
		double plasGain[2][7];
		double plasDead[2][7];
		double naiGain[2][7];
		double naiDead[2][7];

		void init(){
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j< 7; ++j) {
					plasGain[i][j]= 0;
					plasDead[i][j]= 0;
					naiGain[i][j]= 0;
					naiDead[i][j]= 0;
				}

			}

		}
		void loadCalibPara(){
			init();
			ifstream in;
			TString inputName = "calibPara.txt";
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int barId;
			double gPlas;
			double dPlas;
			double gNai;
			double dNai;
			while(1){
				if(!in.good()) break;
				in>>side>>barId>>gPlas>>dPlas>>gNai>>dNai;
				naiGain[side][barId] = gNai;
				naiDead[side][barId] = dNai;
				plasGain[side][barId] = gPlas;
				plasDead[side][barId] = dPlas;
			}
		}
		void print(){
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j< 7; ++j) {
					cout<<i<<"\t"<<j<<"\t"<<plasGain[i][j]<<"\t"<<plasDead[i][j]<<"\t"<<naiGain[i][j]<<"\t"<<naiDead[i][j]<<endl;
				}

			}
		}
	public:
		TCalibPara(){
			loadCalibPara();
			//print();
		}
		~TCalibPara(){}
		double getNaiGain(int side,int barId){
			return naiGain[side][barId];
		}
		double getNaiDead(int side,int barId){
			return naiDead[side][barId];
		}
		double getPlasGain(int side,int barId){
			return plasGain[side][barId];
		}
		double getPlasDead(int side,int barId){
			return plasDead[side][barId];
		}
};
class CheckEx{
	private:
		TChain *tree;
		int markerStyle;

		TCalibPara *calibPara;
		int side;
		int barId;
		double gPlas;
		double gNai;
		double dPlas;
		double dNai;

		DrawCurve *dc;
		
		TH2F *hEA;
		TH2F *hEkAngle;
		TH2F *hNai;
		TH2F *hPlas;
		TH2F *hDEE;
		TH2F *hTOF;
		TH2F *hEkTOF;
		TH2F *hVTOF;
		TH2F *hVTOFRaw;
		TH2F *hVVCorr;
		TH2F *hFLCorr;
		TH2F *hFLTOF;
		TH1F *hEx;
		TH1F *hExDee;
		TH1F *hExTof;
		TString gate;
		TGraph *tot;
		TGraph *nai;
		TGraph *plas;
		TGraph *dEE;

		double flOffset ;
		double tofOffset;


		double getNaiGain(){
			return calibPara->getNaiGain(side,barId);
		}
		double getNaiDead(){
			return calibPara->getNaiDead(side,barId);
		}

		double getPlasGain(){
			return calibPara->getPlasGain(side,barId);
		}
		double getPlasDead(){
			return calibPara->getPlasDead(side,barId);
		}



	public:
		CheckEx(){

			tree = new TChain("tree");
			//tree->Add("ppBe14.root_BeamProtonPRAngleHodBar28-33");
			//tree->Add("ppBe14.root");
			//tree->Add("ppBe14.root_BeamTargetProtonPRAngle");
			//tree->Add("run0383_ppBe14.root");
			//tree->Add("run0383_ppBe14.root");
			dc = new DrawCurve();
			calibPara = new TCalibPara();
			markerStyle = 1;
		}
		void addFile(TString fileName){
			tree->Add(fileName);
		}
		void setMarkerStyle(int style){
			markerStyle = style;
		}
		CheckEx(int side,int barId):side(side),barId(barId){

			tree = new TChain("tree");
			//tree->Add("ppBe10.root");
			//tree->Add("ppBe14.root_BeamProtonPRAngleHodBar28-33");
			calibPara = new TCalibPara();
			setCalibParas(getNaiGain(),getNaiDead(),getPlasGain(),getPlasDead());
			setAlias();
		}

		void setBar(int s, int b){
			side = s; barId = b;
			setCalibParas(getNaiGain(),getNaiDead(),getPlasGain(),getPlasDead());
		}
		void setCalibParas(double gN,double dN,double gP,double dP){
			gNai = gN; dNai = dN;gPlas = gP; dPlas = dP;
		}
		void setOffset(double fl,double tof){
			flOffset = fl;
			tofOffset = tof;
		}
		void loadCut(){

                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar3He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar4He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar5He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar6He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar7He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar8He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar9He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar10He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar11He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar12He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar13He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar14He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar15He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar16He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar17He4.C");

                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar11He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar12He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar13He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar14He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar15He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar16He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar17He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar18He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar19He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar20He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar21He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar22He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar23He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar24He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar26He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar27He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar28He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar29He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar30He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar31He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar32He6.C");

                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar33He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar34He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar35He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar36He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar37He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar38He8.C");

		}
		void setAlias(){

			tree->SetAlias("plasBarQPed0","sqrt(plasQPed[0]*plasQPed[1])");
			tree->SetAlias("plasBarQPed1","sqrt(plasQPed[2]*plasQPed[3])");
			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 7; ++j) {

					tree->SetAlias(Form("naiBarQPed%d%d",i,j),Form("sqrt(naiQPed[%d][%d]*naiQPed[%d][%d])",2*i,j,2*i+1,j));
					tree->SetAlias(Form("naiBarQRaw%d%d",i,j),Form("sqrt(naiQRaw[%d][%d]*naiQRaw[%d][%d])",2*i,j,2*i+1,j));
				}

			}


			tree->SetAlias("SOL","299.792458*1");
			tree->SetAlias("AMU","931.49410242*1");

			tree->SetAlias("MassBe10","10.0113404*1");
			tree->SetAlias("MassBe12","12.02472781*1");
			tree->SetAlias("MassBe14","14.04069708*1");

			tree->SetAlias("MassBe","MassBe12*1");
			//tree->SetAlias("MassBe","MassBe10*1");
			//tree->SetAlias("MassBe","MassBe14*1");
			tree->SetAlias("MassH","1.007276452*1");
			tree->SetAlias("beamMass","MassBe*AMU");
			tree->SetAlias("protonMass","MassH*AMU");

			// Could be better	
			tree->SetAlias("beamEk","(Ek713-3.776)*MassBe");

			tree->SetAlias("TOFSbtTarget","beamFL/(Beta713*SOL-0.654-0.626)"); // 0.654 diff F713 and F13-TGT, 0.626 diff Data to Theoretical point

			tree->SetAlias("dEplas",Form("(%4f*plasBarQPed%d+%4f)",gPlas,side,dPlas));
			//tree->SetAlias("dEplas",Form("(%4f*plasBarQPed%d/(1+%4f*plasBarQPed%d))",gPlas,side,dPlas,side));
			tree->SetAlias("Tof",Form("(%4f*plasBarQPed%d+%4f)",gPlas,side,dPlas));
			tree->SetAlias("plasT0","(plasT[0]-0.01*(rdcY[0]-225))");
			tree->SetAlias("plasT1","(plasT[1]-0.0115*(rdcY[1]-225))");
			//tree->SetAlias("espriLTOF","((plasT[0]-F13T+895.2+19.84)-TOFSbtTarget)");
			//tree->SetAlias("TOF",Form("(plasT%d-F13T-TOFSbtTarget+895.2)+20.27-2.47",side));
			//tree->SetAlias("TOF",Form("(plasT%d-TOFSbtTarget+674.2)+20.27-2.47",side));

			tree->SetAlias("espriTOF","(espriPlasT-TOFSbtTarget)");
			tree->SetAlias("beta","espriFL/(SOL*espriTOF)");
			tree->SetAlias("gamma","1/sqrt(1-beta*beta)");
			tree->SetAlias("espriEk","(gamma-1)*AMU*MassH");


			tree->SetAlias("pGamma","(espriEk/protonMass+1)");
			tree->SetAlias("pMomentum","sqrt(espriEk*espriEk+2*espriEk*protonMass)");

			tree->SetAlias("rMomentum","sqrt(beamMomentum*beamMomentum + pMomentum*pMomentum - 2*beamMomentum*pMomentum*cos(espriAngle*TMath::DegToRad()))");
			tree->SetAlias("rEnergy","beamEk + beamMass - espriEk");
			tree->SetAlias("rMass","sqrt(rEnergy*rEnergy - rMomentum*rMomentum)");
			tree->SetAlias("exEnergy","rMass-beamMass");


			//tree->SetAlias("protonGamma","(protonEk/protonMass+1)");
			tree->SetAlias("protonBeta","sqrt(1-1/(protonGamma*protonGamma))");
			tree->SetAlias("protonVelocity","protonBeta*SOL");

			tree->SetAlias("protonGamma","(espriEnergy/protonMass+1)");
			tree->SetAlias("beamMomentum","sqrt(beamEk*beamEk+2*beamEk*beamMass)");
			tree->SetAlias("protonMomentum","sqrt(espriEnergy*espriEnergy+2*espriEnergy*protonMass)");

			tree->SetAlias("residueMomentum","sqrt(beamMomentum*beamMomentum + protonMomentum*protonMomentum - 2*beamMomentum*protonMomentum*cos(espriAngle*TMath::DegToRad()))");
			tree->SetAlias("residueEnergy","beamEk + beamMass - espriEnergy");
			tree->SetAlias("residueMass","sqrt(residueEnergy*residueEnergy - residueMomentum*residueMomentum)");
			tree->SetAlias("excitationEnergy","residueMass-beamMass");

		}

		void setGate(TString g){
			gate = g;
			//gate = "espriHit==1";
		}
		void drawDEE(){
			tree->Draw(Form("espriPlasE:espriNaiE>>hDEE%d%d(1000,0,200,1000,0,30)",side,barId),gate);
			//tree->Draw(Form("dEplas:Enai>>hDEE%d%d(1000,0,200,1000,0,30)",side,barId),gate);
			hDEE = (TH2F *)gDirectory->Get(Form("hDEE%d%d",side,barId));
			hDEE->SetMarkerColor(2);
			hDEE->SetMarkerStyle(markerStyle);
			hDEE->Draw();
		}
		void drawNai(){
			tree->Draw(Form("Enai:espriAngle>>hNai%d%d(1000,55,75,1000,0,200)",side,barId),gate);

			hNai = (TH2F *)gDirectory->Get(Form("hNai%d%d",side,barId));
			hNai->SetMarkerColor(2);
			//hNai->SetMarkerSize(30);
			hNai->SetMarkerStyle(markerStyle);
			hNai->Draw();
		}
		void drawPlas(){
			tree->Draw(Form("dEplas:espriAngle>>hPlas%d%d(1000,55,75,1000,0,20)",side,barId),gate);

			hPlas = (TH2F *)gDirectory->Get(Form("hPlas%d%d",side,barId));
			hPlas->SetMarkerColor(2);
			//hPlas->SetMarkerSize(30);
			hPlas->SetMarkerStyle(markerStyle);
			hPlas->Draw();
		}
		void drawEspriEA(){
			tree->Draw("espriEnergy:espriAngle>>hEspriEA(200,40,80,150,0,150)",gate,"colz");
			dc->drawProtonEA();
		}
		void drawTeleEA(){
			tree->Draw("teleEnergy:teleAngle>>hTeleEA(200,0,18,200,0,700)",gate,"colz");
			dc->drawAlphaEA();
		}

		void drawAA(){
			tree->Draw("espriAngle:teleAngle>>hAA(200,0,18,200,40,80)",gate,"colz");
			dc->drawAA();
		}
		void drawEE(){
			tree->Draw("espriEnergy:teleEnergy>>hEE(200,0,700,200,0,150)",gate,"colz");
			dc->drawEE();
		}





		void output(){
			//TFile *outputFile = new TFile(Form("rootfiles/Bar%d%d.root",side,barId),"RECREATE");
			gPad->Print(Form("png/Bar%d%d.png",side,barId));
			//hTot->Write();
			//hNai->Write();
			//hPlas->Write();
			//hDEE->Write();
			//outputFile->Close();
		}
		TH2F * getEA(){
			return hEA;
		}
		TH1F * getEx(){
			return hEx;
		}
		TH2F * getDEE(){
			return hDEE;
		}
		TH2F * getTOF(){
			return hTOF;
		}
		TH2F * getEkTOF(){
			return hEkTOF;
		}

		TH2F * getNai(){
			return hNai;
		}
		TH2F * getPlas(){
			return hPlas;
		}

		~CheckEx(){
			delete tree;
			delete dc;
			delete calibPara;
		}
};
TString getGate(){
	TString hodGate;
	TString hodGateHe4 = "(Be14Bar3He4||Be14Bar4He4||Be14Bar5He4||Be14Bar6He4||Be14Bar7He4||Be14Bar8He4||Be14Bar9He4||Be14Bar10He4||Be14Bar11He4||Be14Bar12He4||Be14Bar13He4||Be14Bar14He4||Be14Bar15He4||Be14Bar16He4||Be14Bar17He4)";
	TString hodGateHe6 = "(Be14Bar11He6||Be14Bar12He6||Be14Bar13He6||Be14Bar14He6||Be14Bar15He6||Be14Bar16He6||Be14Bar17He6||Be14Bar18He6||Be14Bar19He6||Be14Bar20He6||Be14Bar21He6||Be14Bar22He6||Be14Bar23He6||Be14Bar24He6||Be14Bar26He6||Be14Bar27He6||Be14Bar28He6||Be14Bar29He6||Be14Bar30He6||Be14Bar31He6||Be14Bar32He6)";
	TString hodGateHe8 = "(Be14Bar33He8||Be14Bar34He8||Be14Bar35He8||Be14Bar36He8||Be14Bar37He8||Be14Bar38He8)";
	//hodGate = hodGateHe4;
	//hodGate = hodGateHe6;
	hodGate = hodGateHe8;
	//hodGate = "("+hodGateHe4+"||"+hodGateHe6+"||"+hodGateHe8+")";

	return hodGate;
}
void drawPACorrelation(){

	CheckEx *ce = new CheckEx();
	//ce->addFile("ppaBe10.root");
	//ce->addFile("ppaBe12.root");
	ce->addFile("ppaBe14.root");
	ce->setAlias();
	ce->loadCut();
	ce->setGate(getGate());

	TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
	cPad->Divide(2,2);
	cPad->cd(1);
	ce->drawEspriEA();
	cPad->cd(2);
	ce->drawTeleEA();
	cPad->cd(3);
	ce->drawAA();
	cPad->cd(4);
	ce->drawEE();
	ce->output();
}


void drawTree(){
	drawPACorrelation();	
}

