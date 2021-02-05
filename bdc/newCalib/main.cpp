#include "header.h"
#include "ppBe.h"
using namespace std;

int main(int argc, char** argv){

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

        PPBe *calibDC =new PPBe();

	calibDC->loadChain(runStart,runStop);
	//calibDC->loadInputFiles();
	calibDC->createOutput();
	calibDC->eventLoop();
	calibDC->saveOutput();
	return 0;
}
