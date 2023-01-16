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
void drawPad150(){

		//gStyle->SetOptStat(0);
		//gROOT->SetStyle("BABAR");
		TString fileName = "output/generate.root";
		TFile *outputFile = new TFile(fileName,"READ");
		TCanvas *cPad = new TCanvas("cPad150","cPad150",1400, 900);
		cPad->Divide(4,2);	

		//cPad->SetLogy();

		TF1 *f = new TF1("fit", "gaus", 0,4000);
		double peak[7]= {1725,1646,1500,1695,1297, 1924,1720 };
		double sigma[7]= {21,11.2, 25.9,17, 9.8, 21, 18};
		TH1F *hCheck[7];
		for (int i = 0; i < 7; ++i) {

			f->SetParameter(1, peak[i]);
			f->SetParameter(2, sigma[i]);

			cPad->cd(i+1);

				
			int cid =i;
			TString hName = Form("hAlpha150Csi%d", cid);
			//TString hName = "hAlpha";

			hCheck[i] = (TH1F*)outputFile->Get(hName);
			hCheck[i]->SetLineColor(1);
			hCheck[i]->GetXaxis()->SetRangeUser(500,2500);

			hCheck[i]->Draw();
			hCheck[i]->Fit(f,"Q","QR", peak[i]-2*sigma[i],peak[i]+2*sigma[i]);
			//cout<<i<<" "<<f->GetParameter(1)<<" "<<f->GetParameter(2)<<endl;
			cout<<i<<" "<<f->GetParameter(1)<<" "<<f->GetParError(2)<<endl;

		}


}
void drawPad120(){

		//gStyle->SetOptStat(0);
		//gROOT->SetStyle("BABAR");
		TString fileName = "output/generate.root";
		TFile *outputFile = new TFile(fileName,"READ");
		TCanvas *cPad = new TCanvas("cPad120","cPad120",1400, 900);
		cPad->Divide(4,2);	

		//cPad->SetLogy();

		TF1 *f = new TF1("fit", "gaus", 0,4000);
		double peak[7]= {1185,1101,1013, 1100, 893, 1244, 1127};
		double sigma[7]= {9.4, 9.0, 8.5, 8.2, 7.7, 9.3, 8.4 };
	
		TH1F *hCheck[7];
		for (int i = 0; i < 7; ++i) {

			f->SetParameter(1, peak[i]);
			f->SetParameter(2, sigma[i]);


			cPad->cd(i+1);

			int cid =i;
			TString hName = Form("hAlpha120Csi%d", cid);
			//TString hName = "hAlpha";

			hCheck[i] = (TH1F*)outputFile->Get(hName);
			hCheck[i]->SetLineColor(1);
			hCheck[i]->GetXaxis()->SetRangeUser(500,1500);

			hCheck[i]->Draw();

			hCheck[i]->Fit(f,"Q","QR", peak[i]-2*sigma[i],peak[i]+2*sigma[i]);
			cout<<i<<" "<<f->GetParameter(1)<<" "<<f->GetParError(2)<<endl;



		}


}
void drawPad(){
	drawPad150();
	drawPad120();
}
