%#include "/Volumes/LPJ/S12/analysis/DrawCurve.h"
void outputText(){
		TString outputName = Form("./txt/dssdPedestal%d.txt",runNumber);
		ofstream fout(outputName,ios_base::out);
		for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 32; ++j) {

						fout<<i<<"      "<<j<<"\t"<<fitPara0[i][j]<<"\t"<<fitPara1[i][j]<<endl;
				}
		}
		fout.close();
}
void drawText(TString name,double x,double y){
		TLatex l;
		l.SetTextSize(0.1);
		l.SetNDC(kTRUE);
		l.DrawLatex(x,y,name);
}
void drawText(TString name){
		TLatex l;
		l.SetTextSize(0.05);
		l.SetNDC(kTRUE);
		l.DrawLatex(0.2,0.8,name);
}
void drawLegend(){
		TLegend *legends=new TLegend(0.7,0.8,0.9,0.90); // the numbers determine the position of the box
		// setting for legend
		legends->SetFillColor(0);
		legends->SetShadowColor(0);
		legends->SetBorderSize(0);
		legends->SetHeader("");
		legends->SetTextFont(72);
		legends->SetTextSize(0.02);
		TString nameHist[2] = {"RDC+Plas","RDC+Plas+NaI"}
		for (int i = 0; i < 2; ++i) {

				h1D[i]->SetLineColor(kOrange+8);
				//h1D[i]->Rebin(2);
				//h1D[i]->Draw("same");
				legends->AddEntry(h1D[i], nameHist[i],"p");
		}
		legends->Draw();
}
void drawPad(){

		//gStyle->SetOptStat(0);
		//gROOT->SetStyle("BABAR");
		TString fileName = "output/generate.root";
		TFile *outputFile = new TFile(fileName,"READ");
		TCanvas *cPad = new TCanvas("cPad","cPad",900, 900);


		TH1F *hCheck[7];
		for (int i = 0; i < 7; ++i) {

			int cid =i;
			TString hName = Form("hCsi%d", cid);
			//TString hName = "hAlpha";

			hCheck[i] = (TH1F*)outputFile->Get(hName);
			hCheck[i]->SetLineColor(i+1);

			if(i==0){

				hCheck[0]->GetYaxis()->SetRangeUser(0,30000);
				hCheck[0]->Draw();
			}
			else hCheck[i]->Draw("same");

		}


}
