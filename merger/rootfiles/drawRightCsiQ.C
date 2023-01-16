{
	gROOT->ProcessLine(".x setAlias.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	gROOT->ProcessLine(".x cutNarrowAlpha598.C");

	tree->Draw("rltQPed>>hrlt(4000,100,4100)"  ,targetArea+"&&csiNHit==1&&narrowAlpha");
	tree->Draw("rlbQPed>>hrlb(4000,100,4100)"  ,targetArea+"&&csiNHit==1&&narrowAlpha");
	tree->Draw("rrtQPed>>hrrt(4000,100,4100)"  ,targetArea+"&&csiNHit==1&&narrowAlpha");
	tree->Draw("rrbQPed>>hrrb(4000,100,4100)"  ,targetArea+"&&csiNHit==1&&narrowAlpha");




	TH1F *hrlt = (TH1F*)gDirectory->Get("hrlt");
	TH1F *hrlb = (TH1F*)gDirectory->Get("hrlb");
	TH1F *hrrt = (TH1F*)gDirectory->Get("hrrt");
	TH1F *hrrb = (TH1F*)gDirectory->Get("hrrb");
	
	hrlt->SetLineColor(1);
	hrlb->SetLineColor(2);
	hrrt->SetLineColor(3);
	hrrb->SetLineColor(4);
	
	hrrb->Draw();
	hrlb->Draw("same");
	hrlt->Draw("same");
	hrrt->Draw("same");
}
