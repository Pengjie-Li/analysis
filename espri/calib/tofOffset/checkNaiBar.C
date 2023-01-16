
void checkBar(){

//	int side = 1;
//	int barId = 6;
//	double gain = 0.037;
//	double dead = 11.5;

//	int side = 1;
//	int barId = 5;
//	double gain = 0.037;
//	double dead = 21;



//	int side = 1;
//	int barId = 4;
//	double gain = 0.037;
//	double dead = 20;


//	int side = 1;
//	int barId = 3;
//	double gain = 0.040;
//	double dead = 14;


//	int side = 1;
//	int barId = 2;
//	double gain = 0.040;
//	double dead = 12;


//	int side = 1;
//	int barId = 1;
//	double gain = 0.040;
//	double dead = 10;


//	int side = 1;
//	int barId = 0;
//	double gain = 0.037;
//	double dead = 12.5;


//	int side = 0;
//	int barId = 6;
//	double gain = 0.04;
//	double dead = 5;


//	int side = 0;
//	int barId = 5;
//	double gain = 0.04;
//	double dead = 3;


//	int side = 0;
//	int barId = 4;
//	double gain = 0.033;
//	double dead = 11.5;

//	int side = 0;
//	int barId = 3;
//	double gain = 0.04;
//	double dead = 7;

//	int side = 0;
//	int barId = 2;
//	double gain = 0.040;
//	double dead = 3;

//	int side = 0;
//	int barId = 1;
//	double gain = 0.040;
//	double dead = 3;


//	int side = 0;
//	int barId = 0;
//	double gain = 0.040;
//	double dead = 3;



	draw(side,barId,gain,dead);
}
void draw(int side,int barId,double gain,double dead){

	TChain *tree = new TChain("tree");
	tree->Add("ppBe14.root");

        tree->SetAlias("plasBarQPed0","sqrt(plasQPed[0]*plasQPed[1])");
        tree->SetAlias("plasBarQPed1","sqrt(plasQPed[2]*plasQPed[3])");
        for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 7; ++j) {

                        tree->SetAlias(Form("naiBarQPed%d%d",i,j),Form("sqrt(naiQPed[%d][%d]*naiQPed[%d][%d])",2*i,j,2*i+1,j));
                        tree->SetAlias(Form("naiBarQRaw%d%d",i,j),Form("sqrt(naiQRaw[%d][%d]*naiQRaw[%d][%d])",2*i,j,2*i+1,j));
                }

        }




	tree->Draw(Form("%4f*naiBarQPed%d%d+%4f:espriAngle>>hQPed%d%d(1000,55,75,1000,0,200)",gain,dead,side,barId,side,barId));

	TH2F *hQPed = (TH2F *)gDirectory->Get(Form("hQPed%d%d",side,barId));
        hQPed->SetMarkerColor(2);
        //hQPed->SetMarkerSize(30);
        hQPed->SetMarkerStyle(6);
	hQPed->Draw();


	TFile *fCurve = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/esBe14Excitation/espriDetectorEnergy.root","READ");
	TGraph *nai = (TGraph *)gDirectory->Get("nai");
	nai->SetMarkerColor(1);
	nai->SetLineColor(1);
	nai->Draw("plsame");

	TFile *outputFile = new TFile(Form("rootfiles/naiBar%d%d_gain%4f.root",side,barId,gain),"RECREATE");
	nai->Write();
	hQPed->Write();
	outputFile->Close();
}
