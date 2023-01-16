#include <TFile.h>
#include <TMath.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TString.h>
#include <TProfile.h>
#include <TF1.h>
#include <TH2D.h>
#include <iostream>
#include <fstream>
using namespace std;

class PlasGain{
	private:
		int runNumber;
		TString inputName;
		TFile *f;
		TTree *tree;
		TCanvas *cPvsQDiff;
		TString outputname;
		double paraFit[2];
		double paraFitError[2];
	public:


		PlasGain(int run){
			runNumber = run;
			findPlasVsPosition();
		}
		~PlasGain(){
			delete f;
			delete tree;
			delete cPvsQDiff;
		}



		void findPlasVsPosition(){

			inputName = Form("../convert/rootfiles/run0%d_ESPRI.root",runNumber);
			f =new TFile(inputName,"UPDATE");
			tree = (TTree *)f->Get("CalTreeESPRI");
			//tree->Print();

			cPvsQDiff = new TCanvas("P vs QDiff","P vs QDiff",1400,800);
			cPvsQDiff->Divide(2,2);
			for (int i = 0; i < 2;++i) {

				cPvsQDiff->cd(2*i+1);
				drawPositionVsQDiff(tree,i);	
				cPvsQDiff->cd(2*i+2);
				fitHisto(i);
				outputTxt(i);
				gPad->Modified();
				gPad->Update();
			}

		}
		void drawPositionVsQDiff(TTree *tree,int i){
			int nBin = 1000;
			int qMin = -3;
			int qMax = 2;
			int pMin = -250; 
			int pMax = 250;
			TString draw = Form("rdcY[%d]-227.5:(TMath::Log(plasQCal[%d])-TMath::Log(plasQCal[%d]))>>hPvsQDiff%d(%d,%d,%d,%d,%d,%d)",i,2*i,2*i+1,i,nBin,qMin,qMax,nBin,pMin,pMax);
			TString condition = "";
			tree->Draw(draw,condition,"colz");
		}
		void fitHisto(int i){

			TF1 *f = new TF1("f","pol1",-150,150);
			TH2D *h2D = (TH2D *)gDirectory->Get(Form("hPvsQDiff%d",i));
			//h2D->Draw("colz");
			TProfile *hPy = h2D->ProfileY();
			//TProfile *hPy = h2D->ProfileY("hPy",0,nBin);
			//hPy->Draw("same");
			hPy->Fit(f,"R");
			if(f->GetChisquare()<5000){
				f->GetParameters(paraFit);
			}
			delete f;
			//f->GetParErrors(paraFitError);

			//hPy->Fit("pol1");
			//double lamda = 1/f->GetParameter(1);
			//double gdOvergu = TMath::Exp(f->GetParameter(0));
			//cout<<"Ln(g_d/g_u)"<<f->GetParameter(0)<<" Error:"<<f->GetParError(0)<<endl;
			//cout<<"lamda = "<<lamda<<" gd/gu = "<<gdOvergu<<endl;

		}
		void outputTxt(int i){

			outputname=Form("PlasticGainRun%d.txt",i);
			ofstream fout(outputname,ios_base::app | ios_base::out);
			double lamda = 1/paraFit[1];
			double gdOvergu = TMath::Exp(paraFit[0]);

			fout <<runNumber<<"\t"<<i<<"\t"<<lamda<<"\t"<< gdOvergu <<"\t"<< paraFit[0] << "\t" << paraFit[1] <<endl;
			fout.close();
		}
};

int findPlasVsPosition(){
	
	for(int i= 296;i<500;i++){
		PlasGain *plasGain = new PlasGain(i);
	}
	
	return 0;
}
int main(int argc, char **argv){

//	for(int i= 444;i<500;i++){
//		if(i == 431||i==432||(i>440&&i<448)) continue;
//		PlasGain *plasGain = new PlasGain(i);
//	}
	
	PlasGain *plasGain = new PlasGain(360);
	return 0;
}
