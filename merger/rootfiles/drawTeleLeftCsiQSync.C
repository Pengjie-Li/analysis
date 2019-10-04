{
	gROOT->ProcessLine(".x setAlias.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	//gROOT->ProcessLine(".x cutNarrowAlpha596.C");

	tree->Draw(" llQSync>>hll(4000,100,4100)"  ,  targetArea+"&&csiNHit==1");
	tree->Draw("lrtQSync>>hlrt(4000,100,4100)"  ,targetArea+"&&csiNHit==1");
	tree->Draw("lrbQSync>>hlrb(4000,100,4100)"  ,targetArea+"&&csiNHit==1");



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
