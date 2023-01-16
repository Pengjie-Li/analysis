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
#include "ldp.h"

void test();
int main(int argc, char **argv)
{
	//gSystem->Load("/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/class/pixel/libTNewPixel.so"); 

	LDP m;
	m.Open();
	m.LoadPar();

	m.Build();

	m.LoadL();
        m.CheckRawLF();
        m.CheckRawLB();

	m.LoadR();
        m.CheckRawRF();
        m.CheckRawRB();


//	m.LoadLB();
//	m.LoadRF();
//	m.LoadRB();
//		m.Remove();

	m.Write();

	//test();
	return 0;
}


void test()
{

	TNewPixel n;
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


	//return 0;
}


