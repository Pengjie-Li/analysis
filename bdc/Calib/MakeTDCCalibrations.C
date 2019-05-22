// macro to decode the ridf format RootFile and put into root tree file
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include "TString.h"
#include <TCanvas.h>
// #include "TArtMapper.hh"
#include "TArtDALINaIPara.hh"
#include "TArtDALINaI.hh"
#include "TArtPlastic.hh"
#include "TArtCalibPID.hh"
#include "TArtCalibPlastic.hh"
#include "TArtCalibBDC1Hit.hh"
#include "TArtCalibBDC1Hit.hh"
#include "TArtCalibBDC2Hit.hh"
#include "TArtCalibBDC2Hit.hh"
#include "TArtCalibBPCHit.hh"
#include "TArtCalibCoin.hh"
#include "TArtCalibDCHit.hh"
#include "TArtCalibDCHit.hh"
#include "TArtCalibFDC0Hit.hh"
#include "TArtCalibFDC0Hit.hh"
#include "TArtCalibFDC1Hit.hh"
#include "TArtCalibFDC1Hit.hh"
#include "TArtCalibFDC2Hit.hh"
#include "TArtCalibFDC2Hit.hh"
#include "TArtCalibHODPla.hh"
// #include "TArtCalibICB.hh"
#include "TArtCalibNEBULA.hh"
#include "TArtCalibNEBULAHPC.hh"
#include "TArtCalibSAMURAI.hh"
// #include "TArtCalibSAMURAIPla.hh"
#include "TArtCalibDALI.hh"
#include "TArtDALINaI.hh"
#include "TArtDALIParameters.hh"
#include "TArtDCHit.hh"
#include "TArtDCHitPara.hh"
#include "TArtDCHit.hh"
#include "TArtHODPla.hh"
#include "TArtHODPlaPara.hh"
#include "TArtNEBULAFilter.hh"
#include "TArtNEBULAHPC.hh"
#include "TArtNEBULAHPCPara.hh"
#include "TArtNEBULAPla.hh"
#include "TArtNEBULAPlaPara.hh"
#include "TArtSAMURAIParameters.hh"
#include "TSystem.h"
#include "TArtEventStore.hh"
#include "TArtEventInfo.hh"
#include "TArtDALIParameters.hh"
#include "TArtBigRIPSParameters.hh"
#include "TArtCalibDALI.hh"
#include "TArtCalibIC.hh"
#include "TArtCalibICF.hh"
#include "TArtICPara.hh"
#include "TFile.h"
#include "TTree.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TMath.h"
#include "TCutG.h"
#include "TArtRecoBeam.hh"

void ConvertRun(int,int);

////////////////////////////////////////////////////////////MAIN////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {

   Int_t RunNumber;
   //Int_t NumberOfEvent = 5000;
   Int_t NumberOfEvent = 50000000;

   if(argc==1) 
   {
      cout << "USAGE: ./MakeTDCCalibrations runnumber MaxmiumEvent " << endl;
   } 
   else if(argc==2)
   {
      RunNumber= atoi(argv[1]);
   }
   else if(argc==3)
   {

      RunNumber= atoi(argv[1]);
      NumberOfEvent = atoi(argv[2]);
   }

   ConvertRun(RunNumber,NumberOfEvent);
   return 0;
}

////////////////////////////////////////////////////////////RUN ANALYSIS FUNCTION////////////////////////////////////////////////////////////

