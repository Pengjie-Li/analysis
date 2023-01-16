// Each dssd have 32+32 strips, so there will be kf0-31, kb0-31,bf0-31,bb0-31
// choose jth strip as reference, then it's k=1;b=0;
// find intersection between ith strip and jth strip and align them by least square method
//********* Least square Method***************//
// 1. keep reading data until condition satisfied
// 2. least square method and condition
// 3. get the final k and b





double sqr(double x){ return x*x; }
void addnewpoint(int n,double x,double y,double &sumx,double &sumx2,double &sumxy,double &sumy,double &sumy2);
void test()
{
	const int n=6;
	double a[6]={1,2,3,4,5,6};
	double b[6]={11,12,13,14,15,16};

	double x[6]= {1, 2, 4,  5,  10, 20};
	double y[6]= {4, 6, 12, 15, 34, 68};

	double   sumx = 0.0;                      /* sum of x     */
	double   sumx2 = 0.0;                     /* sum of x**2  */
	double   sumxy = 0.0;                     /* sum of x * y */
	double   sumy = 0.0;                      /* sum of y     */
	double   sumy2 = 0.0;                     /* sum of y**2  */

	for(int i=0;i<n;i++)
	{

		Least_square(i,x[i],y[i],sumx,sumx2,sumxy,sumy,sumy2);
		//	addnewpoint(i,x[i],y[i],sumx,sumx2,sumxy,sumy,sumy2);	
		//	//addnewpoint(i,a[i],b[i],sumx,sumx2,sumxy,sumy,sumy2);	
		//	double denom = ((i+1) * sumx2 - sqr(sumx));
		//	if( denom==0)  continue; // singular matrix
		//	/* compute correlation coeff */
		//	double r = (sumxy - sumx * sumy / (i+1)) / sqrt((sumx2 - sqr(sumx)/(i+1)) * (sumy2 - sqr(sumy)/(i+1)));

		//	if(abs(r-1)<0.1) cout<<"r="<<r<<" Now in "<<i<<"th data points, it reach the standard"<<endl;

	}


}

void addnewpoint(int n,double x,double y,double &sumx,double &sumx2,double &sumxy,double &sumy,double &sumy2)
{
	sumx  += x;       
	sumx2 += sqr(x);  
	sumxy += x * y;
	sumy  += y;      
	sumy2 += sqr(y); 
}

