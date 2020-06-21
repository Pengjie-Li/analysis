#include "WedgeShape.h"
void wedgeThick2(){
		double posX[10000];
		double thickY[10000];
		int eEvt = 0;
		WedgeShape *ws = new WedgeShape();
		ws->setThick(1.9,26,236.5);
		//cout<<ws->getThickness(178.5);
		for (int i = 0; i < 1800; ++i) {
				eEvt++;
				posX[i] = 0.25*i;
				thickY[i] = ws->getThickness(posX[i]);
				//cout<<i<<" "<<ws->getThickness(i)<<endl;
		}
		TGraph *gr = new TGraph(eEvt,posX,thickY);
		gr->SetName("th2");
		gr->Draw("apl");
		gr->Write();
}
void wedgeThick4(){
		double posX[10000];
		double thickY[10000];
		int eEvt = 0;
		WedgeShape *ws = new WedgeShape();
		//ws->setThick(4,30,230);
		ws->setThick(2,30,236.5);
		//cout<<ws->getThickness(178.5);
		for (int i = 0; i < 1800; ++i) {
				eEvt++;
				posX[i] = 0.25*i;
				thickY[i] = ws->getThickness(posX[i]);
				//cout<<i<<" "<<ws->getThickness(i)<<endl;
		}
		TGraph *gr = new TGraph(eEvt,posX,thickY);
		gr->SetName("th4");
		gr->Draw("plsame");
		gr->Write();
}
void wedgeThick(){
		TString fileName = "wedgeThickness.root";
		TFile *output = new TFile(fileName,"UPDATE");

		wedgeThick2();
		wedgeThick4();
}
