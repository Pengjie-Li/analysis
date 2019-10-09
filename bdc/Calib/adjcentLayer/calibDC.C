#include "header.h"
#include "CalibDC.h"
int main(int argc, char *argv[])
{
	int runStart=-1;
	int runStop=-1;
	if(argc==2) {
		runStart=atoi(argv[1]);
		runStop=runStart;
		
	} else if(argc==3) {
		runStart=atoi(argv[1]);
		runStop=atoi(argv[2]);
	} else {
		cout<<" USAGE: ./calibDC  runNumberber"<<endl;
		cout<<" USAGE: ./calibDC  runStart runStop"<<endl;
	}
	cout<<"Converting calib tdc spectrum from run"<<runStart<<" to "<<runStop<<endl;

	CalibDC *calibDC =new CalibDC();

	calibDC->loadChain(runStart,runStop);
//
	calibDC->setOutput();
//	
	calibDC->fillHistogram();
//	
	calibDC->saveRootfile();
	
	return 0;
}
