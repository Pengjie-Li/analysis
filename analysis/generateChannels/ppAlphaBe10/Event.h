class HodCut{
	private:
		TCutG *hodBarCut[40];
		void loadCut(){
                        gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar29He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar30He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar31He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar32He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar33He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe10Bar34He6.C");

		}
		void getCut(){
			for (int i = 0; i < 40; ++i) {
				hodBarCut[i] = (TCutG*)gROOT->GetListOfSpecials()->FindObject(Form("Be10Bar%dHe6",i));
			}
		}

	public:
		HodCut(){
			loadCut();
			getCut();
		}
		~HodCut(){}
		bool isInside(ReadFile *rf){

			//hodGate = "(Be10Bar29He6||Be10Bar30He6||Be10Bar31He6||Be10Bar32He6||Be10Bar33He6||Be10Bar34He6)";
			for (int i = 29; i < 35; ++i) {
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
		TCutG *alphaCut;
		HodCut *hodCut;
		void loadCut(){
                        gROOT->ProcessLine(".x inputRootfiles/cutBeamBe10.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutProton.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutAlpha.C");
		}
		void getCut(){
			beamCut		= (TCutG*)gROOT->GetListOfSpecials()->FindObject("Beam");
			protonCut	= (TCutG*)gROOT->GetListOfSpecials()->FindObject("Proton");
			alphaCut	= (TCutG*)gROOT->GetListOfSpecials()->FindObject("Alpha");
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
		bool isAlpha(double E,double dE){
			//cout<<"E ="<<E<<" dE ="<<dE<<endl;
			return alphaCut->IsInside(E,dE);
		}
		bool isHodPid(ReadFile *rf){
			return hodCut->isInside(rf);
		}
};
class Event{
	private:
		ReadFile *rf;
		GateCut	*gc;

		bool isPALR(){
			return rf->isPALR();
		}
		bool isBeam(){
			return gc->isBeam(rf->getTof713(),rf->getF13Q());
		}
		bool isProton(){
			//return gc->isProton(rf->getNaiQ(),rf->getPlasQ());
			return gc->isProton(rf->getEspriNaiE(),rf->getEspriPlasE());
		}
		bool isAlpha(){
			//return gc->isProton(rf->getNaiQ(),rf->getPlasQ());
			return gc->isAlpha(rf->getTeleCsiE(),rf->getTeleDssdE());
		}
		bool isTargetArea(){
			return gc->isInsideTargetArea(rf->getTargetX(),rf->getTargetY());
		}
		bool isHodPid(){
			return gc->isHodPid(rf);
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
			//return isBeam()&&isProton()&&isTargetArea()&&isHodPid()&&isPALR();
			//return isAlpha();
			//return isBeam()&&isProton()&&isAlpha()&&isTargetArea()&&isPALR();
			//return isBeam()&&isProton()&&isAlpha()&&isTargetArea(); // Add small gate later
			return isBeam()&&isProton()&&isAlpha()&&isTargetArea(); // Add small gate later
			//return isBeam()&&isProton()&&isAlpha()&&isTargetArea()&&isHodPid();
			//return isBeam()&&isProton()&&isAlpha()&&isTargetArea()&&isHodPid()&&isPALR();
			//return isBeam();
			//return isProton();
			//return isTargetArea();
			//return isPRAngle();
			//return isHodPid();
		}
		void setBranch(TTree *tree){
		}
};
