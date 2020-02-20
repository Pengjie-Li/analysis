#include "PositionTELE.h"
#include "CalibTELE.h"
class DEECurve{
	private:
		TGraph *dEE;
	public:
		DEECurve(){
			TFile *fCalib = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/alphaDEE/dEECurve.root","READ");
                        dEE = (TGraph *)gDirectory->Get("dEEReverse");
                        fCalib->Close();	

		}
		~DEECurve(){}
		double getDEECsiE(double dssd){
			return dEE->Eval(dssd);
		}
};
class TeleHit{
	private:
		MergeTELE *mergeData;
		DEECurve *deePara;

		EnergyTELE *calibEnergy;
		TimeTELE *calibTime;

		Int_t           teleHit;
		Int_t           teleHitSide[10];
		Int_t           teleHitFid[10];
		Int_t           teleHitBid[10];
		Double_t        teleHitDssdFQPed[10];
		Double_t        teleHitDssdBQPed[10];
		Double_t        teleHitDssdTCal[10];
		Int_t           teleHitCid[10];
		Double_t        teleHitCsiQPed[10];
		Double_t        teleHitCsiTCal[10];

		Double_t        teleHitDssdFE[10];
		Double_t        teleHitDssdBE[10];
		Double_t        teleHitCsiE[10];

		int 		bestHit;


		int getHit(){
			return mergeData->getHit();
		}
		double getCsiE(int i){

			double csiE = calibEnergy->getCsiE(mergeData->getHitCid(i),mergeData->getHitCsiQPed(i));

			if(mergeData->getRunNumber()<305&&mergeData->getHitCid(i)==4) csiE = 1.8*csiE;  
			return csiE;
		} 
		double getCsiE_sync(int i){
			double csiE =  calibEnergy->getSyncCsiE(teleHitCid[i],teleHitCsiQPed[i]);
			if(mergeData->getRunNumber()<305&&teleHitCid[i]==4) csiE = 1.8*csiE;  
			return csiE;
		} 

		double getCsiT(int i){
			return calibTime->getCsiT(mergeData->getHitCid(i),mergeData->getHitCsiTCal(i));
		} 
		double getDssdFrontE(int i){
			return calibEnergy->getDssdFrontE(mergeData->getHitSide(i),mergeData->getHitFid(i),mergeData->getHitDssdFQPed(i));
		}

		double getDssdBackE(int i){
			return calibEnergy->getDssdBackE(mergeData->getHitSide(i),mergeData->getHitBid(i),mergeData->getHitDssdBQPed(i));
		}
		double getDssdFrontE_old(int i){
			return calibEnergy->getDssdFrontE_old(teleHitSide[i],teleHitFid[i],teleHitDssdFQPed[i]);
		}

		double getDssdBackE_old(int i){
			return calibEnergy->getDssdBackE_old(teleHitSide[i],teleHitBid[i],teleHitDssdBQPed[i]);
		}
	
		double getDssdT(int i){
			return calibTime->getDssdT(mergeData->getHitSide(i),mergeData->getHitFid(i),mergeData->getHitDssdTCal(i));
		}



	public:
		TeleHit(){
			deePara = new DEECurve();
			calibEnergy = new EnergyTELE();
			calibTime = new TimeTELE();

		}
		~TeleHit(){
			delete calibEnergy;
			delete calibTime;
			delete deePara;
		}
		void loadData(MergeTELE *mergeTELE){
			
			mergeData = mergeTELE;
		}

