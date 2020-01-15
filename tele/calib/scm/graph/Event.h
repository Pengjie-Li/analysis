class RemovePara{
	private:
		double offsetPara[4][32];
		double gainPara[4][32];
	public:
		RemovePara(){
			load();
		}
		~RemovePara(){}
		void load(){
			ifstream in;
			TString inputName = "../fit/txt/dssdScmParaRaw.txt_v5";
			cout<<inputName<<endl;
			in.open(inputName);
			int side;
			int stripId;
			double refId;
			double offset;
			double gain;
			while(1){
				if(!in.good()) break;
				in>>side>>stripId>>refId>>offset>>gain;
				offsetPara[side][stripId] = offset;
				gainPara[side][stripId] = gain;
			}
		}
		bool isInArea(int side, int stripId, int refId,double x,double y){
			return (abs(y-(offsetPara[side][stripId]+gainPara[side][stripId]*x))<30)?true:false;
		}


};
class TGraphContainer{
	private:
		TGraph *gr;
		vector<double> xArray;
		vector<double> yArray;
	public:
		TGraphContainer(){}
		~TGraphContainer(){}
		void fill(double x,double y){
			xArray.push_back(x);
			yArray.push_back(y);
		}
		void setName(int side,int refId,int id){
			gr = new TGraph(xArray.size(),&xArray[0],&yArray[0]);
			gr->SetName(Form("Side%d_Ref%d_strip%d",side,refId,id));
		}
		void write(){
			gr->Write();
		}
};
class Event{
	private:
		ReadFile *rf;
		RemovePara *removePara;
		int gLFRef;
		int gLBRef;
		int gRFRef;
		int gRBRef;

		TGraphContainer *gLF[32];
		TGraphContainer *gLB[32];
		TGraphContainer *gRF[32];
		TGraphContainer *gRB[32];
	public:
		Event(){
		}
		Event(ReadFile *rf):rf(rf){
			removePara = new RemovePara();
			gLFRef = 15;
			gLBRef = 15;
			gRFRef = 15;
			gRBRef = 15;

			for (int i = 0; i < 32; ++i) {
				gLF[i] = new TGraphContainer();	
				gLB[i] = new TGraphContainer();	
				gRF[i] = new TGraphContainer();	
				gRB[i] = new TGraphContainer();	
			}
		}
		~Event(){
			for (int i = 0; i < 32; ++i) {
				delete gLF[i];	
				delete gLB[i];	
				delete gRF[i];	
				delete gRB[i];	
			}

		}
		void setEvent(){
			int side = -1;
			if(rf->getTeleHitSide()==0&&rf->getTeleHitBid()==gLFRef){
				int i = rf->getTeleHitFid();
				side = 0;	
				if(removePara->isInArea(side,i,gLFRef,rf->getTeleHitDssdBQPed(),rf->getTeleHitDssdFQPed())){
					gLF[i]->fill(rf->getTeleHitDssdBQPed(),rf->getTeleHitDssdFQPed());
				}
			}
			if(rf->getTeleHitSide()==0&&rf->getTeleHitFid()==gLBRef){
				int i = rf->getTeleHitBid();
				side = 1;	
				if(removePara->isInArea(side,i,gLBRef,rf->getTeleHitDssdFQPed(),rf->getTeleHitDssdBQPed())){
					gLB[i]->fill(rf->getTeleHitDssdFQPed(),rf->getTeleHitDssdBQPed());
				}
			}

			if(rf->getTeleHitSide()==1&&rf->getTeleHitBid()==gRFRef){
				int i = rf->getTeleHitFid();
				side = 2;	
				if(removePara->isInArea(side,i,gRFRef,rf->getTeleHitDssdBQPed(),rf->getTeleHitDssdFQPed())){
					gRF[i]->fill(rf->getTeleHitDssdBQPed(),rf->getTeleHitDssdFQPed());
				}
			}
			if(rf->getTeleHitSide()==1&&rf->getTeleHitFid()==gRBRef){
				int i = rf->getTeleHitBid();
				side = 3;	
				if(removePara->isInArea(side,i,gRBRef,rf->getTeleHitDssdFQPed(),rf->getTeleHitDssdBQPed())){
					gRB[i]->fill(rf->getTeleHitDssdFQPed(),rf->getTeleHitDssdBQPed());
				}
			}
		}
		void write(){
			for (int i = 0; i < 32; ++i) {
				gLF[i]->setName(0,gLFRef,i);	
				gLF[i]->write();	

				gLB[i]->setName(1,gLFRef,i);	
				gLB[i]->write();	

				gRF[i]->setName(2,gRFRef,i);	
				gRF[i]->write();       

				gRB[i]->setName(3,gRFRef,i);	
				gRB[i]->write();	
			}	
		}
};