void ConvertRun (int RunNumber, int MaxEventNumber) {

	gSystem->Load("libanacore.so");
	gSystem->Load("libanasamurai.so");
	gSystem->Load("libXMLParser.so");

	////////////////////ANAROOT Parameters////////////////////	
	TArtStoreManager *sman = TArtStoreManager::Instance();
	TArtBigRIPSParameters* BigRIPSPara = TArtBigRIPSParameters::Instance();
	TArtSAMURAIParameters *SamuraiPara = TArtSAMURAIParameters::Instance();

	BigRIPSPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/db/SAMURAIPlastic.xml"); //F3 F7 and SBT plastic

	SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/db/SAMURAIBDC1.xml");
	SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/db/SAMURAIBDC2.xml");
	SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/db/SAMURAIFDC0.xml");
	SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/db/SAMURAIFDC1.xml");
	SamuraiPara->LoadParameter((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/db/SAMURAIFDC2.xml");


	////////////////////Create ANAROOT Reconstruction classes////////////////////	
	// Load BigRIPS Plastic detector
	TArtCalibPlastic *CalibPlastic = new TArtCalibPlastic();
	// Load BDC1 & BDC2
	TArtCalibBDC1Hit *CalibBDC1Hit   = new TArtCalibBDC1Hit();
	TArtCalibBDC2Hit *CalibBDC2Hit   = new TArtCalibBDC2Hit();
	// Load FDC0 && FDC1 && FDC2
	TArtCalibFDC0Hit *CalibFDC0Hit = new TArtCalibFDC0Hit();
	TArtCalibFDC1Hit *CalibFDC1Hit = new TArtCalibFDC1Hit();
	TArtCalibFDC2Hit *CalibFDC2Hit = new TArtCalibFDC2Hit();

	////////////////////Starting Analysis////////////////////	
	Int_t EventNumber = 0; 
	// Open RIDF
	TArtEventStore *EventStore = new TArtEventStore;
	TString ridfpath = (TString)"/media/Rawdata/RIKEN_Cluster_2018/";
	TString ridfname=Form("run0%d.ridf.gz",RunNumber);
	const TString RidfFilename = ridfpath +ridfname;
	TString calpath = (TString)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/dc/db/dc/";
	TString rootname=Form("DriftsTDCDistribution_run%d.root",RunNumber);
	const TString calFilename = calpath + rootname;
	//const char *RidfFilename = Form("/data/RIKEN/DayOne/users/revel/ridf/s021/ridf/run%04d.ridf.gz",RunNumber);
	if(!EventStore->Open(RidfFilename)) {
		std::cout << "\e[34m " << "cannot open " << RidfFilename << "\e[37m" << std::endl;
		exit(0);
	} else {
		// RootFile
		//TFile *RootFile = new TFile(Form("/data/RIKEN/DayOne/users/revel/Analysis/Calibrations/DriftsTDCDistributionrun%04d.root",RunNumber),"recreate");
	        TFile *RootFile = new TFile(calFilename,"recreate");
		if(RootFile->IsZombie()) {
			std::cout << "\e[34m " << "cannot open " << calFilename << "\e[37m" << std::endl;
			exit(0);
		} else {

			//Histogram setting
			TH2D *BDC1_TDCDistribution[8];
			TH2D *BDC2_TDCDistribution[8];  
			TH2D *FDC0_TDCDistribution[8];  
			for (Int_t i=0; i<8; i++) {
				BDC1_TDCDistribution[i] = new TH2D(Form("BDC1TDCDistLayer%02d",i),Form("BDC1Layer%02d_RealTDCvsWireID",i),4096,0,4095,18,-0.5,17.5);  
				BDC2_TDCDistribution[i] = new TH2D(Form("BDC2TDCDistLayer%02d",i),Form("BDC2Layer%02d_RealTDCvsWireID",i),4096,0,4095,18,-0.5,17.5);  
				FDC0_TDCDistribution[i] = new TH2D(Form("FDC0TDCDistLayer%02d",i),Form("FDC0Layer%02d_RealTDCvsWireID",i),4096,0,4095,34,-0.5,33.5);  
			}
			TH2D *FDC1_TDCDistribution[14];  
			TH2D *FDC2_TDCDistribution[14];  
			for (Int_t i=0; i<14; i++) {
				FDC1_TDCDistribution[i] = new TH2D(Form("FDC1TDCDistLayer%02d",i),Form("FDC1Layer%02d_RealTDCvsWireID",i),4096,0,4095,34,-0.5,33.5);  
				FDC2_TDCDistribution[i] = new TH2D(Form("FDC2TDCDistLayer%02d",i),Form("FDC2Layer%02d_RealTDCvsWireID",i),4096,0,4095,114,-0.5,113.5);  
			}

			// Start analysis event by event
			std::cout << "\e[31m " << "Starting analysis of run  " << RunNumber << "\e[37m" << endl;

			// Analysis Loop
			while(EventStore->GetNextEvent() 
                  && EventNumber < MaxEventNumber
                  ) {

				// Printing status
				if (EventNumber % 10000 == 0){
					std::cout << "\e[31m " << "Event # : " << EventNumber << "\r";
					std::cout.flush();
				}
				std::cout << "\e[37m";
				EventNumber++;

				//Initialisation of parameters
				CalibPlastic->ClearData();
				CalibPlastic->ReconstructData();

				TArtPlastic *PlasticF3 = CalibPlastic->FindPlastic((char*)"F3pl"); 
				TArtPlastic *PlasticSBT1= CalibPlastic->FindPlastic((char*)"F13pl-1");
				TArtPlastic *PlasticSBT2 = CalibPlastic->FindPlastic((char*)"F13pl-2");
				
                                //cout<<"Plastic="<< (PlasticSBT1 && PlasticSBT2 && PlasticF3)<<endl;
                                //cout<<"Plastic="<< (PlasticSBT1)<<endl;
                                //cout<<"Plastic="<< (PlasticSBT2 )<<endl;
                                //cout<<"Plastic="<< ( PlasticF3)<<endl;
				if(PlasticSBT1 && PlasticSBT2 && PlasticF3) { //WARNING :: here is the issue 

					TArtStoreManager * sman = TArtStoreManager::Instance();
					CalibBDC1Hit->ClearData();
					CalibBDC1Hit->ReconstructData();
					TClonesArray *BDC1Hit = (TClonesArray *)sman->FindDataContainer((char*)"SAMURAIBDC1Hit");

					CalibBDC2Hit->ClearData();
					CalibBDC2Hit->ReconstructData();
					TClonesArray *BDC2Hit = (TClonesArray *)sman->FindDataContainer((char*)"SAMURAIBDC2Hit");

					CalibFDC0Hit->ClearData();
					CalibFDC0Hit->ReconstructData();
					TClonesArray *FDC0Hit = (TClonesArray *)sman->FindDataContainer((char*)"SAMURAIFDC0Hit");

					CalibFDC1Hit->ClearData();
					CalibFDC1Hit->ReconstructData();
					TClonesArray *FDC1Hit = (TClonesArray *)sman->FindDataContainer((char*)"SAMURAIFDC1Hit");

					CalibFDC2Hit->ClearData();
					CalibFDC2Hit->ReconstructData();
					TClonesArray *FDC2Hit = (TClonesArray *)sman->FindDataContainer((char*)"SAMURAIFDC2Hit");
					
					if(BDC1Hit) {
						Int_t BDC1NumberOfHits = BDC1Hit->GetEntries();
						if(BDC1NumberOfHits > 0) {
							TArtDCHit *HitBDC1;
							for(Int_t i=0; i<BDC1NumberOfHits; i++) {
								HitBDC1 = (TArtDCHit *)BDC1Hit->At(i);
								if(HitBDC1){ 
								  BDC1_TDCDistribution[HitBDC1->GetLayer()]->Fill(HitBDC1->GetTDC(),HitBDC1->GetWireID());
								}
							}
						} 
					}

					if(BDC2Hit) { 
						Int_t BDC2NumberOfHits = BDC2Hit->GetEntries();
						if(BDC2NumberOfHits > 0) {
							TArtDCHit *HitBDC2;
							for(Int_t i=0; i<BDC2NumberOfHits; i++) {
								HitBDC2 = (TArtDCHit *)BDC2Hit->At(i);
								if(HitBDC2) 
									BDC2_TDCDistribution[HitBDC2->GetLayer()]->Fill(HitBDC2->GetTDC(),HitBDC2->GetWireID());
							}
						} 
					} 		

                    if(FDC0Hit) { 
                       Int_t FDC0NumberOfHits = FDC0Hit->GetEntries();
                       if(FDC0NumberOfHits > 0) {
                          TArtDCHit *HitFDC0;
                          for(Int_t i=0; i<FDC0NumberOfHits; i++) {
                             HitFDC0 = (TArtDCHit *)FDC0Hit->At(i);
                             if(HitFDC0) 
                                FDC0_TDCDistribution[HitFDC0->GetLayer()]->Fill(HitFDC0->GetTDC(),HitFDC0->GetWireID());
                          }
                       } 
                    }

					if(FDC1Hit) { 
						Int_t FDC1NumberOfHits = FDC1Hit->GetEntries();
						if(FDC1NumberOfHits > 0) {
							TArtDCHit *HitFDC1;
							for(Int_t i=0; i<FDC1NumberOfHits; i++) {
								HitFDC1 = (TArtDCHit *)FDC1Hit->At(i);
								if(HitFDC1) 
									FDC1_TDCDistribution[HitFDC1->GetLayer()]->Fill(HitFDC1->GetTDC(),HitFDC1->GetWireID());
							}
						} 
					} 

					if(FDC2Hit) { 
						Int_t FDC2NumberOfHits = FDC2Hit->GetEntries();
						if(FDC2NumberOfHits > 0) {
							TArtDCHit *HitFDC2;
							for(Int_t i=0; i<FDC2NumberOfHits; i++) {
								HitFDC2 = (TArtDCHit *)FDC2Hit->At(i);
								if(HitFDC2) 
									FDC2_TDCDistribution[HitFDC2->GetLayer()]->Fill(HitFDC2->GetTDC(),HitFDC2->GetWireID());
							}
						} 
					}
				}
			}

			std::cout << "\e[31m " << "Analysis finished ! Writting " << calFilename << "\e[37m" << endl; 
			for (Int_t i=0; i<8; i++) {
				BDC1_TDCDistribution[i]->Write();
				BDC2_TDCDistribution[i]->Write();
				FDC0_TDCDistribution[i]->Write();
			}
			for (Int_t i=0; i<14; i++) {
				FDC1_TDCDistribution[i]->Write();
				FDC2_TDCDistribution[i]->Write();
			}
			RootFile->Close("R");
		}
	}
	EventStore->ClearData();

	cout << "\e[31m " << "Endl of analysis of run " <<RunNumber << "\e[37m" << endl;
	cout << "\e[31m " << "Total events read :: " << EventNumber << "\e[37m" << endl;
	
	delete BigRIPSPara;
	delete SamuraiPara; 
	delete CalibPlastic;
	delete CalibBDC1Hit;
	delete CalibBDC2Hit;
	delete CalibFDC0Hit;
	delete CalibFDC1Hit;
	delete CalibFDC2Hit;
	// delete EventStore;
	delete TArtStoreManager::Instance();
}
