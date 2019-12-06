class HodCut{
	private:
		TCutG *hodBarCut[40];
		void loadCut(){

                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar33Be14.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar32Be14.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar31Be14.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar30Be14.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar29Be14.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar28Be14.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar27Be14.C");

                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar23Be14.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar22Be14.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar21Be14.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar20Be14.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar19Be14.C");

                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar26Be12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar25Be12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar24Be12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar23Be12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar22Be12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar21Be12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar20Be12.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar19Be12.C");

                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar23Be11.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar22Be11.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar21Be11.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar20Be11.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar19Be11.C");

                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar23Be10.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar22Be10.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar21Be10.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar20Be10.C");
			gROOT->ProcessLine(".x inputRootfiles/cutBe14Bar19Be10.C");
		}
		void getCut(){
			for (int i = 0; i < 40; ++i) {
				hodBarCut[i] = (TCutG*)gROOT->GetListOfSpecials()->FindObject(Form("Be14Bar%dBe14",i));
			}
		}

	public:
		HodCut(){
			loadCut();
			getCut();
		}
		~HodCut(){}
		bool isInside(ReadFile *rf){
			for (int i = 28; i < 34; ++i) {
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
                        gROOT->ProcessLine(".x inputRootfiles/cutBeamBe14.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutProtonBe14.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutPRAngleBe14.C");

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
			return isBeam()&&isProton()&&isTargetArea()&&isHodPid();
			//return isBeam()&&isProton()&&isTargetArea();
			//return isBeam()&&isProton()&&isTargetArea()&&isPRAngle();
			//return isBeam();
			//return isProton();
			//return isTargetArea();
			//return isPRAngle();
			//return isHodPid();
		}
		void setBranch(TTree *tree){
		}
};
