{
	//TFile *inputFile = new TFile("dEEPlot.root","read");
	TCanvas *cDEELeft = new TCanvas("cDEELeft","cDEELeft",1600,900);
	cDEELeft->Divide(4,2);
	TCanvas *cDEERight = new TCanvas("cDEERight","cDEERight",1600,900);

	//TColor::CreateGradientColorTable(Number,Length,Red,Green,Blue,nb);
	cDEERight->Divide(4,2);
	TH2D *h[2][7];
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 7; ++j) {
			if(i == 0){
				cDEELeft->cd(j+1);
				h[i][j] = (TH2D*)gDirectory->Get(Form("hLeft%d",j));
				
			}else{

				cDEERight->cd(j+1);
				h[i][j] = (TH2D*)gDirectory->Get(Form("hRight%d",j));
			}
			h[i][j]->Draw("colz");
			//h[i][j]->SetContour(nb);
			h[i][j]->SetMaximum(10000);
			gPad->SetLogz();
			
			gROOT->ProcessLine(Form(".x cut/side%dBarNo%d.C",i,j));
		}
		
	}
}
