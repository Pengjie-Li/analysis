#include "TTree.h" 
#include <vector> 
#ifdef __MAKECINT__ 
#pragma link C++ class 
std::vector < std::vector<float> >+; 
#endif 
void vv(){
	TTree *T = new TTree("T","test");
	vector < vector<float> > test; 
	T->Branch("test",&test);
	T->Print();
} 
