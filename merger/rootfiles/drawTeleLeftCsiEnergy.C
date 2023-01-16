{
	gROOT->ProcessLine(".x setAlias.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	//gROOT->ProcessLine(".x cutNarrowAlpha596.C");

	double parA = 0.297221;
	double parB = -0.000182688;
	tree->Draw("0.297221*llQSync/(1-0.000182688*llQSync)>>hll(500,200,600)"  ,  targetArea+"&&csiNHit==1");
	tree->Draw("0.297221*lrtQSync/(1-0.000182688*lrtQSync)>>hlrt(500,200,600)"  ,targetArea+"&&csiNHit==1");
	tree->Draw("0.297221*lrbQSync/(1-0.000182688*lrbQSync)>>hlrb(500,200,600)"  ,targetArea+"&&csiNHit==1");



	TH1F *hll = (TH1F*)gDirectory->Get("hll");
	TH1F *hlrt = (TH1F*)gDirectory->Get("hlrt");
	TH1F *hlrb = (TH1F*)gDirectory->Get("hlrb");
	hll->SetLineColor(1);
	hlrt->SetLineColor(2);
	hlrb->SetLineColor(3);
	hlrb->Draw();
	hll->Draw("same");
	hlrt->Draw("same");
}
