{
	TCanvas *cSlew = new TCanvas("cSlew","cSlew",1000,500);
	cSlew->Divide(2,1);
	cSlew->cd(1);
	tree->Draw("0.5*(F7TCal[0]+F7TCal[1]):F7Q>>Before(1000,0,4000,1000,540,570)","Trig_DSB","colz");
	cSlew->cd(2);
	tree->Draw("F7TSlew:F7Q>>After(1000,0,4000,1000,540,570)","Trig_DSB","colz");
}
