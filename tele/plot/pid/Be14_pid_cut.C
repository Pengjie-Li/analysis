
void Be14_pid_cut()
{

	TString draw;
	TString color="colz";
	TString gate;

	TChain chain("AnalysisTree");

	//   // Be14
	chain.Add("analysedrootfiles/run0381_analysed_v1.root");
	chain.Add("analysedrootfiles/run0382_analysed_v1.root");
	chain.Add("analysedrootfiles/run0383_analysed_v1.root");
	chain.Add("analysedrootfiles/run0384_analysed_v1.root");
	chain.Add("analysedrootfiles/run0385_analysed_v1.root");
	chain.Add("analysedrootfiles/run0386_analysed_v1.root");
	//
	//	// 20180522
	chain.Add("analysedrootfiles/run0426_analysed_v1.root");
	chain.Add("analysedrootfiles/run0427_analysed_v1.root");
	chain.Add("analysedrootfiles/run0428_analysed_v1.root");
	chain.Add("analysedrootfiles/run0429_analysed_v1.root");
	chain.Add("analysedrootfiles/run0430_analysed_v1.root");
	chain.Add("analysedrootfiles/run0433_analysed_v1.root");
	chain.Add("analysedrootfiles/run0434_analysed_v1.root");
	chain.Add("analysedrootfiles/run0435_analysed_v1.root");
	chain.Add("analysedrootfiles/run0436_analysed_v1.root");
	chain.Add("analysedrootfiles/run0437_analysed_v1.root");
	chain.Add("analysedrootfiles/run0438_analysed_v1.root");
//	//chain.Add("analysedrootfiles/run0450_analys_v1ed.root");



	TFile *g=new TFile("Be14_Tele_Resolution.root","recreate");
	TCanvas *cdEE[31];
	for(int stripid=26;stripid<27;stripid++)
	{

		cdEE[stripid]=new TCanvas(Form("cdEE%d",stripid),Form("cdEE%d",stripid),900,900);
		cdEE[stripid]->Divide(2,2);

		cdEE[stripid]->cd(1);
		draw=Form("SiLB_E[%d]:CsI_LRB_E>>hstrip%d_pid(1000,-100,1000,1000,-1000,25200)",stripid,stripid);
		gate="Trig_BxESPRIxTEL>0";
		chain.Draw(draw,gate,color);
		gROOT->ProcessLine(".x draw_alpha.C");
		gPad->Modified();
		gPad->Update();
	


		cdEE[stripid]->cd(2);
		//AnalysisTree->Draw("SiLB_E[26]:CsI_LRB_E>>hstrip(1000,-100,1000,1000,-1000,25200)")
		draw=Form("SiLB_E[%d]:CsI_LRB_E>>hstrip%d(1000,-100,1000,1000,-1000,25200)",stripid,stripid);
		//gate="CsI_LRB_E<1050&&CsI_LRB_E>950";
		gROOT->ProcessLine(".x alpha.C");
		//gate="Trig_BxESPRIxTEL>0&&CsI_LRB_E<(310+6.8)&&CsI_LRB_E>(310-6.8)&&alpha";
		//gate="(Trig_BxESPRIxTEL>0)";
		//gate="(Trig_BxESPRIxTEL>0)&&CsI_LRB_E>(310-6.8)";
		//gate="(Trig_BxESPRIxTEL>0)&&CsI_LRB_E<(310+6.8)&&CsI_LRB_E>(310-6.8)";
		//gate="CsI_LRB_E<(495+7.5)&&CsI_LRB_E>(495-7.5)&&alpha";
		//TString gate1="CsI_LRB_E>197";
		TString gate1="(Trig_BxESPRIxTEL>0)&&(CsI_LRB_E>303.2)&&(CsI_LRB_E<316.8)&&alpha";
		gROOT->ProcessLine(".x alpha.C");
		//TString gate1="CsI_LRB_E<(200+3)&&CsI_LRB_E>(200-3)&&alpha";
	
		chain.Draw(draw,gate1,color);
		gPad->Modified();
		gPad->Update();
		gPad->SetLogz();
		TH2F *hstrip=(TH2F*)gDirectory->Get(Form("hstrip%d",stripid));
		hstrip->Write();



		cdEE[stripid]->cd(3);
		TH1D * hstripX = hstrip->ProjectionX();
		hstripX->Draw();
		gPad->Modified();
		gPad->Update();




		cdEE[stripid]->cd(4);

		TH1D * hstripY = hstrip->ProjectionY();
		hstripY->Draw();
		gPad->Modified();
		gPad->Update();



		//	hstrip_gate1->Write();
		//	hstripX->Write();
	//	hstripY->Write();

		cdEE[stripid]->cd();
		cdEE[stripid]->Write();
	}



	//	hstore("Be14_Tele_pid.root");
}

