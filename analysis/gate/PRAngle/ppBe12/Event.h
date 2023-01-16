class HodCut{
	private:
		TCutG *hodBarCut[40];
		void loadCut(){
                        gROOT->ProcessLine(".x inputRootfiles/cutBe12Bar23Be12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe12Bar22Be12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe12Bar21Be12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe12Bar20Be12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe12Bar19Be12.C");
		}
		void getCut(){
			for (int i = 0; i < 40; ++i) {
				hodBarCut[i] = (TCutG*)gROOT->GetListOfSpecials()->FindObject(Form("Be12Bar%dBe12",i));
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
                        gROOT->ProcessLine(".x inputRootfiles/cutBeamBe12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutProton.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutPRAngleBe12.C");
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
			//return gc->isProton(rf->getNaiQ(0,0),rf->getPlasQ(0));
			//return gc->isProton(rf->getNaiQ_Pol3(),rf->getPlasQ_Birks());
			return gc->isProton(rf->getNaiQ(),rf->getPlasQ());
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
			//return isBeam()&&isProton()&&isTargetArea()&&isPRAngle();

 			return isBeam()&&isProton()&&isTargetArea()&&isPhi();
			//return isBeam();
			//return isProton();
			//return isTargetArea();
			//return isPRAngle();
			//return isHodPid();
		}
		void setBranch(TTree *tree){
		}
};
