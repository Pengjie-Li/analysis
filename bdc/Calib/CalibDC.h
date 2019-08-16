#include "DCRaw.h"
class CalibDC{
	private:
		TChain *tree;

		// Head Variables

		DCRaw *bdc1RawData;
		DCRaw *bdc2RawData;
		DCRaw *fdc0RawData;
		DCRaw *fdc2RawData;



	public:
		CalibDC(){
			tree = new TChain("tree");
			bdc1RawData = new BDC1Raw();
			bdc2RawData = new BDC2Raw();
			fdc0RawData = new FDC0Raw();
			fdc2RawData = new FDC2Raw();
		}
		~CalibDC(){}
		void loadChain(int runStart,int runStop){
			for (int i = runStart; i < runStop; ++i) {

				tree->Add(Form("mergerRootfiles/run0%d_analysed.root_1",i));
			}
			tree->Print();

		}
		void loadData(){
			//readBranch();
		}
		

		void setOutput(){
		}
		void fillHistogram(){
		}
		void saveRootfile(){
		}
};
