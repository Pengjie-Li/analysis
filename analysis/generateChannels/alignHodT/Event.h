class Event{
	private:
		ReadFile *rf;
		bool isBeam(){
			return (rf->getTof713()>0)&&(rf->getF13Q()>0);
		}
                bool isInsideTargetArea(double x,double y){
                        return (sqrt((x-2.0)*(x-2.0)+(y+1.1)*(y+1.1))<15);
                }
		bool isTarget(){
			return isInsideTargetArea(rf->getTargetX(),rf->getTargetY());
		}
		bool isProton(){
			return (rf->getTrigESPRI()>0&&rf->isEspriRDCHit());		
		}
		bool isAlpha(){
			return (rf->getTeleCsiE()>0)&&(rf->getTeleDssdE()>0);
		}
		bool isHodTwoHit(){
			//cout<<rf->getHodBarQCal(10)<<" "<<rf->getHodQHit()<<" "<<rf->getHodTHit()<<endl;
			//cout<<rf->getHodHit()<<" "<<rf->getHodQHit()<<" "<<rf->getHodTHit()<<endl;
			//return (rf->getHodQHit()>=2&&rf->getHodTHit()>=2);
			return (rf->getHodHit()==2)&&(rf->getHodQHit()==2)&&(rf->getHodTHit()==2)&&(abs(rf->getHodHitId(0)-rf->getHodHitId(1)) == 1);
		}

	public:
		Event(){}
		Event(ReadFile *rf):rf(rf){
		}
		bool isSelectedEvent(){
			return isHodTwoHit();
		}
		void reconstruct(){
		}
		~Event(){
		}
		void setBranch(TTree *tree){
		}
		void print(){
		}
};
