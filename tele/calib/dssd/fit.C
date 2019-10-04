void fitL(){
	double energy[3] = {0,6.9906,9.6561};
	double scm[3] = {92.27,1194.73,1580.92};
	TGraph *gr = new TGraph(3,scm,energy);
	gr->Draw("apl*");
	gr->Fit("pol1");
}
void fitR(){
	double energy[3] = {0,6.9722,9.6306};
	double scm[3] = {84.81,1128.05,1483.95};
	TGraph *gr = new TGraph(3,scm,energy);
	gr->Draw("apl*");
	gr->Fit("pol1");
}
void fit()
{
	fitL();
	//fitR();
}
