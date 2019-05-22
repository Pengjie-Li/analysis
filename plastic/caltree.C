#include "TTree.h"
#include "TFile.h"
#include "TMath.h"
#include "TH2F.h"
#include "TEnv.h"
#include "TH1F.h"
#include "TH1.h"
#include "TVector3.h"
#include "TVectorD.h"
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
void LoadDCTDCDistributionFull(char *FileName, TArtCalibSimpleBDC1Track *, TArtCalibSimpleBDC2Track *, TArtCalibSimpleFDC0Track *, TArtCalibSimpleFDC2Track *);
void LoadDCTDCDistributionFull(char *FileName, TArtCalibSimpleBDC1Track *, TArtCalibSimpleBDC2Track *, TArtCalibFDC0Track *, TArtCalibFDC2Track *);
void SortHodoHit(vector<Int_t> &, vector<Double_t> &);
Double_t DopplerCorrection(Double_t, Double_t, Double_t);
inline bool exists_test (const std::string&);
inline bool exists_test (const TString&);
void SortDaliHit(Int_t, Int_t,vector <Int_t> *,vector <Double_t> *, vector <Double_t> *, vector <Double_t> *, vector <Double_t> *);
void SortNeutronHit(int, int,vector <Bool_t> *, vector <Int_t> *,vector <Double_t> *,vector <Double_t> *,vector <Double_t> *,vector <Double_t> *, vector <Double_t> *, vector <Double_t> *, vector <Double_t> *);

