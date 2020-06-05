#include "header.h"
#include "ppBe.h"
using namespace std;

int main(int argc, char** argv){
	int runNumber = -1;
	int maxEventNumber = 10000000;

	if(argc == 2) runNumber = atoi(argv[1]);
	else if(argc == 3) { runNumber = atoi(argv[1]); maxEventNumber = atoi(argv[2]);}
	else cout<<" Usage: ./Merger runNumber maxEventNumber"<<endl;

	PPBe *ppBe = new PPBe(runNumber,maxEventNumber);
	//cout<<"Now:runNumber="<<runNumber<<endl;
	if(ppBe->isFilesExist()){
		ppBe->loadInputFiles();
		ppBe->createOutput();
		ppBe->eventLoop();
		//ppBe->saveOutput();
	}
	return 0;
}
