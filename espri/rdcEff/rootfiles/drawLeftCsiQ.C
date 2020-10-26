{
	gROOT->ProcessLine(".x setAlias.C");
	gROOT->ProcessLine(".x cutTargetArea.C");
	gROOT->ProcessLine(".x cutNarrowAlpha596.C");

	tree->Draw("llQPed>>hll(4000,100,4100)"  ,targetArea+"&&csiNHit==1&&narrowAlpha");
	tree->Draw("lrtQPed>>hlrt(4000,100,4100)"  ,targetArea+"&&csiNHit==1&&narrowAlpha");
	tree->Draw("lrbQPed>>hlrb(4000,100,4100)"  ,targetArea+"&&csiNHit==1&&narrowAlpha");
//	tree->draw("0.7175554166*lrtqped>>hlrt(4000,100,4100)",targetarea+"&&csinhit==1&&bnarrowAlpha");
//	tree->draw("0.7923015662*lrbqped>>hlrb(4000,100,4100)",targetarea+"&&csinhit==1&&beam");



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
