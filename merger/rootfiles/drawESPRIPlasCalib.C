{

	gROOT->ProcessLine(".x cutPPETBe10.C");
	TCanvas *cPed = new TCanvas("cPed","cPed",1200,800);
	cPed->Divide(2,1);
	for (int i = 0; i < 2; ++i) {

			cPed->cd(i+1);
			tree->Draw(Form("sqrt(plasQPed[%d]*plasQPed[%d]):protonTheta>>hPed%d(100,60,73,100,0,4000)",2*i,2*i+1,i),"ppET","colz");
			gPad->Modified();
			gPad->Update();

		}
	}
}
