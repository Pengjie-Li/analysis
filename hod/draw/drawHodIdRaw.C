
void drawHodIdRaw(){
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
	Int_t           timeUpRaw[40];
	Int_t           timeDownRaw[40];
	Int_t           energyUpRaw[40];
	Int_t           energyDownRaw[40];

	// Set branch addresses.
	CalTreeHOD->SetBranchAddress("timeUpRaw",timeUpRaw);
	CalTreeHOD->SetBranchAddress("timeDownRaw",timeDownRaw);
	CalTreeHOD->SetBranchAddress("energyUpRaw",energyUpRaw);
	CalTreeHOD->SetBranchAddress("energyDownRaw",energyDownRaw);

	TH2F *hHodIdTimeUpRaw = new TH2F("hHodIdTimeUpRaw","hHodIdTimeUpRaw",40,-0.5,39.5,1000,0,35000);
	TH2F *hHodIdTimeDownRaw = new TH2F("hHodIdTimeDownRaw","hHodIdTimeDownRaw",40,-0.5,39.5,1000,0,35000);
	TH2F *hHodIdEnergyUpRaw = new TH2F("hHodIdEnergyUpRaw","hHodIdEnergyUpRaw",40,-0.5,39.5,4096,0,4095);
	TH2F *hHodIdEnergyDownRaw = new TH2F("hHodIdEnergyDownRaw","hHodIdEnergyDownRaw",40,-0.5,39.5,4096,0,4095);
	
	Long64_t nentries = CalTreeHOD->GetEntries();

	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		CalTreeHOD->GetEntry(ientry);
		if(ientry%1000 == 0) cout<<ientry<<endl;
		for(int i = 0;i<40;i++){
			if(timeUpRaw[i]!=-1) hHodIdTimeUpRaw->Fill(i,timeUpRaw[i]);
			if(timeDownRaw[i]!=-1) hHodIdTimeDownRaw->Fill(i,timeDownRaw[i]);
			if(energyUpRaw[i]!=-1) hHodIdEnergyUpRaw->Fill(i,energyUpRaw[i]);
			if(energyDownRaw[i]!=-1) hHodIdEnergyDownRaw->Fill(i,energyDownRaw[i]);
	
		}
	}

	TCanvas *cHodIdTimeUpRaw = new TCanvas("cHodIdTimeUpRaw","cHodIdTimeUpRaw",1200,800);
	TCanvas *cHodIdTimeDownRaw = new TCanvas("cHodIdTimeDownRaw","cHodIdTimeDownRaw",1200,800);
	TCanvas *cHodIdEnergyUpRaw = new TCanvas("cHodIdEnergyUpRaw","cHodIdEnergyUpRaw",1200,800);
	TCanvas *cHodIdEnergyDownRaw = new TCanvas("cHodIdEnergyDownRaw","cHodIdEnergyDownRaw",1200,800);
	
	cHodIdTimeUpRaw->cd();
	gPad->SetLogz();
	hHodIdTimeUpRaw->Draw("colz");
	hHodIdTimeUpRaw->Write();

	cHodIdTimeDownRaw->cd();
	gPad->SetLogz();
	hHodIdTimeDownRaw->Draw("colz");
	hHodIdTimeDownRaw->Write();

	cHodIdEnergyUpRaw->cd();
	gPad->SetLogz();
	hHodIdEnergyUpRaw->Draw("colz");
	hHodIdEnergyUpRaw->Write();

	cHodIdEnergyDownRaw->cd();
	gPad->SetLogz();
	hHodIdEnergyDownRaw->Draw("colz");
	hHodIdEnergyDownRaw->Write();

	f->Close();

}
