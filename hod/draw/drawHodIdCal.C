
void drawHodIdCal(){
	//int runNumber = 310;
	int runNumber = 360; //beam tunning on May 15
	draw(runNumber);


//	int runStart = 100;
//	int runStop = 230;
//
//	for(int runNumber = runStart;runNumber<runStop;runNumber++){
//		draw(runNumber);
//	}
}
void draw(int runNumber){
	TString inputName = Form("../convert/rootfiles/run0%d_HOD.root",runNumber);

	TFile *f = new TFile(inputName,"UPDATE");
	TTree *tree = (TTree *)f->Get("CalTreeHOD");

	//Declaration of leaves types
	Double_t           timeUpCal[40];
	Double_t           timeDownCal[40];
	Double_t           energyUpCal[40];
	Double_t           energyDownCal[40];

	// Set branch addresses.
	CalTreeHOD->SetBranchAddress("timeUpCal",timeUpCal);
	CalTreeHOD->SetBranchAddress("timeDownCal",timeDownCal);
	CalTreeHOD->SetBranchAddress("energyUpCal",energyUpCal);
	CalTreeHOD->SetBranchAddress("energyDownCal",energyDownCal);

	TH2F *hHodIdTimeUpCal = new TH2F("hHodIdTimeUpCal","hHodIdTimeUpCal",40,-0.5,39.5,1000,0,35000);
	TH2F *hHodIdTimeDownCal = new TH2F("hHodIdTimeDownCal","hHodIdTimeDownCal",40,-0.5,39.5,1000,0,35000);
	TH2F *hHodIdEnergyUpCal = new TH2F("hHodIdEnergyUpCal","hHodIdEnergyUpCal",40,-0.5,39.5,4096,-100,3995);
	TH2F *hHodIdEnergyDownCal = new TH2F("hHodIdEnergyDownCal","hHodIdEnergyDownCal",40,-0.5,39.5,4096,-100,3995);
	
	Long64_t nentries = CalTreeHOD->GetEntries();
	//nentries = 100000;

	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		CalTreeHOD->GetEntry(ientry);
		if(ientry%1000 == 0) cout<<ientry<<endl;
		for(int i = 0;i<40;i++){
			if(timeUpCal[i]!=-1) hHodIdTimeUpCal->Fill(i,timeUpCal[i]);
			if(timeDownCal[i]!=-1) hHodIdTimeDownCal->Fill(i,timeDownCal[i]);
			if(energyUpCal[i]!=-1) hHodIdEnergyUpCal->Fill(i,energyUpCal[i]);
			if(energyDownCal[i]!=-1) hHodIdEnergyDownCal->Fill(i,energyDownCal[i]);
	
		}
	}

	TCanvas *cHodIdTimeUpCal = new TCanvas("cHodIdTimeUpCal","cHodIdTimeUpCal",1200,800);
	TCanvas *cHodIdTimeDownCal = new TCanvas("cHodIdTimeDownCal","cHodIdTimeDownCal",1200,800);
	TCanvas *cHodIdEnergyUpCal = new TCanvas("cHodIdEnergyUpCal","cHodIdEnergyUpCal",1200,800);
	TCanvas *cHodIdEnergyDownCal = new TCanvas("cHodIdEnergyDownCal","cHodIdEnergyDownCal",1200,800);
	
	cHodIdTimeUpCal->cd();
	gPad->SetLogz();
	hHodIdTimeUpCal->Draw("colz");
	hHodIdTimeUpCal->Write();

	cHodIdTimeDownCal->cd();
	gPad->SetLogz();
	hHodIdTimeDownCal->Draw("colz");
	hHodIdTimeDownCal->Write();

	cHodIdEnergyUpCal->cd();
	gPad->SetLogz();
	hHodIdEnergyUpCal->Draw("colz");
	hHodIdEnergyUpCal->Write();

	cHodIdEnergyDownCal->cd();
	gPad->SetLogz();
	hHodIdEnergyDownCal->Draw("colz");
	hHodIdEnergyDownCal->Write();

	f->Close();

}
