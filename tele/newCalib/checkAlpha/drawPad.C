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
	TLine *line = new TLine(x,1E4,x,0);
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

	TCanvas *cPad = new TCanvas("cPad150","cPad150",700, 700);

	TH1F *h1D[2];
	h1D[0] = (TH1F*)outputFile->Get("hBeam150");
	h1D[1] = (TH1F*)outputFile->Get("hAlpha150");
	h1D[0]->SetLineColor(1);
	h1D[1]->SetLineColor(2);
	h1D[0]->Draw();
	h1D[1]->Draw("same");


	gPad->SetLogy();	
	TH1F *hCsi[7];
	for (int i = 0; i < 7; ++i) {
		int cid = i;
		hCsi[i] = (TH1F*)outputFile->Get(Form("hAlpha150%d",cid));
		hCsi[i]->SetLineColor(i+1);

		hCsi[i]->GetYaxis()->SetRangeUser(1,5E5);
		hCsi[i]->Draw("same");
	}

	drawVerticleLine(156.854);

}
void drawPad120(){

	TString fileName = "output/generate.root";
	TFile *outputFile = new TFile(fileName,"UPDATE");

	TCanvas *cPad = new TCanvas("cPad120","cPad120",700, 700);

	TH1F *h1D[2];
	h1D[0] = (TH1F*)outputFile->Get("hBeam120");
	h1D[1] = (TH1F*)outputFile->Get("hAlpha120");
	h1D[0]->SetLineColor(1);
	h1D[1]->SetLineColor(2);
	h1D[0]->Draw();
	h1D[1]->Draw("same");


	gPad->SetLogy();	
	TH1F *hCsi[7];
	for (int i = 0; i < 7; ++i) {
		int cid = i;
		hCsi[i] = (TH1F*)outputFile->Get(Form("hAlpha120%d",cid));
		hCsi[i]->SetLineColor(i+1);

		hCsi[i]->GetYaxis()->SetRangeUser(1,5E5);
		hCsi[i]->Draw("same");
	}
	drawVerticleLine(120.252);


}
void drawPad(){
	drawPad150();
	drawPad120();
}
