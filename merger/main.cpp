#include "header.h"
//#include "constant.h"
#include "Merger.h"

int main(int argc, char** argv){
	int runNumber = -1;

	if(argc == 2) runNumber = atoi(argv[1]);
	else cout<<" Usage: ./Merger runNumber"<<endl;

	Merger *merger = new Merger(runNumber);
	//cout<<"Now:runNumber="<<runNumber<<endl;
	if(merger->isFilesExist()){
		merger->loadInputFiles();
		merger->checkTotalEventNumber();
		merger->setBranch();
		merger->addFriend();
		merger->createOutput();
		merger->eventLoop();
		merger->saveOutput();
	}
	return 0;
}
