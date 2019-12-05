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
		TCanvas *cPad;

		TCalibPara *calibPara;
		int side;
		int barId;
		double gPlas;
		double gNai;
		double dPlas;
		double dNai;

		TH2F *hTot;
		TH2F *hNai;
		TH2F *hPlas;
		TH2F *hDEE;
		TH1F *hEx;
		TString gate;
		TGraph *tot;
		TGraph *nai;
		TGraph *plas;
		TGraph *dEE;

		void drawTot(){

			cPad->cd(1);
			tree->Draw(Form("protonEk:espriAngle>>hTot%d%d(1000,55,75,1000,0,200)",side,barId),gate);

			hTot = (TH2F *)gDirectory->Get(Form("hTot%d%d",side,barId));
			hTot->SetMarkerColor(2);
			//hTot->SetMarkerSize(30);
			hTot->SetMarkerStyle(1);
			hTot->Draw();
		}
		void drawEx(){
			cPad->cd(2);
			tree->Draw(Form("excitationEnergy>>hEx%d%d(200,-10,10)",side,barId),gate);
			hEx = (TH1F *)gDirectory->Get(Form("hEx%d%d",side,barId));
			hEx->Draw();
		}

		void drawDEE(){
			cPad->cd(2);
			tree->Draw(Form("dEplas:Enai>>hDEE%d%d(1000,0,200,1000,0,30)",side,barId),gate);
			hDEE = (TH2F *)gDirectory->Get(Form("hDEE%d%d",side,barId));
			hDEE->SetMarkerColor(2);
			hDEE->SetMarkerStyle(1);
			hDEE->Draw();
		}
		void drawNai(){
			cPad->cd(3);
			tree->Draw(Form("Enai:espriAngle>>hNai%d%d(1000,55,75,1000,0,200)",side,barId),gate);

			hNai = (TH2F *)gDirectory->Get(Form("hNai%d%d",side,barId));
			hNai->SetMarkerColor(2);
			//hNai->SetMarkerSize(30);
			hNai->SetMarkerStyle(1);
			hNai->Draw();
		}
		void drawPlas(){
			cPad->cd(4);
			tree->Draw(Form("dEplas:espriAngle>>hPlas%d%d(1000,55,75,1000,0,20)",side,barId),gate);

			hPlas = (TH2F *)gDirectory->Get(Form("hPlas%d%d",side,barId));
			hPlas->SetMarkerColor(2);
			//hPlas->SetMarkerSize(30);
			hPlas->SetMarkerStyle(1);
			hPlas->Draw();
		}

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
			tree->Add("ppBe14.root");
			cPad = new TCanvas("cPad","cPad",1200,700);
			cPad->Divide(2,2);
			calibPara = new TCalibPara();
		}
		CheckEx(int side,int barId):side(side),barId(barId){

			tree = new TChain("tree");
			tree->Add("ppBe14.root");
			cPad = new TCanvas("cPad","cPad",1200,700);
			cPad->Divide(2,2);
			calibPara = new TCalibPara();
			setCalibParas(getNaiGain(),getNaiDead(),getPlasGain(),getPlasDead());
			setAlias();
			draw();
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
			tree->SetAlias("beamEk","(Ek713-3.765)*MassBe");


			tree->SetAlias("dEplas",Form("(%4f*plasBarQPed%d+%4f)",gPlas,side,dPlas));
			//tree->SetAlias("dEplas",Form("(%4f*plasBarQPed%d/(1+%4f*plasBarQPed%d))",gPlas,side,dPlas,side));
			tree->SetAlias("Enai",Form("%4f*naiBarQPed%d%d+%4f",gNai,side,barId,dNai));
			tree->SetAlias("protonEk","dEplas+Enai");

			tree->SetAlias("beamMomentum","sqrt(beamEk*beamEk+2*beamEk*beamMass)");
			tree->SetAlias("protonMomentum","sqrt(protonEk*protonEk+2*protonEk*protonMass)");

			tree->SetAlias("residueMomentum","sqrt(beamMomentum*beamMomentum + protonMomentum*protonMomentum - 2*beamMomentum*protonMomentum*cos(espriAngle*TMath::DegToRad()))");
			tree->SetAlias("residueEnergy","beamEk + beamMass - protonEk");
			tree->SetAlias("residueMass","sqrt(residueEnergy*residueEnergy - residueMomentum*residueMomentum)");
			tree->SetAlias("excitationEnergy","residueMass-beamMass");

		}

		void draw(){
			gate = Form("isEspriLR==%d&&naiBarId==%d",side,barId);
			drawTot();
			//drawEx();
			drawDEE();
			drawNai();
			drawPlas();
		}

		void drawCurve(){

			DrawCurve *dc = new DrawCurve();
			cPad->cd(1);
			dc->drawTot();

			cPad->cd(2);
			dc->drawDEE();


			cPad->cd(3);
			dc->drawNai();

			cPad->cd(4);
			dc->drawPlas();
			
		}
		void output(){
			//TFile *outputFile = new TFile(Form("rootfiles/Bar%d%d.root",side,barId),"RECREATE");
			cPad->Print(Form("png/Bar%d%d.png",side,barId));
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
		TH2F * getNai(){
			return hNai;
		}
		TH2F * getPlas(){
			return hPlas;
		}





		~CheckEx(){
			delete tree;
			delete cPad;
			delete calibPara;
		}
};
void checkDEE(int side,int barId){

	CheckEx *ce = new CheckEx();
	ce->setBar(side,barId);
	//ce->setCalibParas(gNai,dNai,gPlas,dPlas);
	ce->setAlias();
	ce->draw();
	ce->drawCurve();
	ce->output();
	delete ce;
}
void checkDEE(){

	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j< 7; ++j) {

			checkDEE(i,j);
		}
	}
	//int side = 0;
	//int barId = 4;
		//checkDEE(side,barId);

