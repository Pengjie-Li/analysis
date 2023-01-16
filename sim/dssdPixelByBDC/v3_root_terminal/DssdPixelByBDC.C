/**
 * Function: With BDC1 and BDC2 3D Position(x,y,z),deduce the pixel position on DSSD
 * Conditions: By changing the DC resolution, square Area on DSSD then will be dim
 * Method: 1. Beam Generator; 2, BDC response detector, 3, DSSD detector (Position may perpendicular to Z axis or any position)
 * Structure: Detector: BDC, DSSD,
 * Detector: A Plane, intersection position
 */
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
#include "BeamGenerator.h"
#include "Detector.h"
#include "EventBuilder.h"
#include "EventSimulator.h"

void CheckBeamGenerator(){
	TH2F *hBeamXY =new TH2F("hBeamXY","hBeamXY",200,-50,50,200,-50,50);
	TH1F *hDirZ =new TH1F("hDirZ","hDirZ",200,0.9999,1.0001);

	int totalEventNumber = 100000;
	for(int i = 0; i< totalEventNumber; i++){
		BeamGenerator *beam = new BeamGenerator();
		hBeamXY->Fill(beam->getPointX(),beam->getPointY());
		hDirZ->Fill(beam->getDirZ());
	}
	//	TCanvas *cBeamChecker = new TCanvas("");
	TCanvas *cBeamXY = new TCanvas("cBeamXY","cBeamXY",900,800);
	hBeamXY->Draw("colz");
	TCanvas *cDirZ = new TCanvas("cDirZ","cDirZ",900,800);
	hDirZ->Draw();
}
int DssdPixelByBDC(){
	//CheckBeamGenerator();
	//int totalEventNumber = 10;
	//int totalEventNumber = 10000000;
	int totalEventNumber = 1000000;
	EventSimulator *es = new EventSimulator(totalEventNumber);
	return 0;
}
