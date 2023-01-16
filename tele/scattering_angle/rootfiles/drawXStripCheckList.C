{

	TString suffixName = gDirectory->GetName();
	TCanvas *cStrip2D =new TCanvas("cStrip2D"+suffixName,"cStrip2D"+suffixName,800,800);
	cStrip2D->Divide(2,2);
	cStrip2D->cd(1);
	tree->Draw("BDC1_Y:BDC1_X>>hBDC1(100,-50,50,100,-50,50)","","colz");	
	cStrip2D->cd(2);
	tree->Draw("BDC2_Y:BDC2_X>>hBDC2(100,-50,50,100,-50,50)","","colz");	
	cStrip2D->cd(3);
	tree->Draw("Target_Y:Target_X>>hTarget(100,-50,50,100,-50,50)","","colz");	
	cStrip2D->cd(4);
	tree->Draw("pixelY:pixelX>>hPixel(100,-50,50,100,-50,50)","","colz");	
	
	TCanvas *cSiEnergy = new TCanvas("cSiEnergy"+suffixName,"cSiEnergy"+suffixName,800,600);
	tree->Draw("siEnergy>>hsiEnergy(500,0,25000)");	
	TH1F *hsiEnergy =(TH1F *)gDirectory->Get("hsiEnergy");
	hsiEnergy->Fit("gaus");


	TCanvas *cPixelX = new TCanvas("cPixelX"+suffixName,"cPixelX"+suffixName,800,600);
	gStyle->SetStatH(0.15);
	gStyle->SetStatW(0.18);
	gStyle->SetOptFit(1);
	
	tree->Draw("pixelX>>hPixelX(100,-50,50)");
	TH1F *hCurrent =(TH1F *)gDirectory->Get("hPixelX");
	hCurrent->Fit("gaus");
}
}
