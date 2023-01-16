#include "/home/lipj/draw/atlasrootstyle-pub/AtlasStyle.C"
#include "/home/lipj/draw/babarExample/babarStyle.C"
void setDataAnalysis(){
	gROOT->Reset();
	gStyle->SetStatColor(0);
	gStyle->SetStatStyle(0);
	gStyle->SetStatX(0.9);
	gStyle->SetStatY(0.9);
	gStyle->SetStatH(0.15);
	gStyle->SetStatW(0.30);
	gStyle->SetPalette(1,0);
	gStyle->SetOptLogz(1);
	gStyle->SetOptFit(111);
	gStyle->SetOptStat(1111111);
}
void rootlogon(){
	setDataAnalysis();
	//setAtlasStyle();
	//setBabarStyle();
}
