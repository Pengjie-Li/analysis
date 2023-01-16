class Convert{
	private:
	public:
		int runNumber;
		TString detector;
		TEnv *env;

		/**** Input ******/
		TFile *inputFile;
		TString inputName;
		TTree *inputTree;
		TString treeName;


		Convert(){}
		Convert(int runNumber):runNumber(runNumber){
			env = new TEnv("configMerger.prm");
		}

		TTree* getTreePointer(){
			return inputTree;
		}
		void loadInputFiles(){
			inputFile = new TFile(inputName,"READ");
			inputTree = (TTree *)inputFile->Get(treeName);
			//inputTree->Print();
		}

		bool isFileExists(TString detector){
			inputName = getFileName(detector);
			bool isFile = gSystem->AccessPathName(inputName);
			if(!isFile){
				cout<<detector<<" Confirmed::"<<getFileName(detector)<<endl;
			}else{
				inputName = getOldFileName(detector);
				isFile = gSystem->AccessPathName(inputName);
				//cout<<getOldFileName(detector);
				if(!isFile) cout<<detector<<" Old File Confirmed::"<<getOldFileName(detector)<<endl;
				else cout<<detector<<" Failed:: New Path and Old Path not found"<<endl;
			}
			//cout<<getFileName(detector)<<endl;
			return !isFile;
		}
		TString getFileName(TString detector){
			TString inputPath;
			TString runPrefix;
			TString runSuffix;
			char ch = detector[0];
			//cout<<ch<<endl;
			switch(ch){
				case 'M':
					inputPath = env->GetValue("MAINInputPath","MAIN Path Error!");
					runPrefix = env->GetValue("MAINRunPrefix","MAIN Prefix Error!");
					runSuffix = env->GetValue("MAINRunSuffix","MAIN Suffix Error!");
	
				case 'P':
					inputPath = env->GetValue("PLAInputPath","PLA Path Error!");
					runPrefix = env->GetValue("PLARunPrefix","PLA Prefix Error!");
					runSuffix = env->GetValue("PLARunSuffix","PLA Suffix Error!");
					break;
				case 'B':
					inputPath = env->GetValue("BDCInputPath","BDC Path Error!");
					runPrefix = env->GetValue("BDCRunPrefix","BDC Prefix Error!");
					runSuffix = env->GetValue("BDCRunSuffix","BDC Suffix Error!");
					break;

				case 'F':
					inputPath = env->GetValue("FDCInputPath","FDC Path Error!");
					runPrefix = env->GetValue("FDCRunPrefix","FDC Prefix Error!");
					runSuffix = env->GetValue("FDCRunSuffix","FDC Suffix Error!");
					break;

				case 'T':
					inputPath = env->GetValue("TELEInputPath","TELE Path Error!");
					runPrefix = env->GetValue("TELERunPrefix","TELE Prefix Error!");
					runSuffix = env->GetValue("TELERunSuffix","TELE Suffix Error!");
					break;
				case 'H':
					inputPath = env->GetValue("HODInputPath","HOD Path Error!");
					runPrefix = env->GetValue("HODRunPrefix","HOD Prefix Error!");
					runSuffix = env->GetValue("HODRunSuffix","HOD Suffix Error!");
					break;


				default: cout<<"Convert.h Error: Didn't find Detector name!"<<endl;
			}
			TString runString = Form("%04d",runNumber);
			return inputPath+runPrefix+runString+runSuffix;
		}

		TString getOldFileName(TString detector){
			TString inputPathPrefix = "/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/rootfiles/";
			TString runPath = Form("run%04d/",runNumber);
			TString runPrefix = Form("run%04d",runNumber);
			TString runSuffix;
			char ch = detector[0];

			switch(ch){
				case 'M':
					runSuffix = env->GetValue("MAINRunSuffix","MAIN Suffix Error!");
					break;
	
				case 'P':
					runSuffix = env->GetValue("PLARunSuffix","PLA Suffix Error!");
					break;
				case 'B':
					runSuffix = env->GetValue("BDCRunSuffix","BDC Suffix Error!");
					break;

				case 'F':
					runSuffix = env->GetValue("FDCRunSuffix","FDC Suffix Error!");
					break;

				case 'T':
					runSuffix = env->GetValue("TELERunSuffix","TELE Suffix Error!");
					break;
				case 'H':
					runSuffix = env->GetValue("HODRunSuffix","HOD Suffix Error!");
					break;


				default: cout<<"Error: Didn't find Detector name!"<<endl;

			}
			return inputPathPrefix+runPath+runPrefix+runSuffix;
		}


};


