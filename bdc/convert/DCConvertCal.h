class DCConvertCal{
	private:
	public:
		DCConvertCal(){}
		~DCConvertCal(){}
		void setBranch(TTree *tree){
		}
		void calibrate(DCReadRaw *dcReadRaw){
		}
};
class BDC1ConvertCal:public DCConvertCal{
	private:
	public:
		BDC1ConvertCal(){}
		~BDC1ConvertCal(){}
};
class BDC2ConvertCal:public DCConvertCal{
	private:
	public:
		BDC2ConvertCal(){}
		~BDC2ConvertCal(){}
};
class FDC0ConvertCal:public DCConvertCal{
	private:
	public:
		FDC0ConvertCal(){}
		~FDC0ConvertCal(){}
};
