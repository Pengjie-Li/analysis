#include "DssdCal.h"
#include "CsiCal.h"

class TELEHit{
	private:
		DssdCal *dssdCal;
		CsiCal *csiCal;

		int teleHit;
		int teleHitSide[3];
		int teleHitFid[3];
		int teleHitBid[3];
		double teleHitDssdFQPed[3];
		double teleHitDssdBQPed[3];
		double teleHitDssdTCal[3];

		int teleHitCid[3];
		double teleHitCsiQPed[3];
		double teleHitCsiTCal[3];
		int getDssdHit(){
			return dssdCal->getHit();
		}
		int getDssdHitSide(int iHit){
			return dssdCal->getHitSide(iHit);
		}
		int getDssdHitFid(int iHit){
			return dssdCal->getHitFid(iHit);
		}
		int getDssdHitBid(int iHit){
			return dssdCal->getHitBid(iHit);
		}
		double getDssdHitFQPed(int iHit){
			return dssdCal->getHitFQPed(iHit);
		}
		double getDssdHitBQPed(int iHit){
			return dssdCal->getHitBQPed(iHit);
		}
		double getDssdHitTCal(int iHit){
			return dssdCal->getHitTCal(iHit);
		}
		int getCsiHit(){
			return csiCal->getHit();
		}
		int getCsiHitId(int iHit){
			return csiCal->getHitId(iHit);
		}
		double getCsiHitQPed(int iHit){
			return csiCal->getHitQPed(iHit);
		}
		double getCsiHitTCal(int iHit){
			return csiCal->getHitTCal(iHit);
		}

		bool isPixelInSide(int dssdSide,int fid,int bid,int csiId){
			if(dssdSide==0&&csiId>3){
				if(csiId==4&&bid<17) return true;
				if(csiId==5&&fid<17&&bid>14) return true;
				if(csiId==6&&fid>14&&bid>14) return true;
			}
			if(dssdSide==1&&csiId<4){
				if(csiId==0&&fid<18&&bid>15) return true;
				if(csiId==1&&fid<18&&bid<19) return true;
				if(csiId==2&&fid>14&&bid>15) return true;
				if(csiId==3&&fid>14&&bid<19) return true;
			}
			return false;
		}
	public:
		TELEHit(){}
		~TELEHit(){}
		void init(){
		dssdCal = NULL;
		csiCal = NULL;
		 teleHit = 0;
		 for (int i = 0; i < 3; ++i) {
			 teleHitSide[i]	=-1;
			 teleHitFid[i]	=-1;
			 teleHitBid[i]	=-1;
			 teleHitCid[i]	=-1;

			 teleHitDssdFQPed[i]	=-9999;
			 teleHitDssdBQPed[i]	=-9999;
			 teleHitDssdTCal[i]	=-9999;
			 teleHitCsiQPed[i]	=-9999;
			 teleHitCsiTCal[i]	=-9999;
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
		}
		void hitEvent(DssdCal *dssd,CsiCal *csi){
			dssdCal = dssd;	
			csiCal = csi;	
			hitEvent();
		}
		void hitEvent(){
			if(dssdCal->getHit()>0&&csiCal->getHit()>0){
				for (int i = 0; i < getDssdHit(); ++i) {
					for (int j = 0; j < getCsiHit(); ++j) {
						if(isPixelInSide(getDssdHitSide(i),getDssdHitFid(i),getDssdHitBid(i),getCsiHitId(j))&&teleHit<3){
							teleHitSide[teleHit] = getDssdHitSide(i);
							teleHitFid[teleHit] = getDssdHitFid(i);
							teleHitBid[teleHit] = getDssdHitBid(i);
							teleHitDssdFQPed[teleHit] = getDssdHitFQPed(i);
							teleHitDssdBQPed[teleHit] = getDssdHitBQPed(i);
							teleHitDssdTCal[teleHit] = getDssdHitTCal(i);

							teleHitCid[teleHit] = getCsiHitId(j);
							teleHitCsiQPed[teleHit] = getCsiHitQPed(j);
							teleHitCsiTCal[teleHit] = getCsiHitTCal(j);
							teleHit++;
						}
					}
				}	
			}
			// seems good if don't have time if(dssdCal->getQHit()==2&&csiCal->getHitQ()==1){
		}
		void print(){
			cout<<"Tele Hit:"<<endl;
			for (int i = 0; i < teleHit; ++i) {
				cout<<" Hit"<<i<<" Side= "<<teleHitSide[i]<<" fid="<<"\t"<<teleHitFid[i]<<" bid="<<"\t"<<teleHitBid[i]<<"\t"<<teleHitDssdFQPed[i]<<"\t"<<teleHitDssdBQPed[i]<<"\t"<<teleHitDssdTCal[i]<<"\t"<<teleHitCid[i]<<"\t"<<teleHitCsiQPed[i]<<"\t"<<teleHitCsiTCal[i]<<endl;
			}
		}
};
class TELEConvertCal{
	private:
	public:
		TELEReadRaw *teleReadRaw;	
		TELEHit	*teleHit;

		DssdCal *dssdCal;
		CsiCal *csiCal;
		
	
		TELEConvertCal(){
			dssdCal = new DssdCal();
			csiCal = new CsiCal();
			teleHit = new TELEHit();
		}

		void setBranch(TTree *tree){
			dssdCal->setBranch(tree);	
			csiCal->setBranch(tree);	
			teleHit->setBranch(tree);
		}
		void init(){
			teleReadRaw = NULL;
			dssdCal->init();
			csiCal->init();
			teleHit->init();
		}

		void calibration(TELEReadRaw *rawData){
			teleReadRaw = rawData;
			dssdCal->calibration(rawData);
			csiCal->calibration(rawData);
			teleHit->hitEvent(dssdCal,csiCal);
		}
		void print(){
			dssdCal->print();
			csiCal->print();
			teleHit->print();
		}

		~TELEConvertCal(){
			delete dssdCal;
			delete csiCal;
		}

};
