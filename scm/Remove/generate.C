
void generate()
{

	double k[4][32]={0};
	double b[4][32]={0};

	double ek[4][32]={0};
	double eb[4][32]={0};

	Load(0,k,b,ek,eb);

	double newk[4][32]={0};
	double newb[4][32]={0};

	double newek[4][32]={0};
	double neweb[4][32]={0};

	for(int j=0;j<32;j++)
	{

		newk[0][j]=k[0][j];
		newb[0][j]=b[0][j];
		newek[0][j]=ek[0][j];
		neweb[0][j]=eb[0][j];


		newk[1][j]=k[0][15]*k[1][j];
		newb[1][j]=k[0][15]*b[1][j]+b[0][15];

		newek[1][j]=k[0][15]*ek[1][j];
		neweb[1][j]=k[0][15]*eb[1][j]+eb[0][15];

		newk[2][j]=k[2][j];
		newb[2][j]=b[2][j];
		newek[2][j]=ek[2][j];
		neweb[2][j]=eb[2][j];


		newk[3][j]=k[2][15]*k[3][j];
		newb[3][j]=k[2][15]*b[3][j]+b[2][15];

		newek[3][j]=k[2][15]*ek[3][j];
		neweb[3][j]=k[2][15]*eb[3][j]+eb[2][15];

	}

	TString outputname="DSSD_Fit_Whole_v1.txt";
	cout<<outputname<<endl;
	ofstream fout(outputname,ios_base::out);

	for(int i=0;i<4;i++)
		for(int j=0;j<32;j++)
		{
			fout <<"\t"<<i << "\t" << j<< "\t" << newk[i][j]<<"\t"<<newb[i][j]<< "\t" << newek[i][j]<<"\t"<<neweb[i][j]<<endl;
		}
	fout.close();




}

void Load(int lr,double k[4][32],double b[4][32],double ek[4][32],double eb[4][32])
{
	ifstream in;
	TString par_name;
	//par_name="/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/scm/Remove/DSSD_Fit.txt";
	par_name="/media/Projects/RIKEN_Cluster_2018/lipj/exp_201805/anaroot/users/analysis/macros/scm/Remove/DSSD_Fit_v1.txt";
	in.open(par_name);

	int side;
	int strip;
	double  k0;
	double  b0;
	double ek0;
	double eb0;
	while (1)
	{
		in >>side>>strip>>k0>>b0>>ek0>>eb0;
		//cout<<side<< "  "<<strip<<endl;
		if (!in.good()) break;


		k[side][strip]=k0;
		ek[side][strip]=ek0;

		b[side][strip]=b0;
		eb[side][strip]=eb0;

	}
}

