/**
 * Function: With BDC1 and BDC2 3D Position(x,y,z),deduce the pixel position on DSSD
 * Conditions: By changing the DC resolution, square Area on DSSD then will be dim
 * Method: 1. Beam Generator; 2, BDC response detector, 3, DSSD detector (Position may perpendicular to Z axis or any position)
 * Structure: Detector: BDC, DSSD,
 * Detector: A Plane, intersection position
 */
#include "header.h"
using namespace std;
#include <math.h>
#include <fstream>
#include <TFile.h>
#include <TMath.h>
#include <TEnv.h>
#include <TH3D.h>
#include <TTree.h>
#include <TVector3.h>
#include <Math/Functor.h>
#include <Math/Vector3D.h>
#include <TRandom2.h>
#include <TRandom3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF2.h>
#include <TH2D.h>
#include <TView.h>
#include <TH1.h>
#include <Math/Functor.h>
#include <TPolyLine3D.h>
#include <TPolyMarker3D.h>
#include <Math/Vector3D.h>
#include <Fit/Fitter.h>

TRandom3	r;
double AMU = 931.49410242; // MeV/u
double SOL = 299.792458;// mm/ns

#include "ProtonGenerator.h" 
ProtonGenerator *pg = new ProtonGenerator();

#include "Particle.h"
#include "ExcitationEnergy.h"
#include "EventBuilder.h"
#include "EventSimulator.h"


int ExcitationEnergy(int totalEventNumber){
	//CheckBeamGenerator();
	EventSimulator *es = new EventSimulator(totalEventNumber);
	return 0;
}
int main(int argc, char **argv){
	int totalEventNumber = 10;
	//int totalEventNumber = 10000000;
	if(argc == 2) totalEventNumber = atoi(argv[1]);
	return ExcitationEnergy(totalEventNumber);
}
