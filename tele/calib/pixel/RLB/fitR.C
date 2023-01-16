void fitR()
{
//  DSSD();
  CsI();

}
void CsI()
{
	double Energy[2]={311.03,495.05};
	double E[3]; E[0]=0;E[1]=Energy[0];E[2]=Energy[1];

	double ADC[2]={1.10489e+03,1.55832e+03};
	double ADC_Sigma[2]={7.85300e+00,8.66053e+00};
	double ped=9.51679e+01; // 9.50990e+01
	double adc[3]; adc[0]=ped;adc[1]=ADC[0];adc[2]=ADC[1];


	TCanvas *cCsI=new TCanvas("cCsI","cCsI",600,600);
	cCsI->cd();
	TGraph *gCsI3=new TGraph(3,adc,E);
	gCsI3->SetName("gCsI3");
	gCsI3->SetTitle("Pixel CsI ADC vs Energy");
	gCsI3->GetXaxis()->SetTitle("ADC(ch)");
	gCsI3->GetYaxis()->SetTitle("Energy(MeV)");
	
	gCsI3->SetMarkerStyle(21);
	gCsI3->SetMarkerSize(1);
	gCsI3->SetMarkerColor(3);
	gCsI3->Draw("APL");



	TGraph *gCsI2=new TGraph(2,ADC,Energy);
	gCsI2->SetName("gCsI2");
	gCsI2->SetMarkerStyle(20);
	gCsI2->SetMarkerSize(1);
	gCsI2->SetMarkerColor(2);
	gCsI2->Draw("Psame");
	double k=(Energy[1]-Energy[0])/(ADC[1]-ADC[0]);
	double b=Energy[1]-k*ADC[1];
	cout<<"k="<<k<<" b="<<b<<endl;

	TF1 *fCsI=new TF1("fCsI","pol1",0,4000);
	fCsI->SetParameters(b,k);
	fCsI->SetLineColor(2);
	fCsI->Draw("same");





}
void DSSD()
{
        

	double Energy[2]={7017.5,9777.9};
	double E[3]; E[0]=0;E[1]=Energy[0];E[2]=Energy[1];

	double ADCF[2]={1228,1616};
	double ADCF_Sigma[2]={6.60764e+01,6.73684e+01};
	double pedF=94.0844;
	double fadc[3]; fadc[0]=pedF;fadc[1]=ADCF[0];fadc[2]=ADCF[1];


	double ADCB[2]={1127,1488};
	double ADCB_Sigma[2]={6.06949e+01,6.13662e+01};
	double pedB=114.91;
	double badc[3]; badc[0]=pedB;badc[1]=ADCB[0];badc[2]=ADCB[1];

	TCanvas *cF=new TCanvas("cF","cF",600,600);
	cF->cd();
	TGraph *gf3=new TGraph(3,fadc,E);
	gf3->SetName("gf3");
	gf3->SetTitle("Pixel DSSD Front ADC vs Energy");
	gf3->GetXaxis()->SetTitle("ADC(ch)");
	gf3->GetYaxis()->SetTitle("Energy(MeV)");
	
	gf3->SetMarkerStyle(21);
	gf3->SetMarkerSize(1);
	gf3->SetMarkerColor(3);
	gf3->Draw("APL");



	TGraph *gf2=new TGraph(2,ADCF,Energy);
	gf2->SetName("gf2");
	gf2->SetMarkerStyle(20);
	gf2->SetMarkerSize(1);
	gf2->SetMarkerColor(2);
	gf2->Draw("Psame");
	double kf=(Energy[1]-Energy[0])/(ADCF[1]-ADCF[0]);
	double bf=Energy[1]-kf*ADCF[1];
	cout<<"kf="<<kf<<" bf="<<bf<<endl;
	TF1 *ff=new TF1("ff","pol1",0,4000);
	ff->SetParameters(bf,kf);
	ff->SetLineColor(2);
	ff->Draw("same");

	TCanvas *cB=new TCanvas("cB","cB",600,600);
	cB->cd();
	TGraph *gb3=new TGraph(3,badc,E);
	gb3->SetName("gb3");
	gb3->SetTitle("Pixel DSSD Back ADC vs Energy");
	gb3->GetXaxis()->SetTitle("ADC(ch)");
	gb3->GetYaxis()->SetTitle("Energy(MeV)");
	
	gb3->SetMarkerStyle(21);
	gb3->SetMarkerSize(1);
	gb3->SetMarkerColor(3);
	gb3->Draw("APL");



	TGraph *gb2=new TGraph(2,ADCB,Energy);
	gb2->SetName("gb2");
	gb2->SetMarkerStyle(20);
	gb2->SetMarkerSize(1);
	gb2->SetMarkerColor(2);
	gb2->Draw("Psame");

	double kb=(Energy[1]-Energy[0])/(ADCB[1]-ADCB[0]);
	double bb=Energy[1]-kb*ADCB[1];
	
	TF1 *fb=new TF1("fb","pol1",0,4000);
	fb->SetParameters(bb,kb);
	fb->SetLineColor(2);
	fb->Draw("same");
	cout<<"kb="<<kb<<" bb="<<bb<<endl;



}
