{

	int nBin = 600;
	int min = -10;
	int max = 50;

	TCanvas *cESPRI = new TCanvas("ESPRI X vs Y","ESPRI X vs Y",1600,700);
	cESPRI->Divide(2,1);
	cESPRI->cd(1);
	CalTreeESPRI->Draw(Form("rdcY[0]:rdcX[0]>>hLeft(%d,%d,%d,%d,%d,%d)",nBin,min,max,nBin,min,max),"","colz");
	cESPRI->cd(2);
	CalTreeESPRI->Draw(Form("rdcY[1]:rdcX[1]>>hRight(%d,%d,%d,%d,%d,%d)",nBin,min,max,nBin,min,max),"","colz");

}
