class DrawCurve{
	private:
		TGraph *tot_gs;
		TGraph *nai_gs;
		TGraph *plas_gs;

		TGraph *tot_fex;
		TGraph *nai_fex;
		TGraph *plas_fex;

		TGraph *dEE;

		
	public:
		DrawCurve(){
			TFile *fCurve1 = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/esBe10Excitation/espriDetectorEnergy_gs.root","READ");
			tot_gs = (TGraph *)gDirectory->Get("tot");
			nai_gs = (TGraph *)gDirectory->Get("nai");
			plas_gs = (TGraph *)gDirectory->Get("plas");
			fCurve1->Close();

			TFile *fCurve2 = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/esBe10Excitation/espriDetectorEnergy_fex.root","READ");
			tot_fex = (TGraph *)gDirectory->Get("tot");
			nai_fex = (TGraph *)gDirectory->Get("nai");
			plas_fex = (TGraph *)gDirectory->Get("plas");
			fCurve2->Close();



			TFile *fCurve3 = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/protonDEE/dEECurve.root","READ");
			dEE = (TGraph *)gDirectory->Get("dEE");
			fCurve3->Close();



		}
		void drawTot(){
			//tot->SetMarkerColor(1);
			//tot->SetLineColor(1);
			tot_gs->Draw("plsame");
			tot_fex->Draw("plsame");

		}
		void drawDEE(){
			dEE->SetMarkerColor(1);
			dEE->SetLineColor(1);
			dEE->Draw("psame");
		}
		void drawPlas(){
			plas_gs->SetMarkerColor(1);
			plas_gs->SetLineColor(1);
			plas_gs->Draw("plsame");
			plas_fex->Draw("plsame");
		}
		void drawNai(){
			//nai_gs->SetMarkerColor(1);
			//nai_gs->SetLineColor(1);
			nai_gs->Draw("lsame");
			nai_fex->Draw("lsame");

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

		double gain;
		double offset;

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
			//tree->SetAlias("beamEk","(Ek713-3.776)*MassBe");//Be14
			tree->SetAlias("beamEk","(Ek713-3.67)*MassBe");//Be10

			//tree->SetAlias("TOFSbtTarget","beamFL/(Beta713*SOL-0.654-0.626)"); // 0.654 diff F713 and F13-TGT, 0.626 diff Data to Theoretical point
			tree->SetAlias("TOFSbtTarget","beamFL/(Beta713*SOL-1.266)"); //Be10 
			tree->SetAlias("dEplas",Form("(%4f*plasBarQPed%d+%4f)",gPlas,side,dPlas));
			//tree->SetAlias("dEplas",Form("(%4f*plasBarQPed%d/(1+%4f*plasBarQPed%d))",gPlas,side,dPlas,side));
			tree->SetAlias("Tof",Form("(%4f*plasBarQPed%d+%4f)",gPlas,side,dPlas));
			tree->SetAlias("plasT0","(plasT[0]-0.01*(rdcY[0]-225))");
			tree->SetAlias("plasT1","(plasT[1]-0.0115*(rdcY[1]-225))");
			tree->SetAlias("espriTOF","((plasT[0]-F13T+895.2+19.84)-TOFSbtTarget)");
			//tree->SetAlias("TOF",Form("(plasT%d-F13T-TOFSbtTarget+895.2)+20.27-2.47",side));
			//tree->SetAlias("TOF",Form("(plasT%d-TOFSbtTarget+674.2)+20.27-2.47",side));

			//tree->SetAlias("espriTOF","(espriPlasT-TOFSbtTarget)");
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

		void setGate(){
			if(side !=-1&&barId != -1) gate = Form("espriHit==1&&espriHitSide[0]==%d&&naiHit==1&&naiHitBarId==%d",side,barId);
			if(side ==-1&&barId == -1) gate ="1";
			if(side ==0&&barId == -1) gate ="espriHit==1&&espriHitSide[0]==0";
			if(side ==1&&barId == -1) gate ="espriHit==1&&espriHitSide[0]==1";
		}
		void drawNaiQPedAngle(){
			tree->Draw(Form("naiHitQPed:espriAngle>>hNaiQPedAng%d%d(1000,55,75,1000,0,4000)",side,barId),gate);
		}
		void drawPlasQPedAngle(){
			tree->Draw(Form("plasHitQPed:espriAngle>>hPlasQPedAng%d%d(1000,55,75,1000,0,4000)",side,barId),gate);
		}
		void setCalibPara(double g,double o){
			gain =g;
			offset = o;
		}
		void drawNaiEAngle(){
			tree->Draw(Form("naiHitQPed*%4.4f+%4.3f:espriAngle>>hNaiEAng%d%d(1000,55,75,1000,0,150)",gain,offset,side,barId),gate);
			//tree->Draw(Form("espriNaiE_Pol3:espriAngle>>hNaiEAng%d%d(1000,55,75,1000,0,150)",side,barId),gate);
			TH2F *hNaiEAng = (TH2F *)gDirectory->Get(Form("hNaiEAng%d%d",side,barId));
			hNaiEAng->SetMarkerColor(2);
			//hEA->SetMarkerSize(30);
			hNaiEAng->SetMarkerStyle(markerStyle);

			hNaiEAng->Draw();
	
			dc->drawNai();
		}
		void drawPlasEAngle(){
			tree->Draw(Form("espriPlasE_Birks:espriAngle>>hPlasEAng%d%d(1000,55,75,1000,0,20)",side,barId),gate);
			dc->drawPlas();
		}



		void drawTot(){
			
			drawEA();
			drawEkAngle();

			hEA->Draw();
			hEkAngle->Draw("same");
			dc->drawTot();
		}
		void drawEA(){

			tree->Draw(Form("espriEnergy:espriAngle>>hEA%d%d(1000,55,75,1000,0,200)",side,barId),gate);

			hEA = (TH2F *)gDirectory->Get(Form("hEA%d%d",side,barId));
			hEA->SetMarkerColor(2);
			//hEA->SetMarkerSize(30);
			hEA->SetMarkerStyle(markerStyle);

			hEA->Draw();
			//dc->drawTot();
			//dc->drawBe10();
		}
		void drawEkAngle(){

			tree->Draw(Form("espriEk:espriAngle>>hEkAngle%d%d(1000,55,75,1000,0,200)",side,barId),gate);

			hEkAngle = (TH2F *)gDirectory->Get(Form("hEkAngle%d%d",side,barId));
			hEkAngle->SetMarkerColor(2);
			//hEkAngle->SetMarkerSize(30);
			hEkAngle->SetMarkerStyle(markerStyle);
	
			hEkAngle->Draw("");
			//dc->drawBe10();
			//dc->drawTot();
		}
	
	
		void drawEx(){
			tree->Draw(Form("excitationEnergy>>hEx%d%d(200,-10,10)",side,barId),gate);
			hEx = (TH1F *)gDirectory->Get(Form("hEx%d%d",side,barId));
			hEx->Draw();
		}

		void drawExDee(){
			tree->Draw(Form("excitationEnergy>>hExDee%d%d(50,-10,10)",side,barId),gate);
			hExDee = (TH1F *)gDirectory->Get(Form("hExDee%d%d",side,barId));
			hExDee->Draw();
			hExDee->Fit("gaus");
			gStyle->SetOptFit(1);
		}

		void drawExTof(){
			tree->Draw(Form("exEnergy>>hExTof%d%d(50,-10,10)",side,barId),gate);
			hExTof = (TH1F *)gDirectory->Get(Form("hExTof%d%d",side,barId));
			hExTof->Draw();
			hExTof->Fit("gaus");
			gStyle->SetOptFit(1);
		}



		void drawTOF(){
			tree->Draw(Form("dEplas:TOF>>hTOF%d(1000,0,40,1000,0,30)",side),gate);
			hTOF = (TH2F *)gDirectory->Get(Form("hTOF%d",side));
			hTOF->SetMarkerColor(2);
			hTOF->SetMarkerStyle(markerStyle);
			hTOF->Draw();
		}
		void drawTOFTot(){
			tree->Draw(Form("espriEnergy:espriEk>>hEkTOF%d(1000,0,200,1000,0,200)",side),gate);
			//tree->Draw(Form("espriEnergy:espriTOF>>hEkTOF%d(1000,0,40,1000,0,200)",side),gate);
			//tree->Draw(Form("espriFL:TOF>>hEkTOF%d(1000,0,20,1000,1200,1300)",side),gate);
			hEkTOF = (TH2F *)gDirectory->Get(Form("hEkTOF%d",side));
			hEkTOF->SetMarkerColor(2);
			hEkTOF->SetMarkerStyle(markerStyle);
			hEkTOF->Draw();

			TF1 *xyEq = new TF1("xyEq","x",0,200);
			xyEq->SetLineColor(3);
			xyEq->Draw("same");
	
		}
		void drawVelocityTOF(){

			tree->Draw(Form("espriTOF:protonVelocity>>hVTOF%d(1000,50,150,1000,0,40)",side),gate);
			//tree->Draw(Form("protonVelocity:(plasT%d-TOFSbtTarget+%f)>>hVTOF%d(1000,0,40,1000,50,150)",side,tofOffset,side),gate);
			hVTOF = (TH2F *)gDirectory->Get(Form("hVTOF%d",side));
			hVTOF->SetMarkerColor(2);
			hVTOF->SetMarkerStyle(7);

			TF1 *fit = new TF1("fit","[0]/(x)+[1]",90,115);
			fit->SetParLimits(0,1030,1330);
			fit->SetParLimits(1,-3,3);
			fit->SetLineColor(3);
			hVTOF->Fit(fit,"R","");


			tree->Draw(Form("espriTOF:espriFL/espriTOF>>hVTOFData%d(1000,50,150,1000,0,40)",side),gate);
			//tree->Draw(Form("(espriFL+%f)/(plasT0-TOFSbtTarget+%f):(plasT0-TOFSbtTarget+%f)>>hVTOFData%d(1000,0,40,1000,50,150)",flOffset,tofOffset,tofOffset,side),gate);
			TH2F *hVTOFData = (TH2F *)gDirectory->Get(Form("hVTOFData%d",side));
			hVTOFData->SetMarkerColor(1);
			hVTOFData->SetMarkerStyle(markerStyle);

			hVTOF->Draw();
			fit->Draw("same");
			hVTOFData->Draw("same");

		}
		void drawVelocityTOFRaw(){

			tree->Draw(Form("(plasT%d-TOFSbtTarget+%f):protonVelocity>>hVTOFRaw%d(1000,50,150,1000,0,40)",side,tofOffset,side),gate);
			//tree->Draw(Form("protonVelocity:(plasT%d-TOFSbtTarget+%f)>>hVTOFRaw%d(1000,0,40,1000,50,150)",side,tofOffset,side),gate);
			hVTOFRaw = (TH2F *)gDirectory->Get(Form("hVTOFRaw%d",side));
			hVTOFRaw->SetMarkerColor(2);
			hVTOFRaw->SetMarkerStyle(7);
			TF1 *fit = new TF1("fit","[0]/(x)+[1]",90,115);
			fit->SetParLimits(0,1030,1430);
			fit->SetParLimits(1,-5,5);
			fit->SetLineColor(3);
			hVTOFRaw->Fit(fit,"R","");

			tree->Draw(Form("(plasT%d-TOFSbtTarget+%f):(espriFL+%f)/(plasT%d-TOFSbtTarget+%f)>>hVTOFData%d(1000,50,150,1000,0,40)",side,tofOffset,flOffset,side,tofOffset,side),gate);
			//tree->Draw(Form("(espriFL+%f)/(plasT0-TOFSbtTarget+%f):(plasT0-TOFSbtTarget+%f)>>hVTOFData%d(1000,0,40,1000,50,150)",flOffset,tofOffset,tofOffset,side),gate);
			TH2F *hVTOFData = (TH2F *)gDirectory->Get(Form("hVTOFData%d",side));
			hVTOFData->SetMarkerColor(1);
			hVTOFData->SetMarkerStyle(markerStyle);
			hVTOFRaw->Draw();
			fit->Draw("same");
			hVTOFData->Draw("same");


		}
		void drawVVCorr(){
			tree->Draw(Form("protonVelocity:(espriFL+%f)/(plasT%d-TOFSbtTarget+%f)>>hVVCorr%d(1000,50,150,1000,50,150)",flOffset,side,tofOffset,side),gate);
			hVVCorr = (TH2F *)gDirectory->Get(Form("hVVCorr%d",side));
			hVVCorr->SetMarkerColor(2);
			hVVCorr->SetMarkerStyle(markerStyle);
			hVVCorr->Draw();
		}
		void drawFLCorr(){
			//tree->Draw(Form("protonVelocity*(plasT%d-TOFSbtTarget+%f):(espriFL+%f)>>hFLCorr%d(1000,1150,2200,1000,1150,2200)",side,tofOffset,flOffset,side),gate);
			tree->Draw(Form("(espriFL+%f)/protonVelocity:(plasT%d-TOFSbtTarget+%f)>>hFLCorr%d(1000,0,20,1000,0,20)",flOffset,side,tofOffset,side),gate);
			hFLCorr = (TH2F *)gDirectory->Get(Form("hFLCorr%d",side));
			hFLCorr->SetMarkerColor(2);
			hFLCorr->SetMarkerStyle(markerStyle);
			hFLCorr->Draw();
			gPad->SetGridx();
			gPad->SetGridy();
		}
		void drawFLTOF(){
			tree->Draw(Form("plasQ[%d]:(plasT%d-TOFSbtTarget+%f)>>hFLTOF%d(1000,0,40,1000,0,40)",side,side,tofOffset,side),gate);
			//tree->Draw(Form("protonVelocity*(plasT%d-TOFSbtTarget+%f):(plasT%d-TOFSbtTarget+%f)>>hFLTOF%d(1000,0,20,1000,1000,1500)",side,tofOffset,side,tofOffset,side),gate);
			//tree->Draw(Form("protonVelocity*(plasT%d-TOFSbtTarget+%f):TOF>>hFLTOF%d(1000,0,40,1000,1150,1500)",side,tofOffset,side),gate);
			hFLTOF = (TH2F *)gDirectory->Get(Form("hFLTOF%d",side));
			hFLTOF->SetMarkerColor(2);
			hFLTOF->SetMarkerStyle(markerStyle);
			hFLTOF->Draw();
		}












		void drawDEE(){
			tree->Draw(Form("espriPlasE:espriNaiE>>hDEE%d%d(1000,0,200,1000,0,30)",side,barId),gate);
			//tree->Draw(Form("dEplas:Enai>>hDEE%d%d(1000,0,200,1000,0,30)",side,barId),gate);
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
void drawBar(int side,int barId,double gain,double offset){

	int markerStyle = 1;
	if(side!=-1&&barId!=-1) markerStyle = 6;

	TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
	//cPad->Divide(2,2);
	CheckEx *ce = new CheckEx();
	//ce->addFile("ppBe14.root_BeamTargetProtonPRAngle");
	//ce->addFile("ppBe14.root_BeamTargetProtonHodBar28-33");
	ce->addFile("ppBe10.root");
	ce->setAlias();
	ce->setBar(side,barId);
	ce->setCalibPara(gain,offset);
	ce->setMarkerStyle(markerStyle);
	ce->setGate();

///	cPad->cd(1);
//	ce->drawPlasQPedAngle();
//	cPad->cd(2);
//	ce->drawPlasEAngle();
//	cPad->cd(3);
//	ce->drawNaiQPedAngle();
//	cPad->cd(4);
	ce->drawNaiEAngle();
	ce->output();
}

void calibNai(){
	
	drawBar(-1,-1); // draw all bars, left and right
	//drawBar(0,-1); // draw all left bars
	//drawBar(1,-1); // draw all right bars
	//drawBar(1,1); // draw bar side + barId
	//drawBar(0,0,0.038,-0.3); // draw bar side + barId
	//drawBar(0,1,0.040,1); // draw bar side + barId
	//drawBar(0,2,0.0375,1.5); // draw bar side + barId
	//drawBar(0,3,0.039,4.5); // draw bar side + barId
	//drawBar(0,4,0.035,3.5); // draw bar side + barId
	//drawBar(0,5,0.035,3.5); // draw bar side + barId
	//drawBar(0,6,0.039,3.5); // draw bar side + barId
	//
	//drawBar(1,0,0.026,9); // draw bar side + barId
	//drawBar(1,1,0.037,2); // draw bar side + barId
	//drawBar(1,2,0.035,3); // draw bar side + barId
	//drawBar(1,3,0.045,3); // draw bar side + barId
	//drawBar(1,4,0.028,9); // draw bar side + barId
	//drawBar(1,5,0.027,8); // draw bar side + barId
	//drawBar(1,6,0.035,5); // draw bar side + barId
	//drawBar(0,1); // draw bar side + barId
	//drawBar(0,2); // draw bar side + barId
}
