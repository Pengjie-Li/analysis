class HodCut{
	private:
		TCutG *hodBarHe8[40];
		TCutG *hodBarHe6[40];
		TCutG *hodBarHe4[40];
		void loadCut(){
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar33He8.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar34He8.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar35He8.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar36He8.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar37He8.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar38He8.C");

                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar11He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar12He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar13He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar14He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar15He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar16He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar17He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar18He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar19He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar20He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar21He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar22He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar23He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar24He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar26He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar27He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar28He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar29He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar30He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar31He6.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar32He6.C");

                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar3He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar4He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar5He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar6He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar7He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar8He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar9He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar10He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar11He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar12He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar13He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar14He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar15He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar16He4.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar17He4.C");
		}
		void getCut(){
			for (int i = 0; i < 40; ++i) {
				hodBarHe8[i] = (TCutG*)gROOT->GetListOfSpecials()->FindObject(Form("Be14Bar%dHe8",i));
				hodBarHe6[i] = (TCutG*)gROOT->GetListOfSpecials()->FindObject(Form("Be14Bar%dHe6",i));
				hodBarHe4[i] = (TCutG*)gROOT->GetListOfSpecials()->FindObject(Form("Be14Bar%dHe4",i));
			}
		}

	public:
		HodCut(){
			loadCut();
			getCut();
		}
		~HodCut(){}
		bool isInside(ReadFile *rf){

			for (int i = 3; i < 18; ++i) {
				if(isInsideHe4(rf,i)) return true;	
			}

			for (int i = 11; i < 33; ++i) {
				if(i==25) continue;
				if(isInsideHe6(rf,i)) return true;	
			}

			for (int i = 33; i < 39; ++i) {
				if(isInsideHe8(rf,i)) return true;	
			}
			return false;
		}
		bool isInsideHe8(ReadFile *rf,int id){
			return hodBarHe8[id]->IsInside(rf->getHodBarTRaw(id),rf->getHodBarQRaw(id));
		}
		bool isInsideHe6(ReadFile *rf,int id){
			return hodBarHe6[id]->IsInside(rf->getHodBarTRaw(id),rf->getHodBarQRaw(id));
		}
		bool isInsideHe4(ReadFile *rf,int id){
			return hodBarHe4[id]->IsInside(rf->getHodBarTRaw(id),rf->getHodBarQRaw(id));
		}


};
class GateCut{
	private:
		TCutG *beamCut;
		TCutG *protonCut;
		TCutG *alphaCut;
		TCutG *prAngleCut;
		HodCut *hodCut;
		void loadCut(){
                        gROOT->ProcessLine(".x inputRootfiles/cutBeamBe14.C");
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
			return gc->isProton(rf->getEspriNaiE(),rf->getEspriPlasE());
		}
		bool isAlpha(){
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
			//return isBeam()&&isProton()&&isAlpha()&&isTargetArea()&&isHodPid()&&isPALR();
			return isBeam()&&isProton()&&isAlpha()&&isTargetArea();
			//return isBeam();
			//return isProton();
			//return isTargetArea();
			//return isPRAngle();
			//return isHodPid();
		}
		void setBranch(TTree *tree){
		}
};
