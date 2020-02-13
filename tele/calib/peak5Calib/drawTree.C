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

		TH1F *hDssdQPed[4];
		void drawDssdQPed(int peakId,int side,int isFB){
			if(isFB==0) tree->Draw(Form("teleHitDssdFQPed[0]>>hPeak%d_%d_%d(1000,0,4000)",peakId,side,isFB),"teleHit==1&&teleHitFid[0]==15&&"+gate);
			else tree->Draw(Form("teleHitDssdBQPed[0]>>hPeak%d_%d_%d(1000,0,4000)",peakId,side,isFB),"teleHit==1&&teleHitBid[0]==15&&"+gate);

			//tree->Draw(Form("teleDssdE>>hPeak%d_%d(1000,0,1000)",peakId,i),Form("teleHit==1&&teleHitCid[0]==%d&&",i)+gate);
			//tree->Draw(Form("teleHitDssdQPed[0]>>hPeak%d_%d(1000,0,4000)",peakId,i),Form("teleHit==1&&teleHitCid[0]==%d&&",i)+gate);
			int i = 2*side+isFB;
			hDssdQPed[i] = (TH1F *)gDirectory->Get(Form("hPeak%d_%d_%d",peakId,side,isFB));
			//hDssdQPed[i]->SetLineColor(i+1);
			hDssdQPed[i]->Draw();
			hDssdQPed[i]->Write();
		}

		TH1F *hCsiQPed[7];
		void drawCsiQPed(int peakId,int i){
			tree->Draw(Form("teleHitCsiQPed[0]>>hPeak%d_%d(1000,0,4000)",peakId,i),Form("teleHit==1&&teleHitCid[0]==%d&&",i)+gate);
			//tree->Draw(Form("teleCsiE>>hPeak%d_%d(1000,0,1000)",peakId,i),Form("teleHit==1&&teleHitCid[0]==%d&&",i)+gate);
			//tree->Draw(Form("teleHitCsiQPed[0]>>hPeak%d_%d(1000,0,4000)",peakId,i),Form("teleHit==1&&teleHitCid[0]==%d&&",i)+gate);
			hCsiQPed[i] = (TH1F *)gDirectory->Get(Form("hPeak%d_%d",peakId,i));
			//hCsiQPed[i]->SetLineColor(i+1);
			hCsiQPed[i]->Draw();
			hCsiQPed[i]->Write();
		}

		TH1F *hCheck[5];
		void drawRightCsiEnergy(int peakId){
			tree->Draw(Form("teleCsiE>>hPeak%d(500,0,1000)",peakId),"teleHit==1&&"+gate);
			hCheck[0] = (TH1F*)gDirectory->Get(Form("hPeak%d",peakId));
			hCheck[0]->SetLineColor(1);

			int cid =0;
			tree->Draw(Form("teleCsiE>>hPeak%d_%d(500,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[1] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[1]->SetLineColor(2);
			hCheck[1]->Draw();

			cid =1;
			tree->Draw(Form("teleCsiE>>hPeak%d_%d(500,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[2] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[2]->SetLineColor(3);

			cid =2;
			tree->Draw(Form("teleCsiE>>hPeak%d_%d(500,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[3] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[3]->SetLineColor(4);

			cid =3;
			tree->Draw(Form("teleCsiE>>hPeak%d_%d(500,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[4] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[4]->SetLineColor(5);
	
	
			hCheck[0]->Draw();
			hCheck[1]->Draw("same");
			hCheck[2]->Draw("same");
			hCheck[3]->Draw("same");
			hCheck[4]->Draw("same");
		}


		void drawRightAlphaEnergy(int peakId){
			tree->Draw(Form("alphaEnergy>>hPeak%d(1200,0,1000)",peakId),"teleHit==1&&"+gate);
			hCheck[0] = (TH1F*)gDirectory->Get(Form("hPeak%d",peakId));
			hCheck[0]->SetLineColor(1);

			int cid =0;
			tree->Draw(Form("alphaEnergy>>hPeak%d_%d(1200,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[1] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[1]->SetLineColor(2);
			hCheck[1]->Draw();

			cid =1;
			tree->Draw(Form("alphaEnergy>>hPeak%d_%d(1200,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[2] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[2]->SetLineColor(3);

			cid =2;
			tree->Draw(Form("alphaEnergy>>hPeak%d_%d(1200,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[3] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[3]->SetLineColor(4);

			cid =3;
			tree->Draw(Form("alphaEnergy>>hPeak%d_%d(1200,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[4] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[4]->SetLineColor(5);
	
	
			hCheck[0]->Draw();
			hCheck[1]->Draw("same");
			hCheck[2]->Draw("same");
			hCheck[3]->Draw("same");
			hCheck[4]->Draw("same");
		}


		void drawLeftAlphaEnergy(int peakId){
			tree->Draw(Form("alphaEnergy>>hPeak%d(700,0,1000)",peakId),"teleHit==1&&"+gate);
			hCheck[0] = (TH1F*)gDirectory->Get(Form("hPeak%d",peakId));
			hCheck[0]->SetLineColor(1);

			int cid =4;
			tree->Draw(Form("alphaEnergy>>hPeak%d_%d(700,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[1] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[1]->SetLineColor(2);
			hCheck[1]->Draw();

			cid =5;
			tree->Draw(Form("alphaEnergy>>hPeak%d_%d(700,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[2] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[2]->SetLineColor(3);

			cid =6;
			tree->Draw(Form("alphaEnergy>>hPeak%d_%d(700,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[3] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[3]->SetLineColor(4);
	
			hCheck[0]->Draw();
			hCheck[1]->Draw("same");
			hCheck[2]->Draw("same");
			hCheck[3]->Draw("same");
		}


		void drawLeftCsiEnergy(int peakId){
			tree->Draw(Form("teleCsiE>>hPeak%d(500,0,1000)",peakId),"teleHit==1&&"+gate);
			hCheck[0] = (TH1F*)gDirectory->Get(Form("hPeak%d",peakId));
			hCheck[0]->SetLineColor(1);

			int cid =4;
			tree->Draw(Form("teleCsiE>>hPeak%d_%d(500,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[1] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[1]->SetLineColor(2);
			hCheck[1]->Draw();

			cid =5;
			tree->Draw(Form("teleCsiE>>hPeak%d_%d(500,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[2] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[2]->SetLineColor(3);

			cid =6;
			tree->Draw(Form("teleCsiE>>hPeak%d_%d(500,0,1000)",peakId,cid),Form("teleHit==1&&teleHitCid[0]==%d&&",cid)+gate);
			hCheck[3] = (TH1F*)gDirectory->Get(Form("hPeak%d_%d",peakId,cid));
			hCheck[3]->SetLineColor(4);
	
			hCheck[0]->Draw();
			hCheck[1]->Draw("same");
			hCheck[2]->Draw("same");
			hCheck[3]->Draw("same");
		}

		TH1F *hCsiEnergy[7];
		void drawCsiEnergy(int peakId,int i){
			//tree->Draw(Form("teleHitCsiQPed[0]>>hPeak%d_%d(1000,0,4000)",peakId,i),Form("teleHit==1&&teleHitCid[0]==%d&&",i)+gate);
			tree->Draw(Form("teleCsiE>>hPeak%d_%d(500,0,1000)",peakId,i),Form("teleHit==1&&teleHitCid[0]==%d&&",i)+gate);
			//tree->Draw(Form("teleHitCsiQPed[0]>>hPeak%d_%d(1000,0,4000)",peakId,i),Form("teleHit==1&&teleHitCid[0]==%d&&",i)+gate);
			hCsiEnergy[i] = (TH1F *)gDirectory->Get(Form("hPeak%d_%d",peakId,i));
			//hCsiEnergy[i]->SetLineColor(i+1);
			hCsiEnergy[i]->Draw();
			hCsiEnergy[i]->Write();
		}


		TH2F *hTargetArea[5];
		void drawTargetArea(int peakId){
			tree->Draw(Form("vTarget.Y():vTarget.X()>>hPeak%d(1000,-50,50,1000,-50,50)",peakId),gate,"colz");
			hTargetArea[peakId] = (TH2F *)gDirectory->Get(Form("hPeak%d",peakId));
			//hTargetArea[peakId]->SetLpeakIdneColor(peakId+1);
			hTargetArea[peakId]->Draw("colz");
			hTargetArea[peakId]->Write();
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
TString getGate(int peakId){
	TString gate;
	TString targetArea="(sqrt((vTarget.X()-2.0)*(vTarget.X()-2.0)+(vTarget.Y()+1.1)*(vTarget.Y()+1.1))<13)";
	TString Frame="((vTarget.X()-2.0)<30&&(vTarget.X()-2.0)>-30&&(vTarget.Y()+1.1)<25&&(vTarget.Y()+1.1)>-35)";
	TString Neck="((vTarget.X()-2.0)<4&&(vTarget.X()-2.0)>-4&&(vTarget.Y()+1.1)>15&&(vTarget.Y()+1.1)<25)";

	TString R5="(sqrt((vTarget.X()-2.0)*(vTarget.X()-2.0)+(vTarget.Y()+1.1)*(vTarget.Y()+1.1))<14)";
	TString R4="(sqrt((vTarget.X()-2.0)*(vTarget.X()-2.0)+(vTarget.Y()+1.1)*(vTarget.Y()+1.1))<17)";
	TString R3="(sqrt((vTarget.X()-2.0)*(vTarget.X()-2.0)+(vTarget.Y()+1.1)*(vTarget.Y()+1.1))<20)";
	TString R2="(sqrt((vTarget.X()-2.0)*(vTarget.X()-2.0)+(vTarget.Y()+1.1)*(vTarget.Y()+1.1))<21)";
	TString R1="(sqrt((vTarget.X()-2.0)*(vTarget.X()-2.0)+(vTarget.Y()+1.1)*(vTarget.Y()+1.1))<15)";

	TString peak[5];
	 TString peak3_1="(!"+R5+"&&"+R4+"&&!"+Neck+")";
	 TString peak3_2="("+Neck+"&&!"+R2+")";

	 peak[0]=targetArea;
	 peak[1]="("+Neck+"&&"+R2+")";
	 peak[2]="("+peak3_1+"||"+peak3_2+")";
	 peak[3]="(!"+R1+"&&"+R2+"&&!"+Neck+")";
	 peak[4]="("+Frame+"&&!"+R3+"&&!"+Neck+")";

	 peak[0]+="&&(abs(teleCsiE-500.22)<20||abs(teleCsiE-318.27)<10)";
	 peak[1]+="&&(abs(teleCsiE-485.28)<10||abs(teleCsiE-297.24)<10)";
	 peak[2]+="&&(abs(teleCsiE-469.97)<10||abs(teleCsiE-275.030)<10)";
	 peak[3]+="&&(abs(teleCsiE-454.34)<10||abs(teleCsiE-251.38)<10)";
	 peak[4]+="&&(abs(teleCsiE-438.3)<10||abs(teleCsiE-225.87)<10)";
	 //peak[3]+="(!"+R1+"&&"+R2+"&&!"+Neck+")";
	 //peak[4]+="("+Frame+"&&!"+R3+"&&!"+Neck+")";



	return peak[peakId];
}
void checkTargetGate(){

	TString fileName = "targetAreaPeak5.root";
	CheckEx *ce = new CheckEx();
	ce->addFile("rootfiles/run0596_analysed.root");
//	ce->addFile("rootfiles/run0597_analysed.root");
//	ce->addFile("rootfiles/run0599_analysed.root");
//	ce->addFile("rootfiles/run0600_analysed.root");
	ce->setAlias();
	ce->loadCut();

	//TFile *outputFile = new TFile(fileName,"RECREATE");
	TFile *outputFile = new TFile(fileName,"UPDATE");
	TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
	cPad->Divide(3,2);
	for (int i = 0; i < 5; ++i) {
		cPad->cd(i+1);
		ce->setGate(getGate(i));
		ce->drawTargetArea(i);
	}
	ce->output();

}
void drawCsiQPed(){

	int peakId = 0;
	TString fileName = "calibCsiQPedPeak5.root";
	CheckEx *ce = new CheckEx();
	ce->addFile("rootfiles/run0596_analysed.root");
	ce->addFile("rootfiles/run0597_analysed.root");
	ce->addFile("rootfiles/run0598_analysed.root");
	ce->addFile("rootfiles/run0599_analysed.root");
	ce->addFile("rootfiles/run0600_analysed.root");
	ce->setAlias();
	ce->loadCut();
	ce->setGate(getGate(peakId));
	cout<<getGate(peakId)<<endl;

	//TFile *outputFile = new TFile(fileName,"RECREATE");
	TFile *outputFile = new TFile(fileName,"UPDATE");
	TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
	cPad->Divide(4,2);
	for (int i = 0; i < 7; ++i) {
		cPad->cd(i+1);
		ce->drawCsiQPed(peakId,i);
	}
	ce->output();
}

void drawCsiEnergy(){

	int peakId = 0;
	TString fileName = "checkCsiCalibPeak5.root";
	CheckEx *ce = new CheckEx();
	ce->addFile("rootfiles/run0596_analysed.root");
	ce->addFile("rootfiles/run0597_analysed.root");
	ce->addFile("rootfiles/run0598_analysed.root");
	ce->addFile("rootfiles/run0599_analysed.root");
	ce->addFile("rootfiles/run0600_analysed.root");
	ce->setAlias();
	ce->loadCut();
	ce->setGate(getGate(peakId));
	cout<<getGate(peakId)<<endl;

	//TFile *outputFile = new TFile(fileName,"RECREATE");
	TFile *outputFile = new TFile(fileName,"UPDATE");
	TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
	cPad->Divide(4,2);
	for (int i = 0; i < 7; ++i) {
		cPad->cd(i+1);
		ce->drawCsiEnergy(peakId,i);
	}
	ce->output();
}
void drawDssdQPed(){

	int peakId = 4;
	TString fileName = "calibDssdQPedPeak5.root";
	CheckEx *ce = new CheckEx();
	ce->addFile("rootfiles/run0596_analysed.root");
	ce->addFile("rootfiles/run0597_analysed.root");
	ce->addFile("rootfiles/run0598_analysed.root");
	ce->addFile("rootfiles/run0599_analysed.root");
	ce->addFile("rootfiles/run0600_analysed.root");
	ce->setAlias();
	ce->loadCut();
	ce->setGate(getGate(peakId));
	cout<<getGate(peakId)<<endl;

	//TFile *outputFile = new TFile(fileName,"RECREATE");
	TFile *outputFile = new TFile(fileName,"UPDATE");
	TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
	cPad->Divide(2,2);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j< 2; ++j) {
			cPad->cd(2*i+j+1);
			ce->drawDssdQPed(peakId,i,j);
		}
	}
	ce->output();
}

void checkCsiEnergy(){

	///int runNumber = 596;
	int runNumber = 599;
	int peakId = 0;
	TString fileName = Form("checkCsiEnergy%d.root",runNumber);
	CheckEx *ce = new CheckEx();
	ce->addFile(Form("rootfiles/run0%d_analysed.root",runNumber));
	ce->setAlias();
	ce->loadCut();
	ce->setGate(getGate(peakId));
	cout<<getGate(peakId)<<endl;

	//TFile *outputFile = new TFile(fileName,"RECREATE");
	TFile *outputFile = new TFile(fileName,"UPDATE");
	TCanvas *cPad = new TCanvas("cPad","cPad",1200,900);
	ce->drawLeftAlphaEnergy(peakId);
	//ce->drawRightAlphaEnergy(peakId);
//	ce->drawLeftCsiEnergy(peakId);
//	ce->drawRightCsiEnergy(peakId);
	ce->output();
}



void drawTree(){
	//drawDssdQPed();	
	//checkCsiEnergy();	
	//drawCsiQPed();	
	drawCsiEnergy();	
	//checkTargetGate();
}

