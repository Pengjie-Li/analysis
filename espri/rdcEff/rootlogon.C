#if !defined( __CINT__) || defined (__MAKECINT__)

#ifndef ROOT_TStyle
#include "TStyle.h"
#endif

#endif


void rootlogon(){

  delete gROOT->GetStyle("PJStyle");
  TStyle *pjStyle = new TStyle("PJStyle", "PJStyle");
 

		pjStyle->SetPalette(1,0);
		// use plain black on white colors
		pjStyle->SetFrameBorderMode(0);
		pjStyle->SetCanvasBorderMode(0);
		pjStyle->SetPadBorderMode(0);
		pjStyle->SetPadColor(0);
		pjStyle->SetCanvasColor(0);
		pjStyle->SetStatColor(0);
		pjStyle->SetFillColor(0);

		// set the paper & margin sizes
		pjStyle->SetPaperSize(20,26);
		pjStyle->SetPadTopMargin(0.05);
		pjStyle->SetPadRightMargin(0.05);
		pjStyle->SetPadBottomMargin(0.16);
		pjStyle->SetPadLeftMargin(0.12);

		// use large Times-Roman fonts
		pjStyle->SetTextFont(132);
		pjStyle->SetTextSize(0.08);
		pjStyle->SetLabelFont(132,"xyz");
		//pjStyle->SetTitleFont(132,"xyz");
		pjStyle->SetLabelSize(0.05,"xyz");
		pjStyle->SetTitleSize(0.08,"xyz");

		// set title offsets (for axis label)
		pjStyle->SetTitleOffset(1.2, "x");
		pjStyle->SetTitleOffset(1.2, "y");
		pjStyle->SetTitleOffset(1., "z");
		pjStyle->SetTitleSize(0.05, "x");
		pjStyle->SetTitleSize(0.05, "y");
		pjStyle->SetTitleSize(0.05, "z");

		pjStyle->SetTitleX(0.5);
		pjStyle->SetTitleY(0.5);
		//pjStyle->SetTitleAlign(23);

		pjStyle->SetNdivisions(510, "x");
		pjStyle->SetNdivisions(510, "y");
		pjStyle->SetNdivisions(510, "z");

		// use bold lines and markers
		pjStyle->SetMarkerStyle(20);
		pjStyle->SetHistLineWidth(1.85);
		pjStyle->SetLineStyleString(2,"[12 12]"); // postscript dashes

		// get rid of X error bars and y error bar caps
		pjStyle->SetErrorX(0.001);

		// do not display any of the standard histogram decorations
		pjStyle->SetOptTitle(0);
		pjStyle->SetOptStat(0);
		pjStyle->SetOptFit(0);

		// put tick marks on top and RHS of plots
		//	pjStyle->SetPadTickX(1);
		//	pjStyle->SetPadTickY(1);
		gROOT->SetStyle("PJStyle");
		gROOT->UseCurrentStyle();
		gROOT->ForceStyle(kTRUE);


}

