#ifndef __CINT__
#include <iostream>

#include <TFile.h>
#include <TSystem.h>
#include <TString.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TVector3.h>
#include <TDatime.h>
#include <TCanvas.h>
#include <TROOT.h>
#include <TPad.h>
#include <TStyle.h>
#include <TEllipse.h>
//core                                                                                
#include "TArtCore.hh"
#include "TArtStoreManager.hh"
#include "TArtEventStore.hh"

//parameters                                                                          
#include "TArtSAMURAIParameters.hh"
#include "TArtBigRIPSParameters.hh"

//bigrips                                                                             
#include "TArtCalibPlastic.hh"
#include "TArtPlastic.hh"
#include "TArtPlasticPara.hh"
//#include "TArtRecoBeam.hh"                                                          
//#include "TArtRecoPID.hh"                                                           

#include "TArtCalibIC.hh"
#include "TArtIC.hh"
#include "TArtCalibBDC1Hit.hh"
#include "TArtCalibBDC2Hit.hh"
#include "TArtCalibBDC1Track.hh"
#include "TArtCalibBDC2Track.hh"

#include "TArtCalibFDC1Hit.hh"
#include "TArtCalibFDC1Track.hh"

#include "TArtCalibFDC2Hit.hh"
#include "TArtCalibFDC2Track.hh"


#include "TArtDCHit.hh"
#include "TArtDCTrack.hh"
#include "TArtCalcGlobalTrack.hh"

//coin                                                                                
#include "TArtCalibCoin.hh"
#endif

