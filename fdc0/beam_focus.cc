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
#include <TBox.h>

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

#include "TArtDCHit.hh"
#include "TArtDCTrack.hh"
#include "TArtCalcGlobalTrack.hh"

//coin
#include "TArtCalibCoin.hh"
#endif 

void beam_focus(Int_t runnum=0,Int_t nshow = 2000){
  /*
  Double_t Z_low = 20;
  Double_t Z_high = 30;
  Double_t TOF_low = 250;
  Double_t TOF_high = 260;
  */

  Double_t Z_low = -9999;
  Double_t Z_high = -9999;
  Double_t TOF_low = -9999;
  Double_t TOF_high = -9999;
  Double_t TOF713off = 0;

  ifstream ifs1;
  ifstream ifs2;
  ifs1.open("pid_prm.txt");
  ifs2.open("tof713off.txt");

  ifs1>>TOF_low>>TOF_high>>Z_low>>Z_high;
  ifs2>>TOF713off;

  TArtStoreManager* sman = TArtStoreManager::Instance();

 
  TArtSAMURAIParameters *smprm = new TArtSAMURAIParameters();
  TArtBigRIPSParameters* ripsprm =new TArtBigRIPSParameters();
  ripsprm->LoadParameter("db/SAMURAIPlastic.xml");
  smprm->LoadParameter("db/SAMURAIBDC1.xml");
  smprm->LoadParameter("db/SAMURAIBDC2.xml");
  smprm->LoadParameter("db/SAMURAIFDC1.xml");
  smprm->LoadParameter("db/SAMURAIFDC2.xml");
  smprm->LoadParameter("db/BigRIPSIC.xml");
  ripsprm->LoadParameter("db/BigRIPSIC.xml");
  smprm->LoadParameter("db/SAMURAIS1DC1.xml");
  smprm->LoadParameter("db/SAMURAIS1DC2.xml");


  TArtEventStore *estore = new TArtEventStore();

  //ctnprm->PrintListOfCsIPara();
  //ripsprm->PrintListOfPlasticPara();

  TString ridffile = Form("./ridf/run%04d.ridf.gz",runnum);
  //TString ridffile = "./oldridf/run0033.ridf.gz";
  if(runnum!=0){
    estore->Open(ridffile.Data());
  }else{
    estore->Open(0);
  }

  TArtCalibPlastic* calibpla = new TArtCalibPlastic;
  TArtCalibIC* calibic = new TArtCalibIC;
  //TArtCalibCoin *calibcoin = new TArtCalibCoin;
  TArtCalibBDC1Hit* calibbdc1hit = new TArtCalibBDC1Hit;
  TArtCalibBDC2Hit* calibbdc2hit = new TArtCalibBDC2Hit;
  TArtCalibBDC1Track* calibbdc1track = new TArtCalibBDC1Track;
  TArtCalibBDC2Track* calibbdc2track = new TArtCalibBDC2Track;
  TArtCalibFDC1Hit* calibfdc1hit = new TArtCalibFDC1Hit;
  TArtCalibFDC1Track* calibfdc1track = new TArtCalibFDC1Track;

  calibbdc1track->SetTDCWindow(1700,1850);  
  calibbdc2track->SetTDCWindow(1700,1840);

  TFile *dcin = new TFile("root/dcdist.root","READ");
  if(dcin->IsOpen()){
    gROOT->cd();
    TH1* hist = NULL;
    // BDC1
    for(Int_t ihist=0;ihist<8;ihist++){
      hist = (TH1D*)dcin->Get(Form("hbdc1tdc%d",ihist));
      calibbdc1track->SetTDCDistribution(hist,ihist);
      delete hist;
      hist = NULL;
    }

    // BDC2
    for(Int_t ihist=0;ihist<8;ihist++){
      hist = (TH1D*)dcin->Get(Form("hbdc2tdc%d",ihist));
      calibbdc2track->SetTDCDistribution(hist,ihist);
      delete hist;
      hist = NULL;
    }
  }

  //  TFile *f = new TFile(Form("root/run%04d.root",runnum),"RECREATE");
  TFile *f = new TFile("root/focusing.root","RECREATE");

  TH1* hpid = new TH2D("hpid","PID",160,-80,80,400,0,6000);
  TH1* hpid2 = new TH2D("hpid2","PID2(TOF713-F13Q)",160,-80,80,400,0,6000);
  TH1* hpid_outveto = new TH2D("hpid_outveto","hpid (r>15 @veto)",160,-60,60,400,0,6000);
  TH1* hpid_g = new TH2D("hpid_g","PID gated",160,-80,80,400,0,6000);
  TH1* hBVxy = new TH2D("hBVxy","Beam VETO XY",140,-70,70,140,-70,70);
  TH1* hBVxy_g = new TH2D("hBVxy_g","Beam VETO XY VETO ON",140,-100,100,140,-100,100);

  TH1* htgtxy[5];
  TH1* htgtxa[5];
  TH1* htgtyb[5];
  for(int i=0;i<5;i++){
    htgtxy[i] = new TH2D(Form("htgtxy%d",i),Form("Target XY %dm",i-2),100,-50,50,100,-50,50);
    htgtxa[i] = new TH2D(Form("htgtxa%d",i),Form("Target XA %dm",i-2),60,-30,30,60,-30,30);
    htgtyb[i] = new TH2D(Form("htgtyb%d",i),Form("Target YB %dm",i-2),60,-30,30,60,-30,30);
  }

  TH1* htgtxy_g[5];
  TH1* htgtxa_g[5];
  TH1* htgtyb_g[5];
  for(int i=0;i<5;i++){
    htgtxy_g[i] = new TH2D(Form("htgtxy_g%d",i),Form("Target XY %dm gated",i-2),100,-100,100,100,-100,100);
    htgtxa_g[i] = new TH2D(Form("htgtxa_g%d",i),Form("Target XA %dm gated",i-2),60,-30,30,60,-30,30);
    htgtyb_g[i] = new TH2D(Form("htgtyb_g%d",i),Form("Target YB %dm gated",i-2),60,-30,30,60,-30,30);
  }

  TH1* htgtx_g[5] ;
  TH1* htgty_g[5] ;
  TH1* htgta_g[5] ;
  TH1* htgtb_g[5] ;

  for(int i=0;i<5;i++){
   htgtx_g[i]= new TH1D(Form("htgtx_g%d",i),Form("Target X %d gated",i),100,-100,100);
   htgty_g[i]= new TH1D(Form("htgty_g%d",i),Form("Target Y %d gated",i),100,-50,50);
   htgta_g[i]= new TH1D(Form("htgta_g%d",i),Form("Target A %d gated",i),100,-50,50);
   htgtb_g[i]= new TH1D(Form("htgtb_g%d",i),Form("Target B %d gated",i),100,-50,50);
  }
  // TH1* hcoin = new TH1D("hcoin","coincidence",9,-0.5,8.5);
  Int_t nEvent = 1;
  Int_t nEventMax;
  if(runnum==0)
    nEventMax = 50001;
  else
    nEventMax = 100001;

  TCanvas* c_v= new TCanvas("c_v","c_v");  
  TCanvas* c_pro = new TCanvas("c_pro","c_pro");
  TCanvas* c_g = new TCanvas("c_g","c_g");
  TCanvas* cpi = new TCanvas("cpi","cpi");

  
  TF1* gausx=new TF1("gausx","gaus");
  TF1* gausy=new TF1("gausy","gaus");
  TF1* gausa=new TF1("gausa","gaus");
  TF1* gausb=new TF1("gausb","gaus");
 
  Int_t cnt_inbdc1 = 0;
  Int_t cnt_inbdc2 = 0;
  Int_t cnt_inbdc = 0;
  Int_t cnt_inveto = 0;
  Int_t cnt_inbdcveto = 0;
  cout<<"nEventMax="<<nEventMax<<endl;
  while(estore->GetNextEvent() && nEvent<nEventMax){
   
    if(nEvent%100==0)  std::cout << "\r event: " << nEvent << std::flush;
    if(nEvent%nshow == 0 || nEvent == nshow){
      std::cout << "\r event: " << nEvent << std::flush;
      c_g->Clear();
      c_pro->Clear();
      cpi->Clear();
      c_v->Clear();

      c_g->Divide(5,3);
      for(int k=0;k<5;k++){
	c_g->cd(k+1);
	htgtxy_g[k]->SetStats(0);
	htgtxy_g[k]->Draw("colz");
   if(k==3){
      TBox *b1 = new TBox(-80.,-80.,80.,80.);
      b1->SetFillStyle(0000);
      b1->Draw("SAME");
   }
   else
   {
      
	TEllipse *e = new TEllipse(0,0,16.,23.);
	e->SetFillStyle(0000);
	e->Draw("SAME");
   }
	c_g->cd(5+k+1);
	htgtxa_g[k]->SetStats(0);
	htgtxa_g[k]->Draw("colz");
	c_g->cd(10+k+1);
	htgtyb_g[k]->SetStats(0);
	htgtyb_g[k]->Draw("colz");
      }
      c_pro->Divide(2,2);
      c_pro->cd(1);
      htgtx_g[2]->Fit("gausx","Q");
      htgtx_g[2]->Draw(); c_pro->cd(2);
      htgty_g[2]->Fit("gausy","Q");
      htgty_g[2]->Draw();
      c_pro->cd(3);
      htgta_g[2]->Fit("gausa","Q");
      htgta_g[2]->Draw();
      c_pro->cd(4);
      htgtb_g[2]->Fit("gausb","Q");
      htgtb_g[2]->Draw();


      cpi->cd();
      cpi->Divide(2,1);
      cpi->cd(1);
      hpid->Draw("colz");
      cpi->cd(2);
      hpid_g->Draw("colz");

      c_v->cd();
      c_v->Divide(2,1);
      c_v->cd(1);
      hBVxy->Draw("colz");
      TEllipse *e_v = new TEllipse(0,0,16.,23.);
      e_v->SetFillStyle(0000);
      e_v->Draw("SAME");
      c_v->cd(2);
      hBVxy_g->Draw("colz");
      e_v->Draw("SAME");

      cpi->cd(1);
      gPad->Update();

      
      c_g->cd(1);
      gPad->Update();
      
      c_pro->cd(1);
      gPad->Update();

      c_v->cd(1);
      gPad->Update();      
    }
  
    /*
    calibcoin->ClearData();
    calibcoin->ReconstructData();
    */

    calibpla->ClearData();
    calibpla->ReconstructData();

    calibbdc1hit->ClearData();
    calibbdc1hit->ReconstructData();
    calibbdc2hit->ClearData();
    calibbdc2hit->ReconstructData();

    calibbdc1track->ClearData();
    calibbdc1track->ReconstructData();
    calibbdc2track->ClearData();
    calibbdc2track->ReconstructData();
    /*
    for(int id=0;id<9;id++){
      if(calibcoin->IsChTrue(id)){
	hcoin->Fill(id);
      }
    }
    
    if(!calibcoin->IsChTrue(0)){estore->ClearData();nEvent++;continue;} 
    */
    Double_t TOF713=-9999;
    Double_t f7qave=-9999;
    Double_t f13qave=-9999;
    Double_t F13t = -9999;

    Double_t BVQL=-9999;
    Double_t BVQR=-9999;
    Double_t BVQ=-9999;
    Double_t BVTL=-9999;
    Double_t BVTR=-9999;

    TArtPlastic* f7pla;
    TArtPlastic* f13pla1;
    TArtPlastic* f13pla2;
    TArtPlastic* vetopla;

    TClonesArray* pla_array = calibpla->GetPlasticArray();
    int npla=pla_array->GetEntries();
    for(int ipla=0; ipla < npla; ++ipla){
      TArtPlastic* pla = (TArtPlastic*)pla_array->At(ipla);
      Int_t ID=pla->GetID();
      if (ID==3) f7pla = pla;
      if (ID==4) f13pla1 = pla;
      if (ID==5) f13pla2 = pla;
      if (ID==6) vetopla = pla;
    }
    F13t = (f13pla1->GetTime()+f13pla2->GetTime())/2.;
    TOF713=F13t-f7pla->GetTime()+TOF713off;
    f7qave = f7pla->GetQAveRaw();
    f13qave = sqrt((f13pla1->GetQAveRaw())*(f13pla2->GetQAveRaw()));
    hpid->Fill(TOF713,f7qave);
    hpid2->Fill(TOF713,f13qave);

    //BVQL = vetopla->GetQLRaw();
    BVQR = vetopla->GetQRRaw();
    //BVQ = vetopla->GetQAveRaw();
    //BVTL = vetopla->GetTimeL();
    BVTR = vetopla->GetTimeR();

    // BDC1
    Double_t bdc1x=-9999,bdc1y=-9999;
    Double_t bdc1a=-9999,bdc1b=-9999;
    Bool_t OK_bdc1x = false;
    Bool_t OK_bdc1y = false;

    TClonesArray *bdc1trks = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC1Track");
    Int_t bdc1ntr = bdc1trks->GetEntries();
    for(int itr=0;itr<bdc1ntr;itr++){
      TArtDCTrack* bdc1track=(TArtDCTrack*)bdc1trks->At(itr);
      
      if(bdc1track->GetPosition(0)>-9999&&!OK_bdc1x){
	bdc1x = bdc1track->GetPosition(0);
	bdc1a = bdc1track->GetAngle(0);
	OK_bdc1x = true;
      }
      if(bdc1track->GetPosition(1)>-9999&&!OK_bdc1y){
	bdc1y = bdc1track->GetPosition(1);
	bdc1b = bdc1track->GetAngle(1);
	OK_bdc1y = true;
      } 
    }
    if(fabs(bdc1x)<=40&&fabs(bdc1y)<=40) cnt_inbdc1++;
    
    //BDC2                 
    Double_t bdc2x=-9999,bdc2y=-9999;
    Double_t bdc2a=-9999,bdc2b=-9999;
    Bool_t OK_bdc2x = false;
    Bool_t OK_bdc2y = false;
    
    TClonesArray *bdc2trks = (TClonesArray *)sman->FindDataContainer("SAMURAIBDC2Track");
    Int_t bdc2ntr = bdc2trks->GetEntries();
    
    for(int itr=0;itr<bdc2ntr;itr++){
      TArtDCTrack* bdc2track=(TArtDCTrack*)bdc2trks->At(itr);
      
      if(bdc2track->GetPosition(0)>-9999&&!OK_bdc2x){
	bdc2x = bdc2track->GetPosition(0);
	bdc2a = bdc2track->GetAngle(0)*1000.;
	OK_bdc2x = true;
      }
      if(bdc2track->GetPosition(1)>-9999&&!OK_bdc2y){
	bdc2y = bdc2track->GetPosition(1);
	bdc2b = bdc2track->GetAngle(1)*1000.;
	OK_bdc2y = true;
      }
    }
    
    if(fabs(bdc2x)<=40&&fabs(bdc2y)<=40) cnt_inbdc2++;                               
    //if(BVTL<0&&BVTR<0) cnt_inveto++;
    if(BVQR<0) cnt_inveto++;
    if(fabs(bdc1x)<=40&&fabs(bdc1y)<=40&&fabs(bdc2x)<=40&&fabs(bdc2y)<=40) cnt_inbdc++;
    if(fabs(bdc1x)<=40&&fabs(bdc1y)<=40&&fabs(bdc2x)<=40&&fabs(bdc2y)<=40&&BVQR<0) cnt_inbdcveto++;
    //if(fabs(bdc1x)<=40&&fabs(bdc1y)<=40&&fabs(bdc2x)<=40&&fabs(bdc2y)<=40&&BVTL<0&&BVTR<0) cnt_inbdcveto++;

    //Z position tgt center : Z=0
    //Double_t bdc1z=-6624.-60.+4217; //  front face - 60 mm - tgt_pos
    //Double_t bdc2z=-5615.-60.+4217; //  front face - 60 mm - tgt_pos
    //Double_t vetoz=-109-70-10;
    Double_t bdc1z=-6666.11+4222.34; //  center - tgt_pos
    Double_t bdc2z=-5666.67+4222.34; //  center - tgt_pos
    Double_t vetoz=-896.;// Veto detector -150/2-591-460/2
    Double_t ftgtz =0;

    TVector3 beambdc1(bdc1x,bdc1y,bdc1z);
    TVector3 beambdc2(bdc2x,bdc2y,bdc2z);

    TVector3 beamv =beambdc2-beambdc1;
 
    Double_t tgta=atan(beamv.X()/beamv.Z());
    Double_t tgtb=atan(beamv.Y()/beamv.Z());

    for(int j=0;j<5;j++){
      Double_t zpos=ftgtz+(j-2)*890.;
      Double_t kscale = (zpos-bdc1z)/(bdc2z-bdc1z);
      TVector3 beamvtgt=kscale*beamv+beambdc1;
      htgtxy[j]->Fill(beamvtgt.X(),beamvtgt.Y());
      htgtxa[j]->Fill(beamvtgt.X(),tgta*1000.);
      htgtyb[j]->Fill(beamvtgt.Y(),tgtb*1000.);
    }
    
    Double_t kscale_veto = (vetoz-bdc1z)/(bdc2z-bdc1z);
    TVector3 beamvveto=kscale_veto*beamv+beambdc1;
    
    hBVxy->Fill(beamvveto.X(),beamvveto.Y());
    //if(BVTL<0||BVTR<0){
    if(BVQR<0){
      hBVxy_g->Fill(beamvveto.X(),beamvveto.Y());
    }
    Double_t r_veto = TMath::Sqrt(pow(beamvveto.X()*23.,2)+pow(beamvveto.Y()*16.,2));
 
    if(r_veto>368.){
       //dimension of Veto detector are 32x46, so I made a*b(16*23) for condition
      //      cout<<"!!!"<<endl;
      //cout<<r_veto<<endl;
      hpid_outveto->Fill(TOF713,f7qave);
    }
    //gated    
    if(TOF_low<TOF713 && TOF713<TOF_high && Z_low<f7qave && f7qave<Z_high) {
      hpid_g->Fill(TOF713,f7qave);
      //bdc_____________________________________________________________________
      if(bdc1x>-9999&&bdc1y>-9999&&bdc2x>-9999&&bdc2y>-9999){
      
	for(int j=0;j<5;j++){
	  Double_t zpos=ftgtz+(j-2)*890.;
	  Double_t kscale = (zpos-bdc1z)/(bdc2z-bdc1z);
	  TVector3 beamvtgt=kscale*beamv+beambdc1;
	  htgtxy_g[j]->Fill(beamvtgt.X(),beamvtgt.Y());
	  htgtxa_g[j]->Fill(beamvtgt.X(),tgta*1000.);
	  htgtyb_g[j]->Fill(beamvtgt.Y(),tgtb*1000.);
	  
	  // projections
	  htgtx_g[j]->Fill(beamvtgt.X());
	  htgty_g[j]->Fill(beamvtgt.Y());
	  htgta_g[j]->Fill(tgta*1000.);
	  htgtb_g[j]->Fill(tgtb*1000.);

	}
      }
    }

    if(nEvent%nshow == 0){
      Double_t eff_inbdc1;
      Double_t eff_inbdc2;
      Double_t eff_inbdc;
      Double_t eff_inveto;
      Double_t eff_inbdcveto;

      eff_inbdc1 = 100*cnt_inbdc1/nEvent;
      eff_inbdc2 = 100*cnt_inbdc2/nEvent;
      eff_inbdc = 100*cnt_inbdc/nEvent;
      eff_inveto = 100*cnt_inveto/nEvent;
      eff_inbdcveto = 100*cnt_inbdcveto/nEvent;

      cout<<endl;
      cout<<"IN BDC1 : "<<eff_inbdc1<<"%"<<endl;
      cout<<"IN BDC2 : "<<eff_inbdc2<<"%"<<endl;
      cout<<"IN BDC1&BDC2 : "<<eff_inbdc<<"%"<<endl;
      cout<<"IN VETO(anti VETO signal) : "<<eff_inveto<<"%"<<endl;
      cout<<"IN BDC1&BDC2&VETO(anti VETO signal) : "<<eff_inbdcveto<<"%"<<endl;

      char x;
      cout<<endl;
      cout<<"Continue[c]? or SaveFigure[s]? or Finish[any other key]?"<<endl;
      cout<<"----->";
      cin>>x;
      cout<<endl;

      if(x == 's'){
	c_pro->Print("root/focus.root");
	c_g->Print("root/proj.root");
	cpi->Print("root/pid.root");
	c_v->Print("root/veto.root");
      }
      if(x != 'c' && x != 's') break;

    }
    estore->ClearData();
    nEvent++;
  }
  Double_t eff_inbdc1;
  Double_t eff_inbdc2;
  Double_t eff_inbdc;
  Double_t eff_inveto;
  Double_t eff_inbdcveto;

  eff_inbdc1 = 100*cnt_inbdc1/nEvent;
  eff_inbdc2 = 100*cnt_inbdc2/nEvent;
  eff_inbdc = 100*cnt_inbdc/nEvent;
  eff_inveto = 100*cnt_inveto/nEvent;
  eff_inbdcveto = 100*cnt_inbdcveto/nEvent;

  ofstream ofs;
  ofs.open("transport.txt");
  ofs<<"Count of each detector(x other one) / Beam Trigger : "<<endl;
  ofs<<endl;
  ofs<<"IN BDC1 : "<<eff_inbdc1<<"%"<<endl;
  ofs<<"IN BDC2 : "<<eff_inbdc2<<"%"<<endl;
  ofs<<"IN BDC1&BDC2 : "<<eff_inbdc<<"%"<<endl;
  ofs<<"IN VETO(anti VETO signal) : "<<eff_inveto<<"%"<<endl;
  ofs<<"IN BDC1&BDC2&VETO(anti VETO signal) : "<<eff_inbdcveto<<"%"<<endl;
  ofs.close();
  
  c_g->Print();
  c_pro->Print();
  cpi->Print();
  c_v->Print();

  f->Write();
  return;
}
