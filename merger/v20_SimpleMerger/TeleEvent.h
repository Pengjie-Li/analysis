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


		int getCsiTHit(){
			return mergeData->getCsiTHit();
		}
		double getCsiE(int i){

			double csiE = calibEnergy->getCsiE(teleHitCid[teleHit],teleHitCsiQPed[teleHit]);

			if(mergeData->getRunNumber()<305&&teleHitCid[teleHit]==4) csiE = 1.8*csiE;  
			return csiE;
		} 
		double getCsiT(int i){
			return calibTime->getCsiT(teleHitCid[teleHit],teleHitCsiTCal[teleHit]);
		} 
		double getDssdT(int i){
			return calibTime->getDssdT(teleHitSide[teleHit],teleHitFid[teleHit],teleHitDssdTCal[teleHit]);
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

			//mergeData = NULL;
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
		bool csiTimeInRange(double csiTimeRaw ){
			//if(30000<csiTimeRaw&&csiTimeRaw<46000) return true;
			if(-12000<csiTimeRaw&&csiTimeRaw<0) return true;
			else return false;
		}
		void sortHit(){
			for (int i = 0; i < getCsiTHit(); ++i) {
				//if(getCsiTHit()==0) continue;
				if( csiTimeInRange( mergeData->getCsiTHitTCal(i) ) ){
					fillPossibleHit( mergeData->getCsiTHitId(i) );	
				}
			}
		}
		int getHitSide(int cid){
			if(cid<=3&&cid>=0) return 1;
			else if(cid<=6&&cid>=4) return 0;
			else {
				cout<<" Error:: csiId wrong!!!"<<endl;
				return -1;
			}
		}
		bool findTeleHitDssdBackStrip(int side,double fqSync){
			for (int i = 0; i < 32; ++i) { // If here we have dssdBQHit, then more efficient, in this step only 1 BQHit satisfy
				double bqPed = mergeData->getDssdBQPed(side, i);
				if(bqPed<0.3*fqSync) continue;
				double bqSync = calibEnergy->getDssdBQSync(side, i, bqPed);
				if((bqSync/fqSync<1.2)&&(bqSync/fqSync>0.8)){
					teleHitBid[teleHit]	 = i;
					teleHitDssdBQPed[teleHit]= bqSync;
					teleHitDssdBE[teleHit]	 = calibEnergy->getDssdE(side,teleHitDssdBQPed[teleHit]);
					return true;
				}
			}
			return false;
		}

		void fillPossibleHit(int cid){
			//cout<<"cid = "<<cid<<endl;
			int side = getHitSide(cid);
			double fQPedTh = 50; // fQSync > 50 ch
			for (int i = 0; i < mergeData->getDssdTHit(); ++i) {
				if((mergeData->getDssdTHitSide(i) != side) || (teleHit>=10)) continue;
				//cout<<"TeleHit = "<<teleHit<<endl;
				if( csiTimeInRange( mergeData->getDssdTHitTCal(i) ) ){

					teleHitSide[teleHit]	 = getHitSide(cid);

					teleHitCid[teleHit]	 = cid; //1st time
					teleHitCsiQPed[teleHit]	 = mergeData->getCsiQPed(cid);
					teleHitCsiE[teleHit]	 = getCsiE(cid);
					teleHitCsiTCal[teleHit]	 = mergeData->getCsiTRef(cid);

					int fid = mergeData->getDssdTHitStripId(i);
					teleHitFid[teleHit]	 = fid;
					teleHitDssdFQPed[teleHit]= calibEnergy->getDssdFQSync(side, fid, mergeData->getDssdFQPed(side, fid));
					if(teleHitDssdFQPed[teleHit]> fQPedTh){
						teleHitDssdFE[teleHit]	 = calibEnergy->getDssdE(side,teleHitDssdFQPed[teleHit]);
						teleHitDssdTCal[teleHit] = mergeData->getDssdTHitTCal(i);

						if(findTeleHitDssdBackStrip(side, teleHitDssdFQPed[teleHit]) ){// If fid cann't find bid, then bad hit

							if(teleHit>10) cout<<"TeleHit = "<<teleHit<<endl;
							teleHit++;
						}
					}

				}

			}
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
		double getDssdFrontE(){
			return teleHitDssdFE[bestHit];
		}
		double getDssdBackE(){
			return teleHitDssdBE[bestHit];
		}
		double getCsiT(){
			return teleHitCsiTCal[bestHit];
		}
		double getDssdT(){
			return teleHitDssdTCal[bestHit];
		}
		int getHit(){
			return teleHit;
		}
		void print(){
			for (int i = 0; i < teleHit; ++i) {
				cout<<" teleHit"<<i<<" dssd Fid="<<teleHitFid[i]<<" \t QSync = "<<teleHitDssdFQPed[i]<<" Bid="<<teleHitBid[i]<<" \t QSync = "<<teleHitDssdBQPed[i]<<" Cid ="<<teleHitCid[i]<<" csiE = "<<teleHitCsiE[i]<<endl;	
			}
		}
	
};
class TeleEvent{
	private:


		PositionTELE *positionTELE;
		TeleHit *teleHit;
		
		int teleSide;
		double teleCsiE;
		double teleDssdFE;
		double teleDssdBE;
	
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
		double telePhi;
		double teleLocusAngle;
		TVector3 *vTele;


		TVector3 *targetPosition;
		TVector3 *vBeam;

		PhiFunction *phiFuction;


		TVector3 getPosition(){
			return positionTELE->getPosition(teleHit->getSide(),teleHit->getFid(),teleHit->getBid());
		}
		void shiftCenter(){
			double tempZ = (*telePosition).Z();
			(*telePosition).SetZ(tempZ + 4222.34);
		}

		void setAngle(){
			(*vTele)	= (*telePosition)-(*targetPosition);
			(*vTele)	= (*vTele).Unit();
			teleAngle      = (*vTele).Angle((*vBeam))*TMath::RadToDeg();
			TVector3 dssdPlaneNorm = getDssdPlaneNorm();
			teleLocusAngle = (*vTele).Angle(dssdPlaneNorm)*TMath::RadToDeg();
			telePhi 	= phiFuction->getPhi((*vBeam),(*vTele));

		}

	public:
		void print(){
			teleHit->print();
			if(teleHit->getHit()>0){
				cout<<"TELE Event:"<<endl;


				cout<<" dssdE = "<<teleDssdFE<<" "<<" "<<teleDssdBE<<" "<<" "<<teleDssdE<<" "<<teleDssdMaxE<<" csiE ="<<teleCsiE<<" totE = "<<teleEnergy<<" dssdPosition : "<<teleX<<" "<<teleY<<" "<<teleZ<<endl;

				cout<<" Tele Angle = "<<teleAngle<<" Locus Angle ="<<teleLocusAngle<<endl;
				cout<<" Tele Phi = "<<telePhi<<endl;
				telePosition->Print();
			}
			//cout<<"Tele Time: dssdT = "<<teleDssdT<<" csiT ="<<teleCsiT<<endl;	

		}

		TeleEvent(){
			positionTELE = new PositionTELE();
			teleHit = new TeleHit();
			phiFuction = new PhiFunction();
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
			teleSide= -1;
			teleCsiE=-9999;
			teleDssdFE=-9999;
			teleDssdBE=-9999;
	
			teleDssdE=-9999;

			teleDssdMaxE=-9999;
			teleCsiT=-9999;
			teleDssdT=-9999;
			teleEnergy=-9999;
			teleX = -9999;
			teleY = -9999;
			teleZ = -9999;
			telePosition->SetXYZ(-9999,-9999,-9999);
			teleAngle = -9999;
			telePhi = -9999;
			teleLocusAngle = -9999;
			vTele->SetXYZ(-9999,-9999,-9999);


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
			tree->Branch("teleSide",&teleSide,"teleSide/I");
			tree->Branch("teleCsiE",&teleCsiE,"teleCsiE/D");
			tree->Branch("teleDssdFE",&teleDssdFE,"teleDssdFE/D");
			tree->Branch("teleDssdBE",&teleDssdBE,"teleDssdBE/D");
	
			tree->Branch("teleDssdE",&teleDssdE,"teleDssdE/D");
			tree->Branch("teleDssdMaxE",&teleDssdMaxE,"teleDssdMaxE/D");
			tree->Branch("teleCsiT",&teleCsiT,"teleCsiT/D");
			tree->Branch("teleDssdT",&teleDssdT,"teleDssdT/D");
			tree->Branch("teleEnergy",&teleEnergy,"teleEnergy/D");
			tree->Branch("telePosition","TVector3",&telePosition);

			vTele = new TVector3;
			tree->Branch("teleAngle",&teleAngle,"teleAngle/D");
			tree->Branch("telePhi",&telePhi,"telePhi/D");
			tree->Branch("teleLocusAngle",&teleLocusAngle,"teleLocusAngle/D");
			tree->Branch("vTele","TVector3",&vTele);
	
		}
		void setHit(){

			teleHit->sortHit();
			teleHit->findBestHit();
		}
		void setEvent(){
			setHit();
			if(teleHit->isGoodEvent()){


				teleSide	 =teleHit->getSide();
				teleCsiE	 =teleHit->getCsiE();
				teleDssdFE	 =teleHit->getDssdFrontE();
				teleDssdBE	 =teleHit->getDssdBackE();
	
				teleCsiT	 =teleHit->getCsiT();
				teleDssdT	 =teleHit->getDssdT();
				teleDssdE	 = 0.5*(teleDssdFE+teleDssdBE);
				teleDssdMaxE	 = (teleDssdFE>teleDssdBE)?teleDssdFE:teleDssdBE;
				teleEnergy	 = teleDssdE+teleCsiE;
				(*telePosition)	 = getPosition();
				shiftCenter();
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
