{
	tree->Draw("plasQPed[0]:1.0*naiBarQPed00>>h00(1000,0,4000,1000,0,4000)","Trig_BxESPRI","colz");
	tree->Draw("plasQPed[0]:1.3*naiBarQPed01>>h01(1000,0,4000,1000,0,4000)","Trig_BxESPRI","colz");
	tree->Draw("plasQPed[0]:1.35*naiBarQPed02>>h02(1000,0,4000,1000,0,4000)","Trig_BxESPRI","colz");
	tree->Draw("plasQPed[0]:1.8*naiBarQPed03>>h03(1000,0,4000,1000,0,4000)","Trig_BxESPRI","colz");
	tree->Draw("plasQPed[0]:1.8*naiBarQPed04>>h04(1000,0,4000,1000,0,4000)","Trig_BxESPRI","colz");
	tree->Draw("plasQPed[0]:2.2*naiBarQPed05>>h05(1000,0,4000,1000,0,4000)","Trig_BxESPRI","colz");
	tree->Draw("plasQPed[0]:2.6*naiBarQPed06>>h06(1000,0,4000,1000,0,4000)","Trig_BxESPRI","colz");

	TCanvas *cAlign = new TCanvas("cAlign","cAlign",700,900);
	TH2F *h[7];
	for (int i = 0; i < 7; ++i) {
		h[i] = (TH2F *)gDirectory->Get(Form("h0%d",i));
		h[i]->SetMarkerColor(i+1);
		h[i]->SetMarkerSize(10);
		if(i>0) h[i]->Draw("same");
		else h[i]->Draw();
	}
}
