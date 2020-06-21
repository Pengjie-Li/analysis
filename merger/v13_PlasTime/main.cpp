#include "header.h"
#include "Merger.h"

int main(int argc, char** argv){
	int runNumber = -1;
	int maxEventNumber = 10000000;

	if(argc == 2) runNumber = atoi(argv[1]);
	else if(argc == 3) { runNumber = atoi(argv[1]); maxEventNumber = atoi(argv[2]);}
	else cout<<" Usage: ./Merger runNumber maxEventNumber"<<endl;

	Merger *merger = new Merger(runNumber,maxEventNumber);
	//cout<<"Now:runNumber="<<runNumber<<endl;
	if(merger->isFilesExist()){
		merger->loadInputFiles();
		merger->checkTotalEventNumber();
		merger->setBranch();
		merger->createOutput();
		merger->eventLoop();
		merger->saveOutput();
	}
	return 0;
}
