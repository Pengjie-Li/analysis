/*********************************/
/*******Algorithm****************/
/*
 * Open rawdata file
 * Load proper data into pixel
 * fit with least square method or TGraph
 * Self Calibration method to get the final parameter
 * Check
*/


#include "header.h"

#include "Pixel.h"
#include "scm.h"

int main(int argc, char **argv)
{
        TString inputname;
	int runnum;
//	if(argc<2) cout<<" USAGE:./scm inputname"<<endl;
//	if(argc==2) inputname=argv[1];
	if(argc<2) cout<<" USAGE:./scm runnum"<<endl;
	if(argc==2) runnum=atoi(argv[1]);
	inputname=Form("rootfiles/run0%d_Beamv8.root",runnum);
	//test();

	SCM m(15);
	m.Open(inputname);
	m.LoadPar(inputname);
	m.Load();
	m.Build();
	m.Fit();
	m.OverAllSCM(runnum);
       return 0;
}
void test()
{
	Pixel n;
	n.Fill(1.01 ,0.00);
	n.Fill(1.27 ,0.19);
	n.Fill(1.85 ,0.58);
	n.Fill(2.38 ,0.96);
	n.Fill(2.83 ,1.26);
	n.Fill(3.13 ,1.47);
	n.Fill(3.96 ,2.07);
	n.Fill(4.91 ,2.75);

	bool status=n.Fit();
	cout<<"S="<<n.S<<endl;
	cout<<"k="<<n.k<<" b="<<n.b<<" ek="<<n.ek<<" eb="<<n.eb<<endl;


}
