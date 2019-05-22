// External Function
//void LoadDCTDCDistributionFull(char *FileName, TArtCalibBDC1Track *CalibBDC1Track, TArtCalibBDC2Track *CalibBDC2Track, TArtCalibSimpleFDC1Track *CalibFDC1Track, TArtCalibSimpleFDC2Track *CalibFDC2Track) {
//
void LoadDCTDCDistributionBDC(char *FileName, TArtCalibSimpleBDC1Track *CalibBDC1Track, TArtCalibSimpleBDC2Track *CalibBDC2Track) {

	TFile *RootFile = new TFile(FileName,"READ");
	if(RootFile) {
		gROOT->cd();
		TH1F *Hist1D_X = NULL;
		TH1F *Hist1D_Y = NULL;
		TH2F *Hist2D = NULL;
		// Int_t BDCNumberOfLayers = 8;
		// Int_t FDCNumberOfLayers = 14;
		// Int_t FDC0NumberOfLayers=8;
		Int_t BDCNumberOfLayers = 4;

		for(Int_t i=0; i<BDCNumberOfLayers; i++) {

			Hist2D = (TH2F*) RootFile->Get(Form("bdc1_ftdc_corr_%d",i));

			if(Hist2D) {
				Hist1D_X = (TH1F*)(Hist2D->ProjectionX());
				Hist1D_Y = (TH1F*)(Hist2D->ProjectionY());

				//Hist1D = (TH1I*) RootFile->Get(Form("hbdc1tdc%d",i));

				if(Hist1D_X && Hist1D_Y) {
					CalibBDC1Track->SetTDCDistribution(Hist1D_X,2*i);
					CalibBDC1Track->SetTDCDistribution(Hist1D_Y,2*i+1);

					delete Hist1D_X;
					Hist1D_X = NULL;
					delete Hist1D_Y;
					Hist1D_Y = NULL;
					delete Hist2D;
					Hist2D = NULL;
				}
				// else
				// 	  cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("BDC1TDCDistLayer%d",i) << "\e[37m" << endl;
			}
			else {
				cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("bdc1_ftdc_corr_%d",i) << ". Abort. \e[0m" << endl; exit(1);
			}
		}

		for(Int_t i=0; i<BDCNumberOfLayers; i++) {

			Hist2D = (TH2F*) RootFile->Get(Form("bdc2_ftdc_corr_%d",i));

			if(Hist2D) {
				Hist1D_X = (TH1F*)(Hist2D->ProjectionX());
				Hist1D_Y = (TH1F*)(Hist2D->ProjectionY());

				//Hist1D = (TH1I*) RootFile->Get(Form("hbdc1tdc%d",i));

				if(Hist1D_X && Hist1D_Y) {
					CalibBDC2Track->SetTDCDistribution(Hist1D_X,2*i);
					CalibBDC2Track->SetTDCDistribution(Hist1D_Y,2*i+1);

					delete Hist1D_X;
					Hist1D_X = NULL;
					delete Hist1D_Y;
					Hist1D_Y = NULL;
					delete Hist2D;
					Hist2D = NULL;
				}
				// else
				//   cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("BDC2TDCDistLayer%d",i) << "\e[37m" << endl;
			}
			else {
				cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("bdc2_ftdc_corr_%d",i) << ". Abort. \e[0m" << endl; exit(1);
			}
		}
	}

	else {
		cout << "\e[35m " << "Could not find the following file : " << FileName << ". Abort. \e[0m" << endl; exit(1);
	}
	delete RootFile;
}
void LoadDCTDCDistributionFull(char *FileName, TArtCalibSimpleBDC1Track *CalibBDC1Track, TArtCalibSimpleBDC2Track *CalibBDC2Track, TArtCalibSimpleFDC0Track *CalibFDC0Track, TArtCalibSimpleFDC2Track *CalibFDC2Track) {

	TFile *RootFile = new TFile(FileName,"READ");
	if(RootFile) {
		gROOT->cd();
		TH1F *Hist1D_X = NULL;
		TH1F *Hist1D_Y = NULL;
		TH2F *Hist2D = NULL;
		// Int_t BDCNumberOfLayers = 8;
		// Int_t FDCNumberOfLayers = 14;
		// Int_t FDC0NumberOfLayers=8;
		Int_t BDCNumberOfLayers = 4;
		Int_t FDCNumberOfLayers = 7;
		Int_t FDC0NumberOfLayers=4;

		for(Int_t i=0; i<BDCNumberOfLayers; i++) {

			Hist2D = (TH2F*) RootFile->Get(Form("bdc1_ftdc_corr_%d",i));

			if(Hist2D) {
				Hist1D_X = (TH1F*)(Hist2D->ProjectionX());
				Hist1D_Y = (TH1F*)(Hist2D->ProjectionY());

				//Hist1D = (TH1I*) RootFile->Get(Form("hbdc1tdc%d",i));

				if(Hist1D_X && Hist1D_Y) {
					CalibBDC1Track->SetTDCDistribution(Hist1D_X,2*i);
					CalibBDC1Track->SetTDCDistribution(Hist1D_Y,2*i+1);

					delete Hist1D_X;
					Hist1D_X = NULL;
					delete Hist1D_Y;
					Hist1D_Y = NULL;
					delete Hist2D;
					Hist2D = NULL;
				}
				// else
				// 	  cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("BDC1TDCDistLayer%d",i) << "\e[37m" << endl;
			}
			else {
				cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("bdc1_ftdc_corr_%d",i) << ". Abort. \e[0m" << endl; exit(1);
			}
		}

		for(Int_t i=0; i<BDCNumberOfLayers; i++) {

			Hist2D = (TH2F*) RootFile->Get(Form("bdc2_ftdc_corr_%d",i));

			if(Hist2D) {
				Hist1D_X = (TH1F*)(Hist2D->ProjectionX());
				Hist1D_Y = (TH1F*)(Hist2D->ProjectionY());

				//Hist1D = (TH1I*) RootFile->Get(Form("hbdc1tdc%d",i));

				if(Hist1D_X && Hist1D_Y) {
					CalibBDC2Track->SetTDCDistribution(Hist1D_X,2*i);
					CalibBDC2Track->SetTDCDistribution(Hist1D_Y,2*i+1);

					delete Hist1D_X;
					Hist1D_X = NULL;
					delete Hist1D_Y;
					Hist1D_Y = NULL;
					delete Hist2D;
					Hist2D = NULL;
				}
				// else
				//   cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("BDC2TDCDistLayer%d",i) << "\e[37m" << endl;
			}
			else {
				cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("bdc2_ftdc_corr_%d",i) << ". Abort. \e[0m" << endl; exit(1);
			}
		}

		for(Int_t i=0; i<FDC0NumberOfLayers; i++) { //FDC0 8layers
			//Hist1D = (TH1I*) RootFile->Get(Form("hfdc0tdc%d",i));

			Hist2D = (TH2F*) RootFile->Get(Form("fdc0_ftdc_corr_%d",i));

			if(Hist2D) {
				Hist1D_X = (TH1F*)(Hist2D->ProjectionX());
				Hist1D_Y = (TH1F*)(Hist2D->ProjectionY());

				//Hist1D = (TH1I*) RootFile->Get(Form("hbdc1tdc%d",i));

				if(Hist1D_X && Hist1D_Y) {
					CalibFDC0Track->SetTDCDistribution(Hist1D_X,2*i);
					CalibFDC0Track->SetTDCDistribution(Hist1D_Y,2*i+1);

					delete Hist1D_X;
					Hist1D_X = NULL;
					delete Hist1D_Y;
					Hist1D_Y = NULL;
					delete Hist2D;
					Hist2D = NULL;
				}
				//else
				// cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("FDC0TDCDistLayer%d",i) << "\e[37m" << endl;
			}
			else {
				cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("fdc0_ftdc_corr_%d",i) << ". Abort. \e[0m" << endl; exit(1);
			}
		}

		// for(Int_t i=0; i<FDCNumberOfLayers; i++) {
		//   Hist1D = (TH1I*) RootFile->Get(Form("hfdc1tdc%d",i));
		//   if(Hist1D) {
		// 	CalibFDC1Track->SetTDCDistribution(Hist1D,i);
		// 	delete Hist1D;
		// 	Hist1D = NULL;
		// 	delete Hist2D;
		// 	Hist2D = NULL;
		//   }
		//   else
		// 	cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("FDC1TDCDistLayer%d",i) << "\e[37m" << endl;
		// }

		for(Int_t i=0; i<FDCNumberOfLayers; i++) {
			//Hist1D = (TH1I*) RootFile->Get(Form("hfdc2tdc%d",i));

			Hist2D = (TH2F*) RootFile->Get(Form("fdc2_ftdc_corr_%d",i));

			if(Hist2D) {
				Hist1D_X = (TH1F*)(Hist2D->ProjectionX());
				Hist1D_Y = (TH1F*)(Hist2D->ProjectionY());

				//Hist1D = (TH1I*) RootFile->Get(Form("hbdc1tdc%d",i));

				if(Hist1D_X && Hist1D_Y) {
					CalibFDC2Track->SetTDCDistribution(Hist1D_X,2*i);
					CalibFDC2Track->SetTDCDistribution(Hist1D_Y,2*i+1);

					delete Hist1D_X;
					Hist1D_X = NULL;
					delete Hist1D_Y;
					Hist1D_Y = NULL;
					delete Hist2D;
					Hist2D = NULL;
				}
				// else
				//   cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("FDC2TDCDistLayer%d",i) << "\e[0m" << endl;
			}
			else {
				cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("fdc2_ftdc_corr_%d",i) << ". Abort. \e[0m" << endl; exit(1);
			}
		}
	}
	else {
		cout << "\e[35m " << "Could not find the following file : " << FileName << ". Abort. \e[0m" << endl; exit(1);
	}
	delete RootFile;
}

