void draw(int runNumber, int side, int fid, int bid){
	gROOT->ProcessLine(".x rootfiles/cutTargetArea.C");
	TString fileName = Form("rootfiles/run0%d_analysed.root",runNumber);
	TFile *inputFile = new TFile(fileName,"READ");
	TTree *tree = (TTree *)inputFile->Get("tree");
	TString backStrip = Form("Trig_DSB&&dssdEnergyCal[%d][%d]>4",side+1,bid);
	TString gate = targetArea + "&&" + backStrip;
	tree->Draw(Form("dssdEnergyCal[%d][%d]>>h%d_%d_%d_%d(100,4000,12000)",side,fid,runNumber,side,fid,bid),gate);
}
void drawResolutionAlphaRun(){
	//draw(596,0,15,15);
	draw(598,2,15,15);
	//drawHisto();
}
