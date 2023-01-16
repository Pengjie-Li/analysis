{
	gROOT->ProcessLine(".x setAlias.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	//gROOT->ProcessLine(".x cutNarrowAlpha598.C");

	tree->Draw("rltQSync>>hrlt(2000,100,4100)"  ,targetArea+"&&csiNHit==1");
	tree->Draw("rlbQSync>>hrlb(2000,100,4100)"  ,targetArea+"&&csiNHit==1");
	tree->Draw("rrtQSync>>hrrt(2000,100,4100)"  ,targetArea+"&&csiNHit==1");
	tree->Draw("rrbQSync>>hrrb(2000,100,4100)"  ,targetArea+"&&csiNHit==1");




	TH1F *hrlt = (TH1F*)gDirectory->Get("hrlt");
	TH1F *hrlb = (TH1F*)gDirectory->Get("hrlb");
	TH1F *hrrt = (TH1F*)gDirectory->Get("hrrt");
	TH1F *hrrb = (TH1F*)gDirectory->Get("hrrb");
	
	hrlt->SetLineColor(1);
	hrlb->SetLineColor(2);
	hrrt->SetLineColor(3);
	hrrb->SetLineColor(4);
	
	hrrt->Draw();
	hrlt->Draw("same");
	hrlb->Draw("same");
	hrrb->Draw("same");
}
