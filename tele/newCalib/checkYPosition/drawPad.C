#include "/Volumes/LPJ/S12/analysis/DrawCurve.h"
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
		TCanvas *cPad = new TCanvas("cPad","cPad",1400,600);
		cPad->Divide(2,1);

		TH2F *h2D[2];

		h2D[0] = (TH2F*)outputFile->Get("hPhiLeftBe14");
		h2D[1] = (TH2F*)outputFile->Get("hPhiRightBe14");

		cPad->cd(1);
		cPad->SetFillColor(0);
		cPad->SetFillStyle(4000);

		//TGaxis::SetMaxDigits(2);
		gPad->SetLogz();
		h2D[0]->SetTitle("");
		h2D[0]->RebinX(2);
		h2D[0]->RebinY(2);
		//h2D[0]->GetYaxis()->SetRangeUser(20,150);
		//h2D[0]->GetXaxis()->SetRangeUser(55,72);
		h2D[0]->GetYaxis()->SetTitle("#phi_{p}(MeV)");
		h2D[0]->GetXaxis()->SetTitle("#phi_{^{14}Be}(deg)");
		h2D[0]->GetXaxis()->CenterTitle();
		h2D[0]->GetYaxis()->CenterTitle();
		h2D[0]->Draw("colz");
		drawText("Left ESPRI");


		cPad->cd(2);
		cPad->SetFillColor(0);
		cPad->SetFillStyle(4000);

		gPad->SetLogz();
		h2D[1]->SetTitle("");
		h2D[1]->RebinX(2);
		h2D[1]->RebinY(2);
		//h2D[1]->GetYaxis()->SetRangeUser(20,150);
		//h2D[1]->GetXaxis()->SetRangeUser(55,72);
		//h2D[1]->SetMaximum(7);
		h2D[1]->GetYaxis()->SetTitle("#phi_{p}(MeV)");
		h2D[1]->GetXaxis()->SetTitle("#phi_{^{14}Be}(deg)");
		h2D[1]->GetXaxis()->CenterTitle();
		h2D[1]->GetYaxis()->CenterTitle();
		h2D[1]->Draw("colz");
		drawText("Right ESPRI");


		cPad->Print("phiBe14.eps");
		cPad->Print("phiBe14.pdf");
}
