void Draw_fit()
{
	int n=10;

//	double Energy[10]={
//		216.41,
//		242.66,
//		266.91,
//		289.59,
//		311.01,
//		432.27,
//		448.47,
//		464.25,
//		479.67,
//		494.75};


//	double Energy[10]={
//		230.85,
//		255.94,
//		279.3,
//		301.27,
//		322.1,
//		445.76,
//		461.61,
//		477.09,
//		492.23,
//		507.04
//	};

	double Energy[10]={
201.68,
229.26,
254.48,
277.93,
299.97,
419.77,
436.3,
452.39,
468.08,
483.41
	};
	double ADC[10]={
		894.1,
		975.2,
		1054,
		1119,
		1186,
		1515,
		1573,
		1629,
		1678,
		1719};

	TCanvas *cCsI=new TCanvas("cCsI","cCsI",600,600);
	cCsI->cd();
	
	TGraph *gCsI3 =new TGraph(n,ADC,Energy);

//	gCsI3->SetName("gCsI3");
//	gCsI3->SetTitle("Pixel CsI ADC vs Energy");
//	gCsI3->GetXaxis()->SetTitle("ADC(ch)");
//	gCsI3->GetYaxis()->SetTitle("Energy(MeV)");
//
	gCsI3->SetMarkerStyle(21);
	gCsI3->SetMarkerSize(1);
	gCsI3->SetMarkerColor(3);
	gCsI3->Draw("AP");

	TF1 *fCsI=new TF1("fCsI","pol1",0,4000);
	//fCsI->SetParameters(b,k);
	fCsI->SetLineColor(2);
	//fCsI->Draw("same");
	

        gCsI3->Fit(fCsI);






}

