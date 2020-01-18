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

                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar27He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar28He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar29He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar30He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar31He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar32He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar33He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar34He6.C");

			gROOT->ProcessLine(".x rootfiles/cutBe10Bar9He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar10He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar11He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar12He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar13He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar14He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar15He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar16He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar17He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar18He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar19He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar20He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar21He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar22He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar23He4.C");


                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar28He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar29He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar30He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar31He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar32He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar33He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar34He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar35He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar36He8.C");


			gROOT->ProcessLine(".x rootfiles/cutBe12Bar9He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar10He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar11He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar12He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar13He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar14He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar15He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar16He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar17He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar18He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar19He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar20He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar21He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar22He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar23He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar24He6.C");



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

			tree->SetAlias("SOL","299.792458*1");
			tree->SetAlias("AMU","931.49410242*1");

			tree->SetAlias("MassBe10","10.0113404*1");
			tree->SetAlias("MassBe12","12.02472781*1");
			tree->SetAlias("MassBe14","14.04069708*1");

			//tree->SetAlias("MassBe","MassBe12*1");
			//tree->SetAlias("MassBe","MassBe14*1");
			tree->SetAlias("MassH","1.007276452*1");
			tree->SetAlias("MassHe4","4.001506105*1");
			tree->SetAlias("MassHe6","6.017788744*1");
			tree->SetAlias("MassHe8","8.032837245*1");
			tree->SetAlias("MassHe10","10.050167077*1");
			//tree->SetAlias("MassHe10","10.05171959*1");



			tree->SetAlias("MassBe","MassBe10*1");
			tree->SetAlias("residueRestMass","MassHe6*AMU");

			//tree->SetAlias("MassBe","MassBe12*1");
			//tree->SetAlias("residueRestMass","MassHe8*AMU");

			//tree->SetAlias("MassBe","MassBe14*1");
			//tree->SetAlias("residueRestMass","MassHe10*AMU");



			tree->SetAlias("beamMass","MassBe*AMU");
			tree->SetAlias("targetMass","MassH*AMU");
			tree->SetAlias("protonMass","MassH*AMU");
			tree->SetAlias("alphaMass","MassHe4*AMU");


			// 	
			tree->SetAlias("beamEk","beamEnergy*MassBe");
			tree->SetAlias("beamMomentum","sqrt(beamEk*beamEk+2*beamEk*beamMass)");

			tree->SetAlias("xB","vBeam.X()");
			tree->SetAlias("yB","vBeam.Y()");
			tree->SetAlias("zB","vBeam.Z()");
			tree->SetAlias("xP","vESPRI.X()");
			tree->SetAlias("yP","vESPRI.Y()");
			tree->SetAlias("zP","vESPRI.Z()");
			tree->SetAlias("xA","vAlpha.X()");
			tree->SetAlias("yA","vAlpha.Y()");
			tree->SetAlias("zA","vAlpha.Z()");
			tree->SetAlias("xR","vFDC0.X()");
			tree->SetAlias("yR","vFDC0.Y()");
			tree->SetAlias("zR","vFDC0.Z()");

			TString planeOfBPA = "(xB*(yA*zP-yP*zA)+yB*(zA*xP-zP*xA)+zB*(xA*yP-xP*yA))";


	
			tree->SetAlias("A1","yP*zB-zP*yB");
			tree->SetAlias("B1","zP*xB-xP*zB");
			tree->SetAlias("C1","xP*yB-yP*xB");
                                                      
			tree->SetAlias("A2","yA*zB-zA*yB");
			tree->SetAlias("B2","zA*xB-xA*zB");
			tree->SetAlias("C2","xA*yB-yA*xB");
	
			tree->SetAlias("cosPhi12","(A1*A2+B1*B2+C1*C2)/(sqrt(A1*A1+B1*B1+C1*C1)*sqrt(A2*A2+B2*B2+C2*C2))");

			tree->SetAlias("cosTheta12","cos(theta1)*cos(theta2)+sin(theta1)*sin(theta2)*cosPhi12");

			tree->SetAlias("protonGamma","(protonEnergy/protonMass+1)");
			tree->SetAlias("protonBeta","sqrt(1-1/(protonGamma*protonGamma))");
			tree->SetAlias("protonVelocity","protonBeta*SOL");
			tree->SetAlias("protonMomentum","sqrt(protonEnergy*protonEnergy+2*protonEnergy*protonMass)");

			tree->SetAlias("alphaGamma","(alphaEnergy/alphaMass+1)");
			tree->SetAlias("alphaBeta","sqrt(1-1/(alphaGamma*alphaGamma))");
			tree->SetAlias("alphaVelocity","alphaBeta*SOL");
			tree->SetAlias("alphaMomentum","sqrt(alphaEnergy*alphaEnergy+2*alphaEnergy*alphaMass)");


			tree->SetAlias("E0","beamEk+beamMass+targetMass");
			tree->SetAlias("P0","beamMomentum");

			tree->SetAlias("E1","protonEnergy+protonMass");
			tree->SetAlias("P1","protonMomentum");
			tree->SetAlias("theta1","espriAngle*TMath::DegToRad()");

			tree->SetAlias("E2","alphaEnergy+alphaMass");
			tree->SetAlias("P2","alphaMomentum");
			tree->SetAlias("theta2","alphaAngle*TMath::DegToRad()");
			


			tree->SetAlias("residueMomentum","sqrt(P0*P0 + P1*P1+ P2*P2 - 2*P0*P1*cos(theta1) - 2*P0*P2*cos(theta2) + 2*P1*P2*cosTheta12)");

			tree->SetAlias("residueEnergy","E0-E1-E2");

			tree->SetAlias("residueMass","sqrt(residueEnergy*residueEnergy - residueMomentum*residueMomentum)");
			tree->SetAlias("exEnergy","residueMass-residueRestMass");

		}

		void setGate(TString g){
			gate = g;
			//gate = "espriHit==1";
		}
		void addGate(TString g){
			gate = gate+"&&"+g;
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
			tree->Draw("teleEnergy:teleAngle>>hTeleEA(100,0,18,100,0,700)",gate,"colz");
			dc->drawAlphaEA();
		}

		void drawProtonEA(){
			tree->Draw("protonEnergy:espriAngle>>hProtonEA(200,50,80,200,0,150)",gate,"colz");
			dc->drawProtonEA();
		}
		void drawAlphaEA(){
			tree->Draw("alphaEnergy:alphaAngle>>hAlphaEA(200,0,18,200,300,700)",gate,"colz");
			dc->drawAlphaEA();
		}

		void drawAA(){
			tree->Draw("espriAngle:alphaAngle>>hAA(200,0,18,200,50,80)",gate,"colz");
			dc->drawAA();
		}
		void drawEE(){
			tree->Draw("protonEnergy:alphaEnergy>>hEE(200,300,700,200,0,150)",gate,"colz");
			dc->drawEE();
		}

		void drawEx(){
			tree->Draw("exEnergy>>hEx(200,-20,20)",gate,"colz");
			
		}
		void drawEp(){
			tree->Draw("protonEnergy>>hEp(200,0,100)",gate);
		}

		void drawPlaneBPA(){

			TString planeOfBPA = "(xB*(yA*zP-yP*zA)+yB*(zA*xP-zP*xA)+zB*(xA*yP-xP*yA))";
			tree->Draw(planeOfBPA+">>hPlane(400,-0.4,0.4)",gate);
		}
		void drawProtonResAA(){
			tree->Draw("espriAngle:resAngle>>hProtonResAA(500,0,5,500,50,80)",gate,"colz");
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
TString getHodGate(){
	TString hodGate;
	TString hodGateBe14He4 = "(Be14Bar3He4||Be14Bar4He4||Be14Bar5He4||Be14Bar6He4||Be14Bar7He4||Be14Bar8He4||Be14Bar9He4||Be14Bar10He4||Be14Bar11He4||Be14Bar12He4||Be14Bar13He4||Be14Bar14He4||Be14Bar15He4||Be14Bar16He4||Be14Bar17He4)";
	TString hodGateBe14He6 = "(Be14Bar11He6||Be14Bar12He6||Be14Bar13He6||Be14Bar14He6||Be14Bar15He6||Be14Bar16He6||Be14Bar17He6||Be14Bar18He6||Be14Bar19He6||Be14Bar20He6||Be14Bar21He6||Be14Bar22He6||Be14Bar23He6||Be14Bar24He6||Be14Bar26He6||Be14Bar27He6||Be14Bar28He6||Be14Bar29He6||Be14Bar30He6||Be14Bar31He6||Be14Bar32He6)";
	TString hodGateBe14He8 = "(Be14Bar33He8||Be14Bar34He8||Be14Bar35He8||Be14Bar36He8||Be14Bar37He8||Be14Bar38He8)";

	TString hodGateBe12He8  = "(Be12Bar28He8||Be12Bar29He8||Be12Bar30He8||Be12Bar31He8||Be12Bar32He8||Be12Bar33He8||Be12Bar34He8||Be12Bar35He8||Be12Bar36He8)";
	TString hodGateBe12He6 = "(Be12Bar9He6||Be12Bar10He6||Be12Bar11He6||Be12Bar12He6||Be12Bar13He6||Be12Bar14He6||Be12Bar15He6||Be12Bar16He6||Be12Bar17He6||Be12Bar18He6||Be12Bar19He6||Be12Bar20He6||Be12Bar21He6||Be12Bar22He6||Be12Bar23He6||Be12Bar24He6)";
	//TString hodGateBe12He6 = "(Be12Bar9He6||Be12Bar10He6||Be12Bar11He6||Be12Bar12He6||Be12Bar13He6||Be12Bar14He6||Be12Bar15He6||Be12Bar16He6||Be12Bar17He6||Be12Bar18He6||Be12Bar19He6||Be12Bar20He6)";
	//TString hodGateBe12He6 = "(Be12Bar21He6||Be12Bar22He6||Be12Bar23He6||Be12Bar24He6)";
	TString hodGateBe10He4 = "(Be10Bar9He4||Be10Bar10He4||Be10Bar11He4||Be10Bar12He4||Be10Bar13He4||Be10Bar10He4||Be10Bar15He4||Be10Bar16He4||Be10Bar17He4||Be10Bar18He4||Be10Bar19He4||Be10Bar20He4||Be10Bar21He4||Be10Bar22He4||Be10Bar23He4)";
	//TString hodGateBe10He4 = "(Be10Bar20He4||Be10Bar21He4||Be10Bar22He4||Be10Bar23He4)";
	//TString hodGateBe10He4 = "(Be10Bar21He4||Be10Bar22He4||Be10Bar23He4)";
	//TString hodGateBe10He4 = "(Be10Bar22He4||Be10Bar23He4)";
	//TString hodGateBe10He4 = "(Be10Bar20He4||Be10Bar21He4)";
	//TString hodGateBe10He4 = "(Be10Bar16He4||Be10Bar17He4||Be10Bar18He4||Be10Bar19He4)";
	//TString hodGateBe10He4 = "(Be10Bar9He4||Be10Bar10He4||Be10Bar11He4||Be10Bar12He4||Be10Bar13He4||Be10Bar14He4||Be10Bar15He4)";
	//TString hodGateBe10He4 = "(Be10Bar21He4)";
	//TString hodGateBe10He6 = "(Be10Bar27He6||Be10Bar28He6||Be10Bar29He6||Be10Bar30He6)";
	//TString hodGateBe10He6 = "(Be10Bar31He6||Be10Bar32He6||Be10Bar33He6||Be10Bar34He6)";
	TString hodGateBe10He6 = "(Be10Bar27He6||Be10Bar28He6||Be10Bar29He6||Be10Bar30He6||Be10Bar31He6||Be10Bar32He6||Be10Bar33He6||Be10Bar34He6)";

	//hodGate = hodGateBe10He4;
	hodGate = hodGateBe10He6;
	//hodGate = hodGateHe6;
	//hodGate = hodGateBe14He8;
	//hodGate = "("+hodGateHe4+"||"+hodGateHe6+"||"+hodGateHe8+")";

	//hodGate = hodGateBe12He6;
	return hodGate;
}
TString getGate(){
	//return "(espriAngle>66.5)";
	//return "(espriAngle>67.5)";
	//return "(espriAngle>66.5&&espriAngle<67.5)";
	//return "(espriAngle>65.5&&espriAngle<66.5)";
	//return "(espriAngle>64.5&&espriAngle<65.5)";
	//return "(espriAngle<66.5&&espriAngle>63.5)";
	//return "(espriAngle<67&&espriAngle>65&&alphaAngle>6&&alphaAngle<8)";
	//return "(espriAngle<63.5)";
	gROOT->ProcessLine(".x cutAABe10.C");
	//return "(AABe10)&&((abs(protonEnergy-40)<10&&abs(alphaEnergy-550)<10))";
	return "((abs(protonEnergy-40)<10&&abs(alphaEnergy-550)<10))";
	
	TString planeOfBPA = "(xB*(yA*zP-yP*zA)+yB*(zA*xP-zP*xA)+zB*(xA*yP-xP*yA))";
	//return "abs(xB*(yA*zP-yP*zA)+yB*(zA*xP-zP*xA)+zB*(xA*yP-xP*yA))<0.05";
	//return "((espriHitSide==0&&teleHitSide==1)||(espriHitSide==1&&teleHitSide==0))";
	//return "(abs(exEnergy-5.5)<0.15)";
}
void drawExEnergy(){
	CheckEx *ce = new CheckEx();
	ce->addFile("ppaBe10.root");
	//ce->addFile("ppaBe12.root");
	//ce->addFile("ppaBe14.root");
	ce->setAlias();
	ce->loadCut();
	ce->setGate(getGate());
	ce->addGate(getHodGate());
	//ce->setGate(getHodGate());

	TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
//	cPad->Divide(2,2);
//	cPad->cd(1);
	//ce->drawEp();
	//ce->drawProtonResAA();
	ce->drawEx();
	ce->output();

}
void drawPACorrelation(){

	CheckEx *ce = new CheckEx();
	ce->addFile("ppaBe10.root");
	//ce->addFile("ppaBe12.root");
	//ce->addFile("ppaBe14.root");
	ce->setAlias();
	ce->loadCut();
	ce->setGate(getGate());
	ce->addGate(getHodGate());
	//ce->setGate(getHodGate());

	TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
	cPad->Divide(2,2);
	cPad->cd(1);
	ce->drawProtonEA();
	cPad->cd(2);
	ce->drawAlphaEA();
	cPad->cd(3);
	ce->drawAA();
	cPad->cd(4);
	ce->drawEE();
	ce->output();
}

void drawPlaneBPA(){

	CheckEx *ce = new CheckEx();
	ce->addFile("ppaBe10.root");
	//ce->addFile("ppaBe12.root");
	//ce->addFile("ppaBe14.root");
	ce->setAlias();
	ce->loadCut();
	//ce->setGate(getGate());

	TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
	ce->drawPlaneBPA();
	ce->output();
}

void drawTree(){
	drawPACorrelation();	
	//drawExEnergy();
	//drawPlaneBPA();
}

