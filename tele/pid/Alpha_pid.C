
void Alpha_pid()
{

	TString gate1="(CoincidenceTrigger&1)";
	TString gate2="(sqrt(Target_Y*Target_Y+Target_X*Target_X)<13)";
	TString gate3="(SiLF_E[16]>100&&SiLB_E[18]>100)";//Pixel:SiLF_E[16]  SiLB_E[18]
	TString gate4="(SiLF_E[10]>1000||SiLF_E[11]>1000||SiLF_E[12]>1000||SiLF_E[13]>1000||SiLF_E[14]>1000||SiLF_E[15]>1000||SiLF_E[16]>1000||SiLF_E[17]>1000||SiLF_E[18]>1000||SiLF_E[19]>1000||SiLF_E[20]>1000)";
	TString gate6="(CsI_LRT_E<100&&CsI_LRB_E<100)";
	TString draw;
	TString color="colz";
	TString gate;

	TChain chain("AnalysisTree");

	//   
	//chain.Add("analysedrootfiles/run0595_analysed.root");
	chain.Add("analysedrootfiles/run0596_analysed.root");
	chain.Add("analysedrootfiles/run0599_analysed.root");

	TFile *g=new TFile("Alpha_Tele_pid.root","UPDATE");
	TCanvas *cdEE[31];
	for(int stripid=11;stripid<12;stripid++)
	{

		TString gate5=Form("(SiLB_E[%d]<200&&SiLB_E[%d]<200)",stripid-1,stripid+1);
		TString gate6="(CsI_LRT_E<50&&CsI_LRB_E<50)";
		cout<<gate5<<endl;
		cdEE[stripid]=new TCanvas(Form("cdEE%d",stripid),Form("cdEE%d",stripid),900,900);
		cdEE[stripid]->Divide(2,2);

		cdEE[stripid]->cd(1);
		draw=Form("SiLB_E[%d]:CsI_LL_E>>hstrip%d(1000,-100,1000,1000,-1000,25200)",stripid,stripid);
		gate=gate5+"&&"+gate6;

		chain.Draw(draw,gate,color);
		gROOT->ProcessLine(".x draw_alpha.C");
		gPad->Modified();
		gPad->Update();
		gPad->SetLogz();
		TH2F *hstrip=(TH2F*)gDirectory->Get(Form("hstrip%d",stripid));
		hstrip->Write();



		cdEE[stripid]->cd(2);

		draw=Form("SiLB_E[%d]:CsI_LL_E>>hstrip%d_gate1(1000,-100,1000,1000,-1000,25200)",stripid,stripid);
		//gate=gate1;
		gROOT->ProcessLine(".x alpha.C");
		TString gate7="CsI_LL_E<(310+6.8)&&CsI_LL_E>(310-6.8)&&alpha";
		//TString gate7="CsI_LL_E<(495+7.5)&&CsI_LL_E>(495-7.5)&&alpha";
		//TString gate7="CsI_LL_E<(200+3)&&CsI_LL_E>(200-3)&&alpha";
		//TString gate7="alpha";

		gate=gate5+"&&"+gate6+"&&"+gate7;
		//gate=gate7;
		cout<<gate<<endl;
		chain.Draw(draw,gate,color);
		gROOT->ProcessLine(".x alpha.C");
		gPad->Modified();
		gPad->Update();
		TH2F *hstrip_gate1=(TH2F*)gDirectory->Get(Form("hstrip%d_gate1",stripid));
		cdEE[stripid]->cd(3);
		TH1D * hstripX = hstrip_gate1->ProjectionX();
		hstripX->Draw();
		gPad->Modified();
		gPad->Update();



		cdEE[stripid]->cd(4);
		TH1D * hstripY = hstrip_gate1->ProjectionY();
		hstripY->Draw();
		gPad->Modified();
		gPad->Update();




		hstrip_gate1->Write();
		hstripX->Write();
		hstripY->Write();


		cdEE[stripid]->cd(0);
		cdEE[stripid]->Write();
	}






	//	hstore("Be14_Tele_pid.root");
}