		void init(){

			mergeData = NULL;
			bestHit = -1;
			teleHit = 0;
			for (int i = 0; i < 10; ++i) {
				teleHitSide[i] =-1;
				teleHitFid[i]  =-1;
				teleHitBid[i]  =-1;
				teleHitCid[i]  =-1;

				teleHitDssdFQPed[i]    =-9999;
				teleHitDssdBQPed[i]    =-9999;
				teleHitDssdTCal[i]     =-9999;
				teleHitCsiQPed[i]      =-9999;
				teleHitCsiTCal[i]      =-9999;

				teleHitDssdFE[i] = -9999;
				teleHitDssdBE[i] = -9999;
				teleHitCsiE[i] = -9999;
			}
		}
		void setBranch(TTree *tree){

			tree->Branch("teleHit",&teleHit,"teleHit/I");
			tree->Branch("teleHitSide",&teleHitSide,"teleHitSide[teleHit]/I");
			tree->Branch("teleHitFid",&teleHitFid,"teleHitFid[teleHit]/I");
			tree->Branch("teleHitBid",&teleHitBid,"teleHitBid[teleHit]/I");

			tree->Branch("teleHitDssdFQPed",&teleHitDssdFQPed,"teleHitDssdFQPed[teleHit]/D");
			tree->Branch("teleHitDssdBQPed",&teleHitDssdBQPed,"teleHitDssdBQPed[teleHit]/D");
			tree->Branch("teleHitDssdTCal",&teleHitDssdTCal,"teleHitDssdTCal[teleHit]/D");

			tree->Branch("teleHitCid",&teleHitCid,"teleHitCid[teleHit]/I");
			tree->Branch("teleHitCsiQPed",&teleHitCsiQPed,"teleHitCsiQPed[teleHit]/D");
			tree->Branch("teleHitCsiTCal",&teleHitCsiTCal,"teleHitCsiTCal[teleHit]/D");

			tree->Branch("teleHitDssdFE",&teleHitDssdFE,"teleHitDssdFE[teleHit]/D");
			tree->Branch("teleHitDssdBE",&teleHitDssdBE,"teleHitDssdBE[teleHit]/D");
			tree->Branch("teleHitCsiE",&teleHitCsiE,"teleHitCsiE[teleHit]/D");
	
			tree->Branch("bestHit",&bestHit,"bestHit/I");
		}
		double getDEECsiE(double dssdE){
			return deePara->getDEECsiE(dssdE);
		}
		double getDEEResidue(int i){
			return abs(getDEECsiE(0.5*(teleHitDssdFE[i]+teleHitDssdBE[i]))- teleHitCsiE[i]);
		}
		void removeBadHit(){
			for (int i = 0; i < getHit(); ++i) {
				if(abs(getDssdFrontE(i)-getDssdBackE(i))>5) continue;
				if((getDssdFrontE(i)/getDssdBackE(i))>2||(getDssdFrontE(i)/getDssdBackE(i))<0.5) continue;
				reFillHit(i);
			}
		}
		void reFillHit(int i){

			teleHitSide[teleHit]	 = mergeData->getHitSide(i);
			teleHitFid[teleHit]	 = mergeData->getHitFid(i);
			teleHitBid[teleHit]	 = mergeData->getHitBid(i);
			teleHitDssdFQPed[teleHit]= mergeData->getHitDssdFQPed(i);
			teleHitDssdBQPed[teleHit]= mergeData->getHitDssdBQPed(i);
			teleHitDssdTCal[teleHit] = mergeData->getHitDssdTCal(i);

			teleHitCid[teleHit]	 = mergeData->getHitCid(i);
			teleHitCsiQPed[teleHit]	 = mergeData->getHitCsiQPed(i);
			teleHitCsiTCal[teleHit]	 = mergeData->getHitCsiTCal(i);

			teleHitDssdFE[teleHit]	 = getDssdFrontE(i);
			teleHitDssdBE[teleHit]	 = getDssdBackE(i);
			teleHitCsiE[teleHit]	 = getCsiE(i);
			
			teleHit++;

		}
		void findBestHit(){
			double deeResidue = 10000;
			for (int i = 0; i < teleHit; ++i) {
				//cout<<getDEEResidue(i)<<endl;
				if(getDEEResidue(i)<deeResidue){
					bestHit = i;
					deeResidue = getDEEResidue(i);
				}
			}
		}
		bool isGoodEvent(){
			if(bestHit!=-1) return true;
			else return false;
		}
		int getSide(){
			return teleHitSide[bestHit];
		}
		int getFid(){
			return teleHitFid[bestHit];
		}
		int getBid(){
			return teleHitBid[bestHit];
		}
		int getCid(){
			return teleHitCid[bestHit];
		}


