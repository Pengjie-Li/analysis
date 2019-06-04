#include "header.h"
class ConvertPLA{
private:
	int runNumber;
	Long64_t maxEventNumber;
public:
	ConvertPLA(int rn,Long64_t men){
		runNumber = rn;
		maxEventNumber = men;
	}
	void load(){
	}
	void openRawData(){
	}
	void createOutput(){
	}
	void analysis(){
	}
	void saveOutputFile(){
	}
};

int main(int argc, char *argv[]){
	int runNumber=-1;
	Long64_t maxEventNumber = 10000000;
	//      Long64_t maxEventNumber = 30;
	//cout<<maxEventNumber<<endl;
	if(argc==2) runNumber=atoi(argv[1]);
	else if(argc==3) { runNumber=atoi(argv[1]); maxEventNumber=atoi(argv[2]);}
	else {
		cout<<" USAGE: ./ConvertPLA  runNumberber"<<endl;
		cout<<" USAGE: ./ConvertPLA  runnumber maxevtnumber"<<endl;
	}

	ConvertPLA *convertPLA =new ConvertPLA(runNumber, maxEventNumber);

	convertPLA->load();
	convertPLA->openRawData();
	convertPLA->createOutput();
	convertPLA->analysis();
	convertPLA->saveOutputFile();

	return 0;
}
