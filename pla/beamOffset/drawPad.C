// Quadratic background function
Double_t background(Double_t *x, Double_t *par) {
	return par[0] + par[1]*x[0] + par[2]*x[0]*x[0];
}
// Breit-Wigner function
Double_t mybw (Double_t * x, Double_t * by)
{
	Double_t arg1 = 14.0 / 22.0; // 2 over pi
	Double_t arg2 = by [1] * by [1] * by [2] * by [2]; // Gamma = by [1] M = by [2]
	Double_t arg3 = ((x [0] * x [0]) - (by [2] * by [2])) * ((x [0] * x [0]) - (by [2] * by [ 2]));
	Double_t arg4 = x [0] * x [0] * x [0] * x [0] * ((by [1] * by [1]) / (by [2] * by [2]));
	return by [0] * arg1 * arg2 / (arg3 + arg4);
}
Double_t mygauss(Double_t * x, Double_t * par)
{
	Double_t arg = 0;
	if (par[2]<0) par[2]=-par[2];  // par[2]: sigma
	if (par[2] != 0) arg = (x[0] - par[1])/par[2];  // par[1]: mean

	return par[0]*TMath::Exp(-0.5*arg*arg)/
		(TMath::Sqrt(2*TMath::Pi())*par[2]); // par[0] is constant

}
// Sum of background and peak function
Double_t fit(Double_t *x, Double_t *par) {
	return mygauss(x,&par[0]) ;
}


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

	gStyle->SetOptStat(1);
	gStyle->SetOptFit(1);
	//gROOT->SetStyle("BABAR");
	TString fileName = "output/generate.root";
	TFile *outputFile = new TFile(fileName,"READ");
	TCanvas *cPad = new TCanvas("cPad","cPad",1400,600);
	cPad->Divide(2,1);

	TH1F *h1D[2];

	h1D[0] = (TH1F*)outputFile->Get("hAlpha150");
	h1D[1] = (TH1F*)outputFile->Get("hAlpha120");

	cPad->cd(1);
	cPad->SetFillColor(0);
	cPad->SetFillStyle(4000);

	h1D[0]->SetTitle("");
	h1D[0]->GetXaxis()->SetTitle("Ek713");
	h1D[0]->GetXaxis()->CenterTitle();
	h1D[0]->GetYaxis()->CenterTitle();
	h1D[0]->Draw("colz");
	drawText("Alpha150");

	TF1 *f1  = new TF1("f1","gaus", 150,160);
        f1->SetNpx(500);
        f1->SetParameter(1,157);
        f1->SetParameter(2,0.6);


        f1->SetLineColor(2);
        f1->SetLineStyle(1);
        h1D[0]->Fit(f1,"QR","",156,158.5);
        cout<<f1->GetParameter(1)<<" "<<f1->GetParameter(2)<<" "<<endl;



	cPad->cd(2);
	cPad->SetFillColor(0);
	cPad->SetFillStyle(4000);

	h1D[1]->SetTitle("");
	h1D[1]->GetXaxis()->SetTitle("Ek713");
	h1D[1]->GetXaxis()->CenterTitle();
	h1D[1]->GetYaxis()->CenterTitle();
	h1D[1]->Draw("colz");
	drawText("Alpha120");

	TF1 *f2  = new TF1("f2","gaus", 110,125);
        f2->SetNpx(500);
        f2->SetParameter(1,120);
        f2->SetParameter(2,0.5);


        f2->SetLineColor(2);
        f2->SetLineStyle(1);
        h1D[1]->Fit(f2,"QR","",119.5,121.5);
        cout<<f2->GetParameter(1)<<" "<<f2->GetParameter(2)<<" "<<endl;



}
