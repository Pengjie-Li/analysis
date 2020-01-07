/***************************************************************************************************/
/***************************************************************************************************/
////////////////////////////////////*ANALYSIS MACRO FOR SEASTAR3   */////////////////////////////////
/***************************************************************************************************/
/***************************************************************************************************/
#include <TMath.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TAttLine.h>
#include "TMath.h"
#include "TPaveText.h"
#include <vector>
#include "TVector3.h"
#include <TAxis.h>
#include <TH1.h>
#include <TLorentzVector.h>
#include <TH1F.h>
#include <TH2.h>
#include <TEnv.h>
#include <TF1.h>
#include <TVector3.h>
#include <TChain.h>
#include <TROOT.h>
#include <TFile.h>
#include <TMinuit.h>
#include <TVirtualFitter.h>
#include <TLatex.h>
#include <TStyle.h>
#include <TEntryList.h>
#include <TRandom.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <TSystem.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <TCutG.h>
#include <limits>
using namespace std;

#include "./include/DaliDefinition.h"
#include "./include/HodoDefinition.h"
#include "./include/FDCDefinition.h"
//#include "./include/BeamDefinition.h"
#include "./include/BdcDefinition.h"
#include "./include/PlaDefinition.h"
#include "./include/MainDefinition.h"
#include "./include/NeutDefinition.h"
#include "./include/OutputDefinition.h"
#include "./include/SiliconDefinition.h"
#include "./include/EspriDefinition.h"
#include "constant.h"
#include "calibration.h"

//////////////////////////////////////////////////////////////////////////

std::map<string,Double_t> MassExcessTable;

Double_t angle_difference_degree(Double_t, Double_t);
Double_t ExtractMassExcess(string line);
Double_t ReadMassExcess(string isotope);
double calibrate(double value,vector<double>& par);

void initialize(vector< vector<double> > & vec, string file);

void SortNeutronHit(int, int,vector <Bool_t> *, vector <Int_t> *,vector <Double_t> *,vector <Double_t> *,vector <Double_t> *,vector <Double_t> *, vector <Double_t> *, vector <Double_t> *, vector <Double_t> *);

// small function
void Hodo_Charge_F(double *AllHodo_Charge,double *AllHodo_Time,double &Hodo_Charge,double &Hodo_Time,int &Hodo_ID );
void Hodo_Charge_F(double *AllHodo_Charge,double *AllHodo_Time,double &Hodo_Charge,double &Hodo_Time,int &Hodo_ID )
{	
	//////////////////////Begin Change Aldric 1st July ////////////////////
	//Hodo_Charge=NAN;
	Hodo_Charge=-numeric_limits<double>::infinity();
	Hodo_Time=NAN;//added by fabia 30.06
	//Int_t counter = 0;
	for (int i=0;i<24;i++)
		// if(Hodo_Charge<AllHodo_Charge[i]) 
		if(AllHodo_Charge[i] > Hodo_Charge /*&& counter == 0*/) 
		{
			Hodo_Charge=AllHodo_Charge[i]; 
			Hodo_Time= AllHodo_Time[i];
			Hodo_ID=i+1;
			//counter++;
		}
	// else if(Hodo_Charge<AllHodo_Charge[i] && counter > 0)
	//   {
	// 	Hodo_Charge=AllHodo_Charge[i]; 
	// 	Hodo_Time= AllHodo_Time[i];
	// 	Hodo_ID=i+1;
	// 	counter++;
	//   }
	//////////////////////End Change Aldric 1st July ////////////////////
	// Hodo_Charge=-999.;
	// Hodo_Time=-999.;//added by fabia 30.06
	// for (int i=0;i<24;i++)
	//    if(Hodo_Charge<AllHodo_Charge[i]) 
	//    {
	//          Hodo_Charge=AllHodo_Charge[i]; 
	//          Hodo_Time= AllHodo_Time[i];
	//          Hodo_ID=i+1;
	//     }
}

void Hodo_Charge_P(double *AllHodo_Charge,double *AllHodo_Time,double &Hodo_Charge,double &Hodo_Time,int &Hodo_ID );
void Hodo_Charge_P(double *AllHodo_Charge,double *AllHodo_Time,double &Hodo_Charge,double &Hodo_Time,int &Hodo_ID )
{
	//////////////////////Begin Change Aldric 1st July ////////////////////
	//Hodo_Charge=NAN;
	Hodo_Charge=-numeric_limits<double>::infinity();
	Hodo_Time=NAN;//added by fabia 30.06
	//Int_t counter = 0;
	for (int i=24;i<40;i++)
		if(AllHodo_Charge[i] > Hodo_Charge/*&& counter == 0*/) 
		{
			Hodo_Charge=AllHodo_Charge[i]; 
			Hodo_Time= AllHodo_Time[i];
			Hodo_ID=i+1;
			//counter++;
		}
	// else if(Hodo_Charge<AllHodo_Charge[i] && counter > 0)
	//   {
	// 	Hodo_Charge=AllHodo_Charge[i]; 
	// 	Hodo_Time= AllHodo_Time[i];
	// 	Hodo_ID=i+1;
	// 	counter++;
	//   }
	//////////////////////End Change Aldric 1st July ////////////////////
	// Hodo_Charge=-999.;
	// Hodo_Time=-999.;//added by fabia 30.06
	// for (int i=24;i<40;i++)
	//    if(Hodo_Charge<AllHodo_Charge[i]) 
	//    {
	//          Hodo_Charge=AllHodo_Charge[i]; 
	//          Hodo_Time= AllHodo_Time[i];
	//          Hodo_ID=i+1;
	//     }
}

