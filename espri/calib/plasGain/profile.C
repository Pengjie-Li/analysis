{
	auto hprof  = new TProfile("hprof","Profile of pz versus px",100,-4,4,0,20);
	auto hh=new TH2F("hh","2D histogram py versus px",100,-4,4,100,-4,4);
	auto hhprof  = new TProfile("hhprof","Profile of py versus px",100,-4,4,-4,4);
	Float_t px, py, pz;
	for ( Int_t i=0; i<25000; i++) {
		gRandom->Rannor(px,py);
		pz = px*px + py*py;
		hh->Fill(px,py);
		hprof->Fill(px,pz,1);
	}
	auto c1 = new TCanvas("c1","Profile histogram example",200,10,700,500);
	hprof->Draw();
	auto c2 = new TCanvas("c2","histogram ",700,10,1000,500);
	hh->Draw("colz");
	//cout<<hh->GetMaximumbin()<<endl;
	hh->ProfileX("hhprof",1,100,"d");
	hhprof->Draw("same");

}