//==========================================================================
//void LoadDCTDCDistributionFull(char *FileName, TArtCalibBDC1Track *CalibBDC1Track, TArtCalibBDC2Track *CalibBDC2Track, TArtCalibFDC1Track *CalibFDC1Track, TArtCalibFDC2Track *CalibFDC2Track) {
void LoadDCTDCDistributionFull(char *FileName, TArtCalibSimpleBDC1Track *CalibBDC1Track, TArtCalibSimpleBDC2Track *CalibBDC2Track, TArtCalibFDC0Track *CalibFDC0Track, TArtCalibFDC2Track *CalibFDC2Track) {

	TFile *RootFile = new TFile(FileName,"READ");
	if(RootFile) {
		gROOT->cd();
		TH1F *Hist1D_X = NULL;
		TH1F *Hist1D_Y = NULL;
		TH2F *Hist2D = NULL;
		// Int_t BDCNumberOfLayers = 8;
		// Int_t FDCNumberOfLayers = 14;
		// Int_t FDC0NumberOfLayers=8;
		Int_t BDCNumberOfLayers = 4;
		Int_t FDCNumberOfLayers = 7;
		Int_t FDC0NumberOfLayers=4;

		for(Int_t i=0; i<BDCNumberOfLayers; i++) {

			Hist2D = (TH2F*) RootFile->Get(Form("bdc1_ftdc_corr_%d",i));

			if(Hist2D) {
				Hist1D_X = (TH1F*)(Hist2D->ProjectionX());
				Hist1D_Y = (TH1F*)(Hist2D->ProjectionY());

				//Hist1D = (TH1I*) RootFile->Get(Form("hbdc1tdc%d",i));

				if(Hist1D_X && Hist1D_Y) {
					CalibBDC1Track->SetTDCDistribution(Hist1D_X,2*i);
					CalibBDC1Track->SetTDCDistribution(Hist1D_Y,2*i+1);

					delete Hist1D_X;
					Hist1D_X = NULL;
					delete Hist1D_Y;
					Hist1D_Y = NULL;
					delete Hist2D;
					Hist2D = NULL;
				}
				// else
				// 	  cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("BDC1TDCDistLayer%d",i) << "\e[0m" << endl;
			}
			else
				cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("bdc1_ftdc_corr_%d",i) << "\e[0m" << endl;
		}

		for(Int_t i=0; i<BDCNumberOfLayers; i++) {

			Hist2D = (TH2F*) RootFile->Get(Form("bdc2_ftdc_corr_%d",i));

			if(Hist2D) {
				Hist1D_X = (TH1F*)(Hist2D->ProjectionX());
				Hist1D_Y = (TH1F*)(Hist2D->ProjectionY());

				//Hist1D = (TH1I*) RootFile->Get(Form("hbdc1tdc%d",i));

				if(Hist1D_X && Hist1D_Y) {
					CalibBDC2Track->SetTDCDistribution(Hist1D_X,2*i);
					CalibBDC2Track->SetTDCDistribution(Hist1D_Y,2*i+1);

					delete Hist1D_X;
					Hist1D_X = NULL;
					delete Hist1D_Y;
					Hist1D_Y = NULL;
					delete Hist2D;
					Hist2D = NULL;
				}
				// else
				//   cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("BDC2TDCDistLayer%d",i) << "\e[0m" << endl;
			}
			else
				cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("bdc2_ftdc_corr_%d",i) << "\e[0m" << endl;
		}

		for(Int_t i=0; i<FDC0NumberOfLayers; i++) { //FDC0 8layers
			//Hist1D = (TH1I*) RootFile->Get(Form("hfdc0tdc%d",i));

			Hist2D = (TH2F*) RootFile->Get(Form("fdc0_ftdc_corr_%d",i));

			if(Hist2D) {
				Hist1D_X = (TH1F*)(Hist2D->ProjectionX());
				Hist1D_Y = (TH1F*)(Hist2D->ProjectionY());

				//Hist1D = (TH1I*) RootFile->Get(Form("hbdc1tdc%d",i));

				if(Hist1D_X && Hist1D_Y) {
					CalibFDC0Track->SetTDCDistribution(Hist1D_X,2*i);
					CalibFDC0Track->SetTDCDistribution(Hist1D_Y,2*i+1);

					delete Hist1D_X;
					Hist1D_X = NULL;
					delete Hist1D_Y;
					Hist1D_Y = NULL;
					delete Hist2D;
					Hist2D = NULL;
				}
				//else
				// cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("FDC0TDCDistLayer%d",i) << "\e[0m" << endl;
			}
			else
				cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("fdc0_ftdc_corr_%d",i) << "\e[0m" << endl;
		}

		// for(Int_t i=0; i<FDCNumberOfLayers; i++) {
		//   Hist1D = (TH1I*) RootFile->Get(Form("hfdc1tdc%d",i));
		//   if(Hist1D) {
		// 	CalibFDC1Track->SetTDCDistribution(Hist1D,i);
		// 	delete Hist1D;
		// 	Hist1D = NULL;
		// 	delete Hist2D;
		// 	Hist2D = NULL;
		//   }
		//   else
		// 	cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("FDC1TDCDistLayer%d",i) << "\e[0m" << endl;
		// }

		for(Int_t i=0; i<FDCNumberOfLayers; i++) {
			//Hist1D = (TH1I*) RootFile->Get(Form("hfdc2tdc%d",i));

			Hist2D = (TH2F*) RootFile->Get(Form("fdc2_ftdc_corr_%d",i));

			if(Hist2D) {
				Hist1D_X = (TH1F*)(Hist2D->ProjectionX());
				Hist1D_Y = (TH1F*)(Hist2D->ProjectionY());

				//Hist1D = (TH1I*) RootFile->Get(Form("hbdc1tdc%d",i));

				if(Hist1D_X && Hist1D_Y) {
					CalibFDC2Track->SetTDCDistribution(Hist1D_X,2*i);
					CalibFDC2Track->SetTDCDistribution(Hist1D_Y,2*i+1);

					delete Hist1D_X;
					Hist1D_X = NULL;
					delete Hist1D_Y;
					Hist1D_Y = NULL;
					delete Hist2D;
					Hist2D = NULL;
				}
				// else
				//   cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("FDC2TDCDistLayer%d",i) << "\e[0m" << endl;
			}
			else{
				cout << "\e[35m " << "Warning LoadDCTDCDistribution :: Could not find the following histogram " << Form("fdc2_ftdc_corr_%d",i) << ". Abort. \e[0m" << endl; exit(1);
			}
		}
	}
	else {
		cout << "\e[35m " << "Could not find the following file : " << FileName << ". Abort. \e[0m" << endl; exit(1);
	}
	delete RootFile;
}


