class MergeESPRI:public Convert{
	private:
		int runNumber;
	public:

		MergeESPRI(int run){
			env = new TEnv("configMerger.prm");
			detector = "ESPRI";
			treeName = "CalTreeESPRI";
			runNumber = run;
		}
		void init(){
		}
		void setBranch(){
		}
		void setOutputBranch(TTree *tree){
		}
		~MergeESPRI(){}
};