int main(int argc, char *argv[])
{
  Long64_t MaxEventNumber = LLONG_MAX;
   //MaxEventNumber = 100000;
   const Int_t DISPLAY_EVERY_EVENT = 500 ;
  std::clock_t start = std::clock();
  std::clock_t clock0 = std::clock();
  Bool_t kMAIN=kFALSE,
    kNEUT=kFALSE,
    kDALI=kFALSE,
    kFDCs=kFALSE,
    kHODO=kFALSE,
    kBEAM=kFALSE, 
    kFDCs_full=kFALSE,
    kCATANA=kFALSE,
    kESPRI=kFALSE,
    kPANDORA=kFALSE,
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
      kMAIN=kNEUT=kHODO=kBEAM=kESPRI=kSILI=kTRUE; //kDALI=kPANDORA //kFDCs_full
      break;
    case 'B':
      kBEAM=kTRUE;
      break;
    case 'C':
      kCATANA=kTRUE;
      break;
    case 'D':
      kDALI=kTRUE;
      break;
    case 'E':
      kESPRI=kTRUE;
      break;
    case 'F':
      kFDCs=kTRUE;
      break;
    case 'G':
      kFDCs_full=kTRUE;
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
    case 'P':
      kPANDORA=kTRUE;
      break;
    case 'S':
      kSILI=kTRUE;
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
      //      MaxEventNumber = 1e3;
      std::clog << "\e[31m" << "  ANALYSIS-Info : You will analyse " << MaxEventNumber << " events" << "\e[0m" << std::endl;
      break;
    default: /* '?' */
      kMAIN=kNEUT=kDALI=kFDCs=kHODO=kBEAM= kFDCs_full=kCATANA=kESPRI=kPANDORA=kSILI=kFALSE; 
    }
  }

  if(kRunLive && MaxEventNumber == LLONG_MAX){
    std::cerr <<  " For the live mode you should put a maximum number, with -n flag" << endl;
    kShowHelp = kTRUE;
  }

  Int_t FileNumber = TString(argv[optind]).Atoi();

  if(!kRunLive && FileNumber==0){
    std::cerr <<  " You should provide either a runnumber or use the -V (for live) flag" << endl;
    kShowHelp = kTRUE;
  }

  if ( kShowHelp || (!kMAIN && !kNEUT && !kSILI && !kESPRI && !kPANDORA && !kDALI && !kFDCs && !kHODO && !kBEAM && !kFDCs_full)) {
    std::cerr <<  "Usage: " << argv[0] << " run_number " << std::endl;
    std::cerr <<  "Usage: " << argv[0] << " -n nb_of_events run_number " << std::endl ;
    std::cerr <<  "Usage: " << argv[0] << " -h for help"  << std::endl;
    std::cerr <<  "Usage: " << argv[0] << " -V for liVe conversion " << std::endl ;
    std::cerr <<  "       Conversion options: " << endl;
    std::cerr <<  "       -A for ALL " << endl;
    std::cerr <<  "       -B for BEAM (include Bigrips and BDCs)" << endl;
    std::cerr <<  "       -C for CATANA (TODO)" << endl;
    std::cerr <<  "       -D for DALI (N/A here)" << endl;
    std::cerr <<  "       -E for ESPRI " << endl;
    std::cerr <<  "       -F for FDCs (w/ fast tracking) " << endl;
    std::cerr <<  "       -G for FDCs (w/ full tracking) " << endl;
    std::cerr <<  "       -H for HODO " << endl;
    std::cerr <<  "       -M for MAIN " << endl;
    std::cerr <<  "       -N for NEUT(rons) " << endl;
    std::cerr <<  "       -P for PANDORA " << endl;
    std::cerr <<  "       -S for SILICONS " << endl;
    std::cerr <<  "       Other options: " << endl;
    std::cerr <<  "       -f force overwriting the output files " << endl;
    exit(EXIT_FAILURE);
  }

  flagMap['B']=&kBEAM;
  flagMap['C']=&kCATANA;
  flagMap['D']=&kDALI;      
  flagMap['E']=&kESPRI;      
  flagMap['F']=&kFDCs;      
  flagMap['G']=&kFDCs_full;
  flagMap['H']=&kHODO;      
  flagMap['M']=&kMAIN;
  flagMap['N']=&kNEUT;            
  flagMap['P']=&kPANDORA;
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

  if(kDALI){
    next = TString(env_par->GetValue("DALIPara","")).Tokenize(" ");
    while(( xmlfile = (TObjString *)next())) {
      DALIPara->LoadParameter((char*)xmlfile->GetName());
    }
  }

  next = TString(env_par->GetValue("SILICONSPara","")).Tokenize(" ");
  while(( xmlfile = (TObjString *)next())) {
    SILICONSPara->LoadParameter((char*)xmlfile->GetName());
  }

  next = TString(env_par->GetValue("WINDSPara","")).Tokenize(" ");
  while(( xmlfile = (TObjString *)next())) {
    WINDSPara->LoadParameter((char*)xmlfile->GetName());
  }

  next = TString(env_par->GetValue("ESPRIPara","")).Tokenize(" ");
  while(( xmlfile = (TObjString *)next())) {
    ESPRIPara->LoadParameter((char*)xmlfile->GetName());
  }

  next = TString(env_par->GetValue("ESPRIUserPara","")).Tokenize(" ");
  while(( xmlfile = (TObjString *)next())) {
    ESPRIUserPara->LoadParameter((char*)xmlfile->GetName());
  }

  // Load coincidence register
  TArtCalibCoin *CalibCoin = 0;
  CalibCoin=new TArtCalibCoin;
  CalibCoin->SetAddress(85);
  // Load Plastic Detectors
  TArtCalibPlastic *CalibPlastic = new TArtCalibPlastic();
  // Load PAC and FocalPlane
  TArtCalibPPAC *CalibPPAC = new TArtCalibPPAC();
  TArtCalibFocalPlane *CalibFocalPlane = new TArtCalibFocalPlane();
  // Load IC
  TArtCalibIC *CalibIC = new TArtCalibIC();
  // Load Drift Chambers
  TArtCalibBDC1Hit   *CalibBDC1Hit   = new TArtCalibBDC1Hit();
  TArtCalibSimpleBDC1Track *CalibBDC1Track = new TArtCalibSimpleBDC1Track();
  TArtCalibBDC2Hit   *CalibBDC2Hit   = new TArtCalibBDC2Hit();
  TArtCalibSimpleBDC2Track *CalibBDC2Track = new TArtCalibSimpleBDC2Track();

  //TArtCalibSimpleFDC1Track *CalibSimpleFDC1Track;
  TArtCalibSimpleFDC2Track *CalibSimpleFDC2Track;
  //TArtCalibFDC1Track *CalibFDC1Track;
  TArtCalibFDC0Track *CalibFDC0Track;
  TArtCalibSimpleFDC0Track *CalibSimpleFDC0Track;
  TArtCalibFDC2Track *CalibFDC2Track;
  //TArtCalibFDC1Hit   *CalibFDC1Hit   = new TArtCalibFDC1Hit();
  TArtCalibFDC0Hit   *CalibFDC0Hit   = new TArtCalibFDC0Hit();
  TArtCalibFDC2Hit   *CalibFDC2Hit   = new TArtCalibFDC2Hit();

  TArtCalibSILICONS *CalibSILICONS = new TArtCalibSILICONS();

  // Load ESPRI
  TArtCalibRNaI *CalibESPRI_NaI = new TArtCalibRNaI();
  TArtCalibTDCHit *CalibESPRI_tdc = new TArtCalibTDCHit();
  TArtCalibFADC *CalibESPRI_fadc = new TArtCalibFADC();
  TArtCalibRDC *CalibESPRI_rdc = new TArtCalibRDC();
  TArtCalibPlas *CalibESPRI_plas = new TArtCalibPlas();

  if(kFDCs_full){
    //CalibFDC1Track = new TArtCalibFDC1Track();
    CalibFDC0Track = new TArtCalibFDC0Track();
    CalibFDC2Track = new TArtCalibFDC2Track();
  } else {
    CalibSimpleFDC0Track = new TArtCalibSimpleFDC0Track();
    CalibSimpleFDC2Track = new TArtCalibSimpleFDC2Track();
  }

  // Load Hodoscope
  TArtCalibHODPla *CalibHODPla = new TArtCalibHODPla();
  // Load NEBULA
  TArtCalibNEBULA *CalibNEBULA = new TArtCalibNEBULA();

  // Load DALI
  
  TArtCalibDALI *CalibDALI = NULL;
  if(kDALI){
    CalibDALI = new TArtCalibDALI();
  }
  // Load Brho calculation tools
  //  TArtRecoFragment *RecoFragment = new TArtRecoFragment();
  //Load Event Info

  // Load WINDS/PANDORA
  TArtCalibWINDSPla *CalibWINDS = new TArtCalibWINDSPla; //must be called after parameter is constructed

  cout << "   CALTREE-Info : Load TDC Distribution" << endl;
  if(kFDCs_full) {
    //LoadDCTDCDistributionFull((char*)env_par->GetValue("TDCDistribution",""),CalibBDC1Track,CalibBDC2Track,CalibFDC1Track,CalibFDC2Track);
    LoadDCTDCDistributionFull((char*)env_par->GetValue("TDCDistribution",""),CalibBDC1Track,CalibBDC2Track,CalibFDC0Track,CalibFDC2Track);
  } else if(kFDCs || kBEAM) {
    //LoadDCTDCDistributionFull((char*)env_par->GetValue("TDCDistribution",""),CalibBDC1Track,CalibBDC2Track,CalibSimpleFDC1Track,CalibSimpleFDC2Track);
    //LoadDCTDCDistributionFull((char*)env_par->GetValue("TDCDistribution",""),CalibBDC1Track,CalibBDC2Track,CalibSimpleFDC0Track,CalibSimpleFDC2Track);    
	LoadDCTDCDistributionFull((char*)"/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/db/dc/S012DCTDCDistribution_10Be.root",CalibBDC1Track,CalibBDC2Track,CalibSimpleFDC0Track,CalibSimpleFDC2Track);    
  }

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
  //  exit(0);
  //  Double_t hodo_coeffcalib[NUMBER_OF_HODO][2];
  //  Double_t TempA,TempB;
  //  std::ifstream HodoCalibFile("/home/psp17/exp/exp1705_psp17/anaroot/users/convdev/zrecal_hodo.dat",std::ios::in);
  //  if(HodoCalibFile.is_open())
  //    {
  //      for (Int_t ID = 0; ID < NUMBER_OF_HODO; ID++)
  //	{
  //	  HodoCalibFile >> TempA >> TempB;
  //	  hodo_coeffcalib[ID][0] = TempA;
  //	  hodo_coeffcalib[ID][1] = TempB;
  //	}
  //      HodoCalibFile.close();
  //    }
  //  else std::cerr << "Error:: The File : /home/psp17/exp/exp1705_psp17/anaroot/users/convdev/zrecal_hodo.dat was not found" << std::endl;


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

  const TString FileNameBody = FileName;
  FileNameBody(0,FileNameBody.Last('/')+1) = "";
  const TString RootFilenameBody  = rootfilesubpath + (TString)FileName ;
  const TString TmpRootFilenameBody  =  (TString)"/tmp/" + (TString)FileNameBody ;

  system(TString("rm -vf ")+TmpRootFilenameBody+"*.root");

  // MAIN Tree
  const char *TreeName = "CalTree";

  TFile *fout_MAIN = NULL;
  TTree *tree_MAIN = NULL;
  if(kMAIN){
    fout_MAIN = new TFile(TmpRootFilenameBody + (TString)"_MAIN.root" ,"recreate");
    tree_MAIN = new TTree(TreeName,"Analysis Tree MAIN");
    tree_MAIN->AutoSave("SaveSelf");
    tree_MAIN->SetAutoSave(1e5);
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

  // PANDORA Analog (WINDS) Tree

  TFile *fout_PANDORA = NULL;
  TTree *tree_PANDORA = NULL;
  if(kPANDORA){
    fout_PANDORA = new TFile(TmpRootFilenameBody + (TString)"_PANDORA_Analog.root","recreate");
    tree_PANDORA = new TTree(TreeName+(TString)"PANDORA","Analysis Tree PANDORA Analog");
    tree_PANDORA->AutoSave("SaveSelf");
    tree_PANDORA->SetAutoSave(1e5);
  }

  // DALI Tree

  TFile *fout_DALI = NULL;
  TTree *tree_DALI = NULL;
  if(kDALI){
    fout_DALI = new TFile(TmpRootFilenameBody + (TString)"_DALI.root","recreate");
    tree_DALI = new TTree(TreeName+(TString)"DALI","Analysis Tree DALI");
    //  tree_DALI->SetFile(fout_DALI);
    tree_DALI->AutoSave("SaveSelf");
    tree_DALI->SetAutoSave(1e5);
  }

  // FDC Tree

  TFile *fout_FDC = NULL;
  TTree *tree_FDC = NULL;
  if(kFDCs||kFDCs_full){
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

  // BEAM Tree

  TFile *fout_BEAM = NULL;
  TTree *tree_BEAM = NULL;
  if(kBEAM){
    fout_BEAM = new TFile(TmpRootFilenameBody + (TString)"_BEAM.root","recreate");
    tree_BEAM = new TTree(TreeName+(TString)"BEAM","Analysis Tree BEAM");
    //  tree_BEAM->SetFile(fout_BEAM);
    tree_BEAM->AutoSave("SaveSelf");
    tree_BEAM->SetAutoSave(1e5);
  }

  // Beginning of header

  // Variables
  Long64_t EventNumber = 0;
  Int_t RunNumber = -1;
  Int_t CoincidenceTrigger;
  //unsigned int CoincidenceTrigger;

  Double_t F3_Charge,F5_Charge,F7_Charge,F13_Charge,SBV_Charge;
  Double_t F3_Time,F5_Time,F7_Time,F13_Time;
  ////////////////////////////////////////////////////////
  Double_t F3_LTCal,F3_RTCal;
  Double_t F5_LTRaw,F7_LTRaw,SBT1_LTRaw,SBT2_LTRaw; //
  Double_t F5_RTRaw,F7_RTRaw,SBT1_RTRaw,SBT2_RTRaw; //
  Double_t F5_LQRaw,F7_LQRaw,SBT1_LQRaw,SBT2_LQRaw; //
  Double_t F5_RQRaw,F7_RQRaw,SBT1_RQRaw,SBT2_RQRaw; //
  Double_t F5_LTCal,F7_LTCal,SBT1_LTCal,SBT2_LTCal; //
  Double_t F5_RTCal,F7_RTCal,SBT1_RTCal,SBT2_RTCal; //
  Double_t F5_LTSlw,F7_LTSlw,SBT1_LTSlw,SBT2_LTSlw; //
  Double_t F5_RTSlw,F7_RTSlw,SBT1_RTSlw,SBT2_RTSlw; //
  Double_t F7_TResolution,F13_TResolution; //
  Double_t TOFF3F7,TOFF7F13; //
  ////////////////////////////////////////////////////////

  Double_t F3_TimeDiff,F5_TimeDiff,F7_TimeDiff,F13_TimeDiff;
  Double_t F51A_X,F51A_Y,F51B_X,F51B_Y,F52A_X,F52A_Y,F52B_X,F52B_Y;
  Double_t F5X,F5Y,F5B,F5A;
  Double_t BDC1_X,BDC1_Y,BDC2_X,BDC2_Y;
  Double_t BDC1_ThetaX,BDC1_ThetaY,BDC2_ThetaX,BDC2_ThetaY;
  Double_t Target_X,Target_Y,Target_ThetaX,Target_ThetaY; // Value at the entrance
  //Double_t FDC1_X,FDC1_Y,FDC1_ThetaX,FDC1_ThetaY;
  Double_t FDC0_X,FDC0_Y,FDC0_ThetaX,FDC0_ThetaY;
  Double_t FDC2_X,FDC2_Y,FDC2_ThetaX,FDC2_ThetaY;
  Double_t SAMURAI_Brho,SAMURAI_FL,BetaF7F13,ToF_SBTTarget,GammaF7F13;
  Double_t F7IC_E ;

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

  // SILICONS
  vector <Int_t>   *Silicons_ID = new vector <Int_t>();
  vector <Double_t> *Silicons_X = new vector <Double_t>();
  vector <Double_t> *Silicons_Y = new vector <Double_t>();
  vector <Double_t> *Silicons_Z = new vector <Double_t>();
  vector <Double_t> *Silicons_Time = new vector <Double_t>();
  vector <Double_t> *Silicons_Energy = new vector <Double_t>();
  Int_t Silicons_Multiplicity = 0;

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

  // PANDORA
  ULong64_t              TimeStamp ;
  vector <Int_t>	*Pandora_ID	     = new vector<Int_t>(); 
  //  vector <Long64_t>	*Pandora_TimeStamp   = new vector<Long64_t>();
  vector <Double_t>	*Pandora_Time_UP     = new vector<Double_t>();
  vector <Int_t>	*Pandora_Time_Raw_UP = new vector<Int_t>();
  vector <Double_t>	*Pandora_Time_DW     = new vector<Double_t>();
  vector <Int_t>	*Pandora_Time_Raw_DW = new vector<Int_t>();

  // DALI
  vector <Double_t>	*DALI_Energy		    = new vector <Double_t>();
  vector <Double_t>	*DALI_CosTheta		    = new vector<Double_t>();
  vector <Double_t>	*DALI_Time		    = new vector<Double_t>();
  // vector <Double_t> *DALI_EnergyDopplerCorrected = new vector<Double_t>();
  vector <Int_t>	*DALI_ID		    = new vector <Int_t>();
  vector <Double_t>	*DALI_Layer		    = new vector<Double_t>();
  vector <Double_t>	*DALI_X			    = new vector<Double_t>();
  vector <Double_t>	*DALI_Y			    = new vector<Double_t>();
  vector <Double_t>	*DALI_Z			    = new vector<Double_t>();
  vector <TVector3>	*DALI_Pos		    = new vector<TVector3>();
   
  //void Get_Branch_SAMURAI(TChain *tree){ // DO NOT SUPPRESS THIS COMMENT

  if(kMAIN){
    tree_MAIN->Branch("RunNumber",&RunNumber);
    tree_MAIN->Branch("EventNumber",&EventNumber);
    //Triggers
    tree_MAIN->Branch("CoincidenceTrigger",&CoincidenceTrigger);
    tree_MAIN->Branch("TimeStamp",&TimeStamp);
  }

  //Beam
  if(kBEAM){
    tree_BEAM->Branch("RunNumber",&RunNumber);
    tree_BEAM->Branch("EventNumber",&EventNumber);
    tree_BEAM->Branch("F3_Charge",&F3_Charge);
    tree_BEAM->Branch("F3_Time",&F3_Time);
    tree_BEAM->Branch("F3_TimeDiff",&F3_TimeDiff);
    tree_BEAM->Branch("F5_Charge",&F5_Charge);
    tree_BEAM->Branch("F5_Time",&F5_Time);
    tree_BEAM->Branch("F5_TimeDiff",&F5_TimeDiff);
    tree_BEAM->Branch("F7_Charge",&F7_Charge);
    tree_BEAM->Branch("F7_Time",&F7_Time);
    tree_BEAM->Branch("F7_TimeDiff",&F7_TimeDiff);
    tree_BEAM->Branch("F13_Charge",&F13_Charge);
    tree_BEAM->Branch("F13_Time",&F13_Time);
    tree_BEAM->Branch("F13_TimeDiff",&F13_TimeDiff);

    ///////////////////////////////////////////////////////////////////
    tree_BEAM->Branch("F5_LTRaw",&F5_LTRaw);
    tree_BEAM->Branch("F7_LTRaw",&F7_LTRaw);
    tree_BEAM->Branch("SBT1_LTRaw",&SBT1_LTRaw);
    tree_BEAM->Branch("SBT2_LTRaw",&SBT2_LTRaw);
    tree_BEAM->Branch("F5_RTRaw",&F5_RTRaw);
    tree_BEAM->Branch("F7_RTRaw",&F7_RTRaw);
    tree_BEAM->Branch("SBT1_RTRaw",&SBT1_RTRaw);
    tree_BEAM->Branch("SBT2_RTRaw",&SBT2_RTRaw);
    tree_BEAM->Branch("F5_LQRaw",&F5_LQRaw);
    tree_BEAM->Branch("F7_LQRaw",&F7_LQRaw);
    tree_BEAM->Branch("SBT1_LQRaw",&SBT1_LQRaw);
    tree_BEAM->Branch("SBT2_LQRaw",&SBT2_LQRaw);
    tree_BEAM->Branch("F5_RQRaw",&F5_RQRaw);
    tree_BEAM->Branch("F7_RQRaw",&F7_RQRaw);
    tree_BEAM->Branch("SBT1_RQRaw",&SBT1_RQRaw);
    tree_BEAM->Branch("SBT2_RQRaw",&SBT2_RQRaw);
    tree_BEAM->Branch("SBV_Charge",&SBV_Charge);
    
    //    tree_BEAM->Branch("F3_LTCal",&F3_LTCal);
    //    tree_BEAM->Branch("F5_LTCal",&F5_LTCal);
    //    tree_BEAM->Branch("F7_LTCal",&F7_LTCal);
    //    tree_BEAM->Branch("SBT1_LTCal",&SBT1_LTCal);
    //    tree_BEAM->Branch("SBT2_LTCal",&SBT2_LTCal);
    //    tree_BEAM->Branch("F3_RTCal",&F3_RTCal);
    //    tree_BEAM->Branch("F5_RTCal",&F5_RTCal);
    //    tree_BEAM->Branch("F7_RTCal",&F7_RTCal);
    //    tree_BEAM->Branch("SBT1_RTCal",&SBT1_RTCal);
    //    tree_BEAM->Branch("SBT2_RTCal",&SBT2_RTCal);
    //
    //    tree_BEAM->Branch("F5_LTSlw",&F5_LTSlw);
    //    tree_BEAM->Branch("F7_LTSlw",&F7_LTSlw);
    //    tree_BEAM->Branch("SBT1_LTSlw",&SBT1_LTSlw);
    //    tree_BEAM->Branch("SBT2_LTSlw",&SBT2_LTSlw);
    //    tree_BEAM->Branch("F5_RTSlw",&F5_RTSlw);
    //    tree_BEAM->Branch("F7_RTSlw",&F7_RTSlw);
    //    tree_BEAM->Branch("SBT1_RTSlw",&SBT1_RTSlw);
    //    tree_BEAM->Branch("SBT2_RTSlw",&SBT2_RTSlw);
    
    tree_BEAM->Branch("F7_TResolution",&F7_TResolution);
    tree_BEAM->Branch("F13_TResolution",&F13_TResolution);
    tree_BEAM->Branch("TOFF3F7",&TOFF3F7);
    tree_BEAM->Branch("TOFF7F13",&TOFF7F13);
    ///////////////////////////////////////////////////////////////////

    tree_BEAM->Branch("BetaF7F13",&BetaF7F13);
    tree_BEAM->Branch("GammaF7F13",&GammaF7F13);

    tree_BEAM->Branch("F51A_X",&F51A_X);
    tree_BEAM->Branch("F51A_Y",&F51A_Y);
    tree_BEAM->Branch("F51B_X",&F51B_X);
    tree_BEAM->Branch("F51B_Y",&F51B_Y);
    tree_BEAM->Branch("F52A_X",&F52A_X);
    tree_BEAM->Branch("F52A_Y",&F52A_Y);
    tree_BEAM->Branch("F52B_X",&F52B_X);
    tree_BEAM->Branch("F52B_Y",&F52B_Y);

    tree_BEAM->Branch("F5X",&F5X);
    tree_BEAM->Branch("F5Y",&F5Y);
    tree_BEAM->Branch("F5A",&F5A);
    tree_BEAM->Branch("F5B",&F5B);

    tree_BEAM->Branch("F7IC_E",&F7IC_E);

    tree_BEAM->Branch("BDC1_X",&BDC1_X);
    tree_BEAM->Branch("BDC1_Y",&BDC1_Y);
    tree_BEAM->Branch("BDC1_ThetaX",&BDC1_ThetaX);
    tree_BEAM->Branch("BDC1_ThetaY",&BDC1_ThetaY);
    tree_BEAM->Branch("BDC2_X",&BDC2_X);
    tree_BEAM->Branch("BDC2_Y",&BDC2_Y);
    tree_BEAM->Branch("BDC2_ThetaX",&BDC2_ThetaX);
    tree_BEAM->Branch("BDC2_ThetaY",&BDC2_ThetaY);
    tree_BEAM->Branch("Target_X",&Target_X);
    tree_BEAM->Branch("Target_Y",&Target_Y);
    tree_BEAM->Branch("Target_ThetaX",&Target_ThetaX);
    tree_BEAM->Branch("Target_ThetaY",&Target_ThetaY);
  }

  //SAMURAI
  if(kFDCs||kFDCs_full){
    tree_FDC->Branch("RunNumber",&RunNumber);
    tree_FDC->Branch("EventNumber",&EventNumber);
    // tree_FDC->Branch("FDC1_X",&FDC1_X);
    // tree_FDC->Branch("FDC1_Y",&FDC1_Y);
    // tree_FDC->Branch("FDC1_ThetaX",&FDC1_ThetaX);
    // tree_FDC->Branch("FDC1_ThetaY",&FDC1_ThetaY);
    tree_FDC->Branch("FDC0_X",&FDC0_X);
    tree_FDC->Branch("FDC0_Y",&FDC0_Y);
    tree_FDC->Branch("FDC0_ThetaX",&FDC0_ThetaX);
    tree_FDC->Branch("FDC0_ThetaY",&FDC0_ThetaY);
    tree_FDC->Branch("FDC2_X",&FDC2_X);
    tree_FDC->Branch("FDC2_Y",&FDC2_Y);
    tree_FDC->Branch("FDC2_ThetaX",&FDC2_ThetaX);
    tree_FDC->Branch("FDC2_ThetaY",&FDC2_ThetaY);
    tree_FDC->Branch("SAMURAI_Brho",&SAMURAI_Brho);
    tree_FDC->Branch("SAMURAI_Flight_Length",&SAMURAI_FL);
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

  // PANDORA
  if(kPANDORA){
    cout << "Hello you opened the BOX !" << endl;
    tree_PANDORA->Branch("RunNumber",&RunNumber);
    tree_PANDORA->Branch("EventNumber",&EventNumber);
    tree_PANDORA->Branch("TimeStamp",&TimeStamp);
    tree_PANDORA->Branch("Pandora_ID",&Pandora_ID);
    //    tree_PANDORA->Branch("Pandora_TimeStamp",&Pandora_TimeStamp);
    tree_PANDORA->Branch("Pandora_Time_UP",&Pandora_Time_UP);    
    tree_PANDORA->Branch("Pandora_Time_Raw_UP",&Pandora_Time_Raw_UP);    
    tree_PANDORA->Branch("Pandora_Time_DOWN",&Pandora_Time_DW);    
    tree_PANDORA->Branch("Pandora_Time_Raw_DOWN",&Pandora_Time_Raw_DW);    
  }

  //DALI
  if(kDALI){
    tree_DALI->Branch("RunNumber",&RunNumber);
    tree_DALI->Branch("EventNumber",&EventNumber);
    tree_DALI->Branch("DALI_ID",&DALI_ID);
    tree_DALI->Branch("DALI_Energy",&DALI_Energy);
    tree_DALI->Branch("DALI_Time",&DALI_Time);
    tree_DALI->Branch("DALI_CosTheta",&DALI_CosTheta);
    tree_DALI->Branch("DALI_Layer",&DALI_Layer);
    tree_DALI->Branch("DALI_X",&DALI_X);
    tree_DALI->Branch("DALI_Y",&DALI_Y);
    tree_DALI->Branch("DALI_Z",&DALI_Z);
    tree_DALI->Branch("DALI_Pos",&DALI_Pos);
    //  tree_DALI->Branch("DALI_EnergyDopplerCorrected",&DALI_EnergyDopplerCorrected);
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
    tree_MAIN->SetAlias("Trig_BxTEL","CoincidenceTrigger & 4");
    tree_MAIN->SetAlias("Trig_BxESPRI","CoincidenceTrigger & 8");
    tree_MAIN->SetAlias("Trig_BxHODP","CoincidenceTrigger & 16");
    tree_MAIN->SetAlias("Trig_BxHODF","CoincidenceTrigger & 32");
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
  while(EventStore->GetNextEvent() 
        && EventNumber < MaxEventNumber
        )
    {

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

      CalibPlastic->ClearData();
      CalibBDC1Hit->ClearData();
      CalibBDC1Track->ClearData();
      CalibBDC2Hit->ClearData();
      CalibBDC2Track->ClearData();
      // CalibFDC1Hit->ClearData();
      CalibFDC0Hit->ClearData();
      CalibFDC2Hit->ClearData();
      CalibHODPla->ClearData();
      if(CalibDALI) CalibDALI->ClearData();
      CalibWINDS->ClearData();
      CalibSILICONS->ClearData();
      //      RecoFragment->ClearData();
      //      CalibPPAC->ClearData();
      CalibESPRI_NaI->ClearData();
      CalibESPRI_tdc->ClearData();
      CalibESPRI_rdc->ClearData();
      CalibESPRI_fadc->ClearData();
      CalibESPRI_plas->ClearData();


      if(kFDCs)
	{
	  //CalibSimpleFDC1Track->ClearData();
	  CalibSimpleFDC0Track->ClearData();
	  CalibSimpleFDC2Track->ClearData();
	}
      else if(kFDCs_full)
	{
	  //CalibFDC1Track->ClearData();
	  CalibFDC0Track->ClearData();
	  CalibFDC2Track->ClearData();
	}
      //      CalibPID->ClearData();
      CalibFocalPlane->ClearData();


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
	  case    PLAT: if(kBEAM) CalibPlastic->LoadData(seg); break;
	  case STOPPLA: if(kBEAM) CalibPlastic->LoadData(seg); break;
	    //	  case      RF: if(kBEAM) CalibPlastic->LoadData(seg); break; //??
	  case    PLAQ: if(kBEAM) CalibPlastic->LoadData(seg); break;
	  case     COIN: CalibCoin->LoadData(seg); break;	// included to see coin. trigger
	  case       BDC: if(kBEAM || kFDCs||kFDCs_full) CalibBDC1Hit->LoadData(seg); break;
	    // case      FDC1: if(kFDCs||kFDCs_full) CalibFDC1Hit->LoadData(seg); break;
	  case      FDC0: if(kFDCs||kFDCs_full) CalibFDC0Hit->LoadData(seg); break;
	  case      FDC2: if(kFDCs||kFDCs_full) CalibFDC2Hit->LoadData(seg); break;
	  case     HODFQ: if(kHODO)  CalibHODPla->LoadData(seg);  break;
	  case     HODPQ: if(kHODO)  CalibHODPla->LoadData(seg);  break;
	    //	  case    HODPQ2: if(kHODO) CalibHODPla->LoadData(seg); break;
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
	  case    WINDSQ: if(kPANDORA) CalibWINDS->LoadData(seg); break;
	  case    WINDST: if(kPANDORA) CalibWINDS->LoadData(seg); break;
	    //	  case       TEL: if(kSILI) CalibSILICONS->LoadData(seg); break;
	  default:  break;
	  }
	} else if(device== BIGRIPS){
	  switch(detector) {
	    //case     COIN: CalibCoin->LoadData(seg); break;	// included to see coin. trigger
	    //case   PPACT: if(kBEAM) CalibPPAC->LoadData(seg); break;
	    //case   PPACQ: if(kBEAM) CalibPPAC->LoadData(seg); break;
	  default:  break;
	  }
	} else {
	  switch(detector) {
	    case     COIN: CalibCoin->LoadData(seg); break;
	  case    DALIA: if(kDALI && CalibDALI) CalibDALI->LoadData(seg); break;
          case    DALIT: if(kDALI && CalibDALI) CalibDALI->LoadData(seg); break;
	  default:  break;
	  }
	}

      }

      // Coincidence reg

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
      if(kBEAM){
	//plastics
	CalibPlastic->ReconstructData();
	TArtPlastic *PlasticF3 = CalibPlastic->FindPlastic((char*)"F3pl");
	TArtPlastic *PlasticF5 = CalibPlastic->FindPlastic((char*)"F5pl");
	TArtPlastic *PlasticF7 = CalibPlastic->FindPlastic((char*)"F7pl");
	TArtPlastic *PlasticSBT1 = CalibPlastic->FindPlastic((char*)"F13pl-1");
	TArtPlastic *PlasticSBT2 = CalibPlastic->FindPlastic((char*)"F13pl-2");
        TArtPlastic *PlasticSBV = CalibPlastic->FindPlastic((char*)"SBV");
        TArtPlastic *PlasticSBV2 = CalibPlastic->FindPlastic((char*)"SBV2");

	F3_Charge = NAN;
	F3_Time = NAN;
	F5_Charge = NAN;
	F5_Time = NAN;
	F5_TimeDiff = NAN;
	F7_Charge = NAN;
	F7_Time = NAN;
	F13_Charge = NAN;
	F13_Time = NAN;
	BetaF7F13 = NAN;
	GammaF7F13 = NAN;

	////////////////////////////////////////////////////////////

	F5_LTRaw = NAN;
	F7_LTRaw = NAN;
	SBT1_LTRaw = NAN;
	SBT2_LTRaw = NAN;
	F5_RTRaw = NAN;
	F7_RTRaw = NAN;
	SBT1_RTRaw = NAN;
	SBT2_RTRaw = NAN;
	F5_LQRaw = NAN;
	F7_LQRaw = NAN;
	SBT1_LQRaw = NAN;
	SBT2_LQRaw = NAN;
	F5_RQRaw = NAN;
	F7_RQRaw = NAN;
	SBT1_RQRaw = NAN;
	SBT2_RQRaw = NAN;

	F3_LTCal = NAN;
	F5_LTCal = NAN;
	F7_LTCal = NAN;
	SBT1_LTCal = NAN;
	SBT2_LTCal = NAN;
	F3_RTCal = NAN;
	F5_RTCal = NAN;
	F7_RTCal = NAN;
	SBT1_RTCal = NAN;
	SBT2_RTCal = NAN;

	F5_LTSlw = NAN;
	F7_LTSlw = NAN;
	SBT1_LTSlw = NAN;
	SBT2_LTSlw = NAN;
	F5_RTSlw = NAN;
	F7_RTSlw = NAN;
	SBT1_RTSlw = NAN;
	SBT2_RTSlw = NAN;

	F7_TResolution = NAN;
	F13_TResolution = NAN;
	TOFF3F7 = NAN;
	TOFF7F13 = NAN;

	//cout << "time: " << PlasticF7->GetTLRaw() << "\t" << PlasticF7->GetTRRaw() << ", charge: " << PlasticF7->GetQLRaw() << "\t" << PlasticF7->GetQRRaw() << endl;

	if(PlasticF3){
	  F3_Charge = PlasticF3->GetQAveRaw();
	  //F3_Time = PlasticF3->GetTimeSlew() + 25.91;
	  F3_Time = PlasticF3->GetTimeSlew() ;

	  F3_LTCal = PlasticF3->GetTimeL();
	  F3_RTCal = PlasticF3->GetTimeR();
	  //F3_Time  = (F3_LTCal + F3_RTCal)/2.;
	}

	if(PlasticF5){
	  F5_Charge = PlasticF5->GetQAveRaw();
	  //F5_Time = PlasticF5->GetTimeSlew();

	  F5_LTRaw = PlasticF5->GetTLRaw();
	  F5_RTRaw = PlasticF5->GetTRRaw();
	  F5_LQRaw = PlasticF5->GetQLRaw();
	  F5_RQRaw = PlasticF5->GetQRRaw();
	  F5_LTCal = PlasticF5->GetTimeL();
	  F5_RTCal = PlasticF5->GetTimeR();
	  // F5_LTSlw = PlasticF5->GetTimeLSlew();
	  //F5_RTSlw = PlasticF5->GetTimeRSlew();
	  //F5_Time = (F5_LTSlw + F5_RTSlw)/2.+298.472-2.08134;
	  F5_LTSlw = F5_LTCal-97.03/sqrt(F5_LQRaw);
	  F5_RTSlw = F5_RTCal-68.48/sqrt(F5_RQRaw);
	  F5_Time = (F5_LTSlw + F5_RTSlw)/2.+321.61066;

	}
	
	if(PlasticF7){
	  F7_Charge = PlasticF7->GetQAveRaw();
	  //F7_Time = PlasticF7->GetTimeSlew() - 552.1; // Test of offset to have a ToF F7-F13
	  F7_Time = PlasticF7->GetTimeSlew(); // Test of offset to have a ToF F7-F13

	  F7_LTRaw = PlasticF7->GetTLRaw();
	  F7_RTRaw = PlasticF7->GetTRRaw();
	  F7_LQRaw = PlasticF7->GetQLRaw();
	  F7_RQRaw = PlasticF7->GetQRRaw();
	  F7_LTCal = PlasticF7->GetTimeL();
	  F7_RTCal = PlasticF7->GetTimeR();
	 
 
	  F7_LTSlw = F7_LTCal-77.36/sqrt(F7_LQRaw);
	  F7_RTSlw = F7_RTCal-68.17/sqrt(F7_RQRaw);
	  //F7_Time = (F7_LTSlw + F7_RTSlw)/2.+318.95266;//
	  if(F5_Time < -9000.)
	    F5_Time = F7_Time;
	}

	if(PlasticSBT1){

	  SBT1_LTRaw = PlasticSBT1->GetTLRaw();
	  SBT1_RTRaw = PlasticSBT1->GetTRRaw();
	  SBT1_LQRaw = PlasticSBT1->GetQLRaw();
	  SBT1_RQRaw = PlasticSBT1->GetQRRaw();
	  SBT1_LTCal = PlasticSBT1->GetTimeL();
	  SBT1_RTCal = PlasticSBT1->GetTimeR();
	// SBT1_LTSlw = PlasticSBT1->GetTimeLSlew();
	// SBT1_RTSlw = PlasticSBT1->GetTimeRSlew();
          SBT1_LTSlw = SBT1_LTCal-54.74/sqrt(SBT1_LQRaw);
	  SBT1_RTSlw = SBT1_RTCal-50.62/sqrt(SBT1_RQRaw);


	}
	if(PlasticSBT2){

	  SBT2_LTRaw = PlasticSBT2->GetTLRaw();
	  SBT2_RTRaw = PlasticSBT2->GetTRRaw();
	  SBT2_LQRaw = PlasticSBT2->GetQLRaw();
	  SBT2_RQRaw = PlasticSBT2->GetQRRaw();
	  SBT2_LTCal = PlasticSBT2->GetTimeL();
	  SBT2_RTCal = PlasticSBT2->GetTimeR();
	  //	  SBT2_LTSlw = PlasticSBT2->GetTimeLSlew();
	  //SBT2_RTSlw = PlasticSBT2->GetTimeRSlew();
	  SBT2_LTSlw = SBT2_LTCal-33.85/sqrt(SBT2_LQRaw);
	  SBT2_RTSlw = SBT2_RTCal-55.44/sqrt(SBT2_RQRaw);


	}

        	if(PlasticSBV){
		  //	  if(SBV_Charge <100 ){
	          //  if (PlasticSBV->GetQLRaw()> 200) 
                           SBV_Charge = PlasticSBV->GetQRRaw();
		    //	            if (PlasticSBV->GetQRRaw()> 200) SBV_Charge = PlasticSBV->GetQRRaw();
                    
		    //     }

		}

	if(PlasticSBT1 && PlasticSBT2){
	  F13_Charge = ( PlasticSBT1->GetQAveRaw() + PlasticSBT2->GetQAveRaw() ) / 2.;
	  F13_Time = ( PlasticSBT1->GetTimeSlew() + PlasticSBT2->GetTimeSlew() ) / 2.;
	  //F13_Time = ((SBT1_LTSlw + SBT1_RTSlw)/2. + (SBT2_LTSlw + SBT2_RTSlw)/2.)/2.+891.63-1.55335;
	}

	Double_t TOF_offset=336+235.983;// Be14 setting
	F7_TResolution = F7_Time - F5_Time;
	F13_TResolution = (SBT1_RTSlw + SBT1_LTSlw)/2. - (SBT2_RTSlw + SBT2_LTSlw)/2.;
	//TOFF3F7 = F7_Time - F3_Time;
	//TOFF7F13 = F13_Time - F7_Time;
	TOFF3F7 = (F7_Time + F5_Time)/2. - F3_Time;
	//TOFF7F13 = F13_Time - (F7_Time + F5_Time)/2.+TOF_offset;
	TOFF3F7 = F7_Time - F3_Time;
	TOFF7F13 = F13_Time - F7_Time+TOF_offset;


	//BetaF7F13 = Dist_F7F13 / F7_Time / 300.;
	BetaF7F13 = Dist_F7F13 / TOFF7F13 / 299.792;//in SAMURAI_4n exp, F7 time = (F5_Time + F7_Time)/2.
	GammaF7F13 = 1./sqrt(1. - BetaF7F13 * BetaF7F13);
	ToF_SBTTarget = Dist_SBTTarget / ( BetaF7F13 * 299.792); // ns

	if(PlasticF5){
	  if (PlasticF5->GetTLRaw() > 0 && PlasticF5->GetTLRaw()<65536 && PlasticF5->GetTRRaw() > 0 && PlasticF5->GetTRRaw()<65536)
	    {
	      F3_TimeDiff = PlasticF3->GetTimeRSlew() - PlasticF3->GetTimeLSlew();
	      //F5_TimeDiff = PlasticF5->GetTimeRSlew() - PlasticF5->GetTimeLSlew();
	      //F7_TimeDiff = PlasticF7->GetTimeRSlew() - PlasticF7->GetTimeLSlew();
	      //F7_TimeDiff = (PlasticF5->GetTLRaw() + PlasticF5->GetTRRaw())/2. - (PlasticF7->GetTLRaw() + PlasticF7->GetTRRaw())/2.; // for plastic resolution check
	      //F13_TimeDiff = (PlasticSBT1->GetTimeRSlew() - PlasticSBT1->GetTimeLSlew() + PlasticSBT2->GetTimeRSlew() - PlasticSBT2->GetTimeLSlew()) / 2.;
	      //F13_TimeDiff = (PlasticSBT1->GetTLRaw() + PlasticSBT1->GetTRRaw())/2. - (PlasticSBT2->GetTLRaw() + PlasticSBT2->GetTRRaw())/2.; // for plastic resolution check
	      F5_TimeDiff = F5_RTSlw - F5_LTSlw;
	      F7_TimeDiff = F7_RTSlw - F7_LTSlw;
	      F13_TimeDiff = (SBT1_RTSlw - SBT1_LTSlw + SBT2_RTSlw - SBT2_LTSlw)/2.;
	    }
	}

	//PPAC (F5)
	F51A_X = NAN;
	F51A_Y = NAN;
	F51B_X = NAN;
	F51B_Y = NAN;
	F52A_X = NAN;
	F52A_Y = NAN;
	F52B_X = NAN;
	F52B_Y = NAN;

	/*
	  CalibPPAC->ReconstructData();
	  TArtPPAC *PPAC_F51A = CalibPPAC->FindPPAC((char*)"F5PPAC-1A_s");
	  TArtPPAC *PPAC_F51B = CalibPPAC->FindPPAC((char*)"F5PPAC-1B_s");
	  TArtPPAC *PPAC_F52A = CalibPPAC->FindPPAC((char*)"F5PPAC-2A_s");
	  TArtPPAC *PPAC_F52B = CalibPPAC->FindPPAC((char*)"F5PPAC-2B_s");


	  if(PPAC_F51A){
	  F51A_X = PPAC_F51A->GetX();
	  F51A_Y = PPAC_F51A->GetY();
	  }
	  if(PPAC_F51B){
	  F51B_X = PPAC_F51B->GetX();
	  F51B_Y = PPAC_F51B->GetY();
	  }
	  if(PPAC_F52A){
	  F52A_X = PPAC_F52A->GetX();
	  F52A_Y = PPAC_F52A->GetY();
	  }
	  if(PPAC_F52B){
	  F52B_X = PPAC_F52B->GetX();
	  F52B_Y = PPAC_F52B->GetY();
	  }
	*/
	// PID
	// ==============================

	CalibFocalPlane->ReconstructData();
	TArtFocalPlane *tfpl;
	TVectorD *vec;
        tfpl = CalibFocalPlane->FindFocalPlane(5);
	F5X = F5Y = F5A = F5B = NAN;
	if(tfpl){vec=tfpl->GetOptVector(); F5X=(*vec)(0); F5A=(*vec)(1); F5Y=(*vec)(2); F5B=(*vec)(3);}

	// F7 ICB
	// ============== ICB ===========

	CalibIC->ReconstructData();
	TArtIC *BeamIonChamb = CalibIC->FindIC((char*)"F7IC");

	F7IC_E = NAN;
	if(BeamIonChamb) {
	  F7IC_E = BeamIonChamb->GetEnergyAvSum();
	}

	
      }
      
      if(kBEAM || kFDCs||kFDCs_full){
	//BDC1
	BDC1_X = NAN;
	BDC1_Y = NAN;
	BDC1_ThetaX = NAN;
	BDC1_ThetaY = NAN;
	CalibBDC1Hit->ReconstructData();
	CalibBDC1Track->ReconstructData();
	
	TClonesArray *BDC1Tracks = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Track");
	if (BDC1Tracks)
	  {
	    Int_t BDC1NumberOfTracks = BDC1Tracks->GetEntries();
	    Double_t TempXPosition, TempYPosition, TempChi2, MinChi2x = 1e6, MinChi2y = 1e6;

	    if (BDC1NumberOfTracks > 0)
	      {
		TArtDCTrack *TrackBDC1;

		for(Int_t i=0; i<BDC1NumberOfTracks; i++)
		  {
		    TrackBDC1 = (TArtDCTrack *)BDC1Tracks->At(i);

		    if(TrackBDC1)
		      {
			TempXPosition = TrackBDC1->GetPosition(0);
			TempYPosition = TrackBDC1->GetPosition(1);
			TempChi2 = TrackBDC1->GetChi2() / (Double_t)TrackBDC1->GetNDF();

			if(TempChi2 > 0 ){

			  if(TMath::Abs(TempXPosition) < 5000 && TempChi2<MinChi2x){
			    BDC1_X = TempXPosition;
			    BDC1_ThetaX = TMath::ATan(TrackBDC1->GetAngle(0));
			    MinChi2x = TempChi2;
			  }

			  if (TMath::Abs(TempYPosition) < 5000 && TempChi2<MinChi2y){
			    BDC1_Y = TempYPosition;
			    BDC1_ThetaY = TMath::ATan(TrackBDC1->GetAngle(1));
			    MinChi2y = TempChi2;
			  }
			}
		      }
		  }
	      }
	  }
	
	//BDC2
	BDC2_X = NAN;
	BDC2_Y = NAN;
	BDC2_ThetaX = NAN;
	BDC2_ThetaY = NAN;

	CalibBDC2Hit->ReconstructData();
	CalibBDC2Track->ReconstructData();

	TClonesArray *BDC2Tracks = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Track");
	if (BDC2Tracks)
	  {
	    Int_t BDC2NumberOfTracks = BDC2Tracks->GetEntries();
	    Double_t TempXPosition, TempYPosition, TempChi2, MinChi2x=1e6, MinChi2y=1e6;

	    if (BDC2NumberOfTracks > 0)
	      {
		TArtDCTrack *TrackBDC2;

		for(Int_t i=0; i<BDC2NumberOfTracks; i++)
		  {
		    TrackBDC2 = (TArtDCTrack *)BDC2Tracks->At(i);

		    if(TrackBDC2)
		      {
			TempXPosition = TrackBDC2->GetPosition(0);
			TempYPosition = TrackBDC2->GetPosition(1);
			TempChi2 = TrackBDC2->GetChi2() / (Double_t)TrackBDC2->GetNDF();

			if(TempChi2 > 0 ){
			  if(TMath::Abs(TempXPosition) < 5000 && TempChi2<MinChi2x){
			    BDC2_X = TempXPosition;
			    BDC2_ThetaX = TMath::ATan(TrackBDC2->GetAngle(0));
			    MinChi2x = TempChi2;
			  }
			  if (TMath::Abs(TempYPosition) < 5000 && TempChi2<MinChi2y){
			    BDC2_Y = TempYPosition;
			    BDC2_ThetaY = TMath::ATan(TrackBDC2->GetAngle(1));
			    MinChi2y = TempChi2;
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

	if(kBEAM){
	  tree_BEAM ->Fill();
	}

      } // END BEAM ANALYSIS
      
      
      if(kFDCs||kFDCs_full){
	// ============== FDC0 ================
	FDC0_X = NAN;
	FDC0_Y = NAN;
	FDC0_ThetaX = NAN;
	FDC0_ThetaY = NAN;

	if(kFDCs){
	  CalibFDC0Hit->ReconstructData();
	  CalibSimpleFDC0Track->ReconstructData();
	} else if(kFDCs_full){
	  CalibFDC0Hit->ReconstructData();
	  CalibFDC0Track->ReconstructData();
	}


	TClonesArray *FDC0Tracks = (TClonesArray *)sman->FindDataContainer("SAMURAIFDC0Track");
	if (FDC0Tracks)
	  {
	    Int_t FDC0NumberOfTracks = FDC0Tracks->GetEntries();
	    Double_t TempXPosition, TempYPosition, TempChi2, MinChi2x=1e6, MinChi2y=1e6;

	    if (FDC0NumberOfTracks > 0)
	      {
		TArtDCTrack *TrackFDC0;

		for(Int_t i=0; i<FDC0NumberOfTracks; i++)
		  {
		    TrackFDC0 = (TArtDCTrack *)FDC0Tracks->At(i);

		    if(TrackFDC0)
		      {
			TempXPosition = TrackFDC0->GetPosition(0);
			TempYPosition = TrackFDC0->GetPosition(1);
			TempChi2 = TrackFDC0->GetChi2() / (Double_t)TrackFDC0->GetNDF();

			if(TempChi2 > 0 ){
			  if(TMath::Abs(TempXPosition) < 5000 && TempChi2<MinChi2x){
			    FDC0_X = TempXPosition;
			    MinChi2x = TempChi2;
			  }
			  if (TMath::Abs(TempYPosition) < 5000 && TempChi2<MinChi2y){
			    FDC0_Y = TempYPosition;
			    MinChi2y = TempChi2;
			  }
			}
		      }
		  }

		if( TMath::Abs(Target_X)<100 && // 100mm for safety (can be used in most of the experiment ! to be ajusted ?
		    TMath::Abs(Target_Y)<100 && // 100mm for safety (can be used in most of the experiment ! to be ajusted ?
		    TMath::Abs(FDC0_X) < 5000 && TMath::Abs(FDC0_Y) < 5000 )
		  {
		    FDC0_ThetaX = TMath::ATan((FDC0_X - Target_X) / (Dist_BDC1FDC0-Dist_BDC1Target));
		    FDC0_ThetaY = TMath::ATan((FDC0_Y - Target_Y) / (Dist_BDC1FDC0-Dist_BDC1Target));
		  }
	      }
	  }


	// ============== FDC1 ================
	// 	FDC1_X = NAN;
	// 	FDC1_Y = NAN;
	// 	FDC1_ThetaX = NAN;
	// 	FDC1_ThetaY = NAN;

	// 	CalibFDC1Hit->ReconstructData();
	// if(kFDCs)
	// 	CalibSimpleFDC1Track->ReconstructData();
	// else if(kFDCs_full)
	// 	CalibFDC1Track->ReconstructData();

	// 	TClonesArray *FDC1Tracks = (TClonesArray *)sman->FindDataContainer((char*)"SAMURAIFDC1Track");
	// 	Int_t FDC1NumberOfTracks = -1;
	// 	Double_t Chi2_FDC1 = -1.;

	// 	if(FDC1Tracks) {
	// 	  FDC1NumberOfTracks = FDC1Tracks->GetEntries();
	// 	  if(FDC1NumberOfTracks > 0) { //Tracks are already sorted by chi2
	// 	    TArtDCTrack *FDC1Track = (TArtDCTrack *)FDC1Tracks->At(0);
	// 	    if(FDC1Track) {
	// 	      FDC1_X = FDC1Track->GetPosition(0);
	// 	      FDC1_Y = FDC1Track->GetPosition(1);
	// 	      Chi2_FDC1 = FDC1Track->GetChi2() / (Double_t)FDC1Track->GetNDF();


	// 	    }

	// 	    if( FDC1NumberOfTracks > 0 &&
	// 		TMath::Abs(Target_X)<100 && // 100mm for safety (can be used in most of the experiment ! to be ajusted ?
	// 		TMath::Abs(Target_Y)<100 && // 100mm for safety (can be used in most of the experiment ! to be ajusted ?
	// 		TMath::Abs(FDC1_X) < 5000 && TMath::Abs(FDC1_Y) < 5000 )
	// 	      {
	// 		FDC1_ThetaX = TMath::ATan((FDC1_X - Target_X) / (Dist_BDC1FDC1-Dist_BDC1Target));
	// 		FDC1_ThetaY = TMath::ATan((FDC1_Y - Target_Y) / (Dist_BDC1FDC1-Dist_BDC1Target));
	// 	      }
	// 	  }
	// 	}

	// ============== FDC2 ================


	FDC2_X = NAN;
	FDC2_Y = NAN;
	FDC2_ThetaX = NAN;
	FDC2_ThetaY = NAN;

	if(kFDCs){
	  CalibFDC2Hit->ReconstructData();
	  CalibSimpleFDC2Track->ReconstructData();
	} else if(kFDCs_full){
	  CalibFDC2Hit->ReconstructData();
	  CalibFDC2Track->ReconstructData();
	}

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


	// ============== Reconstruct Brho in SAMURAI ==============
        // now the target position is assumed at the center of MINOS
	SAMURAI_Brho = NAN;
	//if(TMath::Abs(FDC1_X) < 5000 && TMath::Abs(FDC1_Y) < 5000  &&
	if(TMath::Abs(FDC0_X) < 5000 && TMath::Abs(FDC0_Y) < 5000  &&
	   TMath::Abs(FDC2_X) < 5000 && TMath::Abs(FDC2_Y) < 5000)
	  {
	    //	    RecoFragment->ReconstructData();
	    //	    TArtFragment *Fragment = RecoFragment->GetFragment(0);
	    //	    if (Fragment)
	    Double_t x[] = {0,0,0,0,FDC2_X};
#ifdef w_tracking	    
	    SAMURAI_Brho = r_fit(x);//Fragment->GetBrho();
	    SAMURAI_FL   = l_fit(x);
#else
	    SAMURAI_Brho = NAN;
	    SAMURAI_FL   = NAN;
#endif

	    //	    cout << SAMURAI_Brho << endl;
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
		  //MODIF ALDRIC 21/11/2015
		  // if(TMath::Abs(NEBULAPla->GetPos(1)) < 1000 && !TMath::IsNaN(NEBULAPla->GetPos(1)))
		  //   {
		  //MODIF ALDRIC 19/11/2015
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
	    Neutron_Time->push_back(NEBULA_Time->at(i) - ToF_SBTTarget + Distance / 300.);
	    Neutron_ChargeUp->push_back(NEBULA_ChargeUp->at(i));
	    Neutron_ChargeDown->push_back(NEBULA_ChargeDown->at(i));
	    Neutron_Charge->push_back(NEBULA_Charge->at(i));
	    Neutron_IsNEBULA->push_back(true);
	    Neutron_Multiplicity++;
	  }

	tree_NEUT ->Fill();
      }

      if(kSILI){

	Silicons_X->clear();
	Silicons_Y->clear();
	Silicons_Z->clear();
	Silicons_ID->clear();
	Silicons_Time->clear();
	Silicons_Energy->clear();
	Silicons_Multiplicity = 0;

	CalibSILICONS->ReconstructData();
	TClonesArray *Sis = (TClonesArray *)sman->FindDataContainer("SILICONS");
	Double_t RefTime1 = 0;
	Double_t RefTime2 = 0;

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
      if(kPANDORA){
	Pandora_ID->clear();
	Pandora_Time_UP->clear();
	Pandora_Time_Raw_UP->clear();
	Pandora_Time_DW->clear();
	Pandora_Time_Raw_DW->clear();
	// Pandora_TimeStamp->clear();
       
	CalibWINDS->ReconstructData();
	TClonesArray *windsplas = (TClonesArray *)sman->FindDataContainer("WINDSPla");
	Long64_t tmptime1 = -1;
	Long64_t tmptime2 = -1;
	Double_t tmptime1_cal = NAN;
	Double_t tmptime2_cal = NAN;

    Long64_t ref1 = 0;
    Long64_t ref2 = 0;
    Long64_t ref3 = 0;

	for(int i=0;i<windsplas->GetEntries();i++){
	  TArtWINDSPla *pla = (TArtWINDSPla *)windsplas->At(i);
	  int ID = pla->GetID();
	  tmptime1 = -1;
	  tmptime2 = -1;
	  tmptime1_cal = NAN;
	  tmptime2_cal = NAN;

	  // Check which 1 or 2 is UP or DOWN ??
	  if(pla->GetT1Raw() > 0 &&
	     pla->GetT1Raw() < 40950 ){	
	    tmptime1 = pla->GetT1Raw();
	    tmptime1_cal = pla->GetTime1();
	  }
	  if(pla->GetT2Raw() > 0 &&
	     pla->GetT2Raw() < 40950){ 
	    tmptime2 = pla->GetT2Raw();
	    tmptime2_cal = pla->GetTime2();
	  }
      if(ID==73){
         ref1=tmptime1;
      }else if(ID==74){
         ref2=tmptime1;
      }else if(ID==75){
         ref3=tmptime1;
      }else{
	     Pandora_ID->push_back(ID);
	     Pandora_Time_Raw_UP->push_back(tmptime1);
	     Pandora_Time_Raw_DW->push_back(tmptime2);
	     //Pandora_Time_UP->push_back(tmptime1);
	     //Pandora_Time_DW->push_back(tmptime2);
      }
	  // if(ID=....) time_ref_cal = ... 
	}
	// loop over vectors, subtract ref
	 for(size_t i=0;i<Pandora_ID->size();i++){
        int tmp_id=(Pandora_ID -> at(i));
        if(tmp_id<16){
           Pandora_Time_UP->push_back(Pandora_Time_Raw_UP->at(i)-ref1);
           Pandora_Time_DW->push_back(Pandora_Time_Raw_DW->at(i)-ref1);

        }else if(tmp_id>23&&tmp_id<39){
           Pandora_Time_UP->push_back(Pandora_Time_Raw_UP->at(i)-ref3);
           Pandora_Time_DW->push_back(Pandora_Time_Raw_DW->at(i)-ref3);
        }else{
           Pandora_Time_UP->push_back(Pandora_Time_Raw_UP->at(i)-ref2);
           Pandora_Time_DW->push_back(Pandora_Time_Raw_DW->at(i)-ref2);
        }
     }
	// vector[i] -= ref ;
	//
	tree_PANDORA ->Fill();
      }


      // ============== DALI ==============
      if(kDALI && CalibDALI){
	DALI_ID->clear();
	DALI_Time->clear();
	DALI_Energy->clear();
	DALI_CosTheta->clear();
	DALI_Layer->clear();
	DALI_X->clear();
	DALI_Y->clear();
	DALI_Z->clear();
	DALI_Pos->clear();

	// Double_t FragmentBeta = 0.6; // TODO TODO TODO
	CalibDALI->ReconstructData();

	TClonesArray *DALINaIHits = (TClonesArray *)sman->FindDataContainer("DALINaI");
	if(DALINaIHits) {
	  Int_t DALI_Mult = 0;
	  Int_t NumberOfNaIHit = DALINaIHits->GetEntries();
	  Double_t ADC;
	  Double_t Time;
	  for(Int_t i=0; i<NumberOfNaIHit; i++) {
	    TArtDALINaI *DALINaI = (TArtDALINaI *)DALINaIHits->At(i);
	    ADC = DALINaI->GetRawADC();
	    Time = DALINaI->GetTimeOffseted();
	    if(ADC > 0){// &&  ADC < 4095*2 /*&& Time > 0*/) {
	      DALI_ID->push_back(DALINaI->GetID());
	      DALI_Energy->push_back(DALINaI->GetEnergy());
	      DALI_CosTheta->push_back(DALINaI->GetCosTheta());
	      DALI_Time->push_back(Time);
	      DALI_Layer->push_back(DALINaI->GetLayer());
	      DALI_X->push_back(DALINaI->GetXPos());
	      DALI_Y->push_back(DALINaI->GetYPos());
	      DALI_Z->push_back(DALINaI->GetZPos());
	      DALI_Pos->push_back(TVector3(DALINaI->GetXPos(),DALINaI->GetYPos(),DALINaI->GetZPos()));
	      DALI_Mult++;

	    }
	  }
	  // if (DALI_Mult > 1)
	  //   SortDaliHit(0,DALI_Mult-1, DALI_ID, DALI_Energy, DALI_EnergyDopplerCorrected, DALI_Time, DALI_CosTheta);
	}
	tree_DALI ->Fill();
      }


    }

  std::clog << std::endl;

  if(kBEAM) { tree_BEAM->BuildIndex("RunNumber","EventNumber"); fout_BEAM->cd(); WriteAllEnvFiles ; fout_BEAM->Write(); fout_BEAM->Close("R"); }
  if(kMAIN) { tree_MAIN->BuildIndex("RunNumber","EventNumber"); fout_MAIN->cd(); WriteAllEnvFiles ; fout_MAIN->Write(); fout_MAIN->Close("R"); }
  if(kNEUT) { tree_NEUT->BuildIndex("RunNumber","EventNumber"); fout_NEUT->cd(); WriteAllEnvFiles ; fout_NEUT->Write(); fout_NEUT->Close("R"); }
  if(kESPRI) { tree_ESPRI->BuildIndex("RunNumber","EventNumber"); fout_ESPRI->cd(); WriteAllEnvFiles ; fout_ESPRI->Write(); fout_ESPRI->Close("R"); }
  if(kDALI) { tree_DALI->BuildIndex("RunNumber","EventNumber"); fout_DALI->cd(); WriteAllEnvFiles ; fout_DALI->Write(); fout_DALI->Close("R"); }
  if(kPANDORA) { tree_PANDORA->BuildIndex("RunNumber","EventNumber"); fout_PANDORA->cd(); WriteAllEnvFiles ; fout_PANDORA->Write(); fout_PANDORA->Close("R"); }
  if(kFDCs||kFDCs_full) { tree_FDC ->BuildIndex("RunNumber","EventNumber"); fout_FDC ->cd(); WriteAllEnvFiles ; fout_FDC ->Write();  fout_FDC ->Close("R"); }
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
  if(kFDCs)
    {
      //delete CalibSimpleFDC1Track;
      delete CalibSimpleFDC2Track;
      delete CalibSimpleFDC0Track;
    }
  if(kFDCs_full)
    {
      //delete CalibFDC1Track;
      delete CalibFDC2Track;
      delete CalibFDC0Track;
    }
  // delete CalibFDC1Hit;
  delete CalibFDC0Hit;
  delete CalibFDC2Hit;
  delete CalibHODPla;
  if(CalibDALI) delete CalibDALI;
  delete CalibWINDS;
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
  delete DALI_ID;
  delete DALI_Time;
  delete DALI_Energy;
  // delete DALI_EnergyDopplerCorrected;
  delete DALI_CosTheta;
  delete TArtStoreManager::Instance();

  return 0;
}


// External Function
//void LoadDCTDCDistributionFull(char *FileName, TArtCalibBDC1Track *CalibBDC1Track, TArtCalibBDC2Track *CalibBDC2Track, TArtCalibSimpleFDC1Track *CalibFDC1Track, TArtCalibSimpleFDC2Track *CalibFDC2Track) {
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
