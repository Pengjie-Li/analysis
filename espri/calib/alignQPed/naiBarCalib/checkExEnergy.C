class CheckEx{
	private:
		TChain *tree;
		TCanvas *cPad;
		int side;
		int barId;
		double gPlas;
		double gNai;
		double dPlas;
		double dNai;

		TH2F *hTot;
		TH2F *hNai;
		TH2F *hPlas;
		TH1F *hEx;
		TGraph *tot;
		TGraph *nai;
		TGraph *plas;

		void drawTot(){

			cPad->cd(1);
			tree->Draw(Form("protonEk:espriAngle>>hTot%d%d(1000,55,75,1000,0,200)",side,barId));

			hTot = (TH2F *)gDirectory->Get(Form("hTot%d%d",side,barId));
			hTot->SetMarkerColor(2);
			//hTot->SetMarkerSize(30);
			hTot->SetMarkerStyle(6);
			hTot->Draw();
		}
		void drawEx(){
			cPad->cd(2);
			tree->Draw(Form("excitationEnergy>>hEx%d%d(200,-10,10)",side,barId));
			hEx = (TH1F *)gDirectory->Get(Form("hEx%d%d",side,barId));
			hEx->Draw();
		}
		void drawNai(){
			cPad->cd(3);
			tree->Draw(Form("Enai:espriAngle>>hNai%d%d(1000,55,75,1000,0,200)",side,barId));

			hNai = (TH2F *)gDirectory->Get(Form("hNai%d%d",side,barId));
			hNai->SetMarkerColor(2);
			//hNai->SetMarkerSize(30);
			hNai->SetMarkerStyle(6);
			hNai->Draw();
		}
		void drawPlas(){
			cPad->cd(4);
			tree->Draw(Form("dEplas:espriAngle>>hPlas%d%d(1000,55,75,1000,0,20)",side,barId),Form("isEspriLR==%d&&naiBarId==%d",side,barId));

			hPlas = (TH2F *)gDirectory->Get(Form("hPlas%d%d",side,barId));
			hPlas->SetMarkerColor(2);
			//hPlas->SetMarkerSize(30);
			hPlas->SetMarkerStyle(6);
			hPlas->Draw();
		}

	public:
		CheckEx(){

			tree = new TChain("tree");
			tree->Add("ppBe14.root");
			cPad = new TCanvas("cPad","cPad",1200,700);
			cPad->Divide(2,2);

		}
		void setBar(int s, int b){
			side = s; barId = b;
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


			tree->SetAlias("dEplas",Form("(%4f*plasBarQPed%d/(1+%4f*plasBarQPed%d))",gPlas,side,dPlas,side));
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
			drawTot();
			drawEx();
			drawNai();
			drawPlas();
		}

		void drawCurve(){
			TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/esBe14Excitation/espriDetectorEnergy.root","READ");
			cPad->cd(1);
			tot = (TGraph *)gDirectory->Get("tot");
			tot->SetMarkerColor(1);
			tot->SetLineColor(1);
			tot->Draw("plsame");

			cPad->cd(3);
			nai = (TGraph *)gDirectory->Get("nai");
			nai->SetMarkerColor(1);
			nai->SetLineColor(1);
			nai->Draw("plsame");

			cPad->cd(4);
			plas = (TGraph *)gDirectory->Get("plas");
			plas->SetMarkerColor(1);
			plas->SetLineColor(1);
			plas->Draw("plsame");

			fCurve->Close();

		}
		void output(){
			TFile *outputFile = new TFile(Form("rootfiles/Bar%d%d.root",side,barId),"RECREATE");
			cPad->Print(Form("png/Bar%d%d.png",side,barId));
			tot->Write();
			nai->Write();
			plas->Write();
			hTot->Write();
			hNai->Write();
			hPlas->Write();
			hEx->Write();
			outputFile->Close();
		}

		~CheckEx(){}
};
void checkExEnergy(){

	//int side = 0; int barId = 0;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.04; double dNai = 3; 
	//int side = 0; int barId = 1;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.04; double dNai = 3; 
	//int side = 0; int barId = 2;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.040; double dNai = 2.5; 
	//int side = 0; int barId = 3;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.04; double dNai = 7; 

	int side = 0; int barId = 4;double gPlas = 0.0037500;double dPlas = -0.0001; double gNai = 0.033; double dNai = 10; 
	//int side = 0; int barId = 4;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.033; double dNai = 10; 
	//int side = 0; int barId = 5;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.040; double dNai = 3; 
	//int side = 0; int barId = 6;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.040; double dNai = 3; 
	//int side = 1; int barId = 0;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 11.5; 
	//int side = 1; int barId = 1;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 12.5; 
	//int side = 1; int barId = 2;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 16; 
	//int side = 1; int barId = 3;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 20; 
	//int side = 1; int barId = 4;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 20; 
	//int side = 1; int barId = 5;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 20; 
	//int side = 1; int barId = 6;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 10; 

	CheckEx *ce = new CheckEx();
	ce->setBar(side,barId);
	ce->setCalibParas(gNai,dNai,gPlas,dPlas);
	ce->setAlias();
	ce->draw();
	ce->drawCurve();
	ce->output();
}

	//int side = 0; int barId = 0;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.04; double dNai = 3; 
	//int side = 0; int barId = 1;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.04; double dNai = 3; 
	//int side = 0; int barId = 2;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.040; double dNai = 2.5; 
	//int side = 0; int barId = 3;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.04; double dNai = 7; 

	//int side = 0; int barId = 4;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.033; double dNai = 10; 
	//int side = 0; int barId = 5;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.040; double dNai = 3; 
	//int side = 0; int barId = 6;double gPlas = 0.0037500;double dPlas = 0; double gNai = 0.040; double dNai = 3; 
	//int side = 1; int barId = 0;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 11.5; 
	//int side = 1; int barId = 1;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 12.5; 
	//int side = 1; int barId = 2;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 16; 
	//int side = 1; int barId = 3;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 20; 
	//int side = 1; int barId = 4;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 20; 
	//int side = 1; int barId = 5;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 20; 
	//int side = 1; int barId = 6;double gPlas = 0.0035000;double dPlas = 1; double gNai = 0.037; double dNai = 10; 


