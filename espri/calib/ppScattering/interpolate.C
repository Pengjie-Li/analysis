#include <iostream>
#include <fstream>
using namespace std;

int main(){
	double x1,y1;
	double x2,y2;
	double x,y;
	cout<<"Please input first Pair:"<<endl;
	cin>>x1>>y1;
	cout<<"Please input second Pair:"<<endl;
	cin>>x2>>y2;
	cout<<"Data:("<<x1<<","<<y1<<") ("<<x2<<","<<y2<<")"<<endl;
	cout<<"Desired X value:"<<endl;
	cin>>x;
	y = y1+(y2-y1)/(x2-x1)*(x-x1);
	cout<<"Coresponding Y= "<<y<<endl;
	return 0;
}
