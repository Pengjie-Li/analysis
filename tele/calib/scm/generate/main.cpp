#include "header.h"
#include "scmGenerator.h"
using namespace std;

int main(int argc, char** argv){
	int runNumber = -1;
	int maxEventNumber = 10000000;

	if(argc == 2) runNumber = atoi(argv[1]);
	else if(argc == 3) { runNumber = atoi(argv[1]); maxEventNumber = atoi(argv[2]);}
	else cout<<" Usage: ./Merger runNumber maxEventNumber"<<endl;

	ScmGenerator *scmGenerator = new ScmGenerator(runNumber,maxEventNumber);
	cout<<"Now:runNumber="<<runNumber<<endl;
	if(scmGenerator->isFilesExist()){
		scmGenerator->loadInputFiles();
		scmGenerator->createOutput();
		scmGenerator->eventLoop();
		scmGenerator->saveOutput();
	}
	return 0;
}
