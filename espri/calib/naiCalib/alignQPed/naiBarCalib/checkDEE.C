class DrawCurve{
	private:
		TGraph *tot;
		TGraph *nai;
		TGraph *plas;
		TGraph *dEE;


		
	public:
		DrawCurve(){
			TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/esBe14Excitation/espriDetectorEnergy.root","READ");
			tot = (TGraph *)gDirectory->Get("tot");
			nai = (TGraph *)gDirectory->Get("nai");
			plas = (TGraph *)gDirectory->Get("plas");
			fCurve->Close();

			TFile *fCurve2 = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/protonDEE/dEECurve.root","READ");
			dEE = (TGraph *)gDirectory->Get("dEE");
			fCurve2->Close();

		}
		void drawTot(){
			tot->SetMarkerColor(1);
			tot->SetLineColor(1);
			tot->Draw("plsame");

		}
		void drawDEE(){
			dEE->SetMarkerColor(1);
			dEE->SetLineColor(1);
			dEE->Draw("psame");
		}
		void drawPlas(){
			plas->SetMarkerColor(1);
			plas->SetLineColor(1);
			plas->Draw("plsame");
		}
		void drawNai(){
			nai->SetMarkerColor(1);
			nai->SetLineColor(1);
			nai->Draw("plsame");
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
		TH2F *hTot;
		TH2F *hNai;
		TH2F *hPlas;
		TH2F *hDEE;
		TH2F *hTOF;
		TH1F *hEx;
		TString gate;
		TGraph *tot;
		TGraph *nai;
		TGraph *plas;
		TGraph *dEE;


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
		CheckEx(int side,int barId):side(side),barId(barId){

			tree = new TChain("tree");
			tree->Add("ppBe14.root");
			//tree->Add("ppBe14.root_BeamProtonPRAngleHodBar28-33");
			calibPara = new TCalibPara();
			setCalibParas(getNaiGain(),getNaiDead(),getPlasGain(),getPlasDead());
			setAlias();
			setGate();
			drawTOF();
			drawDEE();
			drawNai();
			drawPlas();
		}

		void setBar(int s, int b){
			side = s; barId = b;
			setCalibParas(getNaiGain(),getNaiDead(),getPlasGain(),getPlasDead());
		}
		void setCalibParas(double gN,double dN,double gP,double dP){
			gNai = gN; dNai = dN;gPlas = gP; dPlas = dP;
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

			tree->SetAlias("MassBe","MassBe14*1");
			tree->SetAlias("MassH","1.007276452*1");
			tree->SetAlias("beamMass","MassBe*AMU");
			tree->SetAlias("protonMass","MassH*AMU");

			// Could be better	
			tree->SetAlias("beamEk","(Ek713-3.776)*MassBe");

			tree->SetAlias("TOFSbtTarget","beamFL/(Beta713*SOL-0.654)");

			tree->SetAlias("dEplas",Form("(%4f*plasBarQPed%d+%4f)",gPlas,side,dPlas));
			//tree->SetAlias("dEplas",Form("(%4f*plasBarQPed%d/(1+%4f*plasBarQPed%d))",gPlas,side,dPlas,side));
			tree->SetAlias("Tof",Form("(%4f*plasBarQPed%d+%4f)",gPlas,side,dPlas));
			tree->SetAlias("plasT0","(plasT[0]-0.01*(rdcY[0]-225))");
			tree->SetAlias("plasT1","(plasT[1]-0.0115*(rdcY[1]-225))");
			//tree->SetAlias("espriLTOF","((plasT[0]-F13T+895.2+19.84)-TOFSbtTarget)");
			tree->SetAlias("TOF",Form("(plasT%d-F13T-TOFSbtTarget+895.2)+20.27-2.47",side));

        
			tree->SetAlias("Enai",Form("%4f*naiBarQPed%d%d+%4f",gNai,side,barId,dNai));
			tree->SetAlias("protonEk","dEplas+Enai");

			tree->SetAlias("beamMomentum","sqrt(beamEk*beamEk+2*beamEk*beamMass)");
			tree->SetAlias("protonMomentum","sqrt(protonEk*protonEk+2*protonEk*protonMass)");

			tree->SetAlias("residueMomentum","sqrt(beamMomentum*beamMomentum + protonMomentum*protonMomentum - 2*beamMomentum*protonMomentum*cos(espriAngle*TMath::DegToRad()))");
			tree->SetAlias("residueEnergy","beamEk + beamMass - protonEk");
			tree->SetAlias("residueMass","sqrt(residueEnergy*residueEnergy - residueMomentum*residueMomentum)");
			tree->SetAlias("excitationEnergy","residueMass-beamMass");

		}

		void setGate(){
			gate = Form("isEspriLR==%d&&naiBarId==%d",side,barId);
		}
		void draw(){
			drawTot();
			drawEx();
			//drawDEE();
			drawNai();
			drawPlas();
		}
		void drawTot(){

			tree->Draw(Form("protonEk:espriAngle>>hTot%d%d(1000,55,75,1000,0,200)",side,barId),gate);

			hTot = (TH2F *)gDirectory->Get(Form("hTot%d%d",side,barId));
			hTot->SetMarkerColor(2);
			//hTot->SetMarkerSize(30);
			hTot->SetMarkerStyle(markerStyle);
			hTot->Draw();
			dc->drawTot();
		}
		void drawEx(){
			tree->Draw(Form("excitationEnergy>>hEx%d%d(200,-10,10)",side,barId),gate);
			hEx = (TH1F *)gDirectory->Get(Form("hEx%d%d",side,barId));
			hEx->Draw();
		}

		void drawTOF(){
			tree->Draw(Form("dEplas:TOF>>hTOF%d(1000,0,40,1000,0,30)",side),gate);
			hTOF = (TH2F *)gDirectory->Get(Form("hTOF%d",side));
			hTOF->SetMarkerColor(2);
			hTOF->SetMarkerStyle(markerStyle);
			hTOF->Draw();
		}

		void drawDEE(){
			tree->Draw(Form("dEplas:Enai>>hDEE%d%d(1000,0,200,1000,0,30)",side,barId),gate);
			hDEE = (TH2F *)gDirectory->Get(Form("hDEE%d%d",side,barId));
			hDEE->SetMarkerColor(2);
			hDEE->SetMarkerStyle(markerStyle);
			hDEE->Draw();
			dc->drawDEE();
		}
		void drawNai(){
			tree->Draw(Form("Enai:espriAngle>>hNai%d%d(1000,55,75,1000,0,200)",side,barId),gate);

			hNai = (TH2F *)gDirectory->Get(Form("hNai%d%d",side,barId));
			hNai->SetMarkerColor(2);
			//hNai->SetMarkerSize(30);
			hNai->SetMarkerStyle(markerStyle);
			hNai->Draw();
			dc->drawNai();
		}
		void drawPlas(){
			tree->Draw(Form("dEplas:espriAngle>>hPlas%d%d(1000,55,75,1000,0,20)",side,barId),gate);

			hPlas = (TH2F *)gDirectory->Get(Form("hPlas%d%d",side,barId));
			hPlas->SetMarkerColor(2);
			//hPlas->SetMarkerSize(30);
			hPlas->SetMarkerStyle(markerStyle);
			hPlas->Draw();
			dc->drawPlas();
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
		TH2F * getTot(){
			return hTot;
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
CheckEx* checkDEE(int side,int barId);
void drawAllBar(){

	TH2F *hTot;
	TH2F *hTOF;
	TH2F *hDEE;
	TH2F *hNai;
	TH2F *hPlas;
	TH1F *hEx;

	CheckEx *ce[2][7];

	int firstDraw = 0;
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j< 7; ++j) {
			ce[i][j] = checkDEE(i,j);
			if(firstDraw == 0){
				hTOF	 = ce[i][j]->getTOF();
				hTot	 = ce[i][j]->getTot();
				hEx	 = ce[i][j]->getEx();
				hDEE	 = ce[i][j]->getDEE();
				hNai	 = ce[i][j]->getNai();
				hPlas	 = ce[i][j]->getPlas();


				hTot	->SetName("hTot");
				hEx	->SetName("hEx");
				hTOF	->SetName("hTOF");
				hDEE	->SetName("hDEE");
				hNai	->SetName("hNai");
				hPlas	->SetName("hPlas");

				hTot	->SetTitle("protonEk:Angle");
				hEx	->SetTitle("Excitation Energy in g.s.");
				hTOF	->SetTitle("dEplas:TOF");
				hDEE	->SetTitle("dEplas:Enai");
				hNai	->SetTitle("Enai:Angle");
				hPlas	->SetTitle("Eplas:Angle");
	
			}else{
				hTot ->Add(ce[i][j]->getTot());
				hEx  ->Add(ce[i][j]->getEx());
				hTOF	->Add(ce[i][j]->getTOF());
				hDEE	->Add(ce[i][j]->getDEE());
				hNai ->Add(ce[i][j]->getNai());
				hPlas->Add(ce[i][j]->getPlas());
			}
			firstDraw++;
		}
	}
	TCanvas *newPad = new TCanvas("newPad","newPad",1800,900);
	DrawCurve *dc = new DrawCurve();
	newPad->Divide(3,2);

	newPad->cd(1);
	hTot->Draw();
	//hTot->Draw("colz");
	dc->drawTot();

	newPad->cd(2);
	hEx->Draw();

	newPad->cd(4);
	//hNai->Draw("colz");
	hNai->Draw();
	dc->drawNai();
	//
	newPad->cd(5);
	//hPlas->Draw("colz");
	hPlas->Draw();
	dc->drawPlas();

	newPad->cd(3);
	//hDEE->Draw("colz");
	hDEE->Draw();
	dc->drawDEE();

	newPad->cd(6);
	hTOF->Draw();
	//hTOF->Draw();

}
CheckEx* checkDEE(int side,int barId){

	TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
	cPad->Divide(3,2);
	CheckEx *ce = new CheckEx();
	ce->addFile("ppBe14.root_BeamTargetProtonPRAngleHodBar28-33");
	ce->setBar(side,barId);
	//ce->setCalibParas(gNai,dNai,gPlas,dPlas);
	ce->setAlias();
	ce->setGate();
	cPad->cd(1);
	ce->drawTot();
	cPad->cd(2);
	ce->drawNai();
	cPad->cd(3);
	ce->drawPlas();
	cPad->cd(4);
	ce->drawEx();
	cPad->cd(5);
	ce->drawDEE();
	cPad->cd(6);
	ce->drawTOF();
	ce->output();
	return ce;
	//delete ce;
}
void checkDEE(){

//	for (int i = 0; i < 2; ++i) {
//		for (int j = 0; j< 7; ++j) {
//
//			checkDEE(i,j);
//		}
//	}
	int side = 0;
	int barId = 4;
	checkDEE(side,barId);
//	drawAllBar();
}