//	TH2F *hTot;
//	TH2F *hDEE;
//	TH2F *hNai;
//	TH2F *hPlas;
//	TH1F *hEx;
//	CheckEx *ce[2][7];
//
//	int firstDraw = 0;
//	for (int i = 0; i < 2; ++i) {
//		for (int j = 0; j< 7; ++j) {
//			ce[i][j] = new CheckEx(i,j);
//			if(firstDraw == 0){
//				hTot	 = ce[i][j]->getTot();
//				hEx	 = ce[i][j]->getEx();
//				hNai	 = ce[i][j]->getNai();
//				hPlas	 = ce[i][j]->getPlas();
//
//
//				hTot	->SetName("hTot");
//				hEx	->SetName("hEx");
//				hNai	->SetName("hNai");
//				hPlas	->SetName("hPlas");
//
//				hTot	->SetTitle("protonEk:Angle");
//				hEx	->SetTitle("Excitation Energy in g.s.");
//				hNai	->SetTitle("Enai:Angle");
//				hPlas	->SetTitle("Eplas:Angle");
//	
//			}else{
//				hTot ->Add(ce[i][j]->getTot());
//				hEx  ->Add(ce[i][j]->getEx());
//				hNai ->Add(ce[i][j]->getNai());
//				hPlas->Add(ce[i][j]->getPlas());
//			}
//			firstDraw++;
//		}
//	}
//	TCanvas *newPad = new TCanvas("newPad","newPad",1500,900);
//	DrawCurve *dc = new DrawCurve();
//	newPad->Divide(2,2);
//
//	newPad->cd(1);
//	hTot->Draw("colz");
//	dc->drawTot();
//
//	newPad->cd(2);
//	hEx->Draw();
//	//dc->drawDEE();
//	//
//	newPad->cd(3);
//	hNai->Draw("colz");
//	dc->drawNai();
//
//	newPad->cd(4);
//	hPlas->Draw("colz");
//	dc->drawPlas();

}
