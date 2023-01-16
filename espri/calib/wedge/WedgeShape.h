class WedgeShape{
		private:
				double h1;
				double h2;
				double l1;
				double l2;
				double posL;
				double totalL;
		public:
				WedgeShape(){
					//h1 = 2;
					//h2 = 29;
					//l1 = 240;
					//l1 = 236.5;
					posL = 37.5;	
					//posL = 55;	
					totalL = 455;
					//totalL = 450;
				}
				~WedgeShape(){}
				void setThick(double h,double hh,double l){
					h1 = h;
					h2 = hh;
					l1 = l;
					l2 = sqrt(l1*l1+(h2-h1)*(h2-h1));
					cout<<"Wedge Shape:"<<h1<<" mm   "<<h2<<" mm    "<<l1<<" mm    "<<l2<<endl;
				}
				double getThickness(double x){
					if(x>0&&x<posL) return 0;
					if(x<totalL&&x>(posL+l1)) return 0;
					double l = posL+l1 - x;
					return h1+(h2-h1)/l1*l;
				}
};
