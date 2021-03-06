class Event{
	private:
		ReadFile *rf;
		TCutG *protonCut;

		bool isBeam(){
			return (rf->getTof713()>0)&&(rf->getF13Q()>0);
		}
                bool isInsideTargetArea(double x,double y){
                        return (sqrt((x-2.0)*(x-2.0)+(y+1.1)*(y+1.1))<15);
                }
		bool isTarget(){
			return isInsideTargetArea(rf->getTargetX(),rf->getTargetY());
		}
                bool isProton(double E,double dE){
                        return protonCut->IsInside(E,dE);
                }
		bool isProton(){
			return (rf->getTrigESPRI()>0&&rf->isEspriRDCHit())&&isProton(rf->getEspriNaiE(),rf->getEspriPlasE());
			//return (rf->getTrigESPRI()>0);		
		}
		bool isAlpha(){
			//return (rf->getTeleCsiE()>0)&&(rf->getTeleDssdE()>0);
			return (rf->getTrigTele())&&(rf->getTeleHit()>0);
		}

                bool isPhi(){
                        double dPhi = 50;
                        return (abs((rf->getEspriPhi()-rf->getFdc0Phi())-180)<dPhi||abs((rf->getEspriPhi()-rf->getFdc0Phi()+ 360)-180)<dPhi);
                }


	public:
		Event(){}
		Event(ReadFile *rf):rf(rf){
			gROOT->ProcessLine(".x inputRootfiles/cutProton.C");	
			protonCut = (TCutG*)gROOT->GetListOfSpecials()->FindObject("Proton");
		}
		~Event(){
		}
		bool selectEvent(){
			return isBeam()&&isProton()&&isTarget()&&isPhi();
		}
		void setBranch(TTree *tree){
		}
};
