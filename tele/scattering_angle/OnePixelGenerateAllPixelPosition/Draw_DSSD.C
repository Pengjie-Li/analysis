/** 
 * 1. read file pixel 3D position
 * 2. draw poly3D marker
 */

#include <math.h>
#include <fstream>
#include <TFile.h>
#include <TH3D.h>
#include <TTree.h>
#include <TVector3.h>
#include <Math/Functor.h>
#include <Math/Vector3D.h>
#include <TRandom2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TF2.h>
#include <TH2D.h>
#include <TView.h>
#include <TH1.h>
#include <Math/Functor.h>
#include <TPolyLine3D.h>
#include <TPolyMarker3D.h>
#include <Math/Vector3D.h>
#include <Fit/Fitter.h>

class DrawDSSD{
	public:
		double Table[2048][6];
		DrawDSSD(){
			readFile();
			draw2DPoint();
			draw3DPoint();
		}
		void readFile(){
			ifstream inLeft;
			ifstream inRight;
			inLeft.open("LeftDSSDPixelPosition.txt");
			inRight.open("RightDSSDPixelPosition.txt");

			int line=0;

			int side;
			int fid;
			int bid;
			double  x;
			double  y;
			double z;
			while (1)
			{
				inLeft >>fid>>bid>>x>>y>>z;
				if (!inLeft.good()) break;
				Table[line][0]=0;
				Table[line][1]=fid;
				Table[line][2]=bid;
				Table[line][3]=x;
				Table[line][4]=y;
				Table[line][5]=z;
				line++;
			}
			inLeft.close();
			while (1)
			{
				inRight >>fid>>bid>>x>>y>>z;
				cout<<x<<" "<<y<<" "<<z<<endl;
				
				if (!inRight.good()) break;
				Table[line][0]=1;
				Table[line][1]=fid;
				Table[line][2]=bid;
				Table[line][3]=x;
				Table[line][4]=y;
				Table[line][5]=z;

				line++;
			}
			inRight.close();

		}
		void draw2DPoint(){
		}
		void draw3DPoint(){

			const static double zMin=-100;
			const static double zMax=100;

			const static double yMin=-100;
			const static double yMax=100;

			const static double xMin=-7000;
			const static double xMax=-3000;




			TH3D *hdummy = new TH3D("hdummy", "", 2, xMin, xMax, 2, yMin, yMax, 2, zMin, zMax);
			hdummy->GetXaxis()->SetRangeUser(xMin, xMax);
			hdummy->GetYaxis()->SetRangeUser(yMin, yMax);
			hdummy->GetZaxis()->SetRangeUser(zMin, zMax);
			hdummy->SetLineColor(kWhite);
			hdummy->Draw();




			TPolyMarker3D *p=new TPolyMarker3D[2048];
			for(int i=0;i<2048;i++){

				p->SetPoint(i,Table[i][5],Table[i][3],Table[i][4]);
			}

			p->SetMarkerSize(1);
			p->SetMarkerColor(4);
			//p->SetMarkerStyle(8);
			p->Draw();


		}
};
int Draw_DSSD(){

	new DrawDSSD();
	return 1;
}
int main(){
	Draw_DSSD();
	return 1;
}