void Load(){ 
	gROOT->Reset();
	//gStyle->SetStatStyle(0);
	gStyle->SetOptStat(1111111);

	int dDSSD=1;
	int dCsI=1;
	int dMap=1;
	int dMapCsI=1;
	TString inputname="./rootfiles/run0596_Beamv8.root";
	TFile *f = new TFile(inputname,"UPDATE");
	TTree *tree_BEAM=(TTree*)f->Get("tree_BEAM");



	//Declaration of leaves types
	vector<double>  *SiLF_rawADC;
	vector<double>  *SiLB_rawADC;
	vector<double>  *SiRF_rawADC;
	vector<double>  *SiRB_rawADC;
	Double_t        CsILL_rawADC;
	Double_t        CsILRT_rawADC;
	Double_t        CsILRB_rawADC;
	Double_t        CsIRLT_rawADC;
	Double_t        CsIRLB_rawADC;
	Double_t        CsIRRT_rawADC;
	Double_t        CsIRRB_rawADC;

	tree_BEAM->SetBranchAddress("SiLF_rawADC",&SiLF_rawADC);
	tree_BEAM->SetBranchAddress("SiLB_rawADC",&SiLB_rawADC);
	tree_BEAM->SetBranchAddress("SiRF_rawADC",&SiRF_rawADC);
	tree_BEAM->SetBranchAddress("SiRB_rawADC",&SiRB_rawADC);
	tree_BEAM->SetBranchAddress("CsILL_rawADC",&CsILL_rawADC);
	tree_BEAM->SetBranchAddress("CsILRT_rawADC",&CsILRT_rawADC);
	tree_BEAM->SetBranchAddress("CsILRB_rawADC",&CsILRB_rawADC);
	tree_BEAM->SetBranchAddress("CsIRLT_rawADC",&CsIRLT_rawADC);
	tree_BEAM->SetBranchAddress("CsIRLB_rawADC",&CsIRLB_rawADC);
	tree_BEAM->SetBranchAddress("CsIRRT_rawADC",&CsIRRT_rawADC);
	tree_BEAM->SetBranchAddress("CsIRRB_rawADC",&CsIRRB_rawADC);

	Long64_t nentries = tree_BEAM->GetEntries();
	double   sumx = 0.0;                      /* sum of x     */
	double   sumx2 = 0.0;                     /* sum of x**2  */
	double   sumxy = 0.0;                     /* sum of x * y */
	double   sumy = 0.0;                      /* sum of y     */
	double   sumy2 = 0.0;                     /* sum of y**2  */
	int      n=0;
	double k=0;
	double b=0;


	int converge=0;
	nentries=100000;
	Long64_t nbytes = 0;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		nbytes += tree_BEAM->GetEntry(ientry);
		converge=0;

		//Print(SiLF_rawADC);
		//Print(SiLB_rawADC);
		if((*SiLF_rawADC)[15]>1000&&TMath::Abs((*SiLF_rawADC)[15]-(*SiLB_rawADC)[16])<300)
		{
			converge=Least_square(n,(*SiLF_rawADC)[15],(*SiLB_rawADC)[16],sumx,sumx2,sumxy,sumy,sumy2,k,b);

			n++;
		}
		//if(ientry>1000&&converge==1) break; // satisfy condition (r-1)<1E-3
		if(ientry%10000==0) cout<<ientry<<endl;

	}

	cout<<" converge="<<converge<<endl;
	//if(converge==0) exit(0);

	TH2F *hDSSD[2];
	for(int i=0;i<2;i++)
	{
		TString name;
		switch(i)
		{
			case 0: {name="SiLF"; break;}
			case 1: {name="SiLB"; break;}
			default: exit(0);
		}

		TString hname="h"+name;
		hDSSD[i]=new TH2F(hname,name,32,-0.5,31.5,4100,0,4100);
		hDSSD[i]->SetContour(5);
	}
	TH1F *hCheck=new TH1F("hCheck","hCheck",8200,-4100,4100);
	TH2F *hCorr=new TH2F("hCorr","hCorr",4200,-100,4100,4200,-100,4100);

	nentries = tree_BEAM->GetEntries();
	//nentries = 1000000;
	for (Long64_t ientry=0; ientry<nentries;ientry++) {
		tree_BEAM->GetEntry(ientry);
                
		if((*SiLF_rawADC)[15]>500&&TMath::Abs((*SiLF_rawADC)[15]-(*SiLB_rawADC)[16])<300)
                hCheck->Fill((*SiLF_rawADC)[15]*k+b-(*SiLB_rawADC)[16]);
		hDSSD[0]->Fill(15,k*(*SiLF_rawADC)[15]+b);
		hDSSD[1]->Fill(16,(*SiLF_rawADC)[16]);

		hCorr->Fill((*SiLF_rawADC)[15]*k+b,(*SiLB_rawADC)[16]);
		if(ientry%10000==0) cout<<ientry<<endl;

	}

	TCanvas *cDSSD=new TCanvas("cDSSD","cDSSD",1600,800);
	cDSSD->Divide(2,1);
	cDSSD->cd(1); hDSSD[0]->Draw("colz");
	cDSSD->cd(2); hDSSD[1]->Draw("colz");
	cDSSD->cd(0);

	TCanvas *cCheck=new TCanvas("cCheck","cCheck",1600,800);
	cCheck->cd();
	hCheck->Draw();

	TCanvas *cCorr=new TCanvas("cCorr","cCorr",1600,800);
	cCorr->cd();
	hCorr->Draw("colz");

}

int Least_square(int i,double x,double y,double &sumx,double &sumx2,double &sumxy,double &sumy,double &sumy2,double &k,double &b)
{
	addnewpoint(i,x,y,sumx,sumx2,sumxy,sumy,sumy2);	
	//addnewpoint(i,a[i],b[i],sumx,sumx2,sumxy,sumy,sumy2);	
	double denom = ((i+1) * sumx2 - sqr(sumx));
	//if( denom==0)  continue; // singular matrix
	/* compute correlation coeff */
	double r = (sumxy - sumx * sumy / (i+1)) / sqrt((sumx2 - sqr(sumx)/(i+1)) * (sumy2 - sqr(sumy)/(i+1)));

	//if(TMath::Abs(r-1)<0.1) cout<<TMath::Abs(r-1)<<" r="<<r<<" Now in "<<i<<"th data points, it reach the standard"<<endl;

	if(TMath::Abs(r-1)<1E-3) 
	{
		k = ((i+1) * sumxy  -  sumx * sumy) / denom;
		b = (sumy * sumx2  -  sumx * sumxy) / denom;

		cout<<TMath::Abs(r-1)<<" r="<<r<<" Now in "<<i<<"th data points, it reach the standard"<<endl;
		return 1;

	}

	return 0;
}
void Print(vector<double>  *ADC)
{

for(int i=0;i<32;i++) cout<<"\t"<<i;
cout<<endl;
for(int i=0;i<32;i++) cout<<"\t"<<(*ADC)[i];

}
