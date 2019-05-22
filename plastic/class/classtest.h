#include "global.h"
#include "TObject.h"
class TestClass : public TObject {
	public:

	TestClass();
	double x,y,z;
	virtual ~TestClass();
        virtual void Show();
	ClassDef(TestClass,1)

};
