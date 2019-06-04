#include "classtest.h"   

ClassImp(TestClass)

TestClass::~TestClass()
{


}
TestClass::TestClass()   
{
}
void TestClass::Show()
{

	x = 1.0;
	y = 2.0;
	z = 3.0;
        cout<< "xx="<<x<<" yy="<<y<<"  zz="<<z<<endl;

}
