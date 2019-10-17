
//////////////////// Header ////////////////////      
#include "header.h"
//////////////////// Main Function and Argc ////////////////////      
int main(int argc, char* argv[]) {

	Int_t RunNumber;
	Int_t MaxEventNumber = 5;
	//Int_t MaxEventNumber = 50000000;

	if(argc==1) 
	{
		cout << "USAGE: ./plastic runnumber MaxmiumEvent " << endl;
	} 
	else if(argc==2)
	{
		RunNumber= atoi(argv[1]);
	}
	else if(argc==3)
	{

		RunNumber= atoi(argv[1]);
		MaxEventNumber = atoi(argv[2]);
	}


	//////////////////// Load anaroot decode class ////////////////////      
	gSystem->Load("libanacore.so");
	gSystem->Load("libanasamurai.so");
	gSystem->Load("libXMLParser.so");

	////////////////////ANAROOT Parameters////////////////////      
	//
	TString UserFolder="/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/";
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

	////////////////////Setup input and output files////////////////////       
	TString ridfpath = (TString)"/media/Rawdata/RIKEN_Cluster_2018/";
	TString ridfname=Form("run0%d.ridf.gz",RunNumber);
	const TString RidfFilename = ridfpath +ridfname;
	TString calpath = (TString)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/dc/db/dc/";
	TString rootname=Form("DriftsTDCDistribution_run%d.root",RunNumber);
	const TString calFilename = calpath + rootname;
	//const char *RidfFilename = Form("/data/RIKEN/DayOne/users/revel/ridf/s021/ridf/run%04d.ridf.gz",RunNumber);
	// Open RIDF input
	TArtEventStore *EventStore = new TArtEventStore;

	if(!EventStore->Open(RidfFilename)) 
	{
		std::cout << "\e[34m " << "cannot open " << RidfFilename << "\e[37m" << std::endl;
		exit(0);
	}
	// Create Rootfiles Output
	TFile *RootFile = new TFile(calFilename,"recreate");



	//////////////////// Analysis Loop ////////////////////       
	Int_t EventNumber = 0;
	while(EventStore->GetNextEvent() 
			&& EventNumber < MaxEventNumber
	     ) {

		// Clear Data Array
		CalibPlastic->ClearData();

		TArtRawEventObject *fEvent = (TArtRawEventObject *)sman->FindDataContainer("RawEvent");

		for(Int_t i=0;i<fEvent->GetNumSeg();i++){
			TArtRawSegmentObject	*seg	  = fEvent->GetSegment(i);
			Int_t			 device   = seg->GetDevice();
			Int_t			 detector = seg->GetDetector();
			Int_t			 module   = seg->GetModule();

			//cout<<" device "<<device<<" samurai "<<SAMURAI<<" bigrips "<<BIGRIPS<<endl;
			//cout<<" detector "<<detector<<" coin "<<COIN<<endl;
			if(device == SAMURAI){

				switch(detector) {
					//kw: plastic appears twice, under device SAMURAI 2 and BigRIPS 0, Samurai comes first, so if we read this in BigRIPS we actually overwrite
					case    PLAT:{
							     CalibPlastic->LoadData(seg); 
							     for(Int_t j=0;j<seg->GetNumData();j++){
								     TArtRawDataObject *d = seg->GetData(j);
								     Int_t geo = d->GetGeo();
								     Int_t ch = d->GetCh();
								     Int_t val = (Int_t)d->GetVal();
								     Int_t edge = (Int_t)d->GetEdge();
								     cout<<geo<<" "<<ch<<" "<<val<<" "<<edge<<endl;
							     }
							     break;


						     }
					case STOPPLA: CalibPlastic->LoadData(seg); break;
						      //	  case      RF: if(kBEAM) CalibPlastic->LoadData(seg); break; //??
					case    PLAQ: CalibPlastic->LoadData(seg); break;
					default:  break;
				}
			}
		}
		cout<<"here"<<endl; 
		// Printing status
		if (EventNumber % 10000 == 0){
			std::cout << "\e[31m " << "Event # : " << EventNumber << "\r";
			std::cout.flush();
		}
		std::cout << "\e[37m";
		EventNumber++;

		//Initialisation of parameters
		CalibPlastic->ReconstructData();
		cout<<CalibPlastic->GetNumPlastic()<<endl;
		for(Int_t i=0;i<CalibPlastic->GetNumPlastic();i++){
			TArtPlastic *pla = (TArtPlastic*)CalibPlastic->GetPlastic(i);
			if(!pla->IsDataValid()) continue;
			Double_t fTLRaw = pla->GetTLRaw();
			Double_t fTRRaw = pla->GetTRRaw();
			Double_t fQLRaw = pla->GetQLRaw();
			Double_t fQRRaw = pla->GetQRRaw();
			cout<<fTLRaw<<" "<<fTRRaw<<endl;
		}

		TArtPlastic *PlasticF3 = CalibPlastic->FindPlastic((char*)"F3pl"); 
		TArtPlastic *PlasticSBT1= CalibPlastic->FindPlastic((char*)"F13pl-1");
		TArtPlastic *PlasticSBT2 = CalibPlastic->FindPlastic((char*)"F13pl-2");

		//	cout<<"Plastic="<< (PlasticSBT1 && PlasticSBT2 && PlasticF3)<<endl;
		//	cout<<"Plastic="<< (PlasticSBT1)<<endl;
		//	cout<<"Plastic="<< (PlasticSBT2 )<<endl;
		//	cout<<"Plastic="<< ( PlasticF3)<<endl;

	}



	EventStore->ClearData();

	cout << "\e[31m " << "Endl of analysis of run " <<RunNumber << "\e[37m" << endl;
	cout << "\e[31m " << "Total events read :: " << EventNumber << "\e[37m" << endl;

	delete BigRIPSPara;
	delete SamuraiPara;
	delete CalibPlastic;
	// delete EventStore;
	delete TArtStoreManager::Instance();


	return 0;
}
