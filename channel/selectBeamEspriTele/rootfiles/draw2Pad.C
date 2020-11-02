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
void draw2Pad(){

		gStyle->SetOptStat(1111111);
		//gStyle->SetOptStat(0);
		//gROOT->SetStyle("BABAR");
		TString fileName = "output/generate.root";
		TFile *outputFile = new TFile(fileName,"READ");
		TCanvas *cPad = new TCanvas("cPad","cPad",800,700);
		cPad->Divide(2,2);

		TH2 *hRDC[4];
		hRDC[0] = (TH2*)gDirectory->Get("hRDCL02");
		hRDC[1] = (TH2*)gDirectory->Get("hRDCL03");
		hRDC[2] = (TH2*)gDirectory->Get("hRDCR12");
		hRDC[3] = (TH2*)gDirectory->Get("hRDCR13");


		//TGaxis::SetMaxDigits(4);
		cPad->cd(1);
		//gPad->SetLogz();
		hRDC[0]->SetTitle("");
		hRDC[0]->GetYaxis()->SetTitle("Y (mm)");
		hRDC[0]->GetXaxis()->SetTitle("X (mm) ");
		hRDC[0]->GetXaxis()->CenterTitle();
		hRDC[0]->GetYaxis()->CenterTitle();
		hRDC[0]->Draw("colz");
		drawText("(Bar 02 Left RDC X vs Y)");

		//TGaxis::SetMaxDigits(4);
		cPad->cd(2);
		//gPad->SetLogz();
		hRDC[1]->SetTitle("");
		hRDC[1]->GetYaxis()->SetTitle("Y (mm)");
		hRDC[1]->GetXaxis()->SetTitle("X (mm) ");
		hRDC[1]->GetXaxis()->CenterTitle();
		hRDC[1]->GetYaxis()->CenterTitle();
		hRDC[1]->Draw("colz");
		drawText("(Bar 03 Left RDC X vs Y)");



		//TGaxis::SetMaxDigits(4);
		cPad->cd(3);
		//gPad->SetLogz();
		hRDC[2]->SetTitle("");
		hRDC[2]->GetYaxis()->SetTitle("Y (mm)");
		hRDC[2]->GetXaxis()->SetTitle("X (mm) ");
		hRDC[2]->GetXaxis()->CenterTitle();
		hRDC[2]->GetYaxis()->CenterTitle();
		hRDC[2]->Draw("colz");
		drawText("(Bar 02 Right RDC X vs Y)");

		//TGaxis::SetMaxDigits(4);
		cPad->cd(4);
		//gPad->SetLogz();
		hRDC[3]->SetTitle("");
		hRDC[3]->GetYaxis()->SetTitle("Y (mm)");
		hRDC[3]->GetXaxis()->SetTitle("X (mm) ");
		hRDC[3]->GetXaxis()->CenterTitle();
		hRDC[3]->GetYaxis()->CenterTitle();
		hRDC[3]->Draw("colz");
		drawText("(Bar 03 Right RDC X vs Y)");


		cPad->Print("rdcEff.eps");
		cPad->Print("rdcEff.pdf");
}