		double getCsiE(){
			return teleHitCsiE[bestHit];
		}
		double getCsiE_sync(){
			return getCsiE_sync(bestHit);
		}
		double getDssdFrontE(){
			return teleHitDssdFE[bestHit];
		}
		double getDssdBackE(){
			return teleHitDssdBE[bestHit];
		}
		double getDssdFrontE_old(){
			return getDssdFrontE_old(bestHit);
		}
		double getDssdBackE_old(){
			return getDssdBackE_old(bestHit);
		}
	
		double getCsiT(){
			return teleHitCsiTCal[bestHit];
		}
		double getDssdT(){
			return teleHitDssdTCal[bestHit];
		}
		void print(){
			for (int i = 0; i < teleHit; ++i) {
				cout<<" teleHit"<<i<<" dssd Fid="<<teleHitFid[i]<<" Bid="<<teleHitBid[i]<<" "<<teleHitDssdFE[i]<<" "<<teleHitDssdBE[i]<<" Cid ="<<teleHitCid[i]<<" "<<teleHitCsiE[i]<<endl;	
			}
		}
	
};
class TeleEvent{
	private:


		PositionTELE *positionTELE;
		TeleHit *teleHit;
		
		double teleCsiE;
		double teleCsiE_sync; // sync First then calib 1 cyrsatal
		double teleDssdFE;
		double teleDssdBE;
		double teleDssdFE_old;
		double teleDssdBE_old;
	
		double teleDssdE; // save 0.5(FE+BE)
		double teleDssdMaxE; // save max(FE,BE)
		double teleCsiT;
		double teleDssdT;
		double teleEnergy;

		double teleX;
		double teleY;
		double teleZ;
		TVector3 *telePosition;

		double teleAngle;
		double teleLocusAngle;
		TVector3 *vTele;

		double teleAngle_rand;



		TVector3 *targetPosition;
		TVector3 *vBeam;



		TVector3 getPosition(){
			return positionTELE->getPosition(teleHit->getSide(),teleHit->getFid(),teleHit->getBid());
		}

		void setAngle(){
			(*vTele)	= (*telePosition)-(*targetPosition);
			(*vTele)	= (*vTele).Unit();
			teleAngle      = (*vTele).Angle((*vBeam))*TMath::RadToDeg();
			TVector3 dssdPlaneNorm = getDssdPlaneNorm();
			teleLocusAngle = (*vTele).Angle(dssdPlaneNorm)*TMath::RadToDeg();

			teleAngle_rand      = teleAngle+ gRandom->Uniform(-0.5,0.5);
		}

	public:
		void print(){
			teleHit->print();
			cout<<"TELE Event:"<<endl;

				
			cout<<" dssdE = "<<teleDssdFE<<" "<<teleDssdFE_old<<" "<<teleDssdBE<<" "<<teleDssdBE_old<<" "<<teleDssdE<<" "<<teleDssdMaxE<<" csiE ="<<teleCsiE<<" totE = "<<teleEnergy<<" dssdPosition : "<<teleX<<" "<<teleY<<" "<<teleZ<<endl;
			
		cout<<" Tele Angle = "<<teleAngle<<" Locus Angle ="<<teleLocusAngle<<endl;
			//cout<<"Tele Time: dssdT = "<<teleDssdT<<" csiT ="<<teleCsiT<<endl;	
	
		}
		
