
void Be10_pid()
{

	TString gate1="(CoincidenceTrigger&2)";
	TString gate2="(sqrt(Target_Y*Target_Y+Target_X*Target_X)<10)";
	TString gate3="(SiLF_E[16]>100&&SiLB_E[18]>100)";//Pixel:SiLF_E[16]  SiLB_E[18]
	TString draw;
	TString color="colz";
	TString gate;

	TChain chain("AnalysisTree");

	//   // Be14
	chain.Add("analysedrootfiles/run0295_analysed_v1.root");
	chain.Add("analysedrootfiles/run0296_analysed_v1.root");
	chain.Add("analysedrootfiles/run0297_analysed_v1.root");
	chain.Add("analysedrootfiles/run0298_analysed_v1.root");
	chain.Add("analysedrootfiles/run0300_analysed_v1.root");
	chain.Add("analysedrootfiles/run0302_analysed_v1.root");
	chain.Add("analysedrootfiles/run0304_analysed_v1.root");

	TFile *g=new TFile("Be10_Tele_pid.root","recreate");
	TCanvas *cdEE[31];
	for(int stripid=26;stripid<27;stripid++)
	//for(int stripid=0;stripid<32;stripid++)
	{
		cdEE[stripid]=new TCanvas(Form("cdEE%d",stripid),Form("cdEE%d",stripid),900,900);
		cdEE[stripid]->Divide(2,2);

		cdEE[stripid]->cd(1);
		//AnalysisTree->Draw("SiLB_E[26]:CsI_LRB_E>>hstrip(1000,-100,1000,1000,-1000,35000)")
		draw=Form("SiLB_E[%d]:CsI_LRB_E>>hstrip%d(1000,-100,1000,1000,-1000,35000)",stripid,stripid);
		//gate="CsI_LRB_E<1050&&CsI_LRB_E>950";
		gate="";
		chain.Draw(draw,gate,color);
		gROOT->ProcessLine(".x draw_alpha.C");
		gPad->Modified();
		gPad->Update();
		gPad->SetLogz();
		TH2F *hstrip=(TH2F*)gDirectory->Get(Form("hstrip%d",stripid));
		hstrip->Write();

		cdEE[stripid]->cd(2);
		draw=Form("SiLB_E[%d]:CsI_LRB_E>>hstrip%d_gate1(1000,-100,1000,1000,-1000,35000)",stripid,stripid);
		//gate=gate1;
		///gROOT->ProcessLine(".x alpha.C");
		//gate="CsI_LRB_E<(310+6.8)&&CsI_LRB_E>(310-6.8)&&alpha";
		//gate="CsI_LRB_E<(495+7.5)&&CsI_LRB_E>(495-7.5)&&alpha";
		//gate="CsI_LRB_E<(200+3)&&CsI_LRB_E>(200-3)&&alpha";
		gate="Trig_DSB>0";
		chain.Draw(draw,gate,color);
		//gROOT->ProcessLine(".x alpha.C");
		gPad->Modified();
		gPad->Update();
		TH2F *hstrip_gate1=(TH2F*)gDirectory->Get(Form("hstrip%d_gate1",stripid));

		cdEE[stripid]->cd(3);
		draw=Form("SiLB_E[%d]:CsI_LRB_E>>hstrip%d_gate2(1000,-100,1000,1000,-1000,35000)",stripid,stripid);
		gate="Trig_BxTEL>0";
		chain.Draw(draw,gate,color);
		//TH1D * hstripX = hstrip_gate1->ProjectionX();
		//hstripX->Draw();
		gPad->Modified();
		gPad->Update();



		cdEE[stripid]->cd(4);
		draw=Form("SiLB_E[%d]:CsI_LRB_E>>hstrip%d_gate3(1000,-100,1000,1000,-1000,35000)",stripid,stripid);
		gate="Trig_BxESPRIxTEL>0";
		chain.Draw(draw,gate,color);
	
		//TH1D * hstripY = hstrip_gate1->ProjectionY();
		//hstripY->Draw();
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

