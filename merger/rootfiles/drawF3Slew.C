{
	TCanvas *cSlew = new TCanvas("cSlew","cSlew",1000,500);
	cSlew->Divide(2,1);
	cSlew->cd(1);
	tree->Draw("0.5*(F3TCal[0]+F3TCal[1]):F3Q>>Before(1000,0,2000,1000,540,570)","Trig_DSB","colz");
	cSlew->cd(2);
	tree->Draw("F3TSlew:F3Q>>After(1000,0,2000,1000,540,570)","Trig_DSB","colz");
}
