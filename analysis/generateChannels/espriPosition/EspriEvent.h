class EspriEvent{
	private:

		ReadFile *rf;
		TVector3 *espriPosition;
		TVector3 *targetPosition;
		TVector3 *vESPRI;
		TVector3 *vBeam;

		TVector3 *targetCenter;

		double espriAngle_r_1;
		double espriAngle_r_2;
		double espriAngle_r_3;
		double espriAngle_r_4;
		double espriAngle_r_5;
	
		double espriAngle_l_1;
		double espriAngle_l_2;
		double espriAngle_l_3;
		double espriAngle_l_4;
		double espriAngle_l_5;

		double espriAngle_u_1;
		double espriAngle_u_2;
		double espriAngle_u_3;
		double espriAngle_u_4;
		double espriAngle_u_5;

		double espriAngle_d_1;
		double espriAngle_d_2;
		double espriAngle_d_3;
		double espriAngle_d_4;
		double espriAngle_d_5;


		void shiftLR(double angle){
			(*espriPosition) = (*espriPosition) - (*targetCenter);
			(*espriPosition).RotateY(angle*TMath::DegToRad());
			(*espriPosition) = (*espriPosition) + (*targetCenter);
		}
        
		void shiftUD(double angle){
			(*espriPosition) = (*espriPosition) - (*targetCenter);
			(*espriPosition).RotateX(angle*TMath::DegToRad());
			(*espriPosition) = (*espriPosition) + (*targetCenter);
		}
                double setAngle(){
                        (*vESPRI)        = (*espriPosition)-(*targetPosition);
                        (*vESPRI)        = (*vESPRI).Unit();
                        return (*vESPRI).Angle((*vBeam))*TMath::RadToDeg();
                }


	public:
		void print(){
		}
		EspriEvent(){
			vESPRI = new TVector3;
			targetCenter = new TVector3;
			targetCenter->SetXYZ(0,0,0);
		}

		~EspriEvent(){
		}
		void init(){
			rf = NULL;
			vESPRI->SetXYZ(NAN,NAN,NAN);

			espriAngle_u_1 = NAN;
			espriAngle_u_2 = NAN;
			espriAngle_u_3 = NAN;

			espriAngle_d_1 = NAN;
			espriAngle_d_2 = NAN;
			espriAngle_d_3 = NAN;
	
			espriAngle_l_1 = NAN;
			espriAngle_l_2 = NAN;
			espriAngle_l_3 = NAN;
			espriAngle_l_4 = NAN;
			espriAngle_l_5 = NAN;
	
			espriAngle_r_1 = NAN;
			espriAngle_r_2 = NAN;
			espriAngle_r_3 = NAN;
			espriAngle_r_4 = NAN;
			espriAngle_r_5 = NAN;
		}
		void load(ReadFile *te){
			rf = te;
		}

		void setEvent(){
			telePosition = rf->getTelePosition();
			targetPosition = rf->getTargetPosition();
			vBeam = rf->getBeamDirection();

			//targetPosition->Print();
			//vBeam->Print();
			//telePosition->Print();
			shiftLR(0.1);
			teleAngle_right_1 = setAngle();
			shiftLR(0.1);
			teleAngle_right_2 = setAngle();
			shiftLR(0.1);
			teleAngle_right_3 = setAngle();
			shiftLR(0.1);
			teleAngle_right_4 = setAngle();
			shiftLR(0.1);
			teleAngle_right_5 = setAngle();
			//telePosition->Print();
	
			shiftLR(-0.5);

			shiftLR(-0.1);
			teleAngle_left_1 = setAngle();
			shiftLR(-0.1);
			//telePosition->Print();
			teleAngle_left_2 = setAngle();
			shiftLR(-0.1);
			teleAngle_left_3 = setAngle();
			shiftLR(-0.1);
			teleAngle_left_4 = setAngle();
			shiftLR(-0.1);
			teleAngle_left_5 = setAngle();
			//telePosition->Print();
		
			shiftLR(0.5);

			shiftUD(-0.1);
			teleAngle_up_1 = setAngle();
			shiftUD(-0.1);
			teleAngle_up_2 = setAngle();
			shiftUD(-0.1);
			teleAngle_up_3 = setAngle();
			//telePosition->Print();

			shiftUD(0.3);

			shiftUD(0.1);
			teleAngle_down_1 = setAngle();
			shiftUD(0.1);
			teleAngle_down_2 = setAngle();
			shiftUD(0.1);
			teleAngle_down_3 = setAngle();
			//telePosition->Print();
			shiftUD(-0.3);
	
		}
		void print(){
			//cout<<"Alpha Angle: "<<rf->getTeleAngle()<<"  "<<teleAngle_up<<"  "<<teleAngle_down<<"  "<<teleAngle_left<<"  "<<teleAngle_right<<endl;
		}
		void setOutputBranch(TTree *tree){

			tree->Branch("teleAngle_up_1",&teleAngle_up_1,"teleAngle_up_1/D");
			tree->Branch("teleAngle_up_2",&teleAngle_up_2,"teleAngle_up_2/D");
			tree->Branch("teleAngle_up_3",&teleAngle_up_3,"teleAngle_up_3/D");

			tree->Branch("teleAngle_down_1",&teleAngle_down_1,"teleAngle_down_1/D");
			tree->Branch("teleAngle_down_2",&teleAngle_down_2,"teleAngle_down_2/D");
			tree->Branch("teleAngle_down_3",&teleAngle_down_3,"teleAngle_down_3/D");

			tree->Branch("teleAngle_left_1",&teleAngle_left_1,"teleAngle_left_1/D");
			tree->Branch("teleAngle_left_2",&teleAngle_left_2,"teleAngle_left_2/D");
			tree->Branch("teleAngle_left_3",&teleAngle_left_3,"teleAngle_left_3/D");
			tree->Branch("teleAngle_left_4",&teleAngle_left_4,"teleAngle_left_4/D");
			tree->Branch("teleAngle_left_5",&teleAngle_left_5,"teleAngle_left_5/D");
	
			tree->Branch("teleAngle_right_1",&teleAngle_right_1,"teleAngle_right_1/D");
			tree->Branch("teleAngle_right_2",&teleAngle_right_2,"teleAngle_right_2/D");
			tree->Branch("teleAngle_right_3",&teleAngle_right_3,"teleAngle_right_3/D");
			tree->Branch("teleAngle_right_4",&teleAngle_right_4,"teleAngle_right_4/D");
			tree->Branch("teleAngle_right_5",&teleAngle_right_5,"teleAngle_right_5/D");
		}
};
		void setOutputBranch(TTree *tree){

			calibESPRI->setBranch(tree);
			positionESPRI->setBranch(tree);

		}
		void setESPRIEvent(){
			if(mergeData->isGoodEvent()){
				setESPRIEnergy();
				setESPRIPosition();
			}
		}
		bool isGoodEvent(){
			return mergeData->isGoodEvent()&&(getAngle()>0)&&(getNaiEnergy()>0);// Good Event->roughly good, real good event selected by TCut
		}
		void setESPRIPosition(){
			positionESPRI->loadTargetPosition(targetPosition);
			positionESPRI->loadBeamVector(vBeam);
			
			positionESPRI->loadData(mergeData);
			positionESPRI->analysis();
		}
		void setESPRIEnergy(){

			calibESPRI->loadData(mergeData);
			calibESPRI->calibrate();
			
		}
		void loadTargetPosition(TVector3 *target){
			targetPosition = target;
		}
		void loadBeamVector(TVector3 *beam){
			vBeam = beam;
		}
		bool isNaiHit(){
			return (mergeData->getNaiHit()==1);
		}
		double getNaiEnergy(){
			return calibESPRI->getNaiEnergy();
		}
		double getLocusAngle(){
			return positionESPRI->getLocusAngle();
		}
		double getAngle(){
			return positionESPRI->getAngle();
		}
};
