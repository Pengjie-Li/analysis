class HodCut{
	private:
		TCutG *hodBarCut[40];
		void loadCut(){
                        gROOT->ProcessLine(".x inputRootfiles/cutBe12Bar30He8.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe12Bar31He8.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe12Bar32He8.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe12Bar33He8.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe12Bar34He8.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe12Bar35He8.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe12Bar36He8.C");

		}
		void getCut(){
			for (int i = 0; i < 40; ++i) {
				hodBarCut[i] = (TCutG*)gROOT->GetListOfSpecials()->FindObject(Form("Be12Bar%dHe8",i));
			}
		}

	public:
		HodCut(){
			loadCut();
			getCut();
		}
		~HodCut(){}
		bool isInside(ReadFile *rf){

			for (int i = 30; i < 37; ++i) {
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
		TCutG *he3Cut;
		HodCut *hodCut;
		void loadCut(){
                        gROOT->ProcessLine(".x inputRootfiles/cutBeamBe12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutProton.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutHe3.C");
		}
		void getCut(){
			beamCut		= (TCutG*)gROOT->GetListOfSpecials()->FindObject("Beam");
			protonCut	= (TCutG*)gROOT->GetListOfSpecials()->FindObject("Proton");
			he3Cut		= (TCutG*)gROOT->GetListOfSpecials()->FindObject("He3");
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
			//return protonCut->IsInside(E,dE);
		}
		bool isHe3(double E,double dE){
			//cout<<"E ="<<E<<" dE ="<<dE<<endl;
			return he3Cut->IsInside(E,dE);
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
		bool isHe3(){
			return gc->isHe3(rf->getTeleCsiE(),rf->getTeleDssdE());
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
			//return isHe3();
			//return isBeam()&&isProton()&&isHe3()&&isTargetArea()&&isPALR();
			return isBeam()&&isProton()&&isHe3()&&isTargetArea(); // Add small gate later
			//return isBeam()&&isProton()&&isHe3()&&isTargetArea(); // Add small gate later
			//return isBeam()&&isProton()&&isHe3()&&isTargetArea()&&isPALR();
			//return isBeam()&&isProton()&&isHe3()&&isTargetArea()&&isHodPid()&&isPALR();
			//return isBeam();
			//return isProton();
			//return isTargetArea();
			//return isPRAngle();
			//return isHodPid();
		}
		void setBranch(TTree *tree){
		}
};
