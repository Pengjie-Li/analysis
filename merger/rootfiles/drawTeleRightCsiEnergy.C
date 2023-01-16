{
	gROOT->ProcessLine(".x setAlias.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	//gROOT->ProcessLine(".x cutNarrowAlpha598.C");

	tree->Draw("0.264445*rltQSync/(1-0.000153044*rltQSync)>>hrlt(400,200,600)"  ,targetArea+"&&csiNHit==1");
	tree->Draw("0.264445*rlbQSync/(1-0.000153044*rlbQSync)>>hrlb(400,200,600)"  ,targetArea+"&&csiNHit==1");
	tree->Draw("0.264445*rrtQSync/(1-0.000153044*rrtQSync)>>hrrt(400,200,600)"  ,targetArea+"&&csiNHit==1");
	tree->Draw("0.264445*rrbQSync/(1-0.000153044*rrbQSync)>>hrrb(400,200,600)"  ,targetArea+"&&csiNHit==1");




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
