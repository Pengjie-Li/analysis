{

	gROOT->ProcessLine(".x cutPPETBe10.C");
	TCanvas *cNai = new TCanvas("cNai","cNai",1200,800);
	cNai->Divide(4,4);
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 7; ++j) {

			cNai->cd(i*8+j+1);
			tree->Draw(Form("sqrt(naiQPed[%d][%d]*naiQPed[%d][%d]):protonTheta>>hPed%d_%d(100,40,80,100,500,4000)",2*i,j,2*i+1,j,i,j),"ppET","colz");
			gPad->Modified();
			gPad->Update();

		}
	}
}
