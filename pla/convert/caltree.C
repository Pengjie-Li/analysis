#include <TSystem.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "TH2F.h"
#include "TEnv.h"
#include "TH1F.h"
#include "TH1.h"
#include "TVector3.h"
#include "TVectorD.h"
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include "TArtPlastic.hh"
#include "TArtCalibPlastic.hh"
#include "THashList.h"
#include "TArtCalibPPAC.hh"
//#include "TArtCalibPID.hh"
#include "TArtPPACPara.hh"
#include "TArtPPAC.hh"
#include "TArtFocalPlane.hh"
#include "TArtCalibFocalPlane.hh"
#include "TArtEventStore.hh"
#include "TArtEventInfo.hh"
#include "TArtCalibCoin.hh"
#include "TArtBigRIPSParameters.hh"
#include "TArtCalibIC.hh"
#include "TArtCalibICF.hh"
#include "TArtICPara.hh"
#include "TArtCalibDCTrack.hh"
#include "TArtCalibDCHit.hh"
#include "TArtCalibBDC1Hit.hh"
#include "TArtCalibBDC1Track.hh"
#include "TArtCalibBDC2Hit.hh"
#include "TArtCalibBDC2Track.hh"
#include "TArtCalibFDC0Hit.hh"
#include "TArtCalibFDC0Track.hh"
#include "TArtCalibSimpleFDC0Track.hh"
#include "TArtCalibSimpleFDC1Track.hh"
#include "TArtCalibSimpleFDC2Track.hh"
#include "TArtCalibSimpleBDC1Track.hh"
#include "TArtCalibSimpleBDC2Track.hh"
#include "TArtCalibFDC1Track.hh"
#include "TArtCalibFDC2Track.hh"
#include "TArtCalibFDC2Hit.hh"
#include "TArtDCHit.hh"
#include "TArtDCHitPara.hh"
#include "TArtDCTrack.hh"
#include "TArtCalibBPCHit.hh"
#include "TArtCalibHODPla.hh"
#include "TArtHODPla.hh"
#include "TArtHODPlaPara.hh"
#include "TArtSAMURAIParameters.hh"
#include "TArtRawEventObject.hh"
#include "TArtCore.hh"
#include "TArtCalibNEBULA.hh"
#include "TArtCalibNEBULAHPC.hh"
#include "TArtNEBULAFilter.hh"
#include "TArtNEBULAHPC.hh"
#include "TArtNEBULAHPCPara.hh"
#include "TArtNEBULAPla.hh"
#include "TArtNEBULAPlaPara.hh"
#include "TArtDALINaIPara.hh"
#include "TArtDALINaI.hh"
#include "TArtDALIParameters.hh"
#include "TArtCalibDALI.hh"
#include "TArtCalibWINDSPla.hh"
#include "TArtWINDSPla.hh"
#include "TArtWINDSParameters.hh"
#include "TArtSILICONS.hh"
#include "TArtSILICONSParameters.hh"
#include "TArtCalibSILICONS.hh"
#include "TArtBDC.hh"
#include "TArtBLD.hh"
#include "TArtCalibBDC.hh"
#include "TArtCalibBLD.hh"
#include "TArtCalibDia.hh"
#include "TArtCalibFADC.hh"
#include "TArtCalibPlas.hh"
#include "TArtCalibRDC.hh"
#include "TArtCalibRNaI.hh"
#include "TArtCalibTDCHit.hh"
#include "TArtDia.hh"
#include "TArtESPRIParameters.hh"
#include "TArtFADC.hh"
#include "TArtFADCPara.hh"
#include "TArtPlas.hh"
#include "TArtPlasPara.hh"
#include "TArtRDC.hh"
#include "TArtRNaI.hh"
#include "TArtRNaIPara.hh"
#include "TArtTDCHit.hh"
#include "TArtTDCHitPara.hh"
#include "TArtUserParameters.hh"
//#include "TArtRecoFragment.hh"
#include "TArtFragment.hh"

#include <sys/types.h>
#include <sys/stat.h>

//#define w_tracking 
#ifdef w_tracking
#include "macros/samurai_fun_len_s034.C"
#include "macros/samurai_fun_rig_s034.C"
#endif

#include <climits>
#include <map>
#include <ctime>

#define NUMBER_OF_HODO 40

#define WriteOneEnvFile(file) file->Write(TString(TString(file->GetRcName()).ReplaceAll("/","_")).ReplaceAll(".","_"));
#define WriteAllEnvFiles WriteOneEnvFile(env_par); WriteOneEnvFile(env_geo); WriteOneEnvFile(env_nebt0);

// Functions used
//void LoadDCTDCDistributionFull(char *FileName, TArtCalibBDC1Track *, TArtCalibBDC2Track *, TArtCalibSimpleFDC1Track *, TArtCalibSimpleFDC2Track *);
//void LoadDCTDCDistributionFull(char *FileName, TArtCalibBDC1Track *, TArtCalibBDC2Track *, TArtCalibFDC1Track *, TArtCalibFDC2Track *);
void SortHodoHit(vector<Int_t> &, vector<Double_t> &);
Double_t DopplerCorrection(Double_t, Double_t, Double_t);
inline bool exists_test (const std::string&);
inline bool exists_test (const TString&);
void SortDaliHit(Int_t, Int_t,vector <Int_t> *,vector <Double_t> *, vector <Double_t> *, vector <Double_t> *, vector <Double_t> *);
void SortNeutronHit(int, int,vector <Bool_t> *, vector <Int_t> *,vector <Double_t> *,vector <Double_t> *,vector <Double_t> *,vector <Double_t> *, vector <Double_t> *, vector <Double_t> *, vector <Double_t> *);

