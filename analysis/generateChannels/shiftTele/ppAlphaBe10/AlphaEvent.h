#include "PhiFunction.h"
class AlphaCalibPara{
	private:

		double apDssdE;
		double apDegraderE;
		double apWinE;

		TGraph *degraderEnergyToRange;
		TGraph *degraderRangeToEnergy;

		TGraph *dssdEnergyToRange;
		TGraph *dssdRangeToEnergy;
		TGraph *winEloss;


		double dssdThickness;
		double degraderThickness;

		TGraph *csiAlpha;

		double getDssdE(double angle,double energyOut){
			double realThickness = dssdThickness/cos(angle*TMath::DegToRad()); 
			double rangeIn = realThickness + dssdEnergyToRange->Eval(energyOut,0,"S");
			double energyIn = dssdRangeToEnergy->Eval(rangeIn,0,"S");
			//cout<<"DSSD "<<realThickness<<" "<<energyIn<<energyOut<<endl;
			return (energyIn-energyOut);
		}
		double getDegraderE(double angle,double energyOut){
			double realThickness = degraderThickness/cos(angle*TMath::DegToRad()); 
			double rangeIn = realThickness + degraderEnergyToRange->Eval(energyOut,0,"S");
			double energyIn = degraderRangeToEnergy->Eval(rangeIn,0,"S");
			//cout<<"Degrader "<<realThickness<<" "<<energyIn<<energyOut<<endl;
			return (energyIn-energyOut);
		}
		double getWindowE(double energy){
			//cout<<"in "<<energy<<" winE"<<winEloss->Eval(energy,0,"S")<<endl;
			return winEloss->Eval(energy);
		}

	public:
		AlphaCalibPara(){
			dssdThickness = 1.522;//mm
			degraderThickness = 25;//mm
			TFile *fCalib = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/alphaDEE/dEECurve.root","READ");
			csiAlpha = (TGraph *)gDirectory->Get("dEE_TotCsi");
			fCalib->Close();	
			TFile *fEloss = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/energyLossInMaterial/output/alphaInMaterials.root","READ");
			dssdEnergyToRange = (TGraph *)gDirectory->Get("alphaDssdER");
			dssdRangeToEnergy = (TGraph *)gDirectory->Get("alphaDssdRE");
			degraderEnergyToRange = (TGraph *)gDirectory->Get("alphaDegraderER");
			degraderRangeToEnergy = (TGraph *)gDirectory->Get("alphaDegraderRE");
			fEloss->Close();	
			TFile *fWinEloss = new TFile("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/plot/energyLossInMaterial/output/alphaWindowEloss.root","READ");
			winEloss = (TGraph *)gDirectory->Get("windowEloss");
			fWinEloss->Close();
		}
		~AlphaCalibPara(){}
		double getEnergy_old(double csiE){
			return csiAlpha->Eval(csiE);
		}
		double getEnergy(double csiE,double locusAngle){

			apDssdE = getDssdE(locusAngle,csiE);
			apDegraderE = getDegraderE(locusAngle,csiE+apDssdE);
			apWinE = getWindowE(apDegraderE+apDssdE+csiE);
			return apWinE+apDegraderE+apDssdE+csiE;
		}
		void setOutputBranch(TTree *tree){
			tree->Branch("apDssdE",&apDssdE,"apDssdE/D");
			tree->Branch("apDegraderE",&apDegraderE,"apDegraderE/D");
			tree->Branch("apWinE",&apWinE,"apWinE/D");
		}
		void init(){
			apDssdE = NAN;
			apDegraderE = NAN;
			apWinE = NAN;
		}
		void print(){

			cout<<" apWinE ="<<apWinE<<" apDegraderE ="<<apDegraderE<<" apDssdE ="<<apDssdE<<endl;
		}
};
class AlphaEvent{
	private:

		ReadFile *rf;
		TVector3 *telePosition;
		TVector3 *targetPosition;
		TVector3 *vTele;
		TVector3 *vBeam;
		int isLR;
		PhiFunction *phiFuction;

		TVector3 *teleLXAxis;
		TVector3 *teleLYAxis;
		TVector3 *teleRXAxis;
		TVector3 *teleRYAxis;

		double teleAngleRight[10];
		double teleAngleLeft[10];
		double teleAngleUp[10];
		double teleAngleDown[10];


		double telePhiRight[10];
		double telePhiLeft[10];
		double telePhiUp[10];
		double telePhiDown[10];

		double teleAngleNew;
		double telePhiNew;

		void shiftLR(double dx){
			if(isLR==0) (*telePosition) = (*telePosition) + dx*(*teleLXAxis);
			else (*telePosition) = (*telePosition) + dx*(*teleRXAxis);
		}