int analysis(Int_t RunNumber=0){

	/************************************************************************************/
	////////////////////////////////////*FILE DEFINITIONS/////////////////////////////////
	/************************************************************************************/

	//MAIN ROOT FILES
	TFile *infile = new TFile(Form("../rootfiles/run%04d/run%04d_MAIN.root",RunNumber,RunNumber));
	TTree *intree = (TTree*)infile->Get("CalTree");

	//FDC ROOT FILE
	TFile *infile_fdc = new TFile(Form("../rootfiles/run%04d/run%04d_FDCG.root",RunNumber,RunNumber));
	TTree *intree_fdc = (TTree*)infile_fdc->Get("CalTreeFDC");

	//HODO ROOT FILE
	TFile *infile_hodo = new TFile(Form("../rootfiles/run%04d/run%04d_HODO.root",RunNumber,RunNumber));
	TTree *intree_hodo = (TTree*)infile_hodo->Get("CalTreeHODO");

	//BDC ROOT FILE
	TFile *infile_bdc = new TFile(Form("../rootfiles/run%04d/run%04d_BDC.root",RunNumber,RunNumber));
	TTree *intree_bdc = (TTree*)infile_bdc->Get("CalTreeBDC");

	//Beam ROOT FILE
	TFile *infile_pla = new TFile(Form("../rootfiles/run%04d/run%04d_PLA.root",RunNumber,RunNumber));
	TTree *intree_pla = (TTree*)infile_pla->Get("CalTreePLA");



	//NEUT ROOT FILE
	//GiB 8 may 2017
	TFile *infile_neut = new TFile(Form("../rootfiles/run%04d/run%04d_NEUT.root",RunNumber,RunNumber));
	TTree *intree_neut = (TTree*)infile_neut->Get("CalTreeNEUT");

	//SILI ROOT FILE
	//GiB 8 may 2017
	TFile *infile_sili = new TFile(Form("../rootfiles/run%04d/run%04d_SILICONS.root",RunNumber,RunNumber));
	TTree *intree_sili = (TTree*)infile_sili->Get("CalTreeSILICONS");

	//ESPRI ROOT FILE
	TFile *infile_espri = new TFile(Form("../rootfiles/run%04d/run%04d_ESPRI.root",RunNumber,RunNumber));
	TTree *intree_espri = (TTree*)infile_espri->Get("CalTreeESPRI");

	cout << "N of entries (MAIN):\t" << intree->GetEntries() << endl;
	cout << "N of entries (FDC):\t" << intree_fdc->GetEntries() << endl;
	cout << "N of entries (HODO):\t" << intree_hodo->GetEntries() << endl;
	cout << "N of entries (BDC):\t" << intree_bdc->GetEntries() << endl;
	cout << "N of entries (PLA):\t" << intree_pla->GetEntries() << endl;
	cout << "N of entries (NEUT):\t" << intree_neut->GetEntries() << endl;
	cout << "N of entries (SILI):\t" << intree_sili->GetEntries() << endl;
	cout << "N of entries (ESPR):\t" << intree_espri->GetEntries() << endl;

	// check that all calibrated rootfiles have same number of entries
	// ignored for SILICONS and ESPRI for the time being...
	Long64_t nentries = intree->GetEntries();
	cout << "NUMBER OF EVENTS = " << nentries << endl;

	// CONFIGURATION FILE
	ifstream ConfigFile;
	//string ConfigFilePath = "./config/Config_"+outNucleus+"_from_"+inNucleus+".txt";
	string ConfigFilePath = "./config/Config.txt";
	cout<< "ConfigFile: " << ConfigFilePath << endl;
	ConfigFile.open(ConfigFilePath.c_str());

	Int_t frag_A, frag_Z;
	Int_t BEAM_A, BEAM_Z;
	Double_t BEAM_MassExcess, frag_MassExcess;
	Double_t BETA_in, BETA_mid, BETA_out;
	Double_t TargetLength;
	Double_t LH2Offset;
	Double_t NEBULAOffset1, NEBULAOffset2, NEBULAOffset3, NEBULAOffset4;

	string buffer;
	ConfigFile >> buffer >> BEAM_A; cout<< "BEAM_A:\t" << BEAM_A << endl;
	ConfigFile >> buffer >> BEAM_Z; cout<< "BEAM_Z:\t" << BEAM_Z << endl;
	ConfigFile >> buffer >> frag_A; cout<< "frag_A:\t" << frag_A << endl;
	ConfigFile >> buffer >> frag_Z; cout<< "frag_Z:\t" << frag_Z << endl;
	ConfigFile >> buffer >> BEAM_MassExcess; cout<< "BEAM_MassExc:\t" << BEAM_MassExcess << endl;
	ConfigFile >> buffer >> frag_MassExcess; cout<< "FRAG_MassExc:\t" << frag_MassExcess << endl;
	ConfigFile >> buffer >> BETA_in ; cout<< "BETA_in:\t" << BETA_in << endl;
	ConfigFile >> buffer >> BETA_mid; cout<< "BETA_mid:\t" << BETA_mid << endl;
	ConfigFile >> buffer >> BETA_out; cout<< "BETA_out:\t" << BETA_out << endl;
	ConfigFile >> buffer >> TargetLength; cout<< "TargetLength:\t" << TargetLength << endl;
	ConfigFile >> buffer >> LH2Offset; cout<< "LH2Offset:\t" << LH2Offset << endl;
	ConfigFile >> buffer >> NEBULAOffset1;  cout<< "NEBULAOffset1:\t" << NEBULAOffset1 << endl;//GiB 9 may 2017
	ConfigFile >> buffer >> NEBULAOffset2;  cout<< "NEBULAOffset2:\t" << NEBULAOffset2 << endl;//GiB 9 may 2017
	ConfigFile >> buffer >> NEBULAOffset3;  cout<< "NEBULAOffset3:\t" << NEBULAOffset3 << endl;//GiB 9 may 2017
	ConfigFile >> buffer >> NEBULAOffset4;  cout<< "NEBULAOffset4:\t" << NEBULAOffset4 << endl;//GiB 9 may 2017

	ConfigFile.close();
	Double_t M_BEAM = BEAM_A*AMU + BEAM_MassExcess; //(MeV/c²)
	//Double_t M_f = frag_A*AMU + frag_MassExcess; // (MeV/c²)
	Double_t M_f_kg = M_f*1.674927E-27/939.5654133;

	Double_t hod_toff[40] = {
		2.82+14.13,2.82+0.35,2.82+0.32,2.82+5.38,2.82+0.34,2.82+0.07,2.82,2.82+2.86, /* HODOF1-8*/
		2.82-1.89,2.82-2.18,2.82-2.37,2.82,2.82,2.82,2.82,2.82, /* HODOF9-16*/
		2.82,2.82,2.82,2.82,2.82,2.82,2.82,2.82, /* HODOF17-24*/
		20.68,20.68,20.68,20.68,20.68,20.68,20.68,20.68, /* HODOP1-8*/
		20.68,20.68,20.68,20.68,20.68,20.68,20.68,20.68 /* HODOP9-16*/
	};

	////////////////Change by Belen //////////
	hod_toff[24] =  hod_toff[24]+20.1;// 20.1 is from fit to match Hodo_ID==40
	hod_toff[25] =  hod_toff[25]+17.4;
	//////////////////////////////////////////

	//24->40 samurai 4n experiment
	Double_t hod_qoff[40]={
		0., 0., 0., 0., 0., 0., -6.07,-6.07, -6.07, -6.07, -6.07, -6.07, //IDF 1-12
		0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0., //IDF 13-24
		0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0. //IDP 25-40
	};

	Double_t hod_qcor[40] = {
		1.0,1.0,1.0,1.0,1.0,1.0, //IDF 1-6
		1.0957612074,1.0975191131,1.0659660959,1.084603677,1.1038475076,1.0894148757,//IDF 7-12
		1.0682354856,1.007615894,1,1.0869146889 ,1.0254048696,1.0, //IDF 13-18
		1.0,1.0,1.0,1.0,1.0,1.0,//IDF 19-24
		1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0 };

	double p0HodoZ[24]={ -4.854, -4.854, -4.854, -4.854, 0.3112,  -1.7648,
		-2.8982,-3.292-0.42, -4.854, -4.322, -4.797, -3.736,
		-3.552, -2.456, -2.276, -5.091, -2.712-1, -2.138-1,
		-0.765-1, -1.188-1, -1.144-1, -0.8499-1, -0.8535-1, -1.8535};

	double p1HodoZ[24]={	4.263, 4.263, 4.263, 4.263, 3.834, 3.6973,3.880,
		4.025, 4.263, 4.176, 4.284, 4.108, 4.091, 3.903, 3.884, 
		4.262, 4.048, 3.993, 3.715, 3.747, 3.743,
		3.665, 3.612, 3.612};

	//MAIN BEAM AND HODO CUTs


	//------------------------------------------------------------------------------/
	//////////////////////////////////// SetBranchAddress ///////////////////////////
	//------------------------------------------------------------------------------/

	Get_Branch_MAIN(intree);


	Get_Branch_FDC(intree_fdc);
	Get_Branch_HODO(intree_hodo);
	Get_Branch_BDC(intree_bdc);
	Get_Branch_PLA(intree_pla);
	Get_Branch_NEUT(intree_neut);  //GiB 8 may 2017
	Get_Branch_SILI(intree_sili);  //GiB 14 may 2018
	Get_Branch_ESPRI(intree_espri);  



	intree->AddFriend(intree_fdc);
	intree->AddFriend(intree_hodo);
	intree->AddFriend(intree_bdc);
	intree->AddFriend(intree_pla);
	intree->AddFriend(intree_neut);
	intree->AddFriend(intree_sili);
	intree->AddFriend(intree_espri);
	//------------------------------------------------------------------------------/
	//////////////////////// Create Output Tree and Copy branches ///////////////////
	//------------------------------------------------------------------------------/

	//Creating a new File
	//TFile *newfile = new TFile(Form("./RootA/run%04d_analysed_%s.root",RunNumber,outNucleus.c_str()), "recreate");
	//TFile *newfile = new TFile(Form("./RootA/run%04d_analysed_v6.root",RunNumber), "recreate"); // add scm parameter in silicon
	//TFile *newfile = new TFile(Form("./RootA/run%04d_analysed_v6.root",RunNumber), "recreate"); // new parameters for DSSD
	TFile *newfile = new TFile(Form("./RootA/run%04d_analysed_v6.root",RunNumber), "recreate"); // SCM Whole new parameters for DSSD
	//TFile *newfile = new TFile(Form("./test/run%04d_analysed_v6.root",RunNumber), "recreate"); // SCM Whole new parameters for DSSD
	//TFile *newfile = new TFile(Form("./cutWindow/run%04d_analysed_cutWindow.root",RunNumber), "recreate"); // SCM Whole new parameters for DSSD
	TTree *newtree = new TTree("AnalysisTree","AnalysisTree");
	Set_Branch_Output(newtree);



	//temp
	Double_t Zref;
	newtree->Branch("Zref", &Zref);


	//------------------------------------------------------------------------------/
	//////////////////////// Load Calibration Parameters  ///////////////////
	//------------------------------------------------------------------------------/


	// Silicon
	double k[4][32]={0};
	double b[4][32]={0};

	double ek[4][32]={0};
	double eb[4][32]={0};

	Load(k,b,ek,eb);


	double kl=7.17797775;
	double bl=-1524.240925;
	double kr=7.685283145;
	double br=-1646.273395;

	// CsI
	double CsILLpar[32][32][2]={0};
	double CsILRTpar[32][32][2]={0};
	double CsILRBpar[32][32][2]={0};

	double CsIRLTpar[32][32][2]={0};
	double CsIRLBpar[32][32][2]={0};
	double CsIRRTpar[32][32][2]={0};
	double CsIRRBpar[32][32][2]={0};

	Load(CsILLpar,CsILRTpar,CsILRBpar,CsIRLTpar,CsIRLBpar,CsIRRTpar,CsIRRBpar);


	//

	//	int left=0;
	//	double lk[4][32]={0};
	//	double lb[4][32]={0};
	//
	//	double lek[4][32]={0};
	//	double leb[4][32]={0};

	// v6
	//	double lkb=7.11443;
	//	double lbb=-1719.02;
	//	double lkf=7.64654;
	//	double lbf=-1600.15;

	// v6
	//        double lkb=6.626367576;
	//        double lbb=-1903.367442;
	//        double lkf=7.171468546;
	//        double lbf=-1524.868862;
	//
	//	Load(left,lk,lb,lek,leb);
	//
	//
	//	int right=1;
	//	double rk[4][32]={0};
	//	double rb[4][32]={0};
	//
	//	double rek[4][32]={0};
	//	double reb[4][32]={0};

	// v6
	//		double rkb=7.11443;
	//		double rbb=-1719.02;
	//		double rkf=7.64654;
	//		double rbf=-1600.15;
	//
	//        double rkb=7.074502166;
	//        double rbb=-1670.625365;
	//        double rkf=7.698357364;
	//        double rbf=-1665.092353;
	//
	//	Load(right,rk,rb,rek,reb);


	//------------------------------------------------------------------------------/
	///////////////////   MAIN EVENT LOOP  ////////////////////////
	//------------------------------------------------------------------------------/

	cout << "NUMBER OF EVENTS = " << nentries << endl;
	Int_t counter = 1;

	for(int drawid=1;drawid<138;drawid++) AllTele_ID[drawid-1]=drawid;
	//nentries=10;
	for(int i = 0 ; i < nentries ; i++){


		// Init //////////////////////////////////////////////////////////////////////////////////////////



		Trig_DSB=-1;
		Trig_BxESPRIxTEL=-1;
		Trig_BxESPRI=-1;
		Trig_BxTEL=-1;
		Trig_BxHODP=-1;
		Trig_BxHODF=-1;
		Trig_BxNEBULA=-1;


		// BEAM
		F3_Charge_C    = NAN;
		F3_Time_C      = NAN;
		F3_TimeDiff_C  = NAN;
		F7_Charge_C    = NAN;
		F7_Time_C      = NAN;
		F13_Charge_C   = NAN;
		F13_Time_C     = NAN;

		BEAM_A_C = NAN;
		BEAM_Z_C = NAN;

		BigRIPS_AoQ = NAN;
		BigRIPS_Zpl = NAN;
		BigRIPS_Zic = NAN;
		Bz=NAN; 
		BAoQ=NAN;
		beta_in_new=NAN;


		TOF713=NAN;
		Beta713=NAN;
		Gamma713=NAN;
		Ek713=NAN;

		TOF37=NAN;
		Beta37=NAN;
		Gamma37=NAN;
		Ek37=NAN;



		BDC1_X_C = NAN; 
		BDC1_Y_C = NAN;
		BDC1_ThetaX_C = NAN; 
		BDC1_ThetaY_C = NAN; 
		BDC2_X_C = NAN;
		BDC2_Y_C = NAN;
		BDC2_ThetaX_C = NAN;
		BDC2_ThetaY_C = NAN;
		Target_X = NAN;
		Target_Y = NAN;

		Target_ThetaX = NAN;
		Target_ThetaY = NAN;





		// Init input Silicon raw data
		SiLF_rawADC->clear();
		SiLB_rawADC->clear();
		SiRF_rawADC->clear();
		SiRB_rawADC->clear();




		// Init output Silicon data
		MaxSi_E=-999;
		MaxSi_ID=-999;

		MaxCsI_E=-999;
		MaxCsI_ID=-999;

		for(int j=0;j<137;j++)
		{
			AllTele_E[j]=-999;
			AllTele_T[j]=-999;
		}
		for(int j=0;j<128;j++)
		{
			AllSi_E[j]=-999;
			AllSi_T[j]=-999;
		}

		for(int j=0;j<7;j++)
		{
			AllCsI_E[j]=-999;
			AllCsI_T[j]=-999;
		}

		for(int j=0;j<32;j++)
		{
			SiLF_SCM[j]=-999;
			SiLB_SCM[j]=-999;
			SiRF_SCM[j]=-999;
			SiRB_SCM[j]=-999;

			SiLF_E[j]=-999;
			SiLB_E[j]=-999;
			SiRF_E[j]=-999;
			SiRB_E[j]=-999;
			SiLF_T[j]=-999;
			SiLB_T[j]=-999;
			SiRF_T[j]=-999;
			SiRB_T[j]=-999;
			// SiLF_X[j]=-999;
			// SiLB_X[j]=-999;
			// SiRF_X[j]=-999;
			// SiRB_X[j]=-999;
			// SiLF_Y[j]=-999;
			// SiLB_Y[j]=-999;
			// SiRF_Y[j]=-999;
			// SiRB_Y[j]=-999;
			// SiLF_Z[j]=-999;
			// SiLB_Z[j]=-999;
			// SiRF_Z[j]=-999;
			// SiRB_Z[j]=-999;
		}

		// CsI E&T
		CsI_LL_E=-999;
		CsI_LRT_E=-999;
		CsI_LRB_E=-999;
		CsI_RLT_E=-999;
		CsI_RLB_E=-999;
		CsI_RRT_E=-999;
		CsI_RRB_E=-999;

		CsI_LL_T=-999;
		CsI_LRT_T=-999;
		CsI_LRB_T=-999;
		CsI_RLT_T=-999;
		CsI_RLB_T=-999;
		CsI_RRT_T=-999;
		CsI_RRB_T=-999;

		// ESPRI 
		for (Int_t j=0 ; j < 14 ; j++){
			ESPRI_NaI_ID_C[j]      = -999;
			ESPRI_NaI_Layer_C[j]   = -999;
			ESPRI_NaI_Energy_C[j]  = -999;
			ESPRI_NaI_EnergyL_C[j] = -999;
			ESPRI_NaI_EnergyR_C[j] = -999;
			//  ESPRI_NaI_Time[14];
			//  ESPRI_NaI_TimeL[14];
			//  ESPRI_NaI_TimeR[14];
		}

		for (Int_t j=0 ; j < 2; j++){
			ESPRI_Plas_ID_C[j]     = -999;
			ESPRI_Plas_Layer_C[j]  = -999;
			ESPRI_Plas_Energy_C[j] = -999;
			ESPRI_Plas_EnergyU_C[j]= -999;
			ESPRI_Plas_EnergyD_C[j]= -999;
			ESPRI_Plas_Time_C[j]   = -999;
			ESPRI_Plas_TimeU_C[j]  = -999;
			ESPRI_Plas_TimeD_C[j]  = -999;
			// ESPRI_RDC_Side_C[j]    = -999;
			ESPRI_RDC_X_C[j]       = -999;
			ESPRI_RDC_A_C[j]       = -999;
			ESPRI_RDC_Y_C[j]       = -999;
			ESPRI_RDC_B_C[j]       = -999;
		}

		ESPRI_NaI_Mult_C = -999;
		ESPRI_Plas_Mult_C =-999;

		// NEUT
		Neutron_X_sorted->clear();
		Neutron_Y_sorted->clear();
		Neutron_Z_sorted->clear();
		Neutron_ChargeUp_sorted->clear();
		Neutron_ChargeDown_sorted->clear();
		Neutron_Charge_sorted->clear();
		Neutron_ID_sorted->clear();
		Neutron_Time_sorted->clear();
		Neutron_IsNEBULA_sorted->clear();
		Neutron_Energy_sorted->clear();
		Neutron_Beta_sorted->clear();

		////////////
		M_f = NAN;
		BETA_f = NAN;
		GAMMA_f = NAN;
		MOM_f = NAN;
		MOM_f_X = NAN;
		MOM_f_Y = NAN;
		MOM_f_Z = NAN;
		Angle_Frag = NAN;
		Energy_loss_BEAM = NAN;
		Energy_loss_FRAG = NAN;
		BEAM_A_C = NAN;
		BEAM_Z_C = NAN;
		BETA_vertex = NAN;
		BETA_vertex_new = NAN;



		/////////////////////////////////// Loading Data ///////////////////////////////////////////////
		intree->GetEntry(i);
		if(i == (Int_t)counter*nentries/20){
			cout  << '\r' <<  "\033[1;36mConversion running : " << counter*5 << "%                " << flush;
			counter++;
		}

		// Simple check that EventNumber between files is the same
		//		if( EventNumber_main!= EventNumber_fdc){
		//			cerr << "ERROR: EVENT NUMBER DIFFERENT BETWEEN MAIN AND FDC DATA FILES" << endl;
		//			return 0;
		if( EventNumber_main!= EventNumber_hodo){
			cerr << "ERROR: EVENT NUMBER DIFFERENT BETWEEN MAIN AND HODO DATA FILES" << endl;
			return 0;
			if( EventNumber_main!= EventNumber_bdc){
				cerr << "ERROR: EVENT NUMBER DIFFERENT BETWEEN MAIN AND BEAM DATA FILES" << endl;
				return 0;
				if( EventNumber_main!= EventNumber_pla){
					cerr << "ERROR: EVENT NUMBER DIFFERENT BETWEEN MAIN AND BEAM DATA FILES" << endl;
					return 0;
					if( EventNumber_main!= EventNumber_neut){
						cerr << "ERROR: EVENT NUMBER DIFFERENT BETWEEN MAIN AND NEUT DATA FILES" << endl;
						return 0;
						if( EventNumber_main!= EventNumber_sili){
							cerr << "ERROR: EVENT NUMBER DIFFERENT BETWEEN MAIN AND SILI DATA FILES" << endl;
							return 0;
							if( EventNumber_main!= EventNumber_espri){
								cerr << "ERROR: EVENT NUMBER DIFFERENT BETWEEN MAIN AND ESPRI DATA FILES" << endl;
								return 0;
							}
						}
					}
				}
			}
		}












		// Filling /////////////////////////////////////////////////////////////////////////////////////

		// Copy of the main branch
		CoincidenceTrigger_C = CoincidenceTrigger;

		EventNumber_C = EventNumber_main;
		RunNumber_C = RunNumber_main;

		Trig_DSB=CoincidenceTrigger & 1;
		Trig_BxESPRIxTEL=CoincidenceTrigger & 2;
		Trig_BxESPRI=CoincidenceTrigger & 4;
		Trig_BxTEL=CoincidenceTrigger & 8;
		Trig_BxHODP=CoincidenceTrigger & 16;
		Trig_BxHODF=CoincidenceTrigger & 32;
		Trig_BxNEBULA=CoincidenceTrigger & 64;
		//cout<<Trig_DSB<<"   "<<Trig_BxESPRIxTEL<<"   "<<Trig_BxNEBULA<<endl;


		BDC1_X_C = BDC1_X;
		BDC1_Y_C = BDC1_Y;
		BDC1_ThetaX_C = BDC1_ThetaX;
		BDC1_ThetaY_C = BDC1_ThetaY;
		BDC2_X_C = BDC2_X;
		BDC2_Y_C = BDC2_Y;
		BDC2_ThetaX_C = BDC2_ThetaX;
		BDC2_ThetaY_C = BDC2_ThetaY;

		Target_X = BDC1_X + Dist_BDC1Target / Dist_BDC1BDC2 * (BDC2_X - BDC1_X);
		Target_Y = BDC1_Y + Dist_BDC1Target / Dist_BDC1BDC2 * (BDC2_Y - BDC1_Y);
		Target_ThetaX = TMath::ATan( (BDC2_X - BDC1_X) / Dist_BDC1BDC2 );
		Target_ThetaY = TMath::ATan( (BDC2_Y - BDC1_Y) / Dist_BDC1BDC2 );

		TVector3* vBDC1 = new TVector3;
		TVector3* vBDC2 = new TVector3;

		vBDC1->SetXYZ(BDC1_X,BDC1_Y,BDC1_Z);
		vBDC2->SetXYZ(BDC2_X,BDC2_Y,BDC2_Z);

		(*Beam)=(*vBDC2)-(*vBDC1);
		(*Beam)=(*Beam).Unit();
	




		F3_Charge_C   =F3_Charge ;  
		F3_Time_C     =F3_Time ;   
		F7_Charge_C   =F7_Charge ;  
		F7_Time_C     =F7_Time ;   
		F13_Charge_C  =F13_Charge ; 
		F13_Time_C    =F13_Time ;   


		// no F5 for Samurai12 May 2018
		TOF713=F13_Time - F7_Time + 570.619; // ns //20181025
		Beta713=Dist_F7F13/TOF713/C_light;
		Gamma713=1/sqrt(1-Beta713*Beta713);
		Ek713=(Gamma713-1)*AMU;

		TOF37=F7_Time - F3_Time + 299.091; // ns
		Beta37=Dist_F3F7/TOF37/C_light;
		Gamma37=1/sqrt(1-Beta37*Beta37);
		Ek37=(Gamma37-1)*AMU;


		BigRIPS_Zic = -1; // in SAMURAI_4n exp, no F7IC
		//BigRIPS_Zic = calibrate(F7IC_E-calibrate(tof_713_Cal,zet_tof_cal[0]),zet_tof_cal[1]);

		//cout<<" stop here?"<<endl;
		//cout<<"F7_Charge="<<F7_Charge<<endl;
		//cout<<"F13_Charge="<<F13_Charge<<endl;
		//cout<<" stop here?"<<endl;
		double f7f13q=sqrt(F7_Charge_C*F13_Charge_C);
		double f3f7f13q=sqrt(F3_Charge_C*f7f13q);

		//if(zetF7pla_tof_cal[0].size()>0)
		//BigRIPS_Zpl = calibrate(f3f7f13q-calibrate(tof_713_Cal,zetF7pla_tof_cal[0]),zetF7pla_tof_cal[1] );
		BigRIPS_Zpl =0;

		//BigRIPS_AoQ = calibrate(tof_713_Cal,tof_x5_cal[2]);
		BigRIPS_AoQ = 0;

		//cout<<"1BigRIPS_AoQ="<<BigRIPS_AoQ<<endl;
		//---------Calculate the Beta from tof---liuhn--------------
		Double_t f7iceave=0;
		Double_t tof_713_new = F13_Time_C - F7_Time_C +38.24;// TOF_offset: hongna-2017-0508
		Double_t par[10];
		par[0]   =     -81.4151;
		par[1]   =      21.9679;
		par[2]   =      7.61724;
		par[3]   =     0.367397;
		par[4]   =     -1.88067;
		par[5]   =     0.170913;
		par[6]   =     0.214241;
		par[7]   =   -0.0679971;
		par[8]   =   0.00769205;
		par[9]   = -0.000306823;
		Double_t f5dt;

		Double_t bbeta;

		Double_t beam_brho_mean=6.854;
		Double_t beam_brho;

		Double_t fl7_13=117915-78201;
		bbeta=fl7_13/C_light/tof_713_new;
		Double_t beam_dev = 0;
		Double_t zet_in=sqrt(0/beam_dev)*bbeta;

		Bz=8.451836*zet_in-5.89374;
		Bz=0.94429*Bz+1.22794;
		BAoQ=beam_brho*C_light/AMU*sqrt(1.0-bbeta*bbeta)/bbeta;


		//FDC1_X_C = FDC1_X;
		//FDC1_Y_C = FDC1_Y;
		//FDC1_ThetaX_C = FDC1_ThetaX;
		//FDC1_ThetaY_C = FDC1_ThetaY;
		FDC2_X_C = FDC2_X;
		FDC2_Y_C = FDC2_Y;
		FDC2_ThetaX_C = FDC2_ThetaX;
		FDC2_ThetaY_C = FDC2_ThetaY;
		FDC0_X_C = FDC0_X;
		FDC0_Y_C = FDC0_Y;
		FDC0_ThetaX_C = FDC0_ThetaX;
		FDC0_ThetaY_C = FDC0_ThetaY;
		//cout<<"FDC0_X="<<FDC0_X<<" FDC0_Y="<<FDC0_Y<<endl;

		Hodo_ID_C = -1;
		Hodo_Charge_C = -numeric_limits<double>::infinity();
		Hodo_Time_C = NAN;

		for (Int_t j=0 ; j < 40 ; j++)
		{
			//cout<<AllHodo_Charge_C[j]<<endl;
			AllHodo_ID_C[j]=-1;
			AllHodo_ID_C[j]=AllHodo_ID[j];
			//cout<<AllHodo_ID_C[j]<<endl;
			// HODO maximum charge in F/P samurai 4n experiment
			//AllHodo_Charge_C[j] = AllHodo_Charge[j]*hod_qcor[j]+hod_qoff[j];
			//AllHodo_Time_C[j] = AllHodo_Time[j]+HODOT0[j]+hod_toff[j];
			// if(AllHodo_Time[j]>0){
			// cout << AllHodo_Time[j] << "   " << AllHodo_Time[j]+HODOT0[j] << "    " << AllHodo_Time[j]+HODOT0[j]+hod_toff[j] << endl;
			// }
			// if((AllHodo_Time[j]+HODOT0[j])>0){
			//  AllHodo_Time_C[j] = AllHodo_Time[j]+HODOT0[j]+hod_toff[j];
			//   }
			// if(AllHodo_Charge_C[j] > Hodo_Charge_C && AllHodo_Charge_C[j] > 0.){
			//   Hodo_ID_C = j+1;
			//   if(Hodo_ID_C>=1 && Hodo_ID_C<=24)
			//     {
			//       Hodo_ID_rig=25-Hodo_ID_C;
			//     }
			//   else if(Hodo_ID_C>=27 && Hodo_ID_C<=40)
			//      {
			//        Hodo_ID_rig=67-Hodo_ID_C;
			//      } 
			//   else 
			//      {
			//        Hodo_ID_rig=Hodo_ID_C;
			//      }

			//   Hodo_Charge_C = AllHodo_Charge_C[j];
			//   Hodo_Time_C = AllHodo_Time_C[j];
			// }

			//////////////////////Begin Change Aldric 1st July ////////////////////
			if(AllHodo_Charge_C[j] > Hodo_Charge_C ){
				Hodo_ID_C = j+1;
				if(Hodo_ID_C>=1 && Hodo_ID_C<=24)
				{
					Hodo_ID_rig=25-Hodo_ID_C;
				}
				else if(Hodo_ID_C>=27 && Hodo_ID_C<=40)
				{
					Hodo_ID_rig=67-Hodo_ID_C;
				} 
				else 
				{
					Hodo_ID_rig=Hodo_ID_C;
				}

				Hodo_Charge_C = AllHodo_Charge_C[j];
				Hodo_Time_C = AllHodo_Time_C[j];
				//counter++;
			}// else if(AllHodo_Charge_C[j] > Hodo_Charge_C && counter > 0){
			//   Hodo_ID_C = j+1;
			//   if(Hodo_ID_C>=1 && Hodo_ID_C<=24)
			//     {
			//       Hodo_ID_rig=25-Hodo_ID_C;
			//     }
			//   else if(Hodo_ID_C>=27 && Hodo_ID_C<=40)
			//     {
			//       Hodo_ID_rig=67-Hodo_ID_C;
			//     } 
			//   else 
			//     {
			//       Hodo_ID_rig=Hodo_ID_C;
			//     }

			//   Hodo_Charge_C = AllHodo_Charge_C[j];
			//   Hodo_Time_C = AllHodo_Time_C[j];
			//   counter++;
			// }

			//////////////////////End Change Aldric 1st July ////////////////////
		}

		Hodo_Z_C = Hodo_Z;
		Hodo_AoverZ_C = Hodo_AoverZ;
		// Hodo_AoQ added for 4n experiment
		Hodo_AoQ=NAN;
		if(Hodo_Time>0&&Hodo_Time<130&&Hodo_ID_rig>13&&Hodo_ID_rig<41)
		{
			double distance=1;
			//double distance=cal_HOD_dis(Hodo_ID_rig);
			//double distance=cal_FDC_dis(FDC2_X,Target_X,Target_Y,FDC0_X, FDC0_Y);
			//cout<<distance<<endl;
			Hodo_AoQ=(double)Hodo_ID_rig*Hodo_Time/distance;
		}
		//////////////////////////////////////////Changes Fabia 28.06 20:53
		//  Hodo_ChargeF_C = Hodo_ChargeF;
		//  Hodo_ChargeP_C = Hodo_ChargeP;
		//  Hodo_TimeF_C = Hodo_TimeF;
		//  Hodo_TimeP_C = Hodo_TimeP;
		//  Hodo_IDF_C = Hodo_IDF;
		//  Hodo_IDP_C = Hodo_IDP;

		// HODO maximum charge in F/P samurai 4n experiment
		// Hodo_Charge_F(AllHodo_Charge_C,AllHodo_Time_C,Hodo_ChargeF_C,Hodo_TimeF_C,Hodo_IDF_C);
		// Hodo_Charge_P(AllHodo_Charge_C,AllHodo_Time_C,Hodo_ChargeP_C,Hodo_TimeP_C,Hodo_IDP_C);

		//CALCULATION OF FRAGMENT PROPERTIES

		//Angle_Frag = TMath::ATan(TMath::Sqrt((FDC1_X_C-x_vertex)*(FDC1_X_C-x_vertex) + (FDC1_Y_C-y_vertex)*(FDC1_Y_C-y_vertex))/(Dist_TFDC1_Entry-z_vertex));
		Angle_Frag = 0; // need to be redone with sth else instead of FDC1 !!!
		//BETA_f = 1./TMath::Sqrt((1 + (M_f_kg*3E8/(SAMURAI_Brho_C*frag_Z*el_charge))*(M_f_kg*3E8/(SAMURAI_Brho_C*frag_Z*el_charge))));
		GAMMA_f = 1./(TMath::Sqrt(1-BETA_f*BETA_f));
		Energy_FRAG = GAMMA_f*M_f + Energy_loss_FRAG;
		GAMMA_f = Energy_FRAG/M_f;
		BETA_f = TMath::Sqrt(1 - 1./(GAMMA_f*GAMMA_f));
		GAMMA_f = 1./(TMath::Sqrt(1-BETA_f*BETA_f));

		MOM_f = BETA_f*GAMMA_f*M_f;
		//Dist_TFDC1 = TMath::Sqrt((FDC1_X_C-x_vertex)*(FDC1_X_C-x_vertex) + (FDC1_Y_C-y_vertex)*(FDC1_Y_C-y_vertex) + (Dist_TFDC1_Entry-z_vertex)*(Dist_TFDC1_Entry-z_vertex));
		//Dist_TFDC1 = 0; // need to be redone with sth else instead of FDC1 !!!
		MOM_f_X = 0.;//MOM_f*(FDC1_X_C-x_vertex)/Dist_TFDC1;
		MOM_f_Y = 0.;//MOM_f*(FDC1_Y_C-y_vertex)/Dist_TFDC1;
		MOM_f_Z = 0.;//MOM_f*(Dist_TFDC1_Entry-z_vertex)/Dist_TFDC1;

		//________________________________calculate frag_Z and momentum
		//x/y/z_vertex, relative to center of MINOS
		double x[6];

		//double fdc1x = FDC1_X_C;
		//double fdc1y = FDC1_Y_C;
		//___________use FDC1 angle
		//fdc1a = TMath::Tan(ffdc->FDC1_ThetaX)*1000;
		//fdc1b = TMath::Tan(ffdc->FDC1_ThetaY)*1000;
		//___________use target vertex and FDC1 for the angle
		//double fdc1a = (fdc1x - x_vertexSAMURAI)/(fdc1z - Zpos_target)*1000.;//1a
		//double fdc1b = (fdc1y - y_vertexSAMURAI)/(fdc1z - Zpos_target)*1000.;//1b

		double fdc0x = FDC0_X_C;//2x
		double fdc0y = FDC0_Y_C;//2y
		double fdc0a = TMath::Tan(FDC0_ThetaX_C)*1000;//2a
		double fdc0b = TMath::Tan(FDC0_ThetaY_C)*1000;//2b

		double fdc2x = FDC2_X_C;//2x
		double fdc2a = TMath::Tan(FDC2_ThetaX_C)*1000;//2a
		double fdc2y = FDC2_Y_C;//2y
		double fdc2b = TMath::Tan(FDC2_ThetaY_C)*1000;//2b

		x[0] = 0;// fdc1x;//1x needs to be redone with sth else instead of FDC1
		x[1] = 0;// fdc1a;//1a
		x[2] = 0;// fdc1y;//1y
		x[3] = 0;// fdc1b;//1b
		x[4] =  fdc2x;//2x
		x[5] =  fdc2a;//2a

		SAMURAI_AoQ1 = NAN;
		SAMURAI_AoQ2 = NAN;
		SAMURAI_Zho = NAN;
		beta_out_new=NAN;
		//double flight_length = MDF_Len_A52Z18(x);
		double flight_length = 1;

		double beta_frag = flight_length/Hodo_Time_C/C_light;
		double dev=0;
		//double
		Zref=sqrt(Hodo_Charge_C/dev)*beta_frag;
		SAMURAI_Zho =  Zref*p1HodoZ[Hodo_ID_C-1] + p0HodoZ[Hodo_ID_C-1];

		beta_frag = flight_length/(Hodo_Time_C-94.21+55.08)/C_light;
		double gamma_frag = NAN;
		if(beta_frag>0 && beta_frag<1)
			gamma_frag = 1./TMath::Power(1-beta_frag*beta_frag, 0.5);

		//double Brho = MDF_Brho_A52Z18(x);
		double Brho = 1;
		//cout<<"Brho="<<Brho<<endl;
		SAMURAI_AoQ1 = Brho*C_light/(beta_frag*gamma_frag*AMU);

		//cout<<"SAMURAI_AoQ1="<<SAMURAI_AoQ1<<endl;
		SAMURAI_AoQ2 = (Hodo_Time_C-94.21+55.08)+0.0117*fdc2x;
		SAMURAI_AoQ2 = SAMURAI_AoQ2*0.0521 - 0.0217;
		if(Hodo_ID_C==12) SAMURAI_AoQ2=SAMURAI_AoQ2+0.007;
		if(Hodo_ID_C>12&&Hodo_ID_C<19) SAMURAI_AoQ2=SAMURAI_AoQ2-0.012;
		if(Hodo_ID_C==6) SAMURAI_AoQ2=SAMURAI_AoQ2*1.12138-0.512214;

		//-------------beta_out----------------
		Double_t hod_toff_new[24] = {
			0,0,0,0,0,0,
			2.3,2.15,
			-0.18,-0.17,-0.26,-0.18
				-0.11,0,0,0.06,0.09,0,
			0,0,0,0,0,0

		};
		Double_t hod_real_tof=Hodo_Time_C-hod_toff_new[Hodo_ID_C-1]+0.2- 94.21 + 55.08;//tof_offset set for 52Ar
		beta_out_new= flight_length/hod_real_tof/C_light;

		BETA_vertex = BETA_mid;
		BETA_vertex_new = NAN;

		BeamID = 0;
		FragID = 0;
		//if(CutBeam_53K->IsInside(BigRIPS_AoQ,BigRIPS_Zpl)) BeamID = 1;
		//if(CutBeam_57Sc->IsInside(BigRIPS_AoQ,BigRIPS_Zpl)) BeamID = 2;
		//if(CutBeam_63V->IsInside(BigRIPS_AoQ,BigRIPS_Zpl)) BeamID = 3;
		//FragID = 0;
		//if(CutFrag_52Ar->IsInside(XX, XX)) FragID = 1;
		//if(CutFrag_56Ca->IsInside(XX, XX)) FragID = 2;
		//if(CutFrag_63Ti->IsInside(XX, XX)) FragID = 3;

		// GiB 7 mai 2017
		// For 4n experiment
		//  for(unsigned int j=0; j<BeamCutPID.size(); j++){
		//     if(BeamCutPID[j]->IsInside(BigRIPS_AoQ,BigRIPS_Zic)) {
		//        BeamEntryList[j]->Enter(i);
		//        BeamID = j+1;
		//     }
		//  }
		//  for(unsigned int j=0; j<HodoCutPID.size(); j++){
		//     if(HodoCutPID[j]->IsInside(SAMURAI_AoQ2,SAMURAI_Zho)) {
		//        HodoEntryList[j]->Enter(i);
		//        FragID = j+1;
		//        TString tmpname(HodoEntryList[j]->GetName());
		//        tmpname.ReplaceAll(" ","");
		//        M_f = MassExcessTable[string(tmpname.Data())] ;
		//        //	  cout << M_f << endl;

		//     }
		//  }

		//MOMENTA & 4-VECTORS

		TVector3 vertex(0.0, 0.0, LH2Offset); 
		TVector3 FDC1_Hit(0,0,0);  //(FDC1_X, FDC1_Y, Dist_TFDC1_Entry); 
		TVector3 momentum_dir = FDC1_Hit - vertex;
		momentum_dir.Unit();
		Double_t Frag_Theta = momentum_dir.Theta();
		Double_t Frag_Phi = momentum_dir.Phi();

		Double_t Frag_Momentum = BETA_vertex/sqrt(1.-BETA_vertex*BETA_vertex)*M_f;

		TVector3 tmpVect3;
		tmpVect3.SetMagThetaPhi(Frag_Momentum,
				Frag_Theta,
				Frag_Phi);

		Frag_Vector.SetVectM(tmpVect3,M_f);



		// Calibrate Silicon 
		SiLF_Emax=-9999;
		SiLF_id=-1;
		SiLB_Emax=-9999;
		SiLB_id=-1;

		SiRF_Emax=-9999;
		SiRF_id=-1;
		SiRB_Emax=-9999;
		SiRB_id=-1;
	
		for(int id=0;id<32;id++)
		{
			// raw->SCM->cal

			double lfraw=(*SiLF_rawADC)[id];
			double lbraw=(*SiLB_rawADC)[id];
			if(lfraw>4096) lfraw=-9999;
			if(lbraw>4096) lbraw=-9999;
			//double fscm=0;
			double lfscm=k[0][id]*lfraw+b[0][id];
			//double bscm=0;
			double lbscm=k[1][id]*lbraw+b[1][id];
			double lfcal=kl*lfscm+bl;
			double lbcal=kl*lbscm+bl;
			//cout<<fscm<<"  "<<bscm<<endl;
			SiLF_SCM[id]=lfscm;
			SiLB_SCM[id]=lbscm;
			SiLF_E[id]=lfcal;
			SiLB_E[id]=lbcal;

			if(lfcal>SiLF_Emax) { SiLF_Emax=lfcal; SiLF_id=id;}
			if(lbcal>SiLB_Emax) { SiLB_Emax=lbcal; SiLB_id=id;}


			double rfraw=(*SiRF_rawADC)[id];
			double rbraw=(*SiRB_rawADC)[id];
			if(rfraw>4096) rfraw=-9999;
			if(rbraw>4096) rbraw=-9999;
	
			//double fscm=0;
			double rfscm=k[2][id]*rfraw+b[2][id];
			//double bscm=0;
			double rbscm=k[3][id]*rbraw+b[3][id];
			double rfcal=kr*rfscm+br;
			double rbcal=kr*rbscm+br;
			//cout<<fscm<r"  "<<bscm<<endl;
			//
			SiRF_SCM[id]=rfscm;
			SiRB_SCM[id]=rbscm;
			SiRF_E[id]=rfcal;
			SiRB_E[id]=rbcal;

			if(rfcal>SiRF_Emax) { SiRF_Emax=rfcal; SiRF_id=id;}
			if(rbcal>SiRB_Emax) { SiRB_Emax=rbcal; SiRB_id=id;}


			//if(id==31) cout<<rfraw<<" "<<rfscm<<" "<<rfcal<<endl;


		}

		if(abs(SiLF_Emax-SiLB_Emax)>300) {SiLF_id=-1;SiLB_id=-1;SiLF_Emax=-9999;SiLB_Emax=-9999;}
		if(abs(SiRF_Emax-SiRB_Emax)>300) {SiRF_id=-1;SiRB_id=-1;SiRF_Emax=-9999;SiRB_Emax=-9999;}


//		if(SiLB_id<16) CsILE=CsILpar[SiLF_id][SiLB_id][0]*CsILL_rawADC+CsILpar[SiLF_id][SiLB_id][1];
//		else if(SiLF_id<16&&SiLB_id>15) CsILE=CsILpar[SiLF_id][SiLB_id][0]*CsILRT_rawADC+CsILpar[SiLF_id][SiLB_id][1];
//		else if(SiLF_id>15&&SiLB_id>15) CsILE=CsILpar[SiLF_id][SiLB_id][0]*CsILRB_rawADC+CsILpar[SiLF_id][SiLB_id][1];

		CsILL_E =-9999;
		CsILRT_E=-9999;
		CsILRB_E=-9999;

		if(SiLF_id>-1&&SiLB_id>-1)
		{
			CsILL_E =CsILLpar[SiLF_id][SiLB_id][0]*CsILL_rawADC+CsILLpar[SiLF_id][SiLB_id][1];
			CsILRT_E =CsILRTpar[SiLF_id][SiLB_id][0]*CsILRT_rawADC+CsILRTpar[SiLF_id][SiLB_id][1];
			CsILRB_E =CsILRBpar[SiLF_id][SiLB_id][0]*CsILRB_rawADC+CsILRBpar[SiLF_id][SiLB_id][1];
			//cout<<CsILRBpar[SiLF_id][SiLB_id][0]<<endl;
		}

		CsIRLT_E=-9999;
		CsIRLB_E=-9999;
		CsIRRT_E=-9999;
		CsIRRB_E=-9999;



		if(SiRF_id>-1&&SiRB_id>-1)
		{
			CsIRRT_E =CsIRRTpar[SiRF_id][SiRB_id][0]*CsIRRT_rawADC+CsIRRTpar[SiRF_id][SiRB_id][1];
			CsIRRB_E =CsIRRBpar[SiRF_id][SiRB_id][0]*CsIRRB_rawADC+CsIRRBpar[SiRF_id][SiRB_id][1];

			CsIRLT_E =CsIRLTpar[SiRF_id][SiRB_id][0]*CsIRLT_rawADC+CsIRLTpar[SiRF_id][SiRB_id][1];
			CsIRLB_E =CsIRLBpar[SiRF_id][SiRB_id][0]*CsIRLB_rawADC+CsIRLBpar[SiRF_id][SiRB_id][1];
	
			//cout<<CsIRRBpar[SiLF_id][SiLB_id][0]<<endl;
		}



		//		CsIRLT_E=0.357925*CsIRLT_rawADC-139.651;
		//		CsIRLB_E=0.40584 *CsIRLB_rawADC-137.378;
		//		CsIRRT_E=0.350254*CsIRRT_rawADC-105.061;
//		CsIRRB_E=0.350748*CsIRRB_rawADC-108.566;





		CsI_LL_E =0.464291*CsILL_rawADC-150.243;
		CsI_LRT_E=0.306815*CsILRT_rawADC-101.453;
		CsI_LRB_E=0.353228*CsILRB_rawADC-117.866;

		CsI_RLT_E=0.357925*CsIRLT_rawADC-139.651;
		CsI_RLB_E=0.40584 *CsIRLB_rawADC-137.378;
		CsI_RRT_E=0.350254*CsIRRT_rawADC-105.061;
		CsI_RRB_E=0.350748*CsIRRB_rawADC-108.566;


		if(CsI_LL_E>MaxCsI_E) MaxCsI_E=CsI_LL_E;
		if(CsI_LRT_E>MaxCsI_E) MaxCsI_E=CsI_LRT_E;
		if(CsI_LRB_E>MaxCsI_E) MaxCsI_E=CsI_LRB_E;

		if(CsI_RLT_E>MaxCsI_E) MaxCsI_E=CsI_RLT_E;
		if(CsI_RLB_E>MaxCsI_E) MaxCsI_E=CsI_RLB_E;
		if(CsI_RRT_E>MaxCsI_E) MaxCsI_E=CsI_RRT_E;
		if(CsI_RRB_E>MaxCsI_E) MaxCsI_E=CsI_RRB_E;



		CsI_LL_ADC = CsILL_rawADC ;
		CsI_LRT_ADC= CsILRT_rawADC;
		CsI_LRB_ADC= CsILRB_rawADC;

		CsI_RLT_ADC= CsIRLT_rawADC;
		CsI_RLB_ADC= CsIRLB_rawADC;
		CsI_RRT_ADC= CsIRRT_rawADC;
		CsI_RRB_ADC= CsIRRB_rawADC;





		// 2018/09/12
		//	if(Silicons_ID->size()>0)
		//	{
		//		for(unsigned int j =0;j<Silicons_ID->size();j++)
		//		{
		//			int sid=Silicons_ID->at(j);

		//			double sienergy=Silicons_Energy->at(j);
		//			double sitime=Silicons_Time->at(j);
		//			double six=Silicons_X->at(j);
		//			double siy=Silicons_Y->at(j);
		//			double siz=Silicons_Z->at(j);
		//			//cout<<"sid="<<sid<<" sienergy="<<sienergy<<endl;

		//			AllTele_E[sid-1]=sienergy;
		//			AllTele_T[sid-1]=sitime;

		//			if(sid<129&&sid>0)
		//			{
		//				AllSi_E[sid-1]=sienergy;
		//				AllSi_T[sid-1]=sitime;

		//				if(sienergy>MaxSi_E) 
		//				{
		//					MaxSi_E=sienergy;
		//					MaxSi_ID=sid;
		//					//cout<<MaxSi_E<<" "<<MaxSi_ID<<endl;
		//				}

		//				if(sid<33&&sid>0)
		//				{
		//					SiLF_E[sid-1]=sienergy;
		//					SiLF_T[sid-1]=sitime;
		//					//SiLF_X[sid-1]=six;
		//					//SiLF_Y[sid-1]=siy;
		//					//SiLF_Z[sid-1]=siz;

		//				}
		//				if(sid>32&&sid<65)
		//				{
		//					//cout<<"LB"<<sid<<endl;
		//					SiLB_E[sid-1-32]=sienergy;
		//					SiLB_T[sid-1-32]=sitime;
		//					//SiLB_X[sid-1-32]=six;
		//					//SiLB_Y[sid-1-32]=siy;
		//					//SiLB_Z[sid-1-32]=siz;
		//				}
		//				if(sid>64&&sid<97)
		//				{
		//					SiRF_E[sid-1-64]=sienergy;
		//					SiRF_T[sid-1-64]=sitime;
		//					//SiRF_X[sid-1-64]=six;
		//					//SiRF_Y[sid-1-64]=siy;
		//					//SiRF_Z[sid-1-64]=siz;
		//				}
		//				if(sid>96&&sid<129)
		//				{
		//					SiRB_E[sid-1-96]=sienergy;
		//					SiRB_T[sid-1-96]=sitime;
		//					//SiRB_X[sid-1-96]=six;
		//					//SiRB_Y[sid-1-96]=siy;
		//					//SiRB_Z[sid-1-96]=siz;
		//				}
		//			}
		//			else if(sid>128&&sid<136)
		//			{
		//				AllCsI_E[sid-129]=sienergy;
		//				AllCsI_T[sid-129]=sitime;
		//				//cout<<"sid="<<sid<<endl;

		//				if(sienergy>MaxCsI_E) 
		//				{
		//					MaxCsI_E=sienergy;
		//					MaxCsI_ID=sid;
		//				}

		//				switch(sid)
		//				{
		//					case 129:
		//						CsI_RLT_E=sienergy;
		//						CsI_RLT_T=sitime;
		//						//cout<<CsI_RLT_E<<endl;
		//						break;
		//					case 130:
		//						CsI_RRT_E=sienergy;
		//						CsI_RRT_T=sitime;
		//						break;
		//					case 131:
		//						CsI_RLB_E=sienergy;
		//						CsI_RLB_T=sitime;
		//						break;
		//					case 132:
		//						CsI_RRB_E=sienergy;
		//						CsI_RRB_T=sitime;
		//						break;
		//					case 133:
		//						CsI_LL_E=sienergy;
		//						CsI_LL_T=sitime;
		//						break;
		//					case 134:
		//						CsI_LRT_E=sienergy;
		//						CsI_LRT_T=sitime;
		//						break;
		//					case 135:
		//						CsI_LRB_E=sienergy;
		//						CsI_LRB_T=sitime;
		//						break;
		//					default:
		//						cout<<"Error CsI ID"<<endl;
		//				}
		//			}
		//			else
		//			{
		//				// the left 2 is id=136,137, Ref ch 
		//			}

		//		}
		//	}


		for (Int_t ii=0 ; ii < 14 ; ii++){
			ESPRI_NaI_ID_C[ii]      = ESPRI_NaI_ID[ii];
			ESPRI_NaI_Layer_C[ii]   = ESPRI_NaI_Layer[ii];
			ESPRI_NaI_Energy_C[ii]  = ESPRI_NaI_Energy[ii];
			ESPRI_NaI_EnergyL_C[ii] = ESPRI_NaI_EnergyL[ii];
			ESPRI_NaI_EnergyR_C[ii] = ESPRI_NaI_EnergyR[ii];
			//  ESPRI_NaI_Time[14]; // not used
			//  ESPRI_NaI_TimeL[14]; // not used
			//  ESPRI_NaI_TimeR[14]; // not used
		}

		for (Int_t ii=0 ; ii < 2; ii++){
			ESPRI_Plas_ID_C[ii]     = ESPRI_Plas_ID[ii];
			ESPRI_Plas_Layer_C[ii]  = ESPRI_Plas_Layer[ii];
			ESPRI_Plas_Energy_C[ii] = ESPRI_Plas_Energy[ii];
			ESPRI_Plas_EnergyU_C[ii]= ESPRI_Plas_EnergyU[ii];
			ESPRI_Plas_EnergyD_C[ii]= ESPRI_Plas_EnergyD[ii];
			ESPRI_Plas_Time_C[ii]   = ESPRI_Plas_Time[ii];
			ESPRI_Plas_TimeU_C[ii]  = ESPRI_Plas_TimeU[ii];
			ESPRI_Plas_TimeD_C[ii]  = ESPRI_Plas_TimeD[ii];
			// ESPRI_RDC_Side_C[ii]    = ESPRI_RDC_Side[ii];// not used
			ESPRI_RDC_X_C[ii]       = ESPRI_RDC_X[ii];
			ESPRI_RDC_A_C[ii]       = ESPRI_RDC_A[ii];
			ESPRI_RDC_Y_C[ii]       = ESPRI_RDC_Y[ii];
			ESPRI_RDC_B_C[ii]       = ESPRI_RDC_B[ii];
		}

		ESPRI_NaI_Mult_C = ESPRI_NaI_Mult;
		ESPRI_Plas_Mult_C =ESPRI_Plas_Mult;

		//GiB 9 may 2017

		if(Neutron_ID->size()>0){
			Long64_t *idx  = (Long64_t*) calloc (Neutron_ID->size(),sizeof(Long64_t));
			Double_t *tmpt = (Double_t*) calloc (Neutron_ID->size(),sizeof(Double_t));

			//#pragma omp parallel for num_threads(2)
			for(unsigned int j =0;j<Neutron_ID->size();j++){

				if(Neutron_ID->at(j)<=30){
					Neutron_Time->at(j) += NEBULAOffset1;//
				} else if(Neutron_ID->at(j)<=60){
					Neutron_Time->at(j) += NEBULAOffset2;//
				} else if(Neutron_ID->at(j)<=90){
					Neutron_Time->at(j) += NEBULAOffset3;//
				} else {
					Neutron_Time->at(j) += NEBULAOffset4;//
				}

				tmpt[j] = Neutron_Time->at(j) ;
				if(tmpt[j]<0){
					tmpt[j] = 1/0.; // NAN positive !!
				}
			}

			TMath::Sort((Long64_t)Neutron_ID->size(),tmpt,idx,kFALSE);

			Neutron_X_sorted->resize(Neutron_ID->size());
			Neutron_Y_sorted->resize(Neutron_ID->size());
			Neutron_Z_sorted->resize(Neutron_ID->size());
			Neutron_ChargeUp_sorted->resize(Neutron_ID->size());
			Neutron_ChargeDown_sorted->resize(Neutron_ID->size());
			Neutron_Charge_sorted->resize(Neutron_ID->size());
			Neutron_ID_sorted->resize(Neutron_ID->size());
			Neutron_Time_sorted->resize(Neutron_ID->size());
			Neutron_IsNEBULA_sorted->resize(Neutron_ID->size());
			Neutron_Beta_sorted->resize(Neutron_ID->size());
			Neutron_Energy_sorted->resize(Neutron_ID->size());

			Double_t tmpGamma = NAN, tmpBeta = NAN, tmpR2 = NAN;

			for(unsigned int j =0;j<Neutron_ID->size();j++){
				Neutron_X_sorted->at(j) = Neutron_X->at(idx[j]); tmpR2  = Neutron_X->at(idx[j])*Neutron_X->at(idx[j]);
				Neutron_Y_sorted->at(j) = Neutron_Y->at(idx[j]); tmpR2 += Neutron_Y->at(idx[j])*Neutron_Y->at(idx[j]);
				Neutron_Z_sorted->at(j) = Neutron_Z->at(idx[j]); tmpR2 += Neutron_Z->at(idx[j])*Neutron_Z->at(idx[j]);
				Neutron_ChargeUp_sorted->at(j) = Neutron_ChargeUp->at(idx[j]);
				Neutron_ChargeDown_sorted->at(j) = Neutron_ChargeDown->at(idx[j]);
				Neutron_Charge_sorted->at(j) = Neutron_Charge->at(idx[j]);
				Neutron_ID_sorted->at(j) = Neutron_ID->at(idx[j]);
				Neutron_Time_sorted->at(j) = Neutron_Time->at(idx[j]);
				Neutron_IsNEBULA_sorted->at(j) = Neutron_IsNEBULA->at(idx[j]);

				tmpBeta = TMath::Sqrt(tmpR2)/Neutron_Time_sorted->at(j)/C_light;

				if(tmpBeta>0){
					Neutron_Beta_sorted->at(j) = tmpBeta ;
					tmpGamma = 1./TMath::Sqrt(1.-Neutron_Beta_sorted->at(j)*Neutron_Beta_sorted->at(j));
				} else  {
					tmpBeta = NAN;
					tmpGamma = NAN;
				}

				if(tmpBeta<0.8 && tmpBeta>0.1){
					Neutron_Energy_sorted->at(j) = (tmpGamma-1)*M_n;
				} else {
					Neutron_Energy_sorted->at(j) = NAN;
				}

			}
		}

		//////////////////////////////////
		// Define Neutron LorentzVector //
		//////////////////////////////////

		Erel_1n = NAN;
		Neut_Vector.SetXYZM(NAN,NAN,NAN,NAN);

		if(Neutron_Energy_sorted->size()>0){

			Double_t Neut_Momentum = TMath::Sqrt(Neutron_Energy_sorted->at(0)*(Neutron_Energy_sorted->at(0)+2*M_n));
			Double_t Neut_Theta = TMath::ACos(Neutron_Z_sorted->at(0)/TMath::Sqrt(Neutron_X_sorted->at(0)*Neutron_X_sorted->at(0)+
						Neutron_Y_sorted->at(0)*Neutron_Y_sorted->at(0)+
						Neutron_Z_sorted->at(0)*Neutron_Z_sorted->at(0)));
			Double_t Neut_Phi =  TMath::ATan(Neutron_Y_sorted->at(0)/Neutron_X_sorted->at(0));

			tmpVect3.SetMagThetaPhi(Neut_Momentum,
					Neut_Theta,
					Neut_Phi);

			Neut_Vector.SetVectM(tmpVect3,M_n);

			//////////////////////////////////
			// Define Relative Energy ////////
			//////////////////////////////////

			//	cout << M_f << "  " << Frag_Vector.M() << " " <<  Frag_Momentum << " " << Frag_Theta << " " << Frag_Phi << endl;	
			//	cout << Neut_Vector.M() << " " <<  Neut_Momentum << " " << Neut_Theta << " " << Neut_Phi << endl;

			TLorentzVector QVtot = Neut_Vector+Frag_Vector;
			Erel_1n = QVtot.M()- (Neut_Vector.M()+Frag_Vector.M());

			//	cout << Erel_1n << endl<< endl;

		}
		////////////////////////////////////////////////////////////////////

		newtree->Fill();

	}
	cout << '\r' << "\033[1;32mConversion Done :  " << 100 << "%    " << flush;
	cout << "\033[0m" << endl;

	//newtree->Print();
	newfile->Write();

	delete newfile;
	delete infile;

	return 0;
	}


	double calibrate(double value,vector<double>& par){
		int size=par.size();
		double calval=0;
		for(int i=0;i<size;i++)
			calval+=  par[i]*TMath::Power(value,i);

		return calval;
	}

	void initialize(vector< vector<double> > & vec, string file)
	{
		ifstream myfile;
		myfile.open (file.data());
		std::string line;
		while ( getline( myfile, line ) )
		{
			std::istringstream is( line );
			vec.push_back(std::vector<double>( std::istream_iterator<double>(is),
						std::istream_iterator<double>() ) );
		}

	}


	//_________________________________________________________________________________________________

	void SortNeutronHit(int left, int right,vector <Bool_t> *Neutron_IsNEBULA, vector <Int_t> *Neutron_ID,vector <Double_t> *Neutron_X,vector <Double_t> *Neutron_Y,vector <Double_t> *Neutron_Z,vector <Double_t> *Neutron_ChargeUp, vector <Double_t> *Neutron_ChargeDown, vector <Double_t> *Neutron_Charge, vector <Double_t> *Neutron_Time){
		int i = left, j = right;
		double pivot = Neutron_Time->at((left + right) / 2);

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

		if (left < j)
			SortNeutronHit(left, j,Neutron_IsNEBULA,Neutron_ID,Neutron_X,Neutron_Y,Neutron_Z,Neutron_ChargeUp, Neutron_ChargeDown, Neutron_Charge, Neutron_Time);
		if (i < right)
			SortNeutronHit(i, right,Neutron_IsNEBULA,Neutron_ID,Neutron_X,Neutron_Y,Neutron_Z,Neutron_ChargeUp, Neutron_ChargeDown, Neutron_Charge, Neutron_Time);

	}

	//______________________________________________________________________________________________

	void vertex(double *p, double *pp, double &xv,double &yv,double &zv, double &min_dist) {
		//track 1 
		double a1 = p[0]; //x
		double a2 = p[2]; //x velocity
		double b1 = p[1]; //y 
		double b2 = p[3]; //y velocity
		//track 2
		double ap1 = pp[0];
		double ap2 = pp[2];
		double bp1 = pp[1];
		double bp2 = pp[3];

		double alpha, beta, A, B, C;

		alpha = (bp1*(a1-ap1)+bp2*(a2-ap2))/(bp1*bp1 + bp2*bp2 + 1);
		beta = (bp1*b1+bp2*b2+1)/(bp1*bp1 + bp2*bp2 + 1);

		A = beta*(bp1*bp1 + bp2*bp2 + 1) - (bp1*b1 + bp2*b2 + 1);
		B = (b1*b1 + b2*b2 + 1) - beta*(bp1*b1+bp2*b2+1);
		C = beta*(bp1*(ap1-a1) + bp2*(ap2-a2)) - (b1*(ap1-a1) + b2*(ap2-a2));

		double sol1, solf1;
		double x,y,z,xp,yp,zp;


		sol1 = -(A*alpha + C)/(A*beta + B);
		solf1 = alpha + beta* sol1;

		x = a1 + b1*sol1;
		y = a2 + b2*sol1;
		z = sol1;
		xp = ap1 + bp1*solf1;
		yp = ap2 + bp2*solf1;
		zp = solf1;

		xv = (x+xp)/2.;
		yv = (y+yp)/2.;
		zv = (z+zp)/2.;
		min_dist = sqrt(pow((x-xp),2) + pow((y-yp),2) + pow((z-zp),2));

	}

	void vertex_angle(double *p, double *pp, double &xv,double &yv,double &zv, double &min_dist, double &Theta_tr1, double &Theta_tr2) {
		double a1 = p[0];
		double a2 = p[2];
		double b1 = p[1];
		double b2 = p[3];
		double ap1 = pp[0];
		double ap2 = pp[2];
		double bp1 = pp[1];
		double bp2 = pp[3];

		double alpha, beta, A, B, C;

		alpha = (bp1*(a1-ap1)+bp2*(a2-ap2))/(bp1*bp1 + bp2*bp2 + 1);
		beta = (bp1*b1+bp2*b2+1)/(bp1*bp1 + bp2*bp2 + 1);

		A = beta*(bp1*bp1 + bp2*bp2 + 1) - (bp1*b1 + bp2*b2 + 1);
		B = (b1*b1 + b2*b2 + 1) - beta*(bp1*b1+bp2*b2+1);
		C = beta*(bp1*(ap1-a1) + bp2*(ap2-a2)) - (b1*(ap1-a1) + b2*(ap2-a2));

		double sol1, solf1;
		double x,y,z,xp,yp,zp;
		double xt,yt,zt=1;

		sol1 = -(A*alpha + C)/(A*beta + B);
		solf1 = alpha + beta* sol1;

		x = a1 + b1*sol1;
		y = a2 + b2*sol1;
		z = sol1;
		xp = ap1 + bp1*solf1;
		yp = ap2 + bp2*solf1;
		zp = solf1;

		xv = (x+xp)/2.;
		yv = (y+yp)/2.;
		zv = (z+zp)/2.;
		min_dist = sqrt(pow((x-xp),2) + pow((y-yp),2) + pow((z-zp),2));
		//cout<<endl;
		//cout<<"mid-dist(11): "<<min_dist<<endl;

		//below modified by yzh
		//Theta_tr1 = TMath::ATan(TMath::Sqrt((x-a1)*(x-a1)+(y-a2)*(y-a2))/TMath::Abs(sol1));
		//Theta_tr2 = TMath::ATan(TMath::Sqrt((xp-ap1)*(xp-ap1)+(yp-ap2)*(yp-ap2))/TMath::Abs(solf1));
		//1st track
		zt=1;
		xt=b1;
		yt=b2;
		Theta_tr1=TMath::ACos(zt/sqrt(xt*xt+yt*yt+zt*zt));

		//2nd track
		zt=1;
		xt=bp1;
		yt=bp2;
		Theta_tr2=TMath::ACos(1.0/sqrt(xt*xt+yt*yt+zt*zt));


		Theta_tr1 = Theta_tr1*180./PI;
		Theta_tr2 = Theta_tr2*180./PI;
		// if(Theta_tr1 < 0){
		//   cout <<  Theta_tr1*180./PI << endl;
		// }
	}


	Double_t ExtractMassExcess(string line){

		string      Frag_Name;         // Nucleus name
		string      Frag_NucleusName;
		int         Frag_Charge;      // Nucleus charge
		int         Frag_AtomicWeight;   // Nucleus atomic weight
		double      Frag_MassExcess;   // Nucleus mass excess in keV
		string      Frag_SpinParity;   // Nucleus spin and parity
		double      Frag_Spin;         // Nucleus spin
		string      Frag_Parity;      // Nucleus parity
		double      Frag_LifeTime; // life time

		// name of the isotope
		Frag_Name = line.substr(11,7);
		// charge and mass
		string s_mass   = line.substr(0,3);
		string s_charge = line.substr(4,4);
		Frag_AtomicWeight = atoi(s_mass.data());
		Frag_Charge       = atoi(s_charge.data()); Frag_Charge /= 10;

		// mass excess
		string s_excess = line.substr(18,10);
		Frag_MassExcess = atof(s_excess.data());

		// life time
		string s_lt_units = line.substr(69,3); 
		string s_LifeTime = line.substr(57,12);
		// Remove space
		s_LifeTime.erase( std::remove_if( s_LifeTime.begin(), s_LifeTime.end(), ::isspace ), s_LifeTime.end() );
		s_lt_units.erase( std::remove_if( s_lt_units.begin(), s_lt_units.end(), ::isspace ), s_lt_units.end() );

		if(s_LifeTime=="stbl")
			Frag_LifeTime=-1;
		else
			Frag_LifeTime=atof(s_LifeTime.data());

		if(s_lt_units=="ms")
			Frag_LifeTime*=1e-3;
		else if(s_lt_units=="us")
			Frag_LifeTime*=1e-6;
		else if(s_lt_units=="ns")
			Frag_LifeTime*=1e-9;
		else if(s_lt_units=="ps")
			Frag_LifeTime*=1e-12;
		else if(s_lt_units=="fs")
			Frag_LifeTime*=1e-15;
		else if(s_lt_units=="as")
			Frag_LifeTime*=1e-18;
		else if(s_lt_units=="zs")
			Frag_LifeTime*=1e-21;
		else if(s_lt_units=="zs")
			Frag_LifeTime*=1e-23;
		else if(s_lt_units=="m")
			Frag_LifeTime*=60;
		else if(s_lt_units=="h")
			Frag_LifeTime*=3600;
		else if(s_lt_units=="d")
			Frag_LifeTime*=3600*24;
		else if(s_lt_units=="y")
			Frag_LifeTime*=3600*24*365.25;
		else if(s_lt_units=="ky")
			Frag_LifeTime*=3600*24*365.25*1e3;
		else if(s_lt_units=="My")
			Frag_LifeTime*=3600*24*365.25*1e6;
		else if(s_lt_units=="Gy")
			Frag_LifeTime*=3600*24*365.25*1e9;
		else if(s_lt_units=="Py")
			Frag_LifeTime*=3600*24*365.25*1e12;

		// spin and parity
		string s_spinparity = line.substr(79,14);
		Frag_SpinParity = s_spinparity.data();
		size_t found_p = s_spinparity.find("+");
		size_t found_m = s_spinparity.find("-");
		//   size_t found_( = s_jpi.find("(");
		//   size_t found_) = s_jpi.find(")");
		//   size_t found_# = s_jpi.find("#");
		// parity
		if (found_p != string::npos) Frag_Parity = "+";
		if (found_m != string::npos) Frag_Parity = "-";
		// spin
		if (s_spinparity.find("0")    != string::npos) Frag_Spin = 0     ;
		if (s_spinparity.find("1")    != string::npos) Frag_Spin = 1     ;
		if (s_spinparity.find("2")    != string::npos) Frag_Spin = 2     ;
		if (s_spinparity.find("3")    != string::npos) Frag_Spin = 3     ;
		if (s_spinparity.find("4")    != string::npos) Frag_Spin = 4     ;
		if (s_spinparity.find("5")    != string::npos) Frag_Spin = 5     ;
		if (s_spinparity.find("6")    != string::npos) Frag_Spin = 6     ;
		if (s_spinparity.find("7")    != string::npos) Frag_Spin = 7     ;
		if (s_spinparity.find("8")    != string::npos) Frag_Spin = 8     ;
		if (s_spinparity.find("9")    != string::npos) Frag_Spin = 9     ;
		if (s_spinparity.find("10")   != string::npos) Frag_Spin = 10    ;
		if (s_spinparity.find("1/2")  != string::npos) Frag_Spin = 0.5   ;
		if (s_spinparity.find("3/2")  != string::npos) Frag_Spin = 1.5   ;
		if (s_spinparity.find("5/2")  != string::npos) Frag_Spin = 2.5   ;
		if (s_spinparity.find("7/2")  != string::npos) Frag_Spin = 3.5   ;
		if (s_spinparity.find("9/2")  != string::npos) Frag_Spin = 4.5   ;
		if (s_spinparity.find("11/2") != string::npos) Frag_Spin = 5.5   ;
		if (s_spinparity.find("13/2") != string::npos) Frag_Spin = 6.5   ;
		if (s_spinparity.find("15/2") != string::npos) Frag_Spin = 7.5   ;
		if (s_spinparity.find("17/2") != string::npos) Frag_Spin = 8.5   ;
		if (s_spinparity.find("19/2") != string::npos) Frag_Spin = 9.5   ;
		if (s_spinparity.find("21/2") != string::npos) Frag_Spin = 10.5 ;
		//  Frag_NucleusName.assign(Frag_Name); 
		return Frag_MassExcess;
	} 

	Double_t ReadMassExcess(string isotope){
		//----------- Constructor Using nubtab03.asc by name----------
		// open the file to read and check if it is open

		Double_t mass = 0;

		// Replace the p,d,t,a by there standard name:
		if(isotope=="p") isotope="1H";
		else if(isotope=="d") isotope="2H";
		else if(isotope=="t") isotope="3H";
		else if(isotope=="a") isotope="4He";

		ifstream inFile;

		string FileName = "nubtab12.asc";
		inFile.open(FileName.c_str());

		// reading the file
		string line, s_name;
		size_t space;
		if (inFile.is_open()) {
			while (!inFile.eof()) {
				getline(inFile,line);

				s_name = line.substr(11,7);
				space = s_name.find_first_of(" ");
				s_name.resize(space);

				if (s_name.find(isotope) != string::npos && s_name.length() == isotope.length()) break;
			}
			mass  = ExtractMassExcess(line.data());
		}
		else cout << "Unable to open file nuclear data base file " << FileName << endl;

		return mass;

	}

	Double_t angle_difference_degree(Double_t x, Double_t y){
		return 180 - TMath::Abs(TMath::Abs(x - y) - 180) ;
	}

#ifndef __CINT__
	int main(int argc, char *argv[]){
		if(argc>1){
			analysis(TString(argv[1]).Atoi());
		}
		return 0;
	}
#endif