void mkdcdist(Int_t neve_max=1000,Int_t runnum=0)
{
  ifstream ifs1;
  ifstream ifs2;
  ifs1.open("./macros/bdc/Calib/pid_prm.txt");
  ifs2.open("./macros/bdc/Calib/tof713off.txt");

  Double_t Z_low;
  Double_t Z_high;
  Double_t TOF_low;
  Double_t TOF_high;
  Double_t TOF713off;

  ifs1>>TOF_low>>TOF_high>>Z_low>>Z_high;
  ifs2>>TOF713off;

  TFile *f = new TFile("root/dcdist.root","RECREATE");
  TArtBigRIPSParameters *bigrips_prm = new TArtBigRIPSParameters();
  bigrips_prm->LoadParameter("db/SAMURAIPlastic.xml");
  bigrips_prm->LoadParameter("db/BigRIPSIC.xml");
  TArtSAMURAIParameters *samurai_prm = new TArtSAMURAIParameters();
  samurai_prm->LoadParameter("db/SAMURAIBDC1.xml");
  samurai_prm->LoadParameter("db/SAMURAIBDC2.xml");
  samurai_prm->LoadParameter("db/SAMURAIFDC1.xml");
  samurai_prm->LoadParameter("db/SAMURAIFDC2.xml");

  TArtEventStore *estore = new TArtEventStore();
  TString ridffilename = Form("ridf/run%04d.ridf.gz",runnum); 
  if(runnum!=0){
  estore->Open(ridffilename.Data());// for offline analysis
  }
  if(runnum==0){
    estore->Open(0);// for online analysis
  }
  TArtCalibPlastic *calibpla = new TArtCalibPlastic;
  TArtCalibIC *calibic= new TArtCalibIC;

  TArtCalibBDC1Hit *calibbdc1hit = new TArtCalibBDC1Hit;
  TArtCalibBDC2Hit *calibbdc2hit = new TArtCalibBDC2Hit;
  TArtCalibFDC1Hit *calibfdc1hit = new TArtCalibFDC1Hit;
  TArtCalibFDC2Hit *calibfdc2hit = new TArtCalibFDC2Hit;

  TH1* hbeampid = new TH2D("hbeampid","PID",160,-80,80, 200,0,6000);
  TH1* hbeampid_g = new TH2D("hbeampid_g","PID gated",160,-80,80, 200,0,6000);

  TH1* hbdc1tdc[8];
  for (int ilayer=0;ilayer<8;++ilayer){
    hbdc1tdc[ilayer] = new TH1I(Form("hbdc1tdc%d",ilayer),
				Form("BDC1 TDC layer=%d",ilayer),200,1700,1900);
  }
  TH1* hbdc2tdc[8];
  for (int ilayer=0;ilayer<8;++ilayer){
    hbdc2tdc[ilayer] = new TH1I(Form("hbdc2tdc%d",ilayer),
				Form("BDC2 TDC layer=%d",ilayer),200,1700,1900);
  }
  TH1* hfdc1tdc[14];
  for (int ilayer=0;ilayer<14;++ilayer){
    hfdc1tdc[ilayer] = new TH1I(Form("hfdc1tdc%d",ilayer),
				Form("FDC1 TDC layer=%d",ilayer),500,1400,1900);
  }
  TH1* hfdc2tdc[14];
  for (int ilayer=0;ilayer<14;++ilayer){
    hfdc2tdc[ilayer] = new TH1I(Form("hfdc2tdc%d",ilayer),
				Form("FDC2 TDC layer=%d",ilayer),700,1000,1700);
  }

  TArtStoreManager *sman = TArtStoreManager::Instance();

  int neve = -1;
  while(estore->GetNextEvent() && neve<neve_max){
    ++neve;
    if (neve%100==0){
      std::cout<<"\r event: "<<neve<<" / "
	       <<neve_max
	       <<" ("<<100.*neve/neve_max<<"%)"
	       <<std::flush;
    }
    //----------------------------------------------------------
    // Plastic
    Double_t tof713 = -9999;
    Double_t f7qave = -9999;
    calibpla->ClearData();
    calibpla->ReconstructData();
    TArtPlastic *f3pla=0;
    TArtPlastic *f5pla=0;
    TArtPlastic *f7pla=0;
    TArtPlastic *f13pla1=0;
    TArtPlastic *f13pla2=0;
    TClonesArray *pla_array = calibpla->GetPlasticArray();
    Int_t npla = pla_array->GetEntries();
    for(int ipla=0; ipla < npla; ++ipla){
      TArtPlastic* pla = (TArtPlastic*)pla_array->At(ipla);
      Int_t ID=pla->GetID();
      if (ID==1) f3pla = pla;
      if (ID==2) f5pla = pla;
      if (ID==3) f7pla = pla;
      if (ID==4) f13pla1 = pla;
      if (ID==5) f13pla2 = pla;
    }
    if (f7pla!=0 && f13pla1!=0 && f13pla2!=0) {
      tof713 = (f13pla1->GetTimeSlew()+f13pla2->GetTimeSlew())/2. - f7pla->GetTimeSlew() + TOF713off;
      f7qave = f7pla->GetQAveRaw();
    }

    //----------------------------------------------------------
    // PID
    bool OK_beam=false;

    hbeampid->Fill(tof713,f7qave);
    //cout<<tof713<<" "<<f7qave<<endl;
    //cout<<"TOF_low="<<TOF_low<<" TOF_high="<<TOF_high<<endl;
    //cout<<"Z_low="<<Z_low<<" Z_high="<<Z_high<<endl;

    if (tof713 > TOF_low && tof713 < TOF_high &&
	f7qave  > Z_low  && f7qave < Z_high      ) OK_beam = true;

    if (OK_beam) hbeampid_g->Fill(tof713,f7qave);

    if (!OK_beam) continue;
    //----------------------------------------------------------
    // BDC1
    calibbdc1hit->ClearData();
    calibbdc1hit->ReconstructData();
    TClonesArray *bdc1hits = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Hit");
    if(bdc1hits){
      Int_t bdc1nhit = bdc1hits->GetEntries();
      for (int i=0;i<bdc1nhit;++i){
	TArtDCHit *hit = (TArtDCHit*)bdc1hits->At(i);
	hbdc1tdc[hit->GetLayer()]->Fill(hit->GetTDC());
      }
    }
    //----------------------------------------------------------
    // BDC2
    calibbdc2hit->ClearData();
    calibbdc2hit->ReconstructData();
    TClonesArray *bdc2hits = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Hit");
    if(bdc2hits){
      Int_t bdc2nhit = bdc2hits->GetEntries();
      for (int i=0;i<bdc2nhit;++i){
	TArtDCHit *hit = (TArtDCHit*)bdc2hits->At(i);
	hbdc2tdc[hit->GetLayer()]->Fill(hit->GetTDC());
      }
    }
    //----------------------------------------------------------
    // FDC1
    calibfdc1hit->ClearData();
    calibfdc1hit->ReconstructData();
    TClonesArray *fdc1hits = (TClonesArray *)sman->FindDataContainer("SAMURAIFDC1Hit");
    if(fdc1hits){
      Int_t fdc1nhit = fdc1hits->GetEntries();
      for (int i=0;i<fdc1nhit;++i){
	TArtDCHit *hit = (TArtDCHit*)fdc1hits->At(i);
	hfdc1tdc[hit->GetLayer()]->Fill(hit->GetTDC());
      }
    }
    //----------------------------------------------------------
    // FDC2
    calibfdc2hit->ClearData();
    calibfdc2hit->ReconstructData();
    TClonesArray *fdc2hits = (TClonesArray *)sman->FindDataContainer("SAMURAIFDC2Hit");
    if(fdc2hits){
      Int_t fdc2nhit = fdc2hits->GetEntries();
      for (int i=0;i<fdc2nhit;++i){
	TArtDCHit *hit = (TArtDCHit*)fdc2hits->At(i);
	hfdc2tdc[hit->GetLayer()]->Fill(hit->GetTDC());
      }
    }
  
    estore->ClearData();
  }
  f->Write();
  return;
}
