
void Be14_pid()
{

	//pid_pixel();// PID Plots with selected pixel
	//pid_right();// PID Plots for right Telescope
	//pid_left();// PID Plots for left Telescope

}
void pid_trigger() // PID Plots with different ttrigger
{

	TString gate1="(CoincidenceTrigger&2)";
	TString gate2="(sqrt(Target_Y*Target_Y+Target_X*Target_X)<10)";
	TString gate3="(SiLF_E[16]>100&&SiLB_E[18]>100)";//Pixel:SiLF_E[16]  SiLB_E[18]
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
	//chain.Add("analysedrootfiles/run0450_analys_v1ed.root");


	TFile *g=new TFile("Be14_Tele_pid_trigger.root","recreate");
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
		//draw=Form("SiLB_E[%d]:CsI_LRB_E>>hstrip%d_gate3(500,-100,1000,500,-1000,35000)",stripid,stripid);
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

void pid_pixel() // PID Plots with selected pixel
{

	TString gate1="(CoincidenceTrigger&2)";
	TString gate2="(sqrt(Target_Y*Target_Y+Target_X*Target_X)<10)";
	TString gate3="(SiLF_E[16]>300)";
	TString draw;
	TString color="colz";
	TString gate;

	TChain chain("AnalysisTree");

	//   // Be14
	chain.Add("analysedrootfiles/run0381_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0382_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0383_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0384_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0385_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0386_analysed_v1.root");
	//////
	//////	// 20180522
	//	chain.Add("analysedrootfiles/run0426_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0427_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0428_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0429_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0430_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0433_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0434_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0435_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0436_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0437_analysed_v1.root");
	//	chain.Add("analysedrootfiles/run0438_analysed_v1.root");
	//chain.Add("analysedrootfiles/run0450_analys_v1ed.root");


	TFile *g=new TFile("Be14_Tele_pid_pixel.root","recreate");
	TCanvas *cpid_Pixel[31];
	for(int stripid=26;stripid<27;stripid++)
		//for(int stripid=0;stripid<32;stripid++)
	{
		cpid_Pixel[stripid]=new TCanvas(Form("cpid_Pixel%d",stripid),Form("cpid_Pixel%d",stripid),900,900);
		cpid_Pixel[stripid]->Divide(2,2);

		cpid_Pixel[stripid]->cd(1);
		draw=Form("SiLB_E:CsI_LRB_E>>hstrip%d(1000,-100,1000,1000,-1000,35000)",stripid);
		gate="";
		chain.Draw(draw,gate,color);
		gROOT->ProcessLine(".x draw_alpha.C");
		gPad->Modified();
		gPad->Update();
		gPad->SetLogz();

		cpid_Pixel[stripid]->cd(2);
		draw=Form("SiRB_E:CsI_RLB_E>>hstrip%d_gate1(1000,-100,1000,1000,-1000,35000)",stripid);
		gate="";
		//gate=gate3;
		chain.Draw(draw,gate,color);
		gPad->Modified();
		gPad->Update();

		cpid_Pixel[stripid]->cd(3);
		draw=Form("SiLB_E:CsI_LRB_E>>hstrip%d_gate2(1000,-100,1000,1000,-1000,35000)",stripid);
		//gate="Trig_BxTEL>0";
		gate="Trig_BxESPRIxTEL>0";
		chain.Draw(draw,gate,color);
		//TH1D * hstripX = hstrip_gate1->ProjectionX();
		//hstripX->Draw();
		gPad->Modified();
		gPad->Update();



		cpid_Pixel[stripid]->cd(4);
		draw=Form("SiRB_E:CsI_RLB_E>>hstrip%d_gate3(1000,-100,1000,1000,-1000,35000)",stripid);
		//gate="Trig_BxESPRIxTEL>0&&"+gate3;
		gate="Trig_BxESPRIxTEL>0";
		chain.Draw(draw,gate,color);

		//TH1D * hstripY = hstrip_gate1->ProjectionY();
		//hstripY->Draw();
		gPad->Modified();
		gPad->Update();



		//	hstrip_gate1->Write();
		//	hstripX->Write();
		//	hstripY->Write();

		cpid_Pixel[stripid]->cd();
		cpid_Pixel[stripid]->Write();
	}



	//	hstore("Be14_Tele_pid.root");
}

void pid_right() // PID Plots for right Telescope
{

	TString gate1="(CoincidenceTrigger&2)";
	TString gate2="(sqrt(Target_Y*Target_Y+Target_X*Target_X)<10)";
	TString gate3="(SiLF_E[16]>300)";
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
//	////
//	////	// 20180522
//	chain.Add("analysedrootfiles/run0426_analysed_v1.root");
//	chain.Add("analysedrootfiles/run0427_analysed_v1.root");
//	chain.Add("analysedrootfiles/run0428_analysed_v1.root");
//	chain.Add("analysedrootfiles/run0429_analysed_v1.root");
//	chain.Add("analysedrootfiles/run0430_analysed_v1.root");
//	chain.Add("analysedrootfiles/run0433_analysed_v1.root");
//	chain.Add("analysedrootfiles/run0434_analysed_v1.root");
//	chain.Add("analysedrootfiles/run0435_analysed_v1.root");
//	chain.Add("analysedrootfiles/run0436_analysed_v1.root");
//	chain.Add("analysedrootfiles/run0437_analysed_v1.root");
//	chain.Add("analysedrootfiles/run0438_analysed_v1.root");
	//chain.Add("analysedrootfiles/run0450_analys_v1ed.root");


	TFile *g=new TFile("Be14_Tele_right.root","recreate");
	TCanvas *cpid_rf;
	cpid_rf=new TCanvas("cpid_rf","cpid_rf",900,900);
	cpid_rf->Divide(2,2);

	cpid_rf->cd(1);
	draw="SiRF_E:CsI_RLT_E>>hRFRLT(1000,-100,1000,1000,-1000,35000)";
	gate="Trig_BxESPRIxTEL>0";
	//gate="";
	chain.Draw(draw,gate,color);
	gPad->Modified();
	gPad->Update();
	gPad->SetLogz();

	cpid_rf->cd(2);
	draw="SiRF_E:CsI_RLB_E>>hRFRLB(1000,-100,1000,1000,-1000,35000)";
	//gate="";
	gate="Trig_BxESPRIxTEL>0";
	chain.Draw(draw,gate,color);
	gPad->Modified();
	gPad->Update();

	cpid_rf->cd(3);
	draw="SiRF_E:CsI_RRT_E>>hRFRRT(1000,-100,1000,1000,-1000,35000)";
	gate="Trig_BxESPRIxTEL>0";
	chain.Draw(draw,gate,color);
	gPad->Modified();
	gPad->Update();



	cpid_rf->cd(4);
	draw="SiRF_E:CsI_RRB_E>>hRFRRB(1000,-100,1000,1000,-1000,35000)";
	gate="Trig_BxESPRIxTEL>0";
	chain.Draw(draw,gate,color);

	gPad->Modified();
	gPad->Update();


	TCanvas *cpid_rb;
	cpid_rb=new TCanvas("cpid_rb","cpid_rb",900,900);
	cpid_rb->Divide(2,2);

	cpid_rb->cd(1);
	draw="SiRB_E:CsI_RLT_E>>hRBRLT(1000,-100,1000,1000,-1000,35000)";
	gate="Trig_BxESPRIxTEL>0";
	//gate="";
	chain.Draw(draw,gate,color);
	gPad->Modified();
	gPad->Update();
	gPad->SetLogz();

	cpid_rb->cd(2);
	draw="SiRB_E:CsI_RLB_E>>hRBRLB(1000,-100,1000,1000,-1000,35000)";
	//gate="";
	gate="Trig_BxESPRIxTEL>0";
	chain.Draw(draw,gate,color);
	gPad->Modified();
	gPad->Update();

	cpid_rb->cd(3);
	draw="SiRB_E:CsI_RRT_E>>hRBRRT(1000,-100,1000,1000,-1000,35000)";
	gate="Trig_BxESPRIxTEL>0";
	chain.Draw(draw,gate,color);
	gPad->Modified();
	gPad->Update();



	cpid_rb->cd(4);
	draw="SiRB_E:CsI_RRB_E>>hRBRRB(1000,-100,1000,1000,-1000,35000)";
	gate="Trig_BxESPRIxTEL>0";
	chain.Draw(draw,gate,color);

	gPad->Modified();
	gPad->Update();


	cpid_rf->cd();
	cpid_rb->cd();
	cpid_rf->Write();
	cpid_rb->Write();
}

void pid_left() // PID Plots for left Telescope
{

	TString gate1="(CoincidenceTrigger&2)";
	TString gate2="(sqrt(Target_Y*Target_Y+Target_X*Target_X)<10)";
	TString gate3="(SiLF_E[16]>300)";
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
//	////
//	////	// 20180522
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
	//chain.Add("analysedrootfiles/run0450_analys_v1ed.root");


	TFile *g=new TFile("Be14_Tele_left.root","recreate");
	TCanvas *cpid_lf;
	cpid_lf=new TCanvas("cpid_lf","cpid_lf",900,900);
	cpid_lf->Divide(2,2);

	cpid_lf->cd(1);
	draw="SiLF_E:CsI_LL_E>>hLFLL(1000,-100,1000,1000,-1000,35000)";
	gate="Trig_BxESPRIxTEL>0";
	//gate="";
	chain.Draw(draw,gate,color);
	gPad->Modified();
	gPad->Update();
	gPad->SetLogz();

	cpid_lf->cd(2);
	draw="SiLF_E:CsI_LL_E>>hLFLL(1000,-100,1000,1000,-1000,35000)";
	//gate="";
	gate="Trig_BxESPRIxTEL>0";
	chain.Draw(draw,gate,color);
	gPad->Modified();
	gPad->Update();

	cpid_lf->cd(3);
	draw="SiLF_E:CsI_LRT_E>>hLFLRT(1000,-100,1000,1000,-1000,35000)";
	gate="Trig_BxESPRIxTEL>0";
	chain.Draw(draw,gate,color);
	gPad->Modified();
	gPad->Update();



	cpid_lf->cd(4);
	draw="SiLF_E:CsI_LRB_E>>hLFLRB(1000,-100,1000,1000,-1000,35000)";
	gate="Trig_BxESPRIxTEL>0";
	chain.Draw(draw,gate,color);

	gPad->Modified();
	gPad->Update();


	TCanvas *cpid_lb;
	cpid_lb=new TCanvas("cpid_lb","cpid_lb",900,900);
	cpid_lb->Divide(2,2);

	cpid_lb->cd(1);
	draw="SiLB_E:CsI_LL_E>>hLBLL(1000,-100,1000,1000,-1000,35000)";
	gate="Trig_BxESPRIxTEL>0";
	//gate="";
	chain.Draw(draw,gate,color);
	gPad->Modified();
	gPad->Update();
	gPad->SetLogz();

	cpid_lb->cd(2);
	draw="SiLB_E:CsI_LL_E>>hLBLL(1000,-100,1000,1000,-1000,35000)";
	chain.Draw(draw,gate,color);
	gPad->Modified();
	gPad->Update();

	cpid_lb->cd(3);
	draw="SiLB_E:CsI_LRT_E>>hLBLRT(1000,-100,1000,1000,-1000,35000)";
	gate="Trig_BxESPRIxTEL>0";
	chain.Draw(draw,gate,color);
	gPad->Modified();
	gPad->Update();



	cpid_lb->cd(4);
	draw="SiLB_E:CsI_LRB_E>>hLBLRB(1000,-100,1000,1000,-1000,35000)";
	gate="Trig_BxESPRIxTEL>0";
	chain.Draw(draw,gate,color);

	gPad->Modified();
	gPad->Update();


	cpid_lf->cd();
	cpid_lb->cd();
	cpid_lf->Write();
	cpid_lb->Write();
}



