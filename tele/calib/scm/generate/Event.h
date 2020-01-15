
class GateCut{
	private:
	public:
		GateCut(){
		}
		~GateCut(){}
		bool isInArea(int side,int fid,double fQPed,int bid,double bQPed){
			return true;
		}
};
class Event{
	private:
		ReadFile *rf;
		GateCut	*gc;
		bool isTeleHit(){
			return (rf->getTeleHit()==1)?true:false;
		}
		bool isInArea(){
			return gc->isInArea(rf->getTeleHitSide(),rf->getTeleHitFid(),rf->getTeleHitDssdFQPed(),rf->getTeleHitBid(),rf->getTeleHitDssdBQPed());
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
			return isTeleHit()&&isInArea();	
		}
		void setBranch(TTree *tree){
		}
};
