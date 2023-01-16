#include "header.h"
#include "readMerger.h"

class GenerateEnergyTheta{
	public:
		ReadMerger *inputFile;
		int runNumber;
		
		TFile *outputFile;
		TTree *tree;

		TVector3        vBeam;
		TVector3        vBDC1;
		TVector3        vBDC2;
		TVector3        vTarget;
		TVector3        vDSSD;
		TVector3        vAlpha;
		double scatteringAngle;
		double alphaEnergy;
	

		GenerateEnergyTheta(){
		}
		GenerateEnergyTheta(int rn){
			runNumber = rn;
		}

		void loadInputFile(){
			inputFile =new ReadMerger(runNumber);	
			//inputFile =new ReadMerger();	
			//inputFile->print();
		}
		void createOutputFile(){
			outputFile = new TFile(Form("EnergyAlpha%d.root",runNumber),"recreate");
			tree = new TTree("tree","tree");
			setBranch();
			
		}
		void setBranch(){
			inputFile->setOutputBranch(tree);
			tree->Branch("vBeam","TVector3",&vBeam);
			tree->Branch("vAlpha","TVector3",&vAlpha);
			tree->Branch("vBDC1","TVector3",&vBDC1);
			tree->Branch("vBDC2","TVector3",&vBDC2);
			tree->Branch("vTarget","TVector3",&vTarget);
			tree->Branch("vDSSD","TVector3",&vDSSD);
			tree->Branch("scatteringAngle",&scatteringAngle,"scatteringAngle/D");
			tree->Branch("alphaEnergy",&alphaEnergy,"alphaEnergy/D");

		}
		void analysingLoop(){
			Long64_t nentries = inputFile->getEntries();
			//nentries = 5000;
			for(Long64_t ientry = 0; ientry<nentries; ientry++){
				if(ientry%1000 == 0) cout<<ientry<<endl;
				inputFile->getEntry(ientry);
				readBDC1();
				readBDC2();
				readTarget();
				readBeam();//for checking
				if(nentries<100) checkBeam();
				readDSSD();
				calculateAlpha();
				getCsIEnergy();
				tree->Fill();
			}
		}
		void readBDC1(){
			vBDC1 = inputFile->getVectorBDC1();
			//vBDC1.Print();
		}
		void readBDC2(){
			vBDC2 = inputFile->getVectorBDC2();
			//vBDC2.Print();
		}
		void readTarget(){
			vTarget = inputFile->getVectorTarget();
			//vTarget.Print();
		}
		void readBeam(){
			vBeam = inputFile->getVectorBeam();
			//vBeam.Print();
		}
		void readDSSD(){
			vDSSD = inputFile->getVectorDSSD();
			//vDSSD.Print();
		}
	
		void checkBeam(){
			cout<<(vBDC2-vBDC1).Angle(vBeam)<<endl;
			//cout<<(vTarget-vBDC2).Angle(vBeam)<<endl;
		}
		void calculateAlpha(){
			vAlpha = vDSSD - vTarget;
			scatteringAngle = vAlpha.Angle(vBeam)*TMath::RadToDeg();
			//cout<<scatteringAngle<<endl;
		}
		void getCsIEnergy(){
			alphaEnergy = inputFile->getCsIEnergy();
			//cout<<alphaEnergy<<endl;
		}
		void writeOutputFile(){
			tree->Write();
			//outputFile->Close();
		}
		void clearMemory(){
	//		delete inputFile;	
	//		delete outputFile;
	//		delete tree;
		}


};
int alphaEnergyTheta(){
	int runNumber = 595;
	GenerateEnergyTheta *energyTheta = new GenerateEnergyTheta(runNumber);
	//GenerateEnergyTheta *energyTheta = new GenerateEnergyTheta();
	energyTheta->loadInputFile();
	energyTheta->createOutputFile();
	energyTheta->analysingLoop();
	energyTheta->writeOutputFile();
	energyTheta->clearMemory();
	
	delete energyTheta;
	return 0;
}
int main(){
	return 0;
}
