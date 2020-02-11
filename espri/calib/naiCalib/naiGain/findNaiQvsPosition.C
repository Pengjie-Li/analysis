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

class NaiGain{
	private:
		int runNumber;
		TString inputName;
		TFile *f;
		TTree *tree;
		TCanvas *cQvsPosition[2];
		TString outputname;
		double paraFit[2];
		double paraFitError[2];
	public:


		NaiGain(int run){
			runNumber = run;
			findNaiVsPosition();
		}
		~NaiGain(){
			delete f;
			delete tree;
			delete cQvsPosition[0];
			delete cQvsPosition[1];
		}



		void findNaiVsPosition(){

			inputName = Form("../convert/rootfiles/run0%d_ESPRI.root",runNumber);
			f =new TFile(inputName,"UPDATE");
			tree = (TTree *)f->Get("CalTreeESPRI");
			//tree->Print();

			cQvsPosition[0] = new TCanvas("cQvsPosition Left","cQvsPosition Left",1400,800);
			cQvsPosition[1] = new TCanvas("cQvsPosition Right","cQvsPosition Right",1400,800);
			cQvsPosition[0]->Divide(7,2);
			cQvsPosition[1]->Divide(7,2);
			for (int i = 0; i < 2;++i) {
				for (int j = 0; j < 7;++j) {

					cQvsPosition[i]->cd(j+1);
					drawPositionVsQDiff(tree,i,j);	
					cQvsPosition[i]->cd(j+8);
					fitHisto(i,j);
					outputTxt(i,j);
					gPad->Modified();
					gPad->Update();
				}

			}
		}
		void drawPositionVsQDiff(TTree *tree,int i,int j){
			int nBin = 1000;
			int qMin = -3;
			int qMax = 3;
			int pMin = -250; 
			int pMax = 250;
			TString draw = Form("rdcX[%d]-227.5:(TMath::Log(naiQCal[%d][%d])-TMath::Log(naiQCal[%d][%d]))>>hQDiff%d_%d(%d,%d,%d,%d,%d,%d)",i,2*i+1,j,2*i,j,i,j,nBin,qMin,qMax,nBin,pMin,pMax);
			TString condition = Form("naiQCal[%d][%d]>20&&naiQCal[%d][%d]>20",2*i+1,j,2*i,j);
			tree->Draw(draw,condition,"colz");
		}
		void fitHisto(int i,int j){

			TF1 *f = new TF1("f","pol1",-150,150);
			TH2D *h2D = (TH2D *)gDirectory->Get(Form("hQDiff%d_%d",i,j));
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
		void outputTxt(int i,int j){

			outputname=Form("NaiGainRun.txt");
			ofstream fout(outputname,ios_base::app | ios_base::out);
			double lamda = 1/paraFit[1];
			double gdOvergu = TMath::Exp(paraFit[0]);

			fout <<runNumber<<"\t"<<i<<"\t"<<j<<"\t"<<lamda<<"\t"<< gdOvergu <<"\t"<< paraFit[0] << "\t" << paraFit[1] <<endl;
			fout.close();
		}
};

int findNaiQvsPosition(){

	//for(int i= 296;i<500;i++){
	for(int i= 363;i<364;i++){
		NaiGain *naiGain = new NaiGain(i);
	}

	return 0;
}
int main(int argc, char **argv){

	//	for(int i= 444;i<500;i++){
	//		if(i == 431||i==432||(i>440&&i<448)) continue;
	//		NaiGain *naiGain = new NaiGain(i);
	//	}

	NaiGain *naiGain = new NaiGain(363);
	return 0;
}
