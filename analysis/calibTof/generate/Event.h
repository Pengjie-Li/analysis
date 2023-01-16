class GateCut{
	private:
		TCutG *beamCut;
		TCutG *protonCut;
		TCutG *deutronCut;
		TCutG *protonToFCut;
		TCutG *alphaCut;
		TCutG *prAngleCut;
		void loadCut(int runNumber){

			cout<<runNumber<<endl;
			if(runNumber>=298&&runNumber<=330){
				gROOT->ProcessLine(".x inputRootfiles/cutBeamBe10.C");
			}else if(runNumber>=331&&runNumber<=365){
				gROOT->ProcessLine(".x inputRootfiles/cutBeamBe12.C");
			}else if(runNumber>=366&&runNumber<=455){ 
				gROOT->ProcessLine(".x inputRootfiles/cutBeamBe14.C");
			}else{
				cout<<"ERROR: Wrong RunNUmber "<<runNumber<<endl;
			}
                        gROOT->ProcessLine(".x inputRootfiles/cutProton.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutDeutron.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutProtonToF.C");
                        gROOT->ProcessLine(".x inputRootfiles/cutAlpha.C");
		}
		void getCut(){
			beamCut		= (TCutG*)gROOT->GetListOfSpecials()->FindObject("Beam");
			protonCut	= (TCutG*)gROOT->GetListOfSpecials()->FindObject("Proton");
			deutronCut	= (TCutG*)gROOT->GetListOfSpecials()->FindObject("Deutron");
			protonToFCut	= (TCutG*)gROOT->GetListOfSpecials()->FindObject("ProtonToF");
			alphaCut	= (TCutG*)gROOT->GetListOfSpecials()->FindObject("Alpha");
		}
	public:
		GateCut(int runNumber){
			loadCut(runNumber);
			getCut();
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
		bool isProtonToF(double tof,double dE){
			return protonToFCut->IsInside(tof,dE);
		}
		bool isNoDeutron(double E,double dE){
			return !(deutronCut->IsInside(E,dE));
		}
		bool isAlpha(double E,double dE){
			return alphaCut->IsInside(E,dE);
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
			// dEE and dE-ToF - Protons 
			// remove events from deutrons
			//return isEspriRDCHit()&&isEspriPlasTime()&&(isProtonDEE()||isProtonToF());
			return isEspriRDCHit()&&isEspriPlasTime();
		}
		bool isEspriRDCHit(){
			return rf->isEspriRDCHit();
		}
		bool isEspriPlasTime(){
			return rf->isEspriPlasTime();
		}
		bool isProtonDEE(){
			return (gc->isProton(rf->getEspriNaiE(),rf->getEspriPlasE()));
		}
		bool isProtonToF(){
			return (gc->isProtonToF(rf->getEspriToF(),rf->getEspriPlasE())&&gc->isNoDeutron(rf->getEspriNaiE(),rf->getEspriPlasE()));
		}
		bool isAlpha(){
			return gc->isAlpha(rf->getTeleCsiE(),rf->getTeleDssdE());
		}
		bool isTargetArea(){
			return gc->isInsideTargetArea(rf->getTargetX(),rf->getTargetY());
		}

	public:
		Event(){}
		Event(ReadFile *inputFile, int runNumber){
			rf = inputFile;
			gc = new GateCut(runNumber);
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
			return isBeam()&&isProton()&&isTargetArea();
			//return isBeam();
			//return isProton();
			//return isTargetArea();
			//return isPRAngle();
			//return isHodPid();
		}
		void setBranch(TTree *tree){
		}
};