int main(int argc, char *argv[])
{
	Long64_t MaxEventNumber = LLONG_MAX;
	//MaxEventNumber = 100;
	bool EventByEvent=false;
	const Int_t DISPLAY_EVERY_EVENT = 500 ;
	std::clock_t start = std::clock();
	std::clock_t clock0 = std::clock();
	Bool_t kMAIN=kFALSE,
	       kNEUT=kFALSE,
	       kFDC =kFALSE,
	       kHODO=kFALSE,
	       kBDC =kFALSE, 
	       kPLA =kFALSE, 
	       kESPRI=kFALSE,
	       kSILI=kFALSE;
	Bool_t kRunLive = kFALSE, kOverwrite=kTRUE;
	// a (or nothing) or any combinasion mndfhb
	int opt;
	Bool_t kShowHelp = kFALSE;
	std::map<char,bool *> flagMap;

	while ((opt = getopt(argc, argv, "ABCDEFGHMNPSVfhn:")) != -1) {
		switch (opt) {
			case 'A':
				//kMAIN=kNEUT=kFDCs=kHODO=kBEAM=kESPRI=kSILI=kTRUE; //kDALI=kPANDORA //kFDCs_full
				kMAIN=kNEUT=kBDC=kPLA=kHODO=kESPRI=kSILI=kTRUE; //kDALI=kPANDORA //kFDCs_full
				//kMAIN=kNEUT=kBDC=kPLA=kFDC=kHODO=kESPRI=kSILI=kTRUE; //kDALI=kPANDORA //kFDCs_full
				//kMAIN=kNEUT=kHODO=kBEAM=kESPRI=kSILI=kTRUE; //kDALI=kPANDORA //kFDCs_full
				break;
			case 'B':
				kBDC=kTRUE;
				break;
			case 'E':
				kESPRI=kTRUE;
				break;
			case 'F':
				kFDC=kTRUE;
				break;
			case 'H':
				kHODO=kTRUE;
				break;
			case 'N':
				kNEUT=kTRUE;      
				break;
			case 'M':
				kMAIN=kTRUE;
				break;
			case 'S':
				kSILI=kTRUE;
				break;
			case 'P':
				kPLA=kTRUE;
				break;

			case 'V':
				kRunLive=kTRUE;
				break;
			case 'h':
				kShowHelp = kTRUE;
				break;
			case 'f':
				kOverwrite = kTRUE;
				break;
			case 'n':
				MaxEventNumber = atoi(optarg);
				MaxEventNumber = 1e4;
				std::clog << "\e[31m" << "  ANALYSIS-Info : You will analyse " << MaxEventNumber << " events" << "\e[0m" << std::endl;
				break;
			default: /* '?' */
				kMAIN=kNEUT=kFDC=kHODO=kBDC=kESPRI=kSILI=kPLA=kFALSE; 
		}
	}

	if(kRunLive && MaxEventNumber == LLONG_MAX){
		std::cerr <<  " For the live mode you should put a maximum number, with -n flag" << endl;
		kShowHelp = kTRUE;
	}

	Int_t FileNumber = TString(argv[optind]).Atoi();
	Int_t runnum=FileNumber;

	if(!kRunLive && FileNumber==0){
		std::cerr <<  " You should provide either a runnumber or use the -V (for live) flag" << endl;
		kShowHelp = kTRUE;
	}

	if ( kShowHelp || (!kMAIN && !kNEUT && !kSILI && !kESPRI && !kFDC && !kHODO && !kBDC && !kPLA )) {
		std::cerr <<  "Usage: " << argv[0] << " run_number " << std::endl;
		std::cerr <<  "Usage: " << argv[0] << " -n nb_of_events run_number " << std::endl ;
		std::cerr <<  "Usage: " << argv[0] << " -h for help"  << std::endl;
		std::cerr <<  "Usage: " << argv[0] << " -V for liVe conversion " << std::endl ;
		std::cerr <<  "       Conversion options: " << endl;
		std::cerr <<  "       -A for ALL " << endl;
		std::cerr <<  "       -B for BDC " << endl;
		std::cerr <<  "       -P for PLA " << endl;
		std::cerr <<  "       -E for ESPRI " << endl;
		std::cerr <<  "       -F for FDCs (w/ fast tracking) " << endl;
		std::cerr <<  "       -H for HODO " << endl;
		std::cerr <<  "       -M for MAIN " << endl;
		std::cerr <<  "       -N for NEUT(rons) " << endl;
		std::cerr <<  "       -S for SILICONS " << endl;
		std::cerr <<  "       Other options: " << endl;
		std::cerr <<  "       -f force overwriting the output files " << endl;
		exit(EXIT_FAILURE);
	}

	flagMap['E']=&kESPRI;      
	flagMap['F']=&kFDC;      
	flagMap['B']=&kBDC;      
	flagMap['P']=&kPLA;      
	flagMap['H']=&kHODO;      
	flagMap['M']=&kMAIN;
	flagMap['N']=&kNEUT;            
	flagMap['S']=&kSILI;            

	TEnv *env_par = new  TEnv("./conversion_settings.prm") ;
	TString FileName = Form("%s%04d",env_par->GetValue("runprefix","run"),FileNumber);
	TString pathridf = env_par->GetValue("ridffilepath","");
	TString RidfFilename = pathridf + FileName + (TString)".ridf";
	TString rootfilepath = "";
	TString rootfilesubpath = "";

	if(!kRunLive){
		if(!exists_test(RidfFilename)){
			cerr << "\e[1;33;42m" << "  ANALYSIS-Error : File '" << RidfFilename <<  "' does not exists. Test for " << RidfFilename << ".gz\e[0m\n" << endl;

			RidfFilename += ".gz" ;

			if(!exists_test(RidfFilename)){
				cerr << "\e[1;33;41m" << "  ANALYSIS-Error : File '" << RidfFilename <<  "' does not exists. Abort.\e[0m\n" << endl;
				exit(EXIT_FAILURE);
			}
		}
		rootfilepath = TString(env_par->GetValue("rootfilepath","")) ;
		rootfilesubpath = rootfilepath + "/" + TString(FileName);

		// check and/or create root file directory
		struct stat infopath;
		struct stat infosubpath;
		if(stat( rootfilepath, &infopath ) != 0){
			cerr <<  "\e[1;33;41m" << "Root Directory :'" << rootfilepath <<  "' does not exists. Abort.\e[0m\n" << endl;
		} else if( infopath.st_mode & S_IFDIR ) {
			if(stat( rootfilesubpath, &infosubpath ) != 0){
				cout <<  "\e[33m  ANALYSIS-Info : Create directory '" << rootfilesubpath <<  "'\e[0m" << endl;
				system("mkdir "+rootfilesubpath);
			}
		}
		cout <<  "\e[33m  ANALYSIS-Info : Root files in '" << rootfilesubpath <<  "'\e[0m" << endl;
	}
	// ====================== ANAROOT Parameters =======================

	TArtBigRIPSParameters *BigRIPSPara = TArtBigRIPSParameters::Instance();
	TArtSAMURAIParameters *SamuraiPara = new TArtSAMURAIParameters();
	TArtDALIParameters *DALIPara = TArtDALIParameters::Instance();
	TArtSILICONSParameters *SILICONSPara = TArtSILICONSParameters::Instance();
	TArtStoreManager *sman = TArtStoreManager::Instance();
	TArtWINDSParameters *WINDSPara = new TArtWINDSParameters();
	TArtESPRIParameters *ESPRIPara = new TArtESPRIParameters();
	TArtUserParameters *ESPRIUserPara = TArtUserParameters::Instance();

	TObjString *xmlfile;

	TIter next(TString(env_par->GetValue("BigRIPSPara","")).Tokenize(" "));
	while(( xmlfile = (TObjString *)next())) {
		BigRIPSPara->LoadParameter((char*)xmlfile->GetName());
	}

	next = TString(env_par->GetValue("SamuraiPara","")).Tokenize(" ");
	while(( xmlfile = (TObjString *)next())) {
		SamuraiPara->LoadParameter((char*)xmlfile->GetName());
	}

	if(runnum<331)	SamuraiPara->LoadParameter("db/SAMURAIPlastic_Be10.xml");
	else if(runnum>330&&runnum<366)	SamuraiPara->LoadParameter("db/SAMURAIPlastic_Be12.xml");
	else if(runnum>365&&runnum<595)	SamuraiPara->LoadParameter("db/SAMURAIPlastic_Be14.xml");
	else if(runnum>594&&runnum<601) SamuraiPara->LoadParameter("db/SAMURAIPlastic_a.xml");
	else SamuraiPara->LoadParameter("db/SAMURAIPlastic.xml");

	if(runnum<331)	BigRIPSPara->LoadParameter("db/SAMURAIPlastic_Be10.xml");
	else if(runnum>330&&runnum<366)	BigRIPSPara->LoadParameter("db/SAMURAIPlastic_Be12.xml");
	else if(runnum>365&&runnum<595)	BigRIPSPara->LoadParameter("db/SAMURAIPlastic_Be14.xml");
	else if(runnum>594&&runnum<601) BigRIPSPara->LoadParameter("db/SAMURAIPlastic_a.xml");
	else BigRIPSPara->LoadParameter("db/SAMURAIPlastic.xml");




	next = TString(env_par->GetValue("SILICONSPara","")).Tokenize(" ");
	while(( xmlfile = (TObjString *)next())) {
		SILICONSPara->LoadParameter((char*)xmlfile->GetName());
	}

	next = TString(env_par->GetValue("ESPRIPara","")).Tokenize(" ");
	while(( xmlfile = (TObjString *)next())) {
		ESPRIPara->LoadParameter((char*)xmlfile->GetName());
	}

	next = TString(env_par->GetValue("ESPRIUserPara","")).Tokenize(" ");
	while(( xmlfile = (TObjString *)next())) {
		ESPRIUserPara->LoadParameter((char*)xmlfile->GetName());
	}



	////////////////////Create ANAROOT Reconstruction classes////////////////////   

	// Load coincidence register
	TArtCalibCoin *CalibCoin = 0;
	CalibCoin=new TArtCalibCoin;
	CalibCoin->SetAddress(85);

	// Load Beamline Plastic
	TArtCalibPlastic* CalibPlastic = new TArtCalibPlastic;

	// Load Drift Chambers
	TArtCalibBDC1Hit   *CalibBDC1Hit   = new TArtCalibBDC1Hit();
	TArtCalibBDC1Track *CalibBDC1Track = new TArtCalibBDC1Track();
	TArtCalibBDC2Hit   *CalibBDC2Hit   = new TArtCalibBDC2Hit();
	TArtCalibBDC2Track *CalibBDC2Track = new TArtCalibBDC2Track();
	TArtCalibFDC0Hit   *CalibFDC0Hit   = new TArtCalibFDC0Hit();
	TArtCalibFDC0Track *CalibFDC0Track = new TArtCalibFDC0Track();
	TArtCalibFDC2Hit   *CalibFDC2Hit   = new TArtCalibFDC2Hit();
	TArtCalibFDC2Track *CalibFDC2Track = new TArtCalibFDC2Track();


	// Load Telescope
	TArtCalibSILICONS *CalibSILICONS = new TArtCalibSILICONS();


	// Load PAC and FocalPlane
	TArtCalibPPAC *CalibPPAC = new TArtCalibPPAC();
	TArtCalibFocalPlane *CalibFocalPlane = new TArtCalibFocalPlane();
	// Load IC
	TArtCalibIC *CalibIC = new TArtCalibIC();
	//TArtCalibSimpleFDC1Track *CalibSimpleFDC1Track;

	// Load ESPRI
	TArtCalibRNaI *CalibESPRI_NaI = new TArtCalibRNaI();
	TArtCalibTDCHit *CalibESPRI_tdc = new TArtCalibTDCHit();
	TArtCalibFADC *CalibESPRI_fadc = new TArtCalibFADC();
	TArtCalibRDC *CalibESPRI_rdc = new TArtCalibRDC();
	TArtCalibPlas *CalibESPRI_plas = new TArtCalibPlas();

	// Load Hodoscope
	TArtCalibHODPla *CalibHODPla = new TArtCalibHODPla();
	// Load NEBULA
	TArtCalibNEBULA *CalibNEBULA = new TArtCalibNEBULA();



	///////////////////////////////////////////////////////////////////
	/////////////////////Load TDC Distribution/////////////////////////
	///////////////////////////////////////////////////////////////////
	cout << "   CALTREE-Info : Load TDC Distribution" << endl;

	CalibBDC1Track->SetTDCWindow(1700,1870);
	CalibBDC2Track->SetTDCWindow(1700,1870);
	CalibFDC0Track->SetTDCWindow(1700,1870);

	TFile *dcin = new TFile(Form("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/dc/root/dcdist0%d.root",runnum),"READ");
	if(dcin->IsOpen()){
		gROOT->cd();
		TH1* hist = NULL;
		// BDC1
		for(Int_t ihist=0;ihist<8;ihist++){
			hist = (TH1D*)dcin->Get(Form("hbdc1tdc%d",ihist));
			CalibBDC1Track->SetTDCDistribution(hist,ihist);
			delete hist;
			hist = NULL;
		}

		// BDC2
		for(Int_t ihist=0;ihist<8;ihist++){
			hist = (TH1D*)dcin->Get(Form("hbdc2tdc%d",ihist));
			CalibBDC2Track->SetTDCDistribution(hist,ihist);
			delete hist;
			hist = NULL;
		}
		// FDC0
		for(Int_t ihist=0;ihist<8;ihist++){
			hist = (TH1D*)dcin->Get(Form("hfdc0tdc%d",ihist));
			CalibFDC0Track->SetTDCDistribution(hist,ihist);
			delete hist;
			hist = NULL;
		}

	}


	///////////////////////////////////////////////////////////////////
	/////////////////////Load Geometry Data /////////////////////////
	///////////////////////////////////////////////////////////////////


	//Data
	TEnv * env_geo= new TEnv(env_par->GetValue("geometrydata","")); //mm
	Double_t BDC1_Width = env_geo->GetValue("BDC1_Width",0.0); //mm
	//Double_t FDC1_Width = env_geo->GetValue("FDC1_Width",0.0); //mm
	Double_t FDC0_Width = env_geo->GetValue("FDC0_Width",0.0); //mm
	Double_t Dist_BDC1BDC2 = env_geo->GetValue("Dist_BDC1BDC2",0.0); //mm
	Double_t Dist_BDC1Target = env_geo->GetValue("Dist_BDC1Target",0.0); //mm
	//Double_t Dist_BDC1FDC1 = env_geo->GetValue("Dist_BDC1FDC1",0.0); //Distance between the middle of BDC1 and the middle of FDC1 mm
	Double_t Dist_BDC1FDC0 = env_geo->GetValue("Dist_BDC1FDC0",0.0); //Distance between the middle of BDC1 and the middle of FDC0 mm
	Double_t Dist_F7F13 = env_geo->GetValue("Dist_F7F13",0.0); //mm
	Double_t Dist_SBTTarget = env_geo->GetValue("Dist_SBTTarget",0.0); //mm
	Double_t Dist_BDC1SBV = env_geo->GetValue("Dist_BDC1SBV",0.0); //mm

	//HODO Time offset
	vector<Double_t> HODOT0(NUMBER_OF_HODO);
	TEnv *env_hodot0 = new TEnv(env_par->GetValue("HODO_TimeOffset",""));

	for (Int_t ID = 1; ID <= NUMBER_OF_HODO; ID++){
		HODOT0[ID-1] = env_hodot0->GetValue(Form("HODO_T0_DET%d",ID),0.0);
		//    cout << "HODO:"<<ID<<"  "<< HODOT0[ID-1] <<"ns"<< endl;
	}

	vector<Double_t> NEBULAT0(120);
	TEnv *env_nebt0 = new TEnv(env_par->GetValue("NEBULA_TimeOffset",""));

	for (Int_t ID = 1; ID < 121; ID++){
		NEBULAT0[ID-1] = env_nebt0->GetValue(Form("NEBULA_T0_DET%d",ID),0.0);
		//cout << NEBULAT0[ID-1] << endl;
	}

	cout << TString(env_nebt0->GetRcName()).ReplaceAll("/","_")<<endl;


	///////////////////////////////////////////////////////////////////
	///////////////////// Open Raw Data ///////////////////////////////
	///////////////////////////////////////////////////////////////////
	TArtEventStore *EventStore = new TArtEventStore;

	if (kRunLive)
	{
		EventStore->Open();
		FileName = "RunLive";
		std::clog << std::endl << std::endl <<  "     Converting live stream... " << std::endl;
		std::clog << "     Data will be stored in " << rootfilesubpath << FileName << ".root" << std::endl << std::endl;
	}
	else if(!EventStore->Open(RidfFilename))
	{
		std::cerr << "\e[34m " << "cannot open " << RidfFilename << "\e[37m" << std::endl << "aborting..." << std::endl;
		return 1;
	}



	///////////////////////////////////////////////////////////////////
	///////////////////// Create TFile and TTree  /////////////////////
	///////////////////////////////////////////////////////////////////

	const char *TreeName = "CalTree";
	const TString FileNameBody = FileName;
	FileNameBody(0,FileNameBody.Last('/')+1) = "";
	const TString RootFilenameBody  = rootfilesubpath + (TString)FileName ;
	const TString TmpRootFilenameBody  =  (TString)"/tmp/" + (TString)FileNameBody ;

	system(TString("rm -vf ")+TmpRootFilenameBody+"*.root");


	// MAIN Tree
	TFile *fout_MAIN = NULL;
	TTree *tree_MAIN = NULL;
	if(kMAIN){
		fout_MAIN = new TFile(TmpRootFilenameBody + (TString)"_MAIN.root" ,"recreate");
		tree_MAIN = new TTree(TreeName,"Analysis Tree MAIN");
		tree_MAIN->AutoSave("SaveSelf");
		tree_MAIN->SetAutoSave(1e5);
	}

	// BDC Tree
	TFile *fout_BDC = NULL;
	TTree *tree_BDC = NULL;
	if(kBDC){
		fout_BDC = new TFile(TmpRootFilenameBody + (TString)"_BDC.root","recreate");
		tree_BDC = new TTree(TreeName+(TString)"BDC","Analysis Tree BDC");
		//  tree_BDC->SetFile(fout_BDC);
		tree_BDC->AutoSave("SaveSelf");
		tree_BDC->SetAutoSave(1e5);
	}

	// PLA Tree
	TFile *fout_PLA = NULL;
	TTree *tree_PLA = NULL;
	if(kPLA){
		fout_PLA = new TFile(TmpRootFilenameBody + (TString)"_PLA.root","recreate");
		tree_PLA = new TTree(TreeName+(TString)"PLA","Analysis Tree PLA");
		//  tree_PLA->SetFile(fout_PLA);
		tree_PLA->AutoSave("SaveSelf");
		tree_PLA->SetAutoSave(1e5);
	}


	// NEUT Tree
	TFile *fout_NEUT = NULL;
	TTree *tree_NEUT = NULL;
	if(kNEUT){
		fout_NEUT = new TFile(TmpRootFilenameBody + (TString)"_NEUT.root","recreate");
		tree_NEUT = new TTree(TreeName+(TString)"NEUT","Analysis Tree NEUT");
		tree_NEUT->AutoSave("SaveSelf");
		tree_NEUT->SetAutoSave(1e5);
	}

	// SILICONS Tree
	TFile *fout_SILICONS = NULL;
	TTree *tree_SILICONS = NULL;
	if(kSILI){
		fout_SILICONS = new TFile(TmpRootFilenameBody + (TString)"_SILICONS.root","recreate");
		tree_SILICONS = new TTree(TreeName+(TString)"SILICONS","Analysis Tree SILICONS");
		tree_SILICONS->AutoSave("SaveSelf");
		tree_SILICONS->SetAutoSave(1e5);
	}

	// ESPRI Tree
	TFile *fout_ESPRI = NULL;
	TTree *tree_ESPRI = NULL;
	if(kESPRI){
		fout_ESPRI = new TFile(TmpRootFilenameBody + (TString)"_ESPRI.root","recreate");
		tree_ESPRI = new TTree(TreeName+(TString)"ESPRI","Analysis Tree ESPRI");
		tree_ESPRI->AutoSave("SaveSelf");
		tree_ESPRI->SetAutoSave(1e5);
	}

	// FDC Tree
	TFile *fout_FDC = NULL;
	TTree *tree_FDC = NULL;
	if(kFDC){
		fout_FDC = new TFile(TmpRootFilenameBody + (TString)"_FDCG.root","recreate");
		tree_FDC = new TTree(TreeName+(TString)"FDC","Analysis Tree FDC");
		//  tree_FDC->SetFile(fout_FDC);
		tree_FDC->AutoSave("SaveSelf");
		tree_FDC->SetAutoSave(1e5);
	}

	// HODO Tree
	TFile *fout_HODO = NULL;
	TTree *tree_HODO = NULL;
	if(kHODO){
		fout_HODO = new TFile(TmpRootFilenameBody + (TString)"_HODO.root","recreate");
		tree_HODO = new TTree(TreeName+(TString)"HODO","Analysis Tree HODO");
		//  tree_FDC->SetFile(fout_FDC);
		tree_HODO->AutoSave("SaveSelf");
		tree_HODO->SetAutoSave(1e5);
	}



	// Variables
	Long64_t EventNumber = 0;

	ULong64_t  TimeStamp=0 ;
	Int_t RunNumber = -1;
	Int_t CoincidenceTrigger;
	//unsigned int CoincidenceTrigger;



	// Plastics
	////////////////////////////////////////////////////////
	Double_t F3_LTRaw,F5_LTRaw,F7_LTRaw,SBT1_LTRaw,SBT2_LTRaw; //
	Double_t F3_RTRaw,F5_RTRaw,F7_RTRaw,SBT1_RTRaw,SBT2_RTRaw; //
	Double_t F3_LTSlew,F5_LTSlew,F7_LTSlew,SBT1_LTSlew,SBT2_LTSlew; //
	Double_t F3_RTSlew,F5_RTSlew,F7_RTSlew,SBT1_RTSlew,SBT2_RTSlew; //
	Double_t F3_LQRaw,F5_LQRaw,F7_LQRaw,SBT1_LQRaw,SBT2_LQRaw; //
	Double_t F3_RQRaw,F5_RQRaw,F7_RQRaw,SBT1_RQRaw,SBT2_RQRaw; //
	Double_t SBV_RQRaw,SBV_RTRaw,SBV_RTSlew;
	////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////
	Double_t F3_Charge,F3_Time;
	Double_t F7_Charge,F7_Time;
	Double_t F13_Charge,F13_Time;
	Double_t SBV_Charge,SBV_Time;
	Double_t SBT1_Charge,SBT1_Time;
	Double_t SBT2_Charge,SBT2_Time;
	////////////////////////////////////////////////////////


	Double_t F5X,F5Y,F5B,F5A;

	Double_t F7IC_E ;

	// DC Raw Data
	Int_t BDC1_nhits;
	vector<int> BDC1_layer_hits;
	vector<double> BDC1_TDC;// for each hits, no matter layer, wireid
	vector<double> BDC1_layerid;// for each hits, no matter layer, wireid
	vector<double> BDC1_wireid;// for each hits, no matter layer, wireid

	Int_t BDC2_nhits;
	vector<int> BDC2_layer_hits;
	vector<double> BDC2_TDC;// for each hits, no matter layer, wireid
	vector<double> BDC2_layerid;// for each hits, no matter layer, wireid
	vector<double> BDC2_wireid;// for each hits, no matter layer, wireid

	Int_t FDC0_nhits;
	vector<int> FDC0_layer_hits;
	vector<double> FDC0_TDC;// for each hits, no matter layer, wireid
	vector<double> FDC0_layerid;// for each hits, no matter layer, wireid
	vector<double> FDC0_wireid;// for each hits, no matter layer, wireid

	Int_t FDC2_nhits;
	vector<int> FDC2_layer_hits;
	vector<double> FDC2_TDC;// for each hits, no matter layer, wireid
	vector<double> FDC2_layerid;// for each hits, no matter layer, wireid
	vector<double> FDC2_wireid;// for each hits, no matter layer, wireid

	Int_t BDC1_nlayerx;
	Int_t BDC1_nlayery;
	vector<double> BDC1_Track_dl;
	vector<double> BDC1_Track_XY;
	vector<double> BDC1_Track_Z;
	vector<double> BDC1_Track_dXY;

	Int_t BDC2_nlayerx;
	Int_t BDC2_nlayery;
	vector<double> BDC2_Track_dl;
	vector<double> BDC2_Track_XY;
	vector<double> BDC2_Track_Z;
	vector<double> BDC2_Track_dXY;


	Int_t FDC0_nlayerx;
	Int_t FDC0_nlayery;
	vector<double> FDC0_Track_dl;
	vector<double> FDC0_Track_XY;
	vector<double> FDC0_Track_Z;
	vector<double> FDC0_Track_dXY;



	// Calibrated from Anaroot
	Double_t BDC1_X,BDC1_Y,BDC2_X,BDC2_Y,FDC0_X,FDC0_Y;
	Double_t BDC1_ThetaX,BDC1_ThetaY,BDC2_ThetaX,BDC2_ThetaY,FDC0_ThetaX,FDC0_ThetaY;
	Double_t FDC2_X,FDC2_Y,FDC2_ThetaX,FDC2_ThetaY;

	Double_t BDC1_Chi2x,BDC2_Chi2x,FDC0_Chi2x;
	Double_t BDC1_Chi2y,BDC2_Chi2y,FDC0_Chi2y;
	Double_t Target_X,Target_Y,Target_ThetaX,Target_ThetaY; // Value at the entrance
	Double_t SBV_X,SBV_Y,SBV_ThetaX,SBV_ThetaY; // Value at the entrance


	// SILICONS
	vector <Int_t>   *Silicons_ID = new vector <Int_t>();
	vector <Double_t> *Silicons_X = new vector <Double_t>();
	vector <Double_t> *Silicons_Y = new vector <Double_t>();
	vector <Double_t> *Silicons_Z = new vector <Double_t>();
	vector <Double_t> *Silicons_Time = new vector <Double_t>();
	vector <Double_t> *Silicons_Energy = new vector <Double_t>();
	Int_t Silicons_Multiplicity = 0;

	// raw ADC
	vector <double> SiLF_rawADC;
	vector <double> SiLB_rawADC;
	vector <double> SiRF_rawADC;
	vector <double> SiRB_rawADC;

	vector <double> SiLF_rawTDC;
	vector <double> SiLB_rawTDC;
	vector <double> SiRF_rawTDC;
	vector <double> SiRB_rawTDC;

	Double_t CsILL_rawADC;
	Double_t CsILRT_rawADC;
	Double_t CsILRB_rawADC;

	Double_t CsIRLT_rawADC;
	Double_t CsIRLB_rawADC;
	Double_t CsIRRT_rawADC;
	Double_t CsIRRB_rawADC;

	Double_t CsILL_rawTDC;
	Double_t CsILRT_rawTDC;
	Double_t CsILRB_rawTDC;

	Double_t CsIRLT_rawTDC;
	Double_t CsIRLB_rawTDC;
	Double_t CsIRRT_rawTDC;
	Double_t CsIRRB_rawTDC;



	Double_t AllHodo_Charge[NUMBER_OF_HODO],AllHodo_Charge_C[NUMBER_OF_HODO];
	Double_t AllHodo_Time[NUMBER_OF_HODO],AllHodo_Time_C[NUMBER_OF_HODO];
	////////////////////////////////////////////////////////////////////////////
	Double_t AllHodo_ChargeU[NUMBER_OF_HODO],AllHodo_ChargeD[NUMBER_OF_HODO];
	Double_t AllHodo_ChargeCalU[NUMBER_OF_HODO],AllHodo_ChargeCalD[NUMBER_OF_HODO];
	Double_t AllHodo_TimeSlwU[NUMBER_OF_HODO],AllHodo_TimeSlwD[NUMBER_OF_HODO];
	Double_t AllHodo_TimeRawU[NUMBER_OF_HODO],AllHodo_TimeRawD[NUMBER_OF_HODO];
	Int_t AllHodo_ID[NUMBER_OF_HODO];
	////////////////////////////////////////////////////////////////////////////
	//Double_t AllHodo_Z[NUMBER_OF_HODO];
	Int_t Hodo_ID; // ID of the hodoscope with the highest charge
	Int_t HOD_GlobalID; 
	Int_t HodoMultiplicity,HodoFMultiplicity,HodoGMultiplicity,HodoPMultiplicity,HodoSMultiplicity;
	Double_t Hodo_Charge,Hodo_Charge_C; // Highest charge 
	Double_t Hodo_ChargeP; // Highest charge for Hodo P  
	Double_t Hodo_ChargeF; // Highest charge for Hodo F
	Double_t Hodo_Time,Hodo_Time_C; // Time of the hodoscope with the highest charge
	Double_t Hodo_Z,Hodo_AoverZ;

	Bool_t NEBULA_VetoFired;
	Int_t NEBULA_Multiplicity;
	vector <Double_t> *NEBULA_X = new vector <Double_t>();
	vector <Double_t> *NEBULA_Y = new vector <Double_t>();
	vector <Double_t> *NEBULA_Z = new vector <Double_t>();
	vector <Double_t> *NEBULA_ChargeUp = new vector <Double_t>();
	vector <Double_t> *NEBULA_ChargeDown = new vector <Double_t>();
	vector <Double_t> *NEBULA_Charge = new vector <Double_t>();
	vector <Int_t> *NEBULA_ID = new vector <Int_t>();
	vector <Double_t> *NEBULA_Time = new vector <Double_t>();

	vector <Double_t> *Neutron_X = new vector <Double_t>();
	vector <Double_t> *Neutron_Y = new vector <Double_t>();
	vector <Double_t> *Neutron_Z = new vector <Double_t>();
	vector <Double_t> *Neutron_ChargeUp = new vector <Double_t>();
	vector <Double_t> *Neutron_ChargeDown = new vector <Double_t>();
	vector <Double_t> *Neutron_Charge = new vector <Double_t>();
	vector <Int_t> *Neutron_ID = new vector <Int_t>();
	vector <Double_t> *Neutron_Time = new vector <Double_t>();
	vector <Bool_t>   *Neutron_IsNEBULA = new vector <Bool_t>();
	Int_t Neutron_Multiplicity;

	// ESPRI  
	UShort_t	ESPRI_NaI_ID[14];
	UShort_t	ESPRI_NaI_Layer[14];
	Double_t	ESPRI_NaI_Energy[14];
	Double_t	ESPRI_NaI_EnergyL[14];
	Double_t	ESPRI_NaI_EnergyR[14];
	Double_t	ESPRI_NaI_Time[14];
	Double_t	ESPRI_NaI_TimeL[14];
	Double_t	ESPRI_NaI_TimeR[14];
	Int_t		ESPRI_NaI_Mult; 

	UShort_t	ESPRI_Plas_ID     [2];
	UShort_t	ESPRI_Plas_Layer  [2];
	Double_t	ESPRI_Plas_Energy [2];
	Double_t	ESPRI_Plas_EnergyU [2];
	Double_t	ESPRI_Plas_EnergyD [2];
	Double_t	ESPRI_Plas_Time [2];
	Double_t	ESPRI_Plas_TimeU [2];
	Double_t	ESPRI_Plas_TimeD [2];
	Int_t		ESPRI_Plas_Mult;

	Double_t	ESPRI_RDC_X[2];
	Double_t	ESPRI_RDC_A[2];
	Double_t	ESPRI_RDC_Y[2];
	Double_t	ESPRI_RDC_B[2];
	UShort_t	ESPRI_RDC_Side[2];
	Int_t		ESPRI_RDC_Hit;
	Int_t ESPRI_NaIMergeID[] = {1,1,2,2,3,3,4,4,5,5,6,6,7,7,
		8, 8, 9, 9,10,10,11,11,12,12,13,13,14,14};
	Int_t ESPRI_PlaMergeID[] = {1,1, 2, 2};


	if(kMAIN){
		tree_MAIN->Branch("RunNumber",&RunNumber);
		tree_MAIN->Branch("EventNumber",&EventNumber);
		//Triggers
		tree_MAIN->Branch("CoincidenceTrigger",&CoincidenceTrigger);
		tree_MAIN->Branch("TimeStamp",&TimeStamp);
	}

	//PLA
	if(kPLA)
	{
		tree_PLA->Branch("RunNumber",&RunNumber);
		tree_PLA->Branch("EventNumber",&EventNumber);

		tree_PLA->Branch("F3_LTRaw",&F3_LTRaw);
		tree_PLA->Branch("F3_RTRaw",&F3_RTRaw);
		tree_PLA->Branch("F3_LTSlew",&F3_LTSlew);
		tree_PLA->Branch("F3_RTSlew",&F3_RTSlew);
		tree_PLA->Branch("F3_LQRaw",&F3_LQRaw);
		tree_PLA->Branch("F3_RQRaw",&F3_RQRaw);

		tree_PLA->Branch("F7_LTRaw",&F7_LTRaw);
		tree_PLA->Branch("F7_RTRaw",&F7_RTRaw);
		tree_PLA->Branch("F7_LTSlew",&F7_LTSlew);
		tree_PLA->Branch("F7_RTSlew",&F7_RTSlew);
		tree_PLA->Branch("F7_LQRaw",&F7_LQRaw);
		tree_PLA->Branch("F7_RQRaw",&F7_RQRaw);

		tree_PLA->Branch("SBT1_LTRaw",&SBT1_LTRaw);
		tree_PLA->Branch("SBT1_RTRaw",&SBT1_RTRaw);
		tree_PLA->Branch("SBT1_LTSlew",&SBT1_LTSlew);
		tree_PLA->Branch("SBT1_RTSlew",&SBT1_RTSlew);
		tree_PLA->Branch("SBT1_LQRaw",&SBT1_LQRaw);
		tree_PLA->Branch("SBT1_RQRaw",&SBT1_RQRaw);


		tree_PLA->Branch("SBT2_LTRaw",&SBT2_LTRaw);
		tree_PLA->Branch("SBT2_RTRaw",&SBT2_RTRaw);
		tree_PLA->Branch("SBT2_LTSlew",&SBT2_LTSlew);
		tree_PLA->Branch("SBT2_RTSlew",&SBT2_RTSlew);
		tree_PLA->Branch("SBT2_LQRaw",&SBT2_LQRaw);
		tree_PLA->Branch("SBT2_RQRaw",&SBT2_RQRaw);


		tree_PLA->Branch("SBV_RQRaw",&SBV_RQRaw);
		tree_PLA->Branch("SBV_RTRaw",&SBV_RTRaw);
		tree_PLA->Branch("SBV_RTSlew",&SBV_RTSlew);


		tree_PLA->Branch("F3_Charge",&F3_Charge);
		tree_PLA->Branch("F3_Time",&F3_Time);

		tree_PLA->Branch("F7_Charge",&F7_Charge);
		tree_PLA->Branch("F7_Time",&F7_Time);
	
		tree_PLA->Branch("F13_Charge",&F13_Charge);
		tree_PLA->Branch("F13_Time",&F13_Time);

		tree_PLA->Branch("SBV_Charge",&SBV_Charge);
		tree_PLA->Branch("SBV_Time",&SBV_Time);

		tree_PLA->Branch("SBT1_Charge",&SBT1_Charge);
		tree_PLA->Branch("SBT1_Time",&SBT1_Time);

		tree_PLA->Branch("SBT2_Charge",&SBT2_Charge);
		tree_PLA->Branch("SBT2_Time",&SBT2_Time);
	

	}
	if(kBDC)
	{

		tree_BDC->Branch("RunNumber",&RunNumber);
		tree_BDC->Branch("EventNumber",&EventNumber);

		tree_BDC->Branch("BDC1_X",&BDC1_X);
		tree_BDC->Branch("BDC1_Y",&BDC1_Y);
		tree_BDC->Branch("BDC1_ThetaX",&BDC1_ThetaX);
		tree_BDC->Branch("BDC1_ThetaY",&BDC1_ThetaY);
		tree_BDC->Branch("BDC2_X",&BDC2_X);
		tree_BDC->Branch("BDC2_Y",&BDC2_Y);
		tree_BDC->Branch("BDC2_ThetaX",&BDC2_ThetaX);
		tree_BDC->Branch("BDC2_ThetaY",&BDC2_ThetaY);
		tree_BDC->Branch("Target_X",&Target_X);
		tree_BDC->Branch("Target_Y",&Target_Y);
		tree_BDC->Branch("Target_ThetaX",&Target_ThetaX);
		tree_BDC->Branch("Target_ThetaY",&Target_ThetaY);

	}

	//SAMURAI
	if(kFDC){
		tree_FDC->Branch("RunNumber",&RunNumber);
		tree_FDC->Branch("EventNumber",&EventNumber);

		tree_FDC->Branch("FDC0_X",&FDC0_X);
		tree_FDC->Branch("FDC0_Y",&FDC0_Y);
		tree_FDC->Branch("FDC0_ThetaX",&FDC0_ThetaX);
		tree_FDC->Branch("FDC0_ThetaY",&FDC0_ThetaY);
		tree_FDC->Branch("FDC2_X",&FDC2_X);
		tree_FDC->Branch("FDC2_Y",&FDC2_Y);
		tree_FDC->Branch("FDC2_ThetaX",&FDC2_ThetaX);
		tree_FDC->Branch("FDC2_ThetaY",&FDC2_ThetaY);
	}

	if(kHODO){
		tree_HODO->Branch("RunNumber",&RunNumber);
		tree_HODO->Branch("EventNumber",&EventNumber);
		for (Int_t i=0;i<NUMBER_OF_HODO;i++)
		{
			tree_HODO->Branch(Form("Hodo%d_Charge",i+1),&AllHodo_Charge[i],Form("Hodo%d_Charge/D",i+1));
			tree_HODO->Branch(Form("Hodo%d_Charge_C",i+1),&AllHodo_Charge_C[i],Form("Hodo%d_Charge_C/D",i+1));
			tree_HODO->Branch(Form("Hodo%d_ChargeU",i+1),&AllHodo_ChargeU[i],Form("Hodo%d_ChargeU/D",i+1));
			tree_HODO->Branch(Form("Hodo%d_ChargeD",i+1),&AllHodo_ChargeD[i],Form("Hodo%d_ChargeD/D",i+1));
			tree_HODO->Branch(Form("Hodo%d_Time",i+1),&AllHodo_Time[i],Form("Hodo%d_Time/D",i+1));
			tree_HODO->Branch(Form("Hodo%d_Time_C",i+1),&AllHodo_Time_C[i],Form("Hodo%d_Time_C/D",i+1));

			tree_HODO->Branch(Form("Hodo%d_ChargeCalU",i+1),&AllHodo_ChargeCalU[i],Form("Hodo%d_ChargeCalU/D",i+1));
			tree_HODO->Branch(Form("Hodo%d_ChargeCalD",i+1),&AllHodo_ChargeCalD[i],Form("Hodo%d_ChargeCalD/D",i+1));
			tree_HODO->Branch(Form("Hodo%d_TimeSlwU",i+1),&AllHodo_TimeSlwU[i],Form("Hodo%d_TimeSlwU/D",i+1));
			tree_HODO->Branch(Form("Hodo%d_TimeSlwD",i+1),&AllHodo_TimeSlwD[i],Form("Hodo%d_TimeSlwD/D",i+1));
			tree_HODO->Branch(Form("Hodo%d_TimeRawU",i+1),&AllHodo_TimeRawU[i],Form("Hodo%d_TimeRawU/D",i+1));
			tree_HODO->Branch(Form("Hodo%d_TimeRawD",i+1),&AllHodo_TimeRawD[i],Form("Hodo%d_TimeRawD/D",i+1));
			//  tree->Branch(Form("Hodo%d_Z",i+1),&AllHodo_Z[i]);
		}
		tree_HODO->Branch("Hodo_Multiplicity",&HodoMultiplicity);
		tree_HODO->Branch("HodoP_Multiplicity",&HodoPMultiplicity);
		tree_HODO->Branch("HodoF_Multiplicity",&HodoFMultiplicity);
		//    tree_HODO->Branch("HodoG_Multiplicity",&HodoFMultiplicity);
		//    tree_HODO->Branch("HodoS_Multiplicity",&HodoSMultiplicity);

		int NOHOD=NUMBER_OF_HODO;
		tree_HODO->Branch("NUMBER_OF_HODO",&NOHOD,"NUMBER_OF_HODO/I");
		tree_HODO->Branch("AllHodo_Charge",&AllHodo_Charge,"AllHodo_Charge[NUMBER_OF_HODO]/D");
		tree_HODO->Branch("AllHodo_Charge_C",&AllHodo_Charge_C,"AllHodo_Charge_C[NUMBER_OF_HODO]/D");
		tree_HODO->Branch("AllHodo_Time",&AllHodo_Time,"AllHodo_Time[NUMBER_OF_HODO]/D");
		tree_HODO->Branch("AllHodo_Time_C",&AllHodo_Time_C,"AllHodo_Time_C[NUMBER_OF_HODO]/D");
		tree_HODO->Branch("AllHodo_ID",&AllHodo_ID,"AllHodo_ID[NUMBER_OF_HODO]/I");
		tree_HODO->Branch("Hodo_ID",&Hodo_ID);
		tree_HODO->Branch("HOD_GlobalID",&HOD_GlobalID);
		tree_HODO->Branch("Hodo_Charge",&Hodo_Charge);  
		tree_HODO->Branch("Hodo_Charge_C",&Hodo_Charge_C);  
		tree_HODO->Branch("Hodo_ChargeP",&Hodo_ChargeP); 
		tree_HODO->Branch("Hodo_ChargeF",&Hodo_ChargeF);
		tree_HODO->Branch("Hodo_Time",&Hodo_Time);
		tree_HODO->Branch("Hodo_Time_C",&Hodo_Time_C);
		tree_HODO->Branch("Hodo_Z",&Hodo_Z);
		tree_HODO->Branch("Hodo_AoverZ",&Hodo_AoverZ);
	}

	//Neutrons
	if(kNEUT){
		tree_NEUT->Branch("RunNumber",&RunNumber);
		tree_NEUT->Branch("EventNumber",&EventNumber);
		tree_NEUT->Branch("Neutron_ID",&Neutron_ID);
		tree_NEUT->Branch("Neutron_X",&Neutron_X);
		tree_NEUT->Branch("Neutron_Y",&Neutron_Y);
		tree_NEUT->Branch("Neutron_Z",&Neutron_Z);
		tree_NEUT->Branch("Neutron_Time",&Neutron_Time);
		tree_NEUT->Branch("Neutron_ChargeUp",&Neutron_ChargeUp);
		tree_NEUT->Branch("Neutron_ChargeDown",&Neutron_ChargeDown);
		tree_NEUT->Branch("Neutron_Charge",&Neutron_Charge);
		tree_NEUT->Branch("Neutron_IsNEBULA",&Neutron_IsNEBULA);
		tree_NEUT->Branch("Neutron_Multiplicity",&Neutron_Multiplicity);

		//NEBULA
		tree_NEUT->Branch("NEBULA_Multiplicity",&NEBULA_Multiplicity);
		tree_NEUT->Branch("NEBULA_VetoFired",&NEBULA_VetoFired);
	}

	// SILICONS
	if(kSILI){
		tree_SILICONS->Branch("RunNumber",&RunNumber);
		tree_SILICONS->Branch("EventNumber",&EventNumber);

		tree_SILICONS->Branch("Silicons_ID",&Silicons_ID);
		tree_SILICONS->Branch("Silicons_X",&Silicons_X);
		tree_SILICONS->Branch("Silicons_Y",&Silicons_Y);
		tree_SILICONS->Branch("Silicons_Z",&Silicons_Z);
		tree_SILICONS->Branch("Silicons_Time",&Silicons_Time);
		tree_SILICONS->Branch("Silicons_Energy",&Silicons_Energy);
		tree_SILICONS->Branch("Silicons_Multiplicity",&Silicons_Multiplicity);

		tree_SILICONS->Branch("SiLF_rawADC",&SiLF_rawADC);
		tree_SILICONS->Branch("SiLB_rawADC",&SiLB_rawADC);
		tree_SILICONS->Branch("SiRF_rawADC",&SiRF_rawADC);
		tree_SILICONS->Branch("SiRB_rawADC",&SiRB_rawADC);

		tree_SILICONS->Branch("SiLF_rawTDC",&SiLF_rawTDC);
		tree_SILICONS->Branch("SiLB_rawTDC",&SiLB_rawTDC);
		tree_SILICONS->Branch("SiRF_rawTDC",&SiRF_rawTDC);
		tree_SILICONS->Branch("SiRB_rawTDC",&SiRB_rawTDC);

		tree_SILICONS->Branch("CsILL_rawADC",&CsILL_rawADC);
		tree_SILICONS->Branch("CsILRT_rawADC",&CsILRT_rawADC);
		tree_SILICONS->Branch("CsILRB_rawADC",&CsILRB_rawADC);

		tree_SILICONS->Branch("CsIRLT_rawADC",&CsIRLT_rawADC);
		tree_SILICONS->Branch("CsIRLB_rawADC",&CsIRLB_rawADC);
		tree_SILICONS->Branch("CsIRRT_rawADC",&CsIRRT_rawADC);
		tree_SILICONS->Branch("CsIRRB_rawADC",&CsIRRB_rawADC);

		tree_SILICONS->Branch("CsILL_rawTDC",&CsILL_rawTDC);
		tree_SILICONS->Branch("CsILRT_rawTDC",&CsILRT_rawTDC);
		tree_SILICONS->Branch("CsILRB_rawTDC",&CsILRB_rawTDC);

		tree_SILICONS->Branch("CsIRLT_rawTDC",&CsIRLT_rawTDC);
		tree_SILICONS->Branch("CsIRLB_rawTDC",&CsIRLB_rawTDC);
		tree_SILICONS->Branch("CsIRRT_rawTDC",&CsIRRT_rawTDC);
		tree_SILICONS->Branch("CsIRRB_rawTDC",&CsIRRB_rawTDC);


	}

	// ESPRI
	if(kESPRI){



		tree_ESPRI->Branch("RunNumber",&RunNumber);
		tree_ESPRI->Branch("EventNumber",&EventNumber);



		tree_ESPRI->Branch("ESPRI_NaI_ID", ESPRI_NaI_ID,"ESPRI_NaI_ID[14]/s");
		tree_ESPRI->Branch("ESPRI_NaI_Layer", ESPRI_NaI_Layer,  "ESPRI_NaI_Layer[14]/s");
		tree_ESPRI->Branch("ESPRI_NaI_Energy", ESPRI_NaI_Energy, "ESPRI_NaI_Energy[14]/D");
		tree_ESPRI->Branch("ESPRI_NaI_EnergyL", ESPRI_NaI_EnergyL,  "ESPRI_NaI_EnergyL[14]/D");
		tree_ESPRI->Branch("ESPRI_NaI_EnergyR", ESPRI_NaI_EnergyR, "ESPRI_NaI_EnergyR[14]/D");
		tree_ESPRI->Branch("ESPRI_NaI_Mult", &ESPRI_NaI_Mult,  "ESPRI_NaI_Mult/I"); 

		tree_ESPRI->Branch("ESPRI_Plas_ID", ESPRI_Plas_ID ,    "ESPRI_Plas_ID[2]/s");
		tree_ESPRI->Branch("ESPRI_Plas_Layer", ESPRI_Plas_Layer, "ESPRI_Plas_Layer[2]/s");
		tree_ESPRI->Branch("ESPRI_Plas_Energy", ESPRI_Plas_Energy, "ESPRI_Plas_Energy[2]/D");
		tree_ESPRI->Branch("ESPRI_Plas_EnergyU", ESPRI_Plas_EnergyU, "ESPRI_Plas_EnergyU[2]/D");
		tree_ESPRI->Branch("ESPRI_Plas_EnergyD", ESPRI_Plas_EnergyD, "ESPRI_Plas_EnergyD[2]/D");
		tree_ESPRI->Branch("ESPRI_Plas_Time", ESPRI_Plas_Time, "ESPRI_Plas_Time[2]/D");
		tree_ESPRI->Branch("ESPRI_Plas_TimeU", ESPRI_Plas_TimeU, "ESPRI_Plas_TimeU[2]/D");
		tree_ESPRI->Branch("ESPRI_Plas_TimeD", ESPRI_Plas_TimeD,"ESPRI_Plas_TimeD[2]/D");
		tree_ESPRI->Branch("ESPRI_Plas_Mult", &ESPRI_Plas_Mult,"ESPRI_Plas_Mult/I");

		tree_ESPRI->Branch("ESPRI_RDC_X", &ESPRI_RDC_X, "ESPRI_RDC_X[2]/D");
		tree_ESPRI->Branch("ESPRI_RDC_A", &ESPRI_RDC_A, "ESPRI_RDC_A[2]/D");
		tree_ESPRI->Branch("ESPRI_RDC_Y", &ESPRI_RDC_Y, "ESPRI_RDC_Y[2]/D");
		tree_ESPRI->Branch("ESPRI_RDC_B", &ESPRI_RDC_B , "ESPRI_RDC_B[2]/D");



	}

	// End of header

	// Aliases
	if(kMAIN){
		//    tree_MAIN->SetAlias("Trig_DSB","CoincidenceTrigger & 1");
		//    tree_MAIN->SetAlias("Trig_BxNEB","CoincidenceTrigger & 2");
		//    tree_MAIN->SetAlias("Trig_BxNEU","CoincidenceTrigger & 4");
		//    tree_MAIN->SetAlias("Trig_BxD","CoincidenceTrigger & 8");
		//    tree_MAIN->SetAlias("Trig_BxNEB_gamma","CoincidenceTrigger & 8");
		//    tree_MAIN->SetAlias("Trig_BxNEU_gamma","CoincidenceTrigger & 16");
		tree_MAIN->SetAlias("Trig_DSB","(CoincidenceTrigger & 1)");
		tree_MAIN->SetAlias("Trig_BxESPRIxTEL","CoincidenceTrigger & 2");
		tree_MAIN->SetAlias("Trig_BxESPRI","CoincidenceTrigger & 4");
		tree_MAIN->SetAlias("Trig_BxTEL","CoincidenceTrigger & 8");
		tree_MAIN->SetAlias("Trig_BxHODP","CoincidenceTrigger & 16");
		tree_MAIN->SetAlias("Trig_BxHODF","CoincidenceTrigger & 32");
		tree_MAIN->SetAlias("Trig_BxNEBULA","CoincidenceTrigger & 64");
	}
	if(kNEUT){
		tree_NEUT->SetAlias("Neutron_VetoFired","NEBULA_VetoFired");
		tree_NEUT->SetAlias("Neutron_NoVeto","!Neutron_VetoFired");
	}
	Double_t hod_toff[40] = {
		2.82+14.13,2.82+0.35,2.82+0.32,2.82+5.38,2.82+0.34,2.82+0.07,2.82,2.82+2.86, /* HODOF1-8*/
		2.82-1.89,2.82-2.18,2.82-2.37,2.82,2.82,2.82,2.82,2.82, /* HODOF9-16*/
		2.82,2.82,2.82,2.82,2.82,2.82,2.82,2.82, /* HODOF17-24*/
		20.68+20.1,20.68+17.4,20.68,20.68,20.68,20.68,20.68,20.68, /* HODOP1-8, starting from Hodo_ID 40*/ 
		20.68,20.68,20.68,20.68,20.68,20.68,20.68,20.68 /* HODOP9-16*/
	};
	Double_t hod_qoff[40]={
		0., 0., 0., 0., 0., 0., -6.07,-6.07, -6.07, -6.07, -6.07, -6.07, //IDF 1-12
		0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0., //IDF 13-24
		// 0.1632,-0.4438,-0.2803,-0.5241,-0.6953,-0.414,-0.43,-0.411,-0.3783,-0.4032,-0.2906,-0.2919,-1.8411,-0.9907//HODP 1-14
		0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0,0.,0 //HODP 1-14
	};

	Double_t hod_qcor[40] = {
		1.0,1.0,1.0,1.0,1.0,1.0, //IDF 1-6
		1.0957612074,1.0975191131,1.0659660959,1.084603677,1.1038475076,1.0894148757,//IDF 7-12
		1.0682354856,1.007615894,1,1.0869146889 ,1.0254048696,1.0, //IDF 13-18
		1.0,1.0,1.0,1.0,1.0,1.0,//IDF 19-24
		// 0.4557,0.5326,0.5255,0.5759,0.6226,0.5914,0.6113,0.6702,0.6376,0.6872,0.6363,0.6634,0.6992,0.6642//HODP 1-14
		1.0,1.0,
		// 1.0,1.0,1.0,1.14,1.0,1.0,1.026,1.08,1.0,1.088,1.0,1.03,1.0,1.0 //HODP 1-14
		1.0,1.0,1.0,1.0,1.0,0.955,0.971,1.08,1.0,1.088,1.0,1.03,1.0,1.0 //HODP 1-14
	};
	double p0HodoZ[24]={ -4.854, -4.854, -4.854, -4.854, 0.3112,  -1.7648,
		-2.8982,-3.292-0.42, -4.854, -4.322, -4.797, -3.736,
		-3.552, -2.456, -2.276, -5.091, -2.712-1, -2.138-1,
		-0.765-1, -1.188-1, -1.144-1, -0.8499-1, -0.8535-1, -1.8535};

	double p1HodoZ[24]={	4.263, 4.263, 4.263, 4.263, 3.834, 3.6973,3.880,
		4.025, 4.263, 4.176, 4.284, 4.108, 4.091, 3.903, 3.884, 
		4.262, 4.048, 3.993, 3.715, 3.747, 3.743,
		3.665, 3.612, 3.612};




	////////////////////////////////MAIN loop/////////////
	//MaxEventNumber=10000;
	while(EventStore->GetNextEvent() 
			&& EventNumber < MaxEventNumber
	     )
	{

		if(MaxEventNumber<1000) cout<<"EventNumber="<<EventNumber<<endl;
		EventNumber++;
		if (EventNumber%DISPLAY_EVERY_EVENT == 0){
			double duration =  int(10*((std::clock()-start)/ (double) CLOCKS_PER_SEC))/10. ;
			Double_t rate = DISPLAY_EVERY_EVENT/((std::clock()-clock0)/ (double) CLOCKS_PER_SEC) ;
			Int_t color = rate<100?33:31 ;//int(TMath::Log(rate)/TMath::Ln10())+31;
			std::clog << "\e[1;" << color << "m  ANALYSIS-Info : " << EventNumber/1000 << "k events treated in " 
				<< duration << "s. Instantaneous rate = " 
				<< rate << "evt/s\e[0m             \r";
			clock0 = std::clock();
		}


		CalibIC->ClearData();
		CalibCoin->ClearData();
		CalibNEBULA->ClearData();


		CalibFDC2Hit->ClearData();
		CalibFDC2Track->ClearData();


		CalibHODPla->ClearData();
		CalibESPRI_NaI->ClearData();
		CalibESPRI_tdc->ClearData();
		CalibESPRI_rdc->ClearData();
		CalibESPRI_fadc->ClearData();
		CalibESPRI_plas->ClearData();


		CalibFocalPlane->ClearData();

		// Reconstruct 
		CalibPlastic->ClearData();

		CalibBDC1Hit->ClearData();

		CalibBDC1Track->ClearData();
		CalibBDC2Hit->ClearData();

		CalibBDC2Track->ClearData();

		CalibFDC0Hit->ClearData();

		CalibFDC0Track->ClearData();

		CalibSILICONS->ClearData();

		TArtRawEventObject *fEvent = (TArtRawEventObject *)sman->FindDataContainer("RawEvent");

		for(Int_t i=0;i<fEvent->GetNumSeg();i++){
			TArtRawSegmentObject    *seg      = fEvent->GetSegment(i);
			Int_t                    device   = seg->GetDevice();
			Int_t                    detector = seg->GetDetector();
			Int_t                    module   = seg->GetModule();

			//cout<<" device "<<device<<" samurai "<<SAMURAI<<" bigrips "<<BIGRIPS<<endl;
			//cout<<" detector "<<detector<<" coin "<<COIN<<endl;
			if(device == SAMURAI){
				switch(detector) {
					//kw: plastic appears twice, under device SAMURAI 2 and BigRIPS 0, Samurai comes first, so if we read this in BigRIPS we actually overwrite
					case    PLAT: if(kPLA) CalibPlastic->LoadData(seg); break;
					case STOPPLA: if(kPLA) CalibPlastic->LoadData(seg); break;
							      //          case      RF: if(kBEAM) CalibPlastic->LoadData(seg); break; //??
					case    PLAQ: if(kPLA) CalibPlastic->LoadData(seg); break;
					case     COIN: CalibCoin->LoadData(seg); break; // included to see coin. trigger
					case       BDC: if(kBDC) CalibBDC1Hit->LoadData(seg); break;
								// case      FDC1: if(kFDCs||kFDCs_full) CalibFDC1Hit->LoadData(seg); break;
					case      FDC0: if(kFDC) CalibFDC0Hit->LoadData(seg); break;
					case      FDC2: if(kFDC) CalibFDC2Hit->LoadData(seg); break;
					case     HODFQ: if(kHODO)  CalibHODPla->LoadData(seg);  break;
					case     HODPQ: if(kHODO)  CalibHODPla->LoadData(seg);  break;
								//        case    HODPQ2: if(kHODO) CalibHODPla->LoadData(seg); break;
					case     HODFT: if(kHODO)  CalibHODPla->LoadData(seg);  break;
					case     HODPT: if(kHODO)  CalibHODPla->LoadData(seg);  break;
					case  NEBULA1Q: if(kNEUT)  CalibNEBULA->LoadData(seg); break;
					case  NEBULA1T: if(kNEUT)  CalibNEBULA->LoadData(seg); break;
					case  NEBULA2Q: if(kNEUT)  CalibNEBULA->LoadData(seg); break;
					case  NEBULA2T: if(kNEUT)  CalibNEBULA->LoadData(seg); break;
					case  NEBULA3Q: if(kNEUT)  CalibNEBULA->LoadData(seg); break;
					case  NEBULA3T: if(kNEUT)  CalibNEBULA->LoadData(seg); break;
					case  NEBULA4Q: if(kNEUT)  CalibNEBULA->LoadData(seg); break;
					case  NEBULA4T: if(kNEUT)  CalibNEBULA->LoadData(seg); break;
					case       TEL: if(kSILI) CalibSILICONS->LoadData(seg); break;
					default:  break;
				}
			} else if(device== BIGRIPS){
				switch(detector) {

					//case     COIN: CalibCoin->LoadData(seg); break;       // included to see coin. trigger
					//case   PPACT: if(kBEAM) CalibPPAC->LoadData(seg); break;
					//case   PPACQ: if(kBEAM) CalibPPAC->LoadData(seg); break;
					default:  break;
				}
			} else {
				switch(detector) {
					case     COIN: CalibCoin->LoadData(seg); break;
					default:  break;
				}
			}

		}



		// Coincidence reg

		//CalibCoin->LoadData();
		TClonesArray *EventInfo = (TClonesArray*)sman->FindDataContainer("EventInfo");

		CoincidenceTrigger = 0;
		RunNumber = (Int_t)NAN;
		if(EventInfo){
			CoincidenceTrigger = ((TArtEventInfo *)EventInfo->At(0))->GetTriggerBit();
			//cout<<((TArtEventInfo *)EventInfo->At(0))->GetTriggerBit()<<endl;;

			//         for (int id=1; id<=16; id++){
			//	   //cout<<id<<" "<<CalibCoin->IsChTrue(id)<<endl;
			//            if(CalibCoin->IsChTrue(id)){
			//	      CoincidenceTrigger  = id;
			//            }
			//         }

			//cout<<CoincidenceTrigger<<endl;
			RunNumber = ((TArtEventInfo *)EventInfo->At(0))->GetRunNumber() ;
			TimeStamp = (ULong64_t)((TArtEventInfo *)EventInfo->At(0))->GetTimeStamp() ;

		}

		if(kMAIN) {
			tree_MAIN->Fill();
		}

		//Beam
		if(kPLA){
			//plastics
			CalibPlastic->ReconstructData();

			TArtPlastic *PlasticF3 = CalibPlastic->FindPlastic((char*)"F3pl");
			TArtPlastic *PlasticF5 = CalibPlastic->FindPlastic((char*)"F5pl");
			TArtPlastic *PlasticF7 = CalibPlastic->FindPlastic((char*)"F7pl");
			TArtPlastic *PlasticSBT1 = CalibPlastic->FindPlastic((char*)"F13pl-1");
			TArtPlastic *PlasticSBT2 = CalibPlastic->FindPlastic((char*)"F13pl-2");
			TArtPlastic *PlasticSBV = CalibPlastic->FindPlastic((char*)"SBV");
			TArtPlastic *PlasticSBV2 = CalibPlastic->FindPlastic((char*)"SBV2");


			F3_LTRaw = NAN;
			F3_RTRaw = NAN;
			F3_LTSlew = NAN;
			F3_RTSlew = NAN;
			F3_LQRaw = NAN;
			F3_RQRaw = NAN;

			F5_LTRaw = NAN;
			F5_RTRaw = NAN;
			F5_LTSlew = NAN;
			F5_RTSlew = NAN;
			F5_LQRaw = NAN;
			F5_RQRaw = NAN;



			F7_LTRaw = NAN;
			F7_RTRaw = NAN;
			F7_LTSlew = NAN;
			F7_RTSlew = NAN;
			F7_LQRaw = NAN;
			F7_RQRaw = NAN;


			SBT1_LTRaw = NAN;
			SBT1_RTRaw = NAN;
			SBT1_LTSlew = NAN;
			SBT1_RTSlew = NAN;
			SBT1_LQRaw = NAN;
			SBT1_RQRaw = NAN;

			SBT2_LTRaw = NAN;
			SBT2_RTRaw = NAN;
			SBT2_LTSlew = NAN;
			SBT2_RTSlew = NAN;
			SBT2_LQRaw = NAN;
			SBT2_RQRaw = NAN;


			SBV_RQRaw=NAN;
			SBV_RTRaw=NAN;
			SBV_RTSlew=NAN;




			F3_Charge=NAN;
			F3_Time=NAN;
			F7_Charge=NAN;
			F7_Time=NAN;
			F13_Charge=NAN;
			F13_Time=NAN;
			SBV_Charge=NAN;
			SBV_Time=NAN;
			SBT1_Charge=NAN;
			SBT1_Time=NAN;
			SBT2_Charge=NAN;
			SBT2_Time=NAN;









			//cout << "time: " << PlasticF7->GetTLRaw() << "\t" << PlasticF7->GetTRRaw() << ", charge: " << PlasticF7->GetQLRaw() << "\t" << PlasticF7->GetQRRaw() << endl;
			if(PlasticF3->GetTLRaw()>40000)
			{

				cout << "F3 Left Time Raw= " << PlasticF3->GetTLRaw() << " F3 Right Time Raw= "  <<  PlasticF3->GetTRRaw() << endl;
				cout << "F7 Left Time Raw= " << PlasticF7->GetTLRaw() << " F7 Right Time Raw= "  <<  PlasticF7->GetTRRaw() << endl;
				cout << "SBT1 Left Time Raw= " << PlasticSBT1->GetTLRaw() << " SBT1 Right Time Raw= "  <<  PlasticSBT1->GetTRRaw() << endl;
				cout << "SBT2 Left Time Raw= " << PlasticSBT2->GetTLRaw() << " SBT2 Right Time Raw= "  <<  PlasticSBT2->GetTRRaw() << endl;
				cout << "SBV Left Time Raw= " << PlasticSBV->GetTLRaw() << " SBV Right Time Raw= "  <<  PlasticSBV->GetTRRaw() << endl;
			}

			if(PlasticF3){
				F3_LTRaw = PlasticF3->GetTLRaw();
				F3_RTRaw = PlasticF3->GetTRRaw();
				F3_LQRaw = PlasticF3->GetQLRaw();
				F3_RQRaw = PlasticF3->GetQRRaw();

				F3_LTSlew= PlasticF3->GetTimeLSlew();
				F3_RTSlew= PlasticF3->GetTimeRSlew();
				//cout<<"Cal*F3_LTRaw="<<0.0156251*F3_LTRaw<<"  F3_LTSlew="<<F3_LTSlew<<endl;
				F3_Time=(F3_LTSlew+F3_RTSlew)/2;
				F3_Charge=sqrt(F3_LQRaw+F3_RQRaw);


			}


			if(PlasticF7){

				F7_LTRaw = PlasticF7->GetTLRaw();
				F7_RTRaw = PlasticF7->GetTRRaw();
				F7_LQRaw = PlasticF7->GetQLRaw();
				F7_RQRaw = PlasticF7->GetQRRaw();

				F7_LTSlew= PlasticF7->GetTimeLSlew();
				F7_RTSlew= PlasticF7->GetTimeRSlew();
				F7_Time=(F7_LTSlew+F7_RTSlew)/2;
				F7_Charge=sqrt(F7_LQRaw+F7_RQRaw);


			}

			if(PlasticSBT1){

				SBT1_LTRaw = PlasticSBT1->GetTLRaw();
				SBT1_RTRaw = PlasticSBT1->GetTRRaw();
				SBT1_LQRaw = PlasticSBT1->GetQLRaw();
				SBT1_RQRaw = PlasticSBT1->GetQRRaw();

				SBT1_LTSlew = PlasticSBT1->GetTimeLSlew();
				SBT1_RTSlew = PlasticSBT1->GetTimeRSlew();
				SBT1_Time=(SBT1_LTSlew+SBT1_RTSlew)/2;
				SBT1_Charge=sqrt(SBT1_LQRaw+SBT1_RQRaw);



			}
			if(PlasticSBT2){

				SBT2_LTRaw = PlasticSBT2->GetTLRaw();
				SBT2_RTRaw = PlasticSBT2->GetTRRaw();
				SBT2_LQRaw = PlasticSBT2->GetQLRaw();
				SBT2_RQRaw = PlasticSBT2->GetQRRaw();

				SBT2_LTSlew = PlasticSBT2->GetTimeLSlew();
				SBT2_RTSlew = PlasticSBT2->GetTimeRSlew();
				SBT2_Time=(SBT2_LTSlew+SBT2_RTSlew)/2;
				SBT2_Charge=sqrt(SBT2_LQRaw+SBT2_RQRaw);



			}


                        F13_Time=(SBT1_Time+SBT2_Time)/2;
			F13_Charge=(SBT1_Charge+SBT2_Charge)/2;

			if(PlasticSBV){
				SBV_RQRaw = PlasticSBV->GetQRRaw();
				SBV_RTRaw = PlasticSBV->GetTRRaw();

				SBV_RTSlew= PlasticSBV->GetTimeRSlew();
				SBV_Time=SBT2_RTSlew;
				SBV_Charge=SBT2_RQRaw;

			}

			tree_PLA->Fill();
		}

		if(kBDC ){

			CalibBDC1Hit->ReconstructData();
			CalibBDC1Track->ReconstructData();
			CalibBDC2Hit->ReconstructData();
			CalibBDC2Track->ReconstructData();

			// Track check
			TClonesArray *BDC1Hit = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Hit");
			TClonesArray *BDC2Hit = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Hit");
			TClonesArray *BDC1Track= (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Track");
			TClonesArray *BDC2Track= (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Track");
			//BDC1
			// Initialize Array
			BDC1_nhits=0;
			BDC1_layer_hits.clear();
			BDC1_layer_hits.resize(8,0);

			BDC1_TDC.clear();
			BDC1_layerid.clear();
			BDC1_wireid.clear();


			if(BDC1Hit){

				BDC1_nhits=BDC1Hit->GetEntries();

				//cout<<BDC1_nhits<<endl;
				//cout<<"Here"<<endl;
				for(int i=0;i<BDC1_nhits;i++){
					TArtDCHit *hit = (TArtDCHit *)BDC1Hit->At(i);
					int layer = hit->GetLayer();
					int wireid = hit->GetWireID();
					int val = hit->GetTDC();
					//cout<<layer<<endl;
					if(!(layer<0)) BDC1_layer_hits[layer]++;
					else continue;
					//cout<<BDC1_layer_hits[layer]<<endl;
					BDC1_TDC.push_back(val);
					BDC1_layerid.push_back(layer);
					BDC1_wireid.push_back(wireid);


				}
			}



			BDC1_X = NAN;
			BDC1_Y = NAN;
			BDC1_ThetaX = NAN;
			BDC1_ThetaY = NAN;
			BDC1_nlayerx=0;
			BDC1_nlayery=0;
			BDC1_Track_dl.clear();
			BDC1_Track_dl.resize(8,-9999);
			BDC1_Track_XY.clear();
			BDC1_Track_XY.resize(8,-9999);
			BDC1_Track_Z.clear();
			BDC1_Track_Z.resize(8,-9999);
			BDC1_Track_dXY.clear();
			BDC1_Track_dXY.resize(8,-9999);
			if (BDC1Track)
			{
				Int_t BDC1NumberOfTracks = BDC1Track->GetEntries();
				Double_t TempXPosition, TempYPosition,Temp_ThetaX,Temp_ThetaY,MinChi2x = 100, MinChi2y = 100,TempChi2,TempNDF; 

				if (BDC1NumberOfTracks > 0)
				{
					TArtDCTrack *TrackBDC1;

					for(Int_t i=0; i<BDC1NumberOfTracks; i++)
					{
						TrackBDC1 = (TArtDCTrack *)BDC1Track->At(i);

						if(TrackBDC1)
						{

							TempXPosition = TrackBDC1->GetPosition(0);
							Temp_ThetaX = TMath::ATan(TrackBDC1->GetAngle(0));
							TempYPosition = TrackBDC1->GetPosition(1);
							Temp_ThetaY = TMath::ATan(TrackBDC1->GetAngle(1));
							TempChi2 = TrackBDC1->GetChi2();
							TempNDF = TrackBDC1->GetNDF();

							if(TempChi2 > 0 ){

								if(TMath::Abs(TempXPosition) < 50 && TempChi2<MinChi2x){
									MinChi2x = TempChi2;
									BDC1_X = TempXPosition;
									BDC1_ThetaX = TMath::ATan(TrackBDC1->GetAngle(0));
									BDC1_Chi2x=MinChi2x;

									BDC1_nlayerx=TrackBDC1->GetNumHitLayer();
									for(int st=0;st<BDC1_nlayerx;st++)
									{
										Int_t planeid=TrackBDC1->GetHitPlaneID(st)-21;
										BDC1_Track_dl[planeid]=TrackBDC1->GetDriftLength(st);
										BDC1_Track_XY[planeid]=TrackBDC1->GetHitXPosition(st);
										BDC1_Track_Z[planeid]=TrackBDC1->GetHitZPosition(st);
										BDC1_Track_dXY[planeid]=TrackBDC1->GetAngle(0)*BDC1_Track_Z[planeid]+TrackBDC1->GetPosition(0)-BDC1_Track_XY[planeid];
										//if(EventByEvent==1) cout<<"    hitlayer="<<planeid<<" drift length="<<BDC1_Track_dl[planeid]<<" xpos="<<BDC1_Track_XY[planeid]<<" zpos="<<BDC1_Track_Z[planeid]<<" dx="<<BDC1_Track_dXY[planeid]<<endl;

									}


								}

								if (TMath::Abs(TempYPosition) < 50 && TempChi2<MinChi2y){
									BDC1_Y = TempYPosition;
									BDC1_ThetaY = TMath::ATan(TrackBDC1->GetAngle(1));
									MinChi2y = TempChi2;
									BDC1_Chi2y=MinChi2y;

									BDC1_nlayery=TrackBDC1->GetNumHitLayer();
									for(int st=0;st<BDC1_nlayery;st++)
									{
										Int_t planeid=TrackBDC1->GetHitPlaneID(st)-21;
										BDC1_Track_dl[planeid]=TrackBDC1->GetDriftLength(st);
										BDC1_Track_XY[planeid]=TrackBDC1->GetHitXPosition(st);
										BDC1_Track_Z[planeid]=TrackBDC1->GetHitZPosition(st);
										BDC1_Track_dXY[planeid]=TrackBDC1->GetAngle(1)*BDC1_Track_Z[planeid]+TrackBDC1->GetPosition(1)-BDC1_Track_XY[planeid];
										if(EventByEvent==1) cout<<"    hitlayer="<<planeid<<" drift length="<<BDC1_Track_dl[planeid]<<" xpos="<<BDC1_Track_XY[planeid]<<" zpos="<<BDC1_Track_Z[planeid]<<" dx="<<BDC1_Track_dXY[planeid]<<endl;

									}


								}
							}
						}
					}
				}
			}


			//BDC2
			// Initialize Array
			BDC2_nhits=0;
			BDC2_layer_hits.clear();
			BDC2_layer_hits.resize(8,0);
			BDC2_TDC.clear();
			BDC2_layerid.clear();
			BDC2_wireid.clear();

			if(BDC2Hit){

				BDC2_nhits=BDC2Hit->GetEntries();
				for(int i=0;i<BDC2_nhits;i++){
					TArtDCHit *hit = (TArtDCHit *)BDC2Hit->At(i);
					int layer = hit->GetLayer();
					int wireid = hit->GetWireID();
					int val = hit->GetTDC();
					BDC2_layer_hits[layer]++;
					//cout<<BDC2_layer_hits[layer]<<endl;
					BDC2_TDC.push_back(val);
					BDC2_layerid.push_back(layer);
					BDC2_wireid.push_back(wireid);


				}
			}

			BDC2_X = NAN;
			BDC2_Y = NAN;
			BDC2_ThetaX = NAN;
			BDC2_ThetaY = NAN;
			BDC2_nlayerx=0;
			BDC2_nlayery=0;
			BDC2_Track_dl.clear();
			BDC2_Track_dl.resize(8,-9999);
			BDC2_Track_XY.clear();
			BDC2_Track_XY.resize(8,-9999);
			BDC2_Track_Z.clear();
			BDC2_Track_Z.resize(8,-9999);
			BDC2_Track_dXY.clear();
			BDC2_Track_dXY.resize(8,-9999);
			if (BDC2Track)
			{
				Int_t BDC2NumberOfTracks = BDC2Track->GetEntries();
				Double_t TempXPosition, TempYPosition,Temp_ThetaX,Temp_ThetaY,MinChi2x = 100, MinChi2y = 100,TempChi2,TempNDF; 

				if (BDC2NumberOfTracks > 0)
				{
					TArtDCTrack *TrackBDC2;

					for(Int_t i=0; i<BDC2NumberOfTracks; i++)
					{
						TrackBDC2 = (TArtDCTrack *)BDC2Track->At(i);

						if(TrackBDC2)
						{

							TempXPosition = TrackBDC2->GetPosition(0);
							Temp_ThetaX = TMath::ATan(TrackBDC2->GetAngle(0));
							TempYPosition = TrackBDC2->GetPosition(1);
							Temp_ThetaY = TMath::ATan(TrackBDC2->GetAngle(1));
							TempChi2 = TrackBDC2->GetChi2();
							TempNDF = TrackBDC2->GetNDF();

							if(TempChi2 > 0 ){

								if(TMath::Abs(TempXPosition) < 50 && TempChi2<MinChi2x){
									MinChi2x = TempChi2;
									BDC2_X = TempXPosition;
									BDC2_ThetaX = TMath::ATan(TrackBDC2->GetAngle(0));
									BDC2_Chi2x=MinChi2x;

									BDC2_nlayerx=TrackBDC2->GetNumHitLayer();
									for(int st=0;st<BDC2_nlayerx;st++)
									{
										Int_t planeid=TrackBDC2->GetHitPlaneID(st)-31;
										BDC2_Track_dl[planeid]=TrackBDC2->GetDriftLength(st);
										BDC2_Track_XY[planeid]=TrackBDC2->GetHitXPosition(st);
										BDC2_Track_Z[planeid]=TrackBDC2->GetHitZPosition(st);
										BDC2_Track_dXY[planeid]=TrackBDC2->GetAngle(0)*BDC2_Track_Z[planeid]+TrackBDC2->GetPosition(0)-BDC2_Track_XY[planeid];
										if(EventByEvent==true) cout<<"    hitlayer="<<planeid<<" drift length="<<BDC2_Track_dl[planeid]<<" xpos="<<BDC2_Track_XY[planeid]<<" zpos="<<BDC2_Track_Z[planeid]<<" dx="<<BDC2_Track_dXY[planeid]<<endl;

									}


								}

								if (TMath::Abs(TempYPosition) < 50 && TempChi2<MinChi2y){
									BDC2_Y = TempYPosition;
									BDC2_ThetaY = TMath::ATan(TrackBDC2->GetAngle(1));
									MinChi2y = TempChi2;
									BDC2_Chi2y=MinChi2y;

									BDC2_nlayery=TrackBDC2->GetNumHitLayer();
									for(int st=0;st<BDC2_nlayery;st++)
									{
										Int_t planeid=TrackBDC2->GetHitPlaneID(st)-31;
										BDC2_Track_dl[planeid]=TrackBDC2->GetDriftLength(st);
										BDC2_Track_XY[planeid]=TrackBDC2->GetHitXPosition(st);
										BDC2_Track_Z[planeid]=TrackBDC2->GetHitZPosition(st);
										BDC2_Track_dXY[planeid]=TrackBDC2->GetAngle(1)*BDC2_Track_Z[planeid]+TrackBDC2->GetPosition(1)-BDC2_Track_XY[planeid];
										if(EventByEvent==true) cout<<"    hitlayer="<<planeid<<" drift length="<<BDC2_Track_dl[planeid]<<" xpos="<<BDC2_Track_XY[planeid]<<" zpos="<<BDC2_Track_Z[planeid]<<" dx="<<BDC2_Track_dXY[planeid]<<endl;

									}


								}
							}
						}
					}
				}
			}


			//TARGET
			Target_X = NAN;
			Target_Y = NAN;
			Target_ThetaX = NAN;
			Target_ThetaY = NAN;


			Target_X = BDC1_X + Dist_BDC1Target / Dist_BDC1BDC2 * (BDC2_X - BDC1_X);
			Target_Y = BDC1_Y + Dist_BDC1Target / Dist_BDC1BDC2 * (BDC2_Y - BDC1_Y);
			Target_ThetaX = TMath::ATan( (BDC2_X - BDC1_X) / Dist_BDC1BDC2 );
			Target_ThetaY = TMath::ATan( (BDC2_Y - BDC1_Y) / Dist_BDC1BDC2 );
			//cout<<"Dist_BDC1Target="<<Dist_BDC1Target<<endl;
			//cout<<"Dist_BDC1BDC2="<<Dist_BDC1BDC2 <<endl;
			//cout<<Target_X<<" "<<Target_Y<<endl;

			//SBV
			SBV_X = NAN;
			SBV_Y = NAN;
			SBV_ThetaX = NAN;
			SBV_ThetaY = NAN;


			SBV_X = BDC1_X + Dist_BDC1SBV / Dist_BDC1BDC2 * (BDC2_X - BDC1_X);
			SBV_Y = BDC1_Y + Dist_BDC1SBV / Dist_BDC1BDC2 * (BDC2_Y - BDC1_Y);
			SBV_ThetaX = TMath::ATan( (BDC2_X - BDC1_X) / Dist_BDC1BDC2 );
			SBV_ThetaY = TMath::ATan( (BDC2_Y - BDC1_Y) / Dist_BDC1BDC2 );




			tree_BDC ->Fill();

		} // END BDC ANALYSIS


		if(kFDC){

			CalibFDC0Hit->ReconstructData();
			CalibFDC0Track->ReconstructData();


			// ============== FDC0 ================
			TClonesArray *FDC0Hit = (TClonesArray *)sman->FindDataContainer("SAMURAIFDC0Hit");
			TClonesArray *FDC0Track= (TClonesArray *)sman->FindDataContainer("SAMURAIFDC0Track");


			//FDC0
			// Initialize Array
			FDC0_nhits=0;
			FDC0_layer_hits.clear();
			FDC0_layer_hits.resize(8,0);
			FDC0_TDC.clear();
			FDC0_layerid.clear();
			FDC0_wireid.clear();

			if(FDC0Hit){

				FDC0_nhits=FDC0Hit->GetEntries();
				for(int i=0;i<FDC0Hit->GetEntries();i++){
					TArtDCHit *hit = (TArtDCHit *)FDC0Hit->At(i);
					int layer = hit->GetLayer();
					int wireid = hit->GetWireID();
					int val = hit->GetTDC();
					FDC0_layer_hits[layer]++;
					//cout<<FDC0_layer_hits[layer]<<endl;
					FDC0_TDC.push_back(val);
					FDC0_layerid.push_back(layer);
					FDC0_wireid.push_back(wireid);


				}
			}

			FDC0_X = NAN;
			FDC0_Y = NAN;
			FDC0_ThetaX = NAN;
			FDC0_ThetaY = NAN;
			FDC0_nlayerx=0;
			FDC0_nlayery=0;
			FDC0_Track_dl.clear();
			FDC0_Track_dl.resize(8,-9999);
			FDC0_Track_XY.clear();
			FDC0_Track_XY.resize(8,-9999);
			FDC0_Track_Z.clear();
			FDC0_Track_Z.resize(8,-9999);
			FDC0_Track_dXY.clear();
			FDC0_Track_dXY.resize(8,-9999);
			if (FDC0Track)
			{
				Int_t FDC0NumberOfTracks = FDC0Track->GetEntries();
				Double_t TempXPosition, TempYPosition,Temp_ThetaX,Temp_ThetaY,MinChi2x = 100, MinChi2y = 100,TempChi2,TempNDF; 

				//cout<<"Number of Tracks="<<FDC0NumberOfTracks<<endl;

				if (FDC0NumberOfTracks > 0)
				{
					TArtDCTrack *TrackFDC0;

					for(Int_t i=0; i<FDC0NumberOfTracks; i++)
					{
						TrackFDC0 = (TArtDCTrack *)FDC0Track->At(i);

						if(TrackFDC0)
						{

							TempXPosition = TrackFDC0->GetPosition(0);
							Temp_ThetaX = TMath::ATan(TrackFDC0->GetAngle(0));
							TempYPosition = TrackFDC0->GetPosition(1);
							Temp_ThetaY = TMath::ATan(TrackFDC0->GetAngle(1));
							TempChi2 = TrackFDC0->GetChi2();
							TempNDF = TrackFDC0->GetNDF();

							if(TempChi2 > 0 ){

								if(TMath::Abs(TempXPosition) < 50 && TempChi2<MinChi2x){
									MinChi2x = TempChi2;
									FDC0_X = TempXPosition;
									FDC0_ThetaX = TMath::ATan(TrackFDC0->GetAngle(0));
									FDC0_Chi2x=MinChi2x;

									FDC0_nlayerx=TrackFDC0->GetNumHitLayer();
									for(int st=0;st<FDC0_nlayerx;st++)
									{
										Int_t planeid=TrackFDC0->GetHitPlaneID(st)-11;
										if(planeid>8||planeid<0) 
										{
											cout<<" CALTREE info: Error! Plane id readout wrong!"<<endl;
											exit(0);

										}
										FDC0_Track_dl[planeid]=TrackFDC0->GetDriftLength(st);
										FDC0_Track_XY[planeid]=TrackFDC0->GetHitXPosition(st);
										FDC0_Track_Z[planeid]=TrackFDC0->GetHitZPosition(st);
										FDC0_Track_dXY[planeid]=TrackFDC0->GetAngle(0)*FDC0_Track_Z[planeid]+TrackFDC0->GetPosition(0)-FDC0_Track_XY[planeid];
										//if(EventByEvent==1) cout<<"    hitlayer="<<planeid<<" drift length="<<FDC0_Track_dl[planeid]<<" xpos="<<FDC0_Track_XY[planeid]<<" zpos="<<FDC0_Track_Z[planeid]<<" dx="<<FDC0_Track_dXY[planeid]<<endl;

									}


								}

								if (TMath::Abs(TempYPosition) < 50 && TempChi2<MinChi2y){
									FDC0_Y = TempYPosition;
									FDC0_ThetaY = TMath::ATan(TrackFDC0->GetAngle(1));
									MinChi2y = TempChi2;
									FDC0_Chi2y=MinChi2y;

									FDC0_nlayery=TrackFDC0->GetNumHitLayer();
									for(int st=0;st<FDC0_nlayery;st++)
									{
										Int_t planeid=TrackFDC0->GetHitPlaneID(st)-11;
										if(planeid>8||planeid<0) 
										{
											cout<<" CALTREE info: Error! Plane id readout wrong!"<<endl;
											exit(0);

										}
										FDC0_Track_dl[planeid]=TrackFDC0->GetDriftLength(st);
										FDC0_Track_XY[planeid]=TrackFDC0->GetHitXPosition(st);
										FDC0_Track_Z[planeid]=TrackFDC0->GetHitZPosition(st);
										FDC0_Track_dXY[planeid]=TrackFDC0->GetAngle(1)*FDC0_Track_Z[planeid]+TrackFDC0->GetPosition(1)-FDC0_Track_XY[planeid];
										//if(EventByEvent==1) cout<<"    hitlayer="<<planeid<<" drift length="<<FDC0_Track_dl[planeid]<<" xpos="<<FDC0_Track_XY[planeid]<<" zpos="<<FDC0_Track_Z[planeid]<<" dx="<<FDC0_Track_dXY[planeid]<<endl;

									}


								}
							}
						}
					}
				}
			}



			// ============== FDC2 ================

			CalibFDC0Hit->ReconstructData();
			CalibFDC0Track->ReconstructData();


			FDC2_X = NAN;
			FDC2_Y = NAN;
			FDC2_ThetaX = NAN;
			FDC2_ThetaY = NAN;

			TClonesArray *FDC2Tracks = (TClonesArray *)sman->FindDataContainer((char*)"SAMURAIFDC2Track");
			Int_t FDC2NumberOfTracks = -1;
			if(FDC2Tracks) {
				FDC2NumberOfTracks = FDC2Tracks->GetEntries();
				if(FDC2NumberOfTracks > 0) { //Tracks are already sorted by chi2
					TArtDCTrack *FDC2Track = (TArtDCTrack *)FDC2Tracks->At(0);
					if(FDC2Track) {
						FDC2_X = FDC2Track->GetPosition(0);
						FDC2_Y = FDC2Track->GetPosition(1);
						FDC2_ThetaX = TMath::ATan(FDC2Track->GetAngle(0));
						FDC2_ThetaY = TMath::ATan(FDC2Track->GetAngle(1));

					}
				}
			}


			tree_FDC  ->Fill();
		} // END FDCs ANALYSIS

		if(kHODO) {
			// ============== Hodoscope data ==============
			for (Int_t i=0;i<NUMBER_OF_HODO;i++)
			{
				AllHodo_Charge[i] = NAN;
				AllHodo_ID[i] = -1;
				AllHodo_Charge_C[i] = NAN;
				AllHodo_ChargeU[i] = NAN;
				AllHodo_ChargeD[i] = NAN;
				AllHodo_Time[i] = NAN;
				AllHodo_Time_C[i] = NAN;
			}

			HodoMultiplicity = 0;
			HodoFMultiplicity = 0;
			HodoGMultiplicity = 0;
			HodoPMultiplicity = 0;
			HodoSMultiplicity = 0;

			Hodo_ID = -1, HOD_GlobalID=-1;
			Hodo_Time = NAN;
			Hodo_Charge =  NAN;	
			Hodo_ChargeP = NAN;	
			Hodo_ChargeF = NAN;
			Hodo_Z = NAN;
			Hodo_AoverZ = NAN;

			CalibHODPla->ReconstructData();

			vector<Int_t> HodoHitID;
			vector<Double_t> HodoHitCharge;
			vector<Double_t> HodoHitCharge_C;
			vector<Double_t> HodoHitChargeU;
			vector<Double_t> HodoHitChargeD;
			vector<Double_t> HodoHitTime;
			vector<Double_t> HodoHitTime_C;
			Int_t   maxhodid=-1,maxhodid_o=-1,ccount=0,tempID[2];
			Double_t tempQ[2];

			if(CalibHODPla) {
				HodoMultiplicity = CalibHODPla->GetNumHODPla();

				if(HodoMultiplicity != 0)
				{

					for(Int_t i=0; i<HodoMultiplicity; i++)
					{
						TArtHODPla *HODPla = CalibHODPla->GetHODPla(i);

						if(HODPla->GetID()>=1 && HODPla->GetID()<=NUMBER_OF_HODO) { 
							Hodo_ID=HODPla->GetID();
							//		    if(HODPla->GetTimeU()!=-1000) cout << HODPla->GetTimeU() << " " <<  HODPla->GetTimeD() << endl;
							//check which HODO fired: HODP:24~40, HODF:24~1
							//define the intraID as 1~40, 1 from the lower momentum side one by one (HODF No.24 as intraID 1)
							if(Hodo_ID<25){   //HODF
								HodoFMultiplicity++;
								HOD_GlobalID=25-Hodo_ID; //1~24 			 
							} else {
								HodoPMultiplicity++;   
								HOD_GlobalID=65-Hodo_ID;
							}

							//cout<<"Hodo_ID="<<Hodo_ID<<" HOD_GlobalID="<<HOD_GlobalID<<endl;


							Hodo_Charge=HODPla->GetQAveCal();
							if( Hodo_Charge < HODPla->GetQAveCal()) {
								maxhodid=HOD_GlobalID; 
							}   //max ID

							//cout<<"Hodo_Charge="<<Hodo_Charge<<endl;
							//		    if(HODPla->GetTDRaw()!=0) cout<<"test "<<HOD_GlobalID << " " << EventNumber << " " <<  HODPla->GetTURaw()<< " "<<HODPla->GetTDRaw()<< " " << HODPla->GetTime() << endl;

							HodoHitID.push_back(HOD_GlobalID);
							HodoHitCharge.push_back(HODPla->GetQAveRaw());
							HodoHitCharge_C.push_back(HODPla->GetQAveCal());
							HodoHitChargeU.push_back(HODPla->GetQURaw());
							HodoHitChargeD.push_back(HODPla->GetQDRaw());
							HodoHitTime.push_back(HODPla->GetTime());
							HodoHitTime_C.push_back(HODPla->GetTimeSlew());



							//-----------Beyond the demension-------------
							if(HODPla->GetQAveRaw()>0 // to be change when detector calibrated ?
									//HodoHitCharge.back() < 4095 //&&
									//		       HodoHitTime.back() > -1000 && // check if this is true also for time ? New electronics !!
									//		       HodoHitTime.back() < 4095)    // check if this is true also for time ? New electronics !! 
								)
								{
									AllHodo_ID[HOD_GlobalID-1] = HodoHitID.back();// * hodo_coeffcalib[HodoHitID.back()-1][0] + hodo_coeffcalib[HodoHitID.back()-1][1];   
									AllHodo_ChargeU[HOD_GlobalID-1] = HodoHitChargeU.back();// 
									AllHodo_ChargeD[HOD_GlobalID-1] = HodoHitChargeD.back();// 
									AllHodo_Charge[HOD_GlobalID-1] = HodoHitCharge.back();// * hodo_coeffcalib[HodoHitID.back()-1][0] + hodo_coeffcalib[HodoHitID.back()-1][1];   
									AllHodo_Time[HOD_GlobalID-1] = HodoHitTime.back();// - F13_Time;
									AllHodo_Charge_C[HOD_GlobalID-1] = HodoHitCharge_C.back();// * hodo_coeffcalib[HodoHitID.back()-1][0] + hodo_coeffcalib[HodoHitID.back()-1][1];   
									AllHodo_Time_C[HOD_GlobalID-1] = HodoHitTime_C.back();// - F13_Time;

									//	if(HOD_GlobalID<=24) //HODF
									//	  {
									//	    AllHodo_Time_C[HOD_GlobalID-1] = HodoHitTime.back()+hod_toff[HOD_GlobalID-1];// 
									//	    AllHodo_Charge_C[HOD_GlobalID-1] = HodoHitCharge.back()*hod_qcor[HOD_GlobalID-1]+hod_qoff[HOD_GlobalID-1];
									//	  }
									//	if(HOD_GlobalID>24 && HOD_GlobalID<=NUMBER_OF_HODO) //HODP 
									//	  {
									//	    AllHodo_Time_C[HOD_GlobalID-1] = HodoHitTime.back()+hod_toff[HOD_GlobalID-1-1];// 
									//	    AllHodo_Charge_C[HOD_GlobalID-1] = HodoHitCharge.back()*hod_qcor[HOD_GlobalID-1-1]+hod_qoff[HOD_GlobalID-1-1];
									//	  }
									//
									AllHodo_ChargeCalU[HOD_GlobalID-1] =HODPla->GetQUCal();// 
									AllHodo_ChargeCalD[HOD_GlobalID-1] = HODPla->GetQDCal();//
									AllHodo_TimeRawU[HOD_GlobalID-1]  = HODPla->GetTURaw();// 
									AllHodo_TimeRawD[HOD_GlobalID-1]  = HODPla->GetTDRaw();// 
									AllHodo_TimeSlwU[HOD_GlobalID-1]  = HODPla->GetTimeUSlew();// 
									AllHodo_TimeSlwD[HOD_GlobalID-1]  = HODPla->GetTimeDSlew();// 

								}

							else
							{
								HodoHitID.pop_back();
								HodoHitCharge.pop_back();
								HodoHitCharge_C.pop_back();
								HodoHitChargeU.pop_back();
								HodoHitChargeD.pop_back();
								HodoHitTime.pop_back();
								HodoHitTime_C.pop_back();
							}
						}
					}
					Int_t RealMultiplicity = HodoHitID.size();

					if(RealMultiplicity != 0) {

						if(RealMultiplicity > 1) {
							SortHodoHit(HodoHitID,HodoHitCharge);
						}
						//	Hodo_ID = HodoHitID.at(0);
						//Hodo_Charge = AllHodo_Charge[Hodo_ID-1];
						//Hodo_Time = AllHodo_Time[Hodo_ID-1] + HODOT0[Hodo_ID-1];

						Hodo_Time = AllHodo_Time[Hodo_ID-1] + HODOT0[Hodo_ID-1];
						Hodo_Time_C = AllHodo_Time_C[Hodo_ID-1] + HODOT0[Hodo_ID-1];   
						Hodo_Z = Hodo_Charge-(-17.98+0.7443*Hodo_Time-0.005006*TMath::Power(Hodo_Time,2.));
						Hodo_AoverZ = Hodo_Time-(-0.01205*FDC2_X + 63.41)
							-(-3.168 + 0.02068 * FDC0_X);
						// -(-3.168 + 0.02068 * FDC1_X);

					}
				}
			}
			tree_HODO->Fill();
		} // END HODOSCOPE ANALYSIS

		if(kNEUT){
			//NEBULA
			NEBULA_ID->clear();
			NEBULA_X->clear();
			NEBULA_Y->clear();
			NEBULA_Z->clear();
			NEBULA_ChargeUp->clear();
			NEBULA_ChargeDown->clear();
			NEBULA_Charge->clear();
			NEBULA_Time->clear();
			NEBULA_VetoFired = 0;

			CalibNEBULA->ReconstructData();

			if(CalibNEBULA) {
				Int_t NEBULAMultiplicity = CalibNEBULA->GetNumNEBULAPla();

				for(Int_t i=0; i<NEBULAMultiplicity; i++)
				{
					TArtNEBULAPla *NEBULAPla = CalibNEBULA->GetNEBULAPla(i);
					if(NEBULAPla)
					{
						if(NEBULAPla->GetTURaw() > 0 && NEBULAPla->GetTURaw() < 4095 &&  NEBULAPla->GetTDRaw() > 0 && NEBULAPla->GetTDRaw() < 4095){
							NEBULA_ID->push_back(NEBULAPla->GetID());
							if (NEBULA_ID->back() > 120) // Don't put veto into tree
							{
								if(NEBULAPla->GetQDCal() > 1.){
									NEBULA_VetoFired = 1;
								}

								NEBULA_ID->pop_back();
							}
							else
							{
								NEBULA_ChargeUp->push_back(NEBULAPla->GetQURaw());
								NEBULA_ChargeDown->push_back(NEBULAPla->GetQDRaw());
								NEBULA_Charge->push_back(TMath::Sqrt(NEBULA_ChargeUp->back()*NEBULA_ChargeDown->back()));
								NEBULA_Time->push_back(NEBULAPla->GetTAveSlw() - NEBULAT0.at(NEBULA_ID->back()-1));
								NEBULA_X->push_back(NEBULAPla->GetPos(0));
								NEBULA_Y->push_back(NEBULAPla->GetPos(1));
								NEBULA_Z->push_back(NEBULAPla->GetPos(2));
							}
						}
					}
				}

				NEBULA_Multiplicity = NEBULA_X->size();
			}

			// ============== NEBULA to NEUTRON (backward comp w/ NEULAND)  ==============

			Neutron_X->clear();
			Neutron_Y->clear();
			Neutron_Z->clear();
			Neutron_ID->clear();
			Neutron_Time->clear();
			Neutron_ChargeUp->clear();
			Neutron_ChargeDown->clear();
			Neutron_Charge->clear();
			Neutron_IsNEBULA->clear();
			Neutron_Multiplicity = 0;

			for (Int_t i=0;i<NEBULA_Multiplicity;i++)
			{
				Neutron_X->push_back(NEBULA_X->at(i));
				Neutron_Y->push_back(NEBULA_Y->at(i));
				Neutron_Z->push_back(NEBULA_Z->at(i));

				Double_t DistanceX = Neutron_X->back();
				Double_t DistanceZ = Neutron_Z->back() - 337.; // Distance from Al Tgt used for calib
				Double_t Distance = TMath::Sqrt(DistanceX*DistanceX + DistanceZ*DistanceZ);

				Neutron_ID->push_back(NEBULA_ID->at(i));
				//Neutron_Time->push_back(NEBULA_Time->at(i) - ToF_SBTTarget + Distance / 300.);
				Neutron_Time->push_back(NEBULA_Time->at(i)  + Distance / 300.);
				Neutron_ChargeUp->push_back(NEBULA_ChargeUp->at(i));
				Neutron_ChargeDown->push_back(NEBULA_ChargeDown->at(i));
				Neutron_Charge->push_back(NEBULA_Charge->at(i));
				Neutron_IsNEBULA->push_back(true);
				Neutron_Multiplicity++;
			}

			tree_NEUT ->Fill();
		}

		//cout<<" waht"<<endl;
		//cout<<kSILI<<endl;
		if(kSILI){


			CalibSILICONS->ReconstructData();

			Silicons_X->clear();
			Silicons_Y->clear();
			Silicons_Z->clear();
			Silicons_ID->clear();
			Silicons_Time->clear();
			Silicons_Energy->clear();
			Silicons_Multiplicity = 0;

			SiLF_rawADC.clear();
			SiLF_rawADC.resize(32,-1);
			SiLB_rawADC.clear();
			SiLB_rawADC.resize(32,-1);
			SiRF_rawADC.clear();
			SiRF_rawADC.resize(32,-1);
			SiRB_rawADC.clear();
			SiRB_rawADC.resize(32,-1);

			SiLF_rawTDC.clear();
			SiLF_rawTDC.resize(32,-1);
			SiLB_rawTDC.clear();
			SiLB_rawTDC.resize(32,-1);
			SiRF_rawTDC.clear();
			SiRF_rawTDC.resize(32,-1);
			SiRB_rawTDC.clear();
			SiRB_rawTDC.resize(32,-1);

			CsILL_rawADC=NAN;
			CsILRT_rawADC=NAN;
			CsILRB_rawADC=NAN;
			CsIRLT_rawADC=NAN;
			CsIRLB_rawADC=NAN;
			CsIRRT_rawADC=NAN;
			CsIRRB_rawADC=NAN;

			CsILL_rawTDC=NAN;
			CsILRT_rawTDC=NAN;
			CsILRB_rawTDC=NAN;
			CsIRLT_rawTDC=NAN;
			CsIRLB_rawTDC=NAN;
			CsIRRT_rawTDC=NAN;
			CsIRRB_rawTDC=NAN;


			TClonesArray *Sis = (TClonesArray *)sman->FindDataContainer("SILICONS");
			Double_t RefTime1 = 0;
			Double_t RefTime2 = 0;

			//cout<<Sis->GetEntries()<<endl;
			for(int i=0;i<Sis->GetEntries();i++){
				TArtSILICONS *Si = (TArtSILICONS *)Sis->At(i);
				if(Si){

					if(Si->GetID()==136) {
						RefTime1 = Si->GetTime() ;
					}
					if(Si->GetID()==137) {
						RefTime2 = Si->GetTime() ;
					}

					Silicons_ID->push_back(Si->GetID());
					Silicons_X->push_back(Si->GetPosX());
					Silicons_Y->push_back(Si->GetPosY());
					Silicons_Z->push_back(Si->GetPosZ());
					Silicons_Time->push_back(Si->GetTime());
					Silicons_Energy->push_back(Si->GetEnergy());
					Silicons_Multiplicity++;

					int Teleid=Si->GetID();
					Double_t adc=Si->GetRawADC();
					Double_t tdc=Si->GetRawTDC();
					//cout<<"id="<<Teleid<<" RawADC="<<adc<<" RawTDC="<<tdc<<endl;
					//if(adc>4096) continue;
					if(Teleid>0&&Teleid<33)   { SiLF_rawADC[Teleid-1 ]= adc;SiLF_rawTDC[Teleid-1 ]= tdc;}
					if(Teleid>32&&Teleid<65)  { SiLB_rawADC[Teleid-33]= adc;SiLB_rawTDC[Teleid-33]= tdc;}
					if(Teleid>64&&Teleid<97)  { SiRF_rawADC[Teleid-65]= adc;SiRF_rawTDC[Teleid-65]= tdc;}
					if(Teleid>96&&Teleid<129) { SiRB_rawADC[Teleid-97]= adc;SiRB_rawTDC[Teleid-97]= tdc;}
					if(Teleid==129) { CsIRLT_rawADC=adc; CsIRLT_rawTDC=tdc;}
					if(Teleid==130) { CsIRRT_rawADC=adc; CsIRRT_rawTDC=tdc;}
					if(Teleid==131) { CsIRLB_rawADC=adc; CsIRLB_rawTDC=tdc;}
					if(Teleid==132) { CsIRRB_rawADC=adc; CsIRRB_rawTDC=tdc;}
					if(Teleid==133) { CsILL_rawADC=adc;   CsILL_rawTDC=tdc;}
					if(Teleid==134) { CsILRT_rawADC=adc; CsILRT_rawTDC=tdc;}
					if(Teleid==135) { CsILRB_rawADC=adc; CsILRB_rawTDC=tdc;}
					if(Si->GetID()==136) { RefTime1 = Si->GetTime() ;}
					if(Si->GetID()==137) { RefTime2 = Si->GetTime() ;}

				}
			}
			for(int i=0;i<Silicons_ID->size();i++) {
				Silicons_Time->at(i) -=  RefTime1 ;
			}
			tree_SILICONS ->Fill();
		}

		if(kESPRI){

			Double_t ADC;
			ESPRI_NaI_Mult=ESPRI_Plas_Mult=ESPRI_RDC_Hit=0;

			fill(ESPRI_NaI_ID       , ESPRI_NaI_ID       +14       , (UShort_t)NAN);
			fill(ESPRI_NaI_Layer    , ESPRI_NaI_Layer    +14          , (UShort_t)NAN);
			fill(ESPRI_NaI_Energy   , ESPRI_NaI_Energy   +14           , NAN);
			fill(ESPRI_NaI_EnergyL  , ESPRI_NaI_EnergyL  +14           , NAN);
			fill(ESPRI_NaI_EnergyR  , ESPRI_NaI_EnergyR  +14           , NAN);
			//fill(ESPRI_NaI_Time   , ESPRI_NaI_Time   +14           , NAN);
			//fill(ESPRI_NaI_TimeL  , ESPRI_NaI_TimeL  +14           , NAN);
			//fill(ESPRI_NaI_TimeR  , ESPRI_NaI_TimeR  +14           , NAN);

			fill(ESPRI_Plas_ID      , ESPRI_Plas_ID      +2        , (UShort_t)NAN);
			fill(ESPRI_Plas_Layer   , ESPRI_Plas_Layer   +2           , (UShort_t)NAN);
			fill(ESPRI_Plas_Energy  , ESPRI_Plas_Energy  +2            , NAN);
			fill(ESPRI_Plas_EnergyU  , ESPRI_Plas_EnergyU  +2            , NAN);
			fill(ESPRI_Plas_EnergyD  , ESPRI_Plas_EnergyD  +2            , NAN);
			fill(ESPRI_Plas_Time  , ESPRI_Plas_Time  +2            , NAN);
			fill(ESPRI_Plas_TimeU  , ESPRI_Plas_TimeU  +2            , NAN);
			fill(ESPRI_Plas_TimeD  , ESPRI_Plas_TimeD  +2            , NAN);

			fill(ESPRI_RDC_X        , ESPRI_RDC_X        +2      , NAN);
			fill(ESPRI_RDC_A        , ESPRI_RDC_A        +2      , NAN);
			fill(ESPRI_RDC_Y        , ESPRI_RDC_Y        +2      , NAN);
			fill(ESPRI_RDC_B        , ESPRI_RDC_B        +2      , NAN);
			fill(ESPRI_RDC_Side     , ESPRI_RDC_Side     +2         , NAN);

			//ADC for NaI(TDC is not included yet)

			Int_t tmpID ;
			CalibESPRI_NaI->ReconstructData();
			TClonesArray *ESPRI_NaIs = (TClonesArray *)sman->FindDataContainer("ESPRINaI");
			for(int i=0;i<ESPRI_NaIs->GetEntries();i++){
				TArtRNaI *ESPRINaI = (TArtRNaI*)ESPRI_NaIs->At(i);
				{
					ADC = ESPRINaI->GetRawADC();
					//	    cout << ESPRINaI->GetID() << " " << ESPRINaI->GetLayer() << endl; 
					if(ADC > 0 && ESPRINaI->GetID()>0 && ESPRINaI->GetID()<29){
						tmpID = ESPRI_NaIMergeID[ESPRINaI->GetID()-1];
						ESPRI_NaI_ID[tmpID-1] = tmpID ;
						ESPRI_NaI_Layer[tmpID-1] = ESPRINaI->GetLayer();
						if(ESPRINaI->GetID()%2){
							ESPRI_NaI_EnergyL[tmpID-1] = ESPRINaI->GetEnergy();
							//ESPRI_NaI_TimeL[tmpID-1] = ESPRINaI->GetTime();
						} else {
							ESPRI_NaI_EnergyR[tmpID-1] = ESPRINaI->GetEnergy();
							//ESPRI_NaI_TimeR[tmpID-1] = ESPRINaI->GetTime();
						}
						ESPRI_NaI_Mult++;
					}
				}
			}
			for(int i=0;i<14;i++){
				ESPRI_NaI_Energy[i] = TMath::Sqrt(ESPRI_NaI_EnergyL[i]*ESPRI_NaI_EnergyR[i]);
				//ESPRI_NaI_Time[i] = ( ESPRI_NaI_TimeR[i] + ESPRI_NaI_TimeL[i] )/2.;
			}
			//All of multihitTDC
			CalibESPRI_tdc->ReconstructData();

			//RDCup&dw
			CalibESPRI_rdc->ReconstructData();
			TClonesArray *ESPRI_RDC = (TClonesArray *)sman->FindDataContainer("ESPRIRDC");
			for(int i=0;i<ESPRI_RDC->GetEntries();i++){
				TArtRDC *rdc = (TArtRDC*)ESPRI_RDC->At(i);
				if(rdc){
					if(rdc->GetLayer()>0 && rdc->GetLayer()<3) {
						// ESPRI_RDC_Side=rdc->GetLayer();
						ESPRI_RDC_X[rdc->GetLayer()-1]=rdc->GetRDCX();
						ESPRI_RDC_A[rdc->GetLayer()-1]=rdc->GetRDCA();
						ESPRI_RDC_Y[rdc->GetLayer()-1]=rdc->GetRDCY();
						ESPRI_RDC_B[rdc->GetLayer()-1]=rdc->GetRDCB();
						ESPRI_RDC_Hit++;
					}
				}
			}

			/*
			//FlashADC by SIS3350
			CalibESPRI_fadc->ReconstructData();
			TClonesArray *ESPRI_FADC = (TClonesArray *)sman->FindDataContainer("ESPRIFADC");	
			for(int i=0;i<ESPRI_FADC->GetEntries();i++){
			TArtFADC *FADC = (TArtFADC*)ESPRI_FADC->At(i);
			{
			/////////////////////////////////////
			}
			}
			*/

			//QDC
			ESPRI_Plas_Mult=0;
			CalibESPRI_plas->ReconstructData();
			TClonesArray *ESPRI_Plas = (TClonesArray *)sman->FindDataContainer("ESPRIPLAS");
			if(ESPRI_Plas){
				for(int i=0;i<ESPRI_Plas->GetEntries();i++){
					TArtPlas *ESPRIPlas = (TArtPlas*)ESPRI_Plas->At(i);
					//cout << ESPRIPlas->GetID() << " " << ESPRIPlas->GetLayer() << endl; 
					if(ESPRIPlas){
						ADC = ESPRIPlas->GetRawADC();
						//cout<<ESPRIPlas->GetID()<<endl;
						if(ADC > 0 && ESPRIPlas->GetID()>0 && ESPRIPlas->GetID()<5){
							tmpID = ESPRI_PlaMergeID[ESPRIPlas->GetID()-1];
							ESPRI_Plas_ID[tmpID-1] = tmpID ;
							ESPRI_Plas_Layer[tmpID-1] = ESPRIPlas->GetLayer();
							if(ESPRIPlas->GetID()%2){
								ESPRI_Plas_EnergyU[tmpID-1] = ESPRIPlas->GetEnergy();
								ESPRI_Plas_TimeU[tmpID-1] = ESPRIPlas->GetTime();
							} else {
								ESPRI_Plas_EnergyD[tmpID-1] = ESPRIPlas->GetEnergy();
								ESPRI_Plas_TimeD[tmpID-1] = ESPRIPlas->GetTime();
							}
							ESPRI_Plas_Mult++;
						}
					}
				}
			}
			for(int i=0;i<2;i++){
				ESPRI_Plas_Energy[i] = TMath::Sqrt(ESPRI_Plas_EnergyU[i]*ESPRI_Plas_EnergyD[i]);
				ESPRI_Plas_Time[i] = ( ESPRI_Plas_TimeU[i] + ESPRI_Plas_TimeD[i] )/2.;
			}

			tree_ESPRI->Fill();
		}

	}

	std::clog << std::endl;

	if(kBDC) { tree_BDC->BuildIndex("RunNumber","EventNumber"); fout_BDC->cd(); WriteAllEnvFiles ; fout_BDC->Write(); fout_BDC->Close("R"); }
	if(kPLA) { tree_PLA->BuildIndex("RunNumber","EventNumber"); fout_PLA->cd(); WriteAllEnvFiles ; fout_PLA->Write(); fout_PLA->Close("R"); }
	if(kMAIN) { tree_MAIN->BuildIndex("RunNumber","EventNumber"); fout_MAIN->cd(); WriteAllEnvFiles ; fout_MAIN->Write(); fout_MAIN->Close("R"); }
	if(kNEUT) { tree_NEUT->BuildIndex("RunNumber","EventNumber"); fout_NEUT->cd(); WriteAllEnvFiles ; fout_NEUT->Write(); fout_NEUT->Close("R"); }
	if(kESPRI) { tree_ESPRI->BuildIndex("RunNumber","EventNumber"); fout_ESPRI->cd(); WriteAllEnvFiles ; fout_ESPRI->Write(); fout_ESPRI->Close("R"); }
	if(kFDC) { tree_FDC ->BuildIndex("RunNumber","EventNumber"); fout_FDC ->cd(); WriteAllEnvFiles ; fout_FDC ->Write();  fout_FDC ->Close("R"); }
	if(kHODO) { tree_HODO->BuildIndex("RunNumber","EventNumber"); fout_HODO->cd(); WriteAllEnvFiles ; fout_HODO->Write(); fout_HODO->Close("R"); }
	if(kSILI) { tree_SILICONS->BuildIndex("RunNumber","EventNumber"); fout_SILICONS->cd(); WriteAllEnvFiles ; fout_SILICONS->Write(); fout_SILICONS->Close("R"); }


	if(kOverwrite){
		system(TString("mv -vfu ")+TmpRootFilenameBody+"*.root "+rootfilesubpath+"/");
	} else {
		system(TString("mv -viu ")+TmpRootFilenameBody+"*.root "+rootfilesubpath+"/");
	}


	EventStore->ClearData();

	delete CalibNEBULA;
	delete CalibPlastic;
	delete CalibPPAC;
	delete CalibBDC1Hit;
	delete CalibBDC1Track;
	delete CalibBDC2Hit;
	delete CalibBDC2Track;
	//delete CalibFDC1Track;
	delete CalibFDC2Track;
	delete CalibFDC0Track;
	// delete CalibFDC1Hit;
	delete CalibFDC0Hit;
	delete CalibFDC2Hit;
	delete CalibHODPla;
	delete CalibCoin;
	//  delete RecoFragment;
	delete NEBULA_X;
	delete NEBULA_Y;
	delete NEBULA_Z;
	delete NEBULA_ID;
	delete NEBULA_Time;
	delete NEBULA_ChargeUp;
	delete NEBULA_ChargeDown;

	delete CalibESPRI_NaI ;
	delete CalibESPRI_tdc ;
	delete CalibESPRI_rdc ;
	delete CalibESPRI_fadc ;
	delete CalibESPRI_plas ;

	delete Neutron_X;
	delete Neutron_Y;
	delete Neutron_Z;
	delete Neutron_ID;
	delete Neutron_Time;
	delete Neutron_ChargeUp;
	delete Neutron_ChargeDown;
	delete TArtStoreManager::Instance();

	return 0;
}


// External Function
// ======================================================================================

void SortHodoHit(vector<Int_t> &HodoHitID, vector<Double_t> &HodoHitEnergy) {

	Int_t NumberOfHits = HodoHitID.size();

	//  for(int i=0; i<NumberOfHits; i++) {
	//    cout <<  HodoHitID[i]<< "] " << HodoHitEnergy[i]  << " " ;
	//  }
	//  cout << endl;

	for(int i=0; i<NumberOfHits-1; i++)
	{
		for(int j=0; j<NumberOfHits-i-1; j++)
		{
			if(HodoHitID[i]<=NUMBER_OF_HODO && HodoHitID[j]<=NUMBER_OF_HODO){
				if(HodoHitEnergy[j]<HodoHitEnergy[j+1])
				{
					Double_t tempE = HodoHitEnergy[j+1];
					HodoHitEnergy[j+1] = HodoHitEnergy[j];
					HodoHitEnergy[j] = tempE;

					Double_t tempI = HodoHitID[j+1];
					HodoHitID[j+1] = HodoHitID[j];
					HodoHitID[j] = tempI;

				}
			}
		}
	}


	//  if( HodoHitEnergy[0] >0) cout << HodoHitEnergy[0] << " " << HodoHitEnergy[1] << endl;   
	//  for(int i=0; i<NumberOfHits; i++) {
	//    cout <<  HodoHitID[i]<< ") " << HodoHitEnergy[i]  << " " ;
	//  }
	//  cout << endl << endl;
}

//---------------------------------------------------

Double_t DopplerCorrection(Double_t GammaDopplerEnergy, Double_t Beta, Double_t CosTheta) {
	Double_t Gamma = 1 / TMath::Sqrt(1 - Beta * Beta);
	Double_t DopplerCorrected = GammaDopplerEnergy * Gamma * (1 - Beta * CosTheta);
	return DopplerCorrected;
}

//---------------------------------------------------

inline bool exists_test (const std::string& name) {
	return ( access( name.c_str(), F_OK ) != -1 );
}
inline bool exists_test (const TString& name) {
	return ( access( name.Data(), F_OK ) != -1 );
}


void SortDaliHit(Int_t left, Int_t right,vector <Int_t> *DALI_ID,vector <Double_t> *DALI_Energy, vector <Double_t> *DALI_EnergyDopplerCorrected, vector <Double_t> *DALI_Time, vector <Double_t> *DALI_CosTheta)
{
	Int_t TempID;
	Double_t TempEnergy;
	Double_t TempEnergyDopplerCorrected;
	Double_t TempTime;
	Double_t TempCosTheta;

	int i = left, j = right;
	double pivot = DALI_EnergyDopplerCorrected->at((left + right) / 2);

	/* partition */
	while (i <= j) {
		while (DALI_EnergyDopplerCorrected->at(i) > pivot)
			i++;
		while (DALI_EnergyDopplerCorrected->at(j) < pivot)
			j--;
		if (i <= j) {
			TempID = DALI_ID->at(j);
			TempEnergy = DALI_Energy->at(j);
			TempEnergyDopplerCorrected = DALI_EnergyDopplerCorrected->at(j);
			TempTime = DALI_Time->at(j);
			TempCosTheta = DALI_CosTheta->at(j);

			DALI_ID->at(j) = DALI_ID->at(i);
			DALI_Energy->at(j) = DALI_Energy->at(i);
			DALI_EnergyDopplerCorrected->at(j) = DALI_EnergyDopplerCorrected->at(i);
			DALI_Time->at(j) = DALI_Time->at(i);
			DALI_CosTheta->at(j) = DALI_CosTheta->at(i);

			DALI_ID->at(i) = TempID;
			DALI_Energy->at(i) = TempEnergy;
			DALI_EnergyDopplerCorrected->at(i) = TempEnergyDopplerCorrected;
			DALI_Time->at(i) = TempTime;
			DALI_CosTheta->at(i) = TempCosTheta;

			i++;
			j--;
		}
	};
	/* recursion */
	if (left < j)
		SortDaliHit(left, j, DALI_ID, DALI_Energy, DALI_EnergyDopplerCorrected, DALI_Time, DALI_CosTheta);
	if (i < right)
		SortDaliHit(i, right, DALI_ID, DALI_Energy, DALI_EnergyDopplerCorrected, DALI_Time, DALI_CosTheta);
}

//--------------------------------------------------------

void SortNeutronHit(int left, int right,vector <Bool_t> *Neutron_IsNEBULA, vector <Int_t> *Neutron_ID,vector <Double_t> *Neutron_X,vector <Double_t> *Neutron_Y,vector <Double_t> *Neutron_Z,vector <Double_t> *Neutron_ChargeUp, vector <Double_t> *Neutron_ChargeDown, vector <Double_t> *Neutron_Charge, vector <Double_t> *Neutron_Time){
	int i = left, j = right;
	double pivot = Neutron_Time->at((left + right) / 2);

	/* partition */
	while (i <= j) {
		while (Neutron_Time->at(i) < pivot)
			i++;
		while (Neutron_Time->at(j) > pivot)
			j--;
		if (i <= j) {

			//MODIF ALDRIC 19/11/2015 : ajout de Neutron_IsNEBULA !!

			Int_t TempID;
			Double_t TempChargeUp;
			Double_t TempChargeDown;
			Double_t TempCharge;
			Double_t TempTime;
			Double_t TempXPosition;
			Double_t TempYPosition;
			Double_t TempZPosition;
			Bool_t TempIsNEBULA;

			TempID = Neutron_ID->at(i);
			TempChargeUp = Neutron_ChargeUp->at(i);
			TempChargeDown = Neutron_ChargeDown->at(i);
			TempCharge = Neutron_Charge->at(i);
			TempTime = Neutron_Time->at(i);
			TempXPosition = Neutron_X->at(i);
			TempYPosition = Neutron_Y->at(i);
			TempZPosition = Neutron_Z->at(i);
			TempIsNEBULA = Neutron_IsNEBULA->at(i);

			Neutron_ID->at(i) =  Neutron_ID->at(j);
			Neutron_ChargeUp->at(i) = Neutron_ChargeUp->at(j);
			Neutron_ChargeDown->at(i) = Neutron_ChargeDown->at(j);
			Neutron_Charge->at(i) = Neutron_Charge->at(j);
			Neutron_Time->at(i) = Neutron_Time->at(j);
			Neutron_X->at(i) = Neutron_X->at(j);
			Neutron_Y->at(i) = Neutron_Y->at(j);
			Neutron_Z->at(i) = Neutron_Z->at(j);
			Neutron_IsNEBULA->at(i) = Neutron_IsNEBULA->at(j);


			Neutron_ID->at(j) = TempID;
			Neutron_ChargeUp->at(j) = TempChargeUp;
			Neutron_ChargeDown->at(j) = TempChargeDown;
			Neutron_Charge->at(j) = TempCharge;
			Neutron_Time->at(j) = TempTime;
			Neutron_X->at(j) = TempXPosition;
			Neutron_Y->at(j) = TempYPosition;
			Neutron_Z->at(j) = TempZPosition;
			Neutron_IsNEBULA->at(j) = TempIsNEBULA;

			i++;
			j--;
		}
	};

	/* recursion */
	if (left < j)
		SortNeutronHit(left, j,Neutron_IsNEBULA,Neutron_ID,Neutron_X,Neutron_Y,Neutron_Z,Neutron_ChargeUp, Neutron_ChargeDown, Neutron_Charge, Neutron_Time);
	if (i < right)
		SortNeutronHit(i, right,Neutron_IsNEBULA,Neutron_ID,Neutron_X,Neutron_Y,Neutron_Z,Neutron_ChargeUp, Neutron_ChargeDown, Neutron_Charge, Neutron_Time);

}