		TeleEvent(){
			positionTELE = new PositionTELE();
			teleHit = new TeleHit();
		}
		~TeleEvent(){
			delete teleHit;
			delete positionTELE;
		}
		void loadData(MergeTELE *mergeTELE){
			teleHit->loadData(mergeTELE);
		}
		void init(){
			teleHit->init();
			teleCsiE=NAN;
			teleCsiE_sync=NAN;
			teleDssdFE=NAN;
			teleDssdBE=NAN;
			teleDssdFE_old=NAN;
			teleDssdBE_old=NAN;
	
			teleDssdE=NAN;

			teleDssdMaxE=NAN;
			teleCsiT=NAN;
			teleDssdT=NAN;
			teleEnergy=NAN;
			teleX = NAN;
			teleY = NAN;
			teleZ = NAN;
			telePosition->SetXYZ(NAN,NAN,NAN);
			teleAngle = NAN;
			teleLocusAngle = NAN;
			vTele->SetXYZ(NAN,NAN,NAN);

			teleAngle_rand = NAN;

		}
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}

		void setOutputBranch(TTree *tree){

			telePosition = new TVector3();

			teleHit->setBranch(tree);
			tree->Branch("teleCsiE",&teleCsiE,"teleCsiE/D");
			tree->Branch("teleCsiE_sync",&teleCsiE_sync,"teleCsiE_sync/D");
			tree->Branch("teleDssdFE",&teleDssdFE,"teleDssdFE/D");
			tree->Branch("teleDssdBE",&teleDssdBE,"teleDssdBE/D");
			tree->Branch("teleDssdFE_old",&teleDssdFE_old,"teleDssdFE_old/D");
			tree->Branch("teleDssdBE_old",&teleDssdBE_old,"teleDssdBE_old/D");
	
			tree->Branch("teleDssdE",&teleDssdE,"teleDssdE/D");
			tree->Branch("teleDssdMaxE",&teleDssdMaxE,"teleDssdMaxE/D");
			tree->Branch("teleCsiT",&teleCsiT,"teleCsiT/D");
			tree->Branch("teleDssdT",&teleDssdT,"teleDssdT/D");
			tree->Branch("teleEnergy",&teleEnergy,"teleEnergy/D");
			tree->Branch("telePosition","TVector3",&telePosition);

			vTele = new TVector3;
			tree->Branch("teleAngle",&teleAngle,"teleAngle/D");
			tree->Branch("teleLocusAngle",&teleLocusAngle,"teleLocusAngle/D");
			tree->Branch("vTele","TVector3",&vTele);
	
			tree->Branch("teleAngle_rand",&teleAngle_rand,"teleAngle_rand/D");
		}
		void setHit(){

			teleHit->removeBadHit();
			teleHit->findBestHit();
		}
		void setEvent(){
			setHit();
			if(teleHit->isGoodEvent()){


				teleCsiE	 =teleHit->getCsiE();
				teleCsiE_sync	 =teleHit->getCsiE_sync();
				teleDssdFE	 =teleHit->getDssdFrontE();
				teleDssdBE	 =teleHit->getDssdBackE();
				teleDssdFE_old	 =teleHit->getDssdFrontE_old();
				teleDssdBE_old	 =teleHit->getDssdBackE_old();
	
				teleCsiT	 =teleHit->getCsiT();
				teleDssdT	 =teleHit->getDssdT();
				teleDssdE	 = 0.5*(teleDssdFE+teleDssdBE);
				teleDssdMaxE	 = (teleDssdFE>teleDssdBE)?teleDssdFE:teleDssdBE;
				teleEnergy	 = teleDssdE+teleCsiE;
				(*telePosition)	 = getPosition();
				teleX = telePosition->X();
				teleY = telePosition->Y();
				teleZ = telePosition->Z();

				setAngle();
			}
		}
		TVector3 getDssdPlaneNorm(){
			return positionTELE->getDssdPlaneNorm(teleHit->getSide());
		}
		TVector3 *getTelePosition(){
			return telePosition;
		}
		double getCsiEnergy(){
			return teleCsiE;
		}
		double getLocusAngle(){
			return teleLocusAngle;
		}
		bool isGoodEvent(){
			return teleHit->isGoodEvent()&&(getLocusAngle()>0);
		}
};
