void fitR()
{
  DSSD();
//  CsI();

}

void DSSD()
{
        

        int fid=15; int bid=15;
	double Energy[2]={7017.5,9777.9};
	double E[3]; E[0]=0;E[1]=Energy[0];E[2]=Energy[1];

	double ADCF[2]={1228.09,1618.28};
	double pedF=91.78;
	double fadc[3]; fadc[0]=pedF;fadc[1]=ADCF[0];fadc[2]=ADCF[1];


	double ADCB[2]={1127.85,1486.42};
	double pedB=84.81;
	double badc[3]; badc[0]=pedB;badc[1]=ADCB[0];badc[2]=ADCB[1];

	TCanvas *cF=new TCanvas("cF","cF",600,600);
	cF->cd();
	TGraph *gf3=new TGraph(3,fadc,E);
	gf3->SetName("gf3");
	gf3->SetTitle("Pixel 15_15 SiRF ADC vs Energy");
	gf3->GetXaxis()->SetTitle("ADC(ch)");
	gf3->GetYaxis()->SetTitle("Energy(MeV)");
	gf3->SetMarkerStyle(21);
	gf3->SetMarkerSize(1);
	gf3->SetMarkerColor(3);
	gf3->Draw("AP");



	TF1 *ff=new TF1("ff","pol1",0,4000);
	//ff->SetParameters(bf,kf);
	ff->SetLineColor(2);
	gf3->Fit(ff);
	ff->Draw("same");

	TCanvas *cB=new TCanvas("cB","cB",600,600);
	cB->cd();
	TGraph *gb3=new TGraph(3,badc,E);
	gb3->SetName("gb3");
	gb3->SetTitle("Pixel 15_15 SiRB ADC vs Energy");
	gb3->GetXaxis()->SetTitle("ADC(ch)");
	gb3->GetYaxis()->SetTitle("Energy(MeV)");
	gb3->SetMarkerStyle(21);
	gb3->SetMarkerSize(1);
	gb3->SetMarkerColor(3);
	gb3->Draw("AP");



	TF1 *fb=new TF1("fb","pol1",0,4000);
	fb->SetLineColor(2);
	gb3->Fit(fb);
	fb->Draw("same");



}
