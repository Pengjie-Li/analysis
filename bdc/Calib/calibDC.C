#include "header.h"
#include "CalibDC.h"
int main(int argc, char *argv[])
{
	int runStart=-1;
	int runStop=-1;
	if(argc==2) {
		runStart=atoi(argv[1]);
		runStop=runStart+1;
		
	} else if(argc==3) {
		runStart=atoi(argv[1]);
		runStop=atoi(argv[2]);
	} else {
		cout<<" USAGE: ./TDCSpectrum  runNumberber"<<endl;
		cout<<" USAGE: ./TDCSpectrum  runStart runStop"<<endl;
	}
	CalibDC *calibDC =new CalibDC();

	calibDC->loadChain(runStart,runStop);

//	calibDC->openData();
//
//	calibDC->setOutput();
//	
//	calibDC->fillHistogram();
//	
//	calibDC->saveRootfile();
	
	return 0;
}
