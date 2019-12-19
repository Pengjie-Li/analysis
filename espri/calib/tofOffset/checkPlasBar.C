
void checkPlasBar(){

//	int side = 0;
//	double gain = 0.040;
//	double dead = 3;


//	int side = 1;
//	double gain = 0.003500;
//	double dead = 1;


	int side = 0;
	double gain = 0.0037500;
	double dead = 0;

	draw(side,gain,dead);
}
void draw(int side,double gain,double dead){

	TChain *tree = new TChain("tree");
	tree->Add("ppBe14.root");

        tree->SetAlias("plasBarQPed0","sqrt(plasQPed[0]*plasQPed[1])");
        tree->SetAlias("plasBarQPed1","sqrt(plasQPed[2]*plasQPed[3])");


	tree->Draw(Form("%4f*plasBarQPed%d+%4f:espriAngle>>hQPed%d(1000,55,75,1000,0,20)",gain,dead,side,side));

	TH2F *hQPed = (TH2F *)gDirectory->Get(Form("hQPed%d",side));
        hQPed->SetMarkerColor(2);
        //hQPed->SetMarkerSize(30);
        hQPed->SetMarkerStyle(6);
	hQPed->Draw();


	TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/esBe14Excitation/espriDetectorEnergy.root","READ");
	TGraph *plas = (TGraph *)gDirectory->Get("plas");
	plas->SetMarkerColor(1);
	plas->SetLineColor(1);
	plas->Draw("plsame");

	TFile *outputFile = new TFile(Form("rootfiles/plasBar%d_gain%4f.root",side,gain),"RECREATE");
	plas->Write();
	hQPed->Write();
	outputFile->Close();
}
