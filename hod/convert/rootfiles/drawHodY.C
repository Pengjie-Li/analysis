{
	TCanvas *c1 = new TCanvas("HOD Y Position Ediff vs Tdiff"," HOD Y Position Ediff vs Tdiff ",1800,1200);
	c1->Divide(8,5);
	for (int i = 0; i < 40; ++i) {
		c1->cd(i+1);
		TString draw = Form("(log(hodQCal[0][%d])-log(hodQCal[1][%d])):(hodTRaw[0][%d]-hodTRaw[1][%d])>>hHODY%d(100,-500,500,100,-3,3)",i,i,i,i,i);
		CalTreeHOD->Draw(draw,"","colz");
		gPad->Modified();
		gPad->Update();
	}
}
