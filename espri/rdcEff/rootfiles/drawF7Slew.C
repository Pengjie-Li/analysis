{
	TCanvas *cSlew = new TCanvas("cSlew","cSlew",1000,500);
	cSlew->Divide(2,1);
	cSlew->cd(1);
	tree->Draw("0.5*(F7TCal[0]+F7TCal[1]):F7Q>>Before(1000,0,4000,1000,540,570)","Trig_DSB","colz");
	cSlew->cd(2);
	
	tree->SetAlias("f7t_slew","(0.5*(F7TCal[0]+F7TCal[1])-(-1.06072e-03*F7Q+1.15839e+00/sqrt(sqrt(sqrt(F7Q+92.5)))))");
	tree->Draw("f7t_slew:F7Q>>After(1000,0,4000,1000,540,570)","Trig_DSB","colz");
}
