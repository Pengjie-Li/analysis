//#include "/Volumes/LPJ/S12/analysis/DrawCurve.h"
//
TH1F *h1D[2];
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
void drawVerticleLine(double x){
	TLine *line = new TLine(x,1,x,0);
	line->SetLineColor(1);
	line->SetLineStyle(2);
	line->SetLineWidth(2);
	line->Draw();
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
	TString nameHist[2] = {"Beam","Reconstructed Alpha"}
	for (int i = 0; i < 2; ++i) {
		h1D[i]->SetLineColor(kOrange+8);
		//h1D[i]->Rebin(2);
		//h1D[i]->Draw("same");
		legends->AddEntry(h1D[i], nameHist[i],"p");
	}
	legends->Draw();
}
void drawPad150(){

	TString fileName = "output/generate.root";
	TFile *outputFile = new TFile(fileName,"UPDATE");

	TCanvas *cPad = new TCanvas("cPad150","cPad150",1400, 700);
	cPad->Divide(4,2);
	
	
	TH1F *hCsi[7];
	TH1F *hBeam[7];

	for (int i = 0; i < 7; ++i) {
		int cid = i;
		hCsi[i] = (TH1F*)outputFile->Get(Form("hAlpha150%d",cid));
		hCsi[i]->SetLineColor(i+1);

		hBeam[i] = (TH1F*)outputFile->Get(Form("hBeam150%d",cid));
		hBeam[i]->SetLineColor(1);
		hBeam[i]->SetLineWidth(2);
		hBeam[i]->GetXaxis()->SetRangeUser(150,162);
	
		//hCsi[i]->GetYaxis()->SetRangeUser(1,5E5);
		//hCsi[i]->Draw("same");
	}



	for (int i = 0; i < 7; ++i) {

		hBeam[i]->Scale(1.0/hBeam[i]->GetMaximum());
		hCsi[i]->Scale(1.0/hCsi[i]->GetMaximum());
	
		cPad->cd(i+1);
		hBeam[i]->Draw();
		hCsi[i]->Draw("same");
		drawVerticleLine(156.689);
		//h1D[1]->Draw("same");

	}

}
void drawPad120(){

	TString fileName = "output/generate.root";
	TFile *outputFile = new TFile(fileName,"UPDATE");

	TCanvas *cPad = new TCanvas("cPad120","cPad120",1400, 700);
	cPad->Divide(4,2);

	
	TH1F *hBeam[7];
	TH1F *hCsi[7];

	for (int i = 0; i < 7; ++i) {

		int cid = i;

		hBeam[i] = (TH1F*)outputFile->Get(Form("hBeam120%d",cid));
		hBeam[i]->SetLineColor(1);
		hBeam[i]->SetLineWidth(2);
		hBeam[i]->GetXaxis()->SetRangeUser(115,125);
		hCsi[i] = (TH1F*)outputFile->Get(Form("hAlpha120%d",cid));
		hCsi[i]->SetLineColor(i+1);

		//hCsi[i]->GetYaxis()->SetRangeUser(1,5E5);
		//hCsi[i]->Draw("same");
	}



	for (int i = 0; i < 7; ++i) {

		hBeam[i]->Scale(1.0/hBeam[i]->GetMaximum());
		hCsi[i]->Scale(1.0/hCsi[i]->GetMaximum());
		cPad->cd(i+1);
		hBeam[i]->Draw();
		hCsi[i]->Draw("same");
		drawVerticleLine(120.157);

	}

}
void draw7Pad(){
	drawPad150();
	drawPad120();
}
