class HodCut{
	private:
		TCutG *hodBarCut[40];
		void loadCut(){
			gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar23Be10.C");
			gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar22Be10.C");
			gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar21Be10.C");
			gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar20Be10.C");
			gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar19Be10.C");

			gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar23Be9.C");
			gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar22Be9.C");
			gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar21Be9.C");
			gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar20Be9.C");
			gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar19Be9.C");
       		}
		void getCut(){
			for (int i = 0; i < 40; ++i) {
				hodBarCut[i] = (TCutG*)gROOT->GetListOfSpecials()->FindObject(Form("Be10Bar%dBe10",i));
			}
		}

	public:
		HodCut(){
			loadCut();
			getCut();
		}
		~HodCut(){}
		bool isInside(ReadFile *rf){
			for (int i = 19; i < 24; ++i) {
				if(isInside(rf,i)) return true;	
			}
			return false;
		}
		bool isInside(ReadFile *rf,int id){
			return hodBarCut[id]->IsInside(rf->getHodBarTRaw(id),rf->getHodBarQRaw(id));
		}
};
class GateCut{
	private:
		TCutG *beamCut;
		TCutG *protonCut;
		TCutG *prAngleCut;
		HodCut *hodCut;
		void loadCut(){
                        gROOT->ProcessLine(".x inputRootfiles/cutBeamBe10.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutProton.C");
                        //gROOT->ProcessLine(".x inputRootfiles/cutProtonBe10Bar00.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutPRAngleBe10.C");
		}
		void getCut(){
			beamCut		= (TCutG*)gROOT->GetListOfSpecials()->FindObject("Beam");
			protonCut	= (TCutG*)gROOT->GetListOfSpecials()->FindObject("Proton");
			prAngleCut	= (TCutG*)gROOT->GetListOfSpecials()->FindObject("PRAngle");
		}
	public:
		GateCut(){
			loadCut();
			getCut();
			hodCut = new HodCut();
		}
		~GateCut(){}
		bool isBeam(double tof,double q){
			return beamCut->IsInside(tof,q);
		}
		bool isInsideTargetArea(double x,double y){
			return (sqrt((x-2.0)*(x-2.0)+(y+1.1)*(y+1.1))<13);
		}
		bool isProton(double E,double dE){
			return protonCut->IsInside(E,dE);
		}
		bool isInsidePRAngle(double resAngle,double protonAngle){
			return prAngleCut->IsInside(resAngle,protonAngle);
		}
		bool isHodPid(ReadFile *rf){
			return hodCut->isInside(rf);
		}
};
class Event{
	private:
		ReadFile *rf;
		GateCut	*gc;

		bool isBeam(){
			return gc->isBeam(rf->getTof713(),rf->getF13Q());
		}
		bool isProton(){
			//return gc->isProton(rf->getNaiQ(),rf->getPlasQ());
			return gc->isProton(rf->getEspriNaiE(),rf->getEspriPlasE());
		}
		bool isTargetArea(){
			return gc->isInsideTargetArea(rf->getTargetX(),rf->getTargetY());
		}
		bool isPRAngle(){
			return gc->isInsidePRAngle(rf->getResAngle(),rf->getEspriAngle());
		}
		bool isHodPid(){
			return gc->isHodPid(rf);
		}
		bool isPhi(){
			double dPhi = 50;
			return (abs((rf->getEspriPhi()-rf->getFdc0Phi())-180)<dPhi||abs((rf->getEspriPhi()-rf->getFdc0Phi()+ 360)-180)<dPhi);
		}
		bool isTrigDSB(){
			return (rf->getTrigDSB()>0);
		}

		bool isTeleOneHit(){
			return (rf->getTeleHit()==1);
		}
		bool isFQPedInRange(){
			return rf->getTeleDssdFQPed()>300&&rf->getTeleDssdFQPed()<4000;
		}

		bool isBQPedInRange(){
			return rf->getTeleDssdBQPed()>300&&rf->getTeleDssdBQPed()<4000;
		}
		bool isFBEffective(){
			//return abs(rf->getTeleDssdFQPed()-rf->getTeleDssdBQPed())<300;
			return rf->getTeleDssdFQPed()>0.7*rf->getTeleDssdBQPed()&&rf->getTeleDssdFQPed()<1.3*rf->getTeleDssdBQPed();
		}

		bool isDssdInRange(){
			return isFQPedInRange()&&isBQPedInRange()&&isFBEffective();
		}
		bool isRefStrip(){
			return (rf->getTeleDssdFid()==15) || (rf->getTeleDssdBid()==15) ;
		}

	public:
		Event(){}
		Event(ReadFile *rf):rf(rf){
			gc = new GateCut();
		}
		~Event(){
			delete gc;
		}
		bool selectEvent(){
			//return isBeam()&&isProton()&&isTargetArea()&&isPRAngle()&&isHodPid();
			//return isBeam()&&isProton()&&isTargetArea()&&isPRAngle();
			//return isBeam()&&isTargetArea()&&isPRAngle();
			//return isBeam()&&isTargetArea()&&isPRAngle();
			//return isBeam()&&isProton();
			//return isBeam()&&isProton()&&isTargetArea()&&isPhi();
			return isRefStrip()&&isTeleOneHit()&&isDssdInRange();
		}
		void setBranch(TTree *tree){
		}
};