		void shiftUD(double dy){
			if(isLR==0) (*telePosition) = (*telePosition) + dy*(*teleLYAxis);
			else (*telePosition) = (*telePosition) + dy*(*teleRYAxis);
		}
		void setAngle(){
			(*vTele)        = (*telePosition)-(*targetPosition);
			(*vTele)        = (*vTele).Unit();
		}
		double getAngle(){
			return (*vTele).Angle((*vBeam))*TMath::RadToDeg();
		}
		double getPhi(){
			return phiFuction->getPhi((*vBeam),(*vTele));
		}
	public:
		AlphaEvent(){
			vTele = new TVector3;
			phiFuction = new PhiFunction();

			teleLXAxis=new TVector3();teleLXAxis->SetXYZ(0.989134,0.000000,0.147020);
			teleLYAxis=new TVector3();teleLYAxis->SetXYZ(0.000588,0.999992,-0.003957);
			teleRXAxis=new TVector3();teleRXAxis->SetXYZ(0.988069,0.000000,-0.154011);
			teleRYAxis=new TVector3();teleRYAxis->SetXYZ(0.000308,0.999998,0.001976);
		}
		~AlphaEvent(){
		}

		void init(){
			rf = NULL;
			vTele->SetXYZ(NAN,NAN,NAN);
			isLR = -1;

			teleAngleNew = NAN;
			telePhiNew = NAN;
			for (int i = 0; i < 10; ++i) {

				teleAngleLeft[i] = NAN;
				teleAngleRight[i] = NAN;
				teleAngleUp[i] = NAN;
				teleAngleDown[i] = NAN;

				telePhiLeft[i] = NAN;
				telePhiRight[i] = NAN;
				telePhiUp[i] = NAN;
				telePhiDown[i] = NAN;

			}
		}
		void load(ReadFile *te){
			rf = te;
		}
		void setEvent(){
			telePosition = rf->getTelePosition();
			targetPosition = rf->getTargetPosition();
			vBeam = rf->getBeamDirection();
			isLR = rf->getTeleSide();

			telePosition->Print();
			if(isLR == 0) shiftLR(0.9);
			else shiftLR(2.4);

			setAngle();
			teleAngleNew = getAngle();
			telePhiNew = getPhi();

			//targetPosition->Print();
			//vBeam->Print();
			telePosition->Print();
			for (int i = 0; i < 10; ++i) {
				shiftLR(0.3);
				setAngle();
				teleAngleRight[i] = getAngle();
				telePhiRight[i] = getPhi();
			}
			//telePosition->Print();

			shiftLR(-3);

			for (int i = 0; i < 10; ++i) {
				shiftLR(-0.3);
				setAngle();
				teleAngleLeft[i] = getAngle();
				telePhiLeft[i] = getPhi();
			}
			shiftLR(3);

			for (int i = 0; i < 10; ++i) {
				shiftUD(0.3);
				setAngle();
				teleAngleUp[i] = getAngle();
				telePhiUp[i] = getPhi();
			}
			shiftUD(-3);


			for (int i = 0; i < 10; ++i) {
				shiftUD(-0.3);
				setAngle();
				teleAngleDown[i] = getAngle();
				telePhiDown[i] = getPhi();
			}
			shiftUD(3);

		}
		void print(){

			cout<<"Alpha Angle: "<<rf->getTeleAngle()<<"  ";
			for (int i = 0; i < 10; ++i) {
				cout<<teleAngleLeft[i]<<"  ";
			}
			cout<<endl;
			for (int i = 0; i < 10; ++i) {
				cout<<teleAngleRight[i]<<"  ";
			}
			cout<<endl;
			for (int i = 0; i < 10; ++i) {
				cout<<teleAngleUp[i]<<"  ";
			}
			cout<<endl;
			for (int i = 0; i < 10; ++i) {
				cout<<teleAngleDown[i]<<"  ";
			}
			cout<<endl;


			cout<<"Alpha Phi: "<<rf->getTelePhi()<<"  ";
			for (int i = 0; i < 10; ++i) {
				cout<<telePhiLeft[i]<<"  ";
			}
			cout<<endl;
			for (int i = 0; i < 10; ++i) {
				cout<<telePhiRight[i]<<"  ";
			}
			cout<<endl;
			for (int i = 0; i < 10; ++i) {
				cout<<telePhiUp[i]<<"  ";
			}
			cout<<endl;
			for (int i = 0; i < 10; ++i) {
				cout<<telePhiDown[i]<<"  ";
			}
			cout<<endl;


		}
		void setOutputBranch(TTree *tree){
			tree->Branch("teleAngleNew",&teleAngleNew,"teleAngleNew/D");
			tree->Branch("telePhiNew",&telePhiNew,"telePhiNew/D");

			tree->Branch("teleAngleRight",teleAngleRight,"teleAngleRight[10]/D");
			tree->Branch("teleAngleLeft",teleAngleLeft,"teleAngleLeft[10]/D");
			tree->Branch("teleAngleUp",teleAngleUp,"teleAngleUp[10]/D");
			tree->Branch("teleAngleDown",teleAngleDown,"teleAngleDown[10]/D");

			tree->Branch("telePhiRight",telePhiRight,"telePhiRight[10]/D");
			tree->Branch("telePhiLeft",telePhiLeft,"telePhiLeft[10]/D");
			tree->Branch("telePhiUp",telePhiUp,"telePhiUp[10]/D");
			tree->Branch("telePhiDown",telePhiDown,"telePhiDown[10]/D");

		}
};
