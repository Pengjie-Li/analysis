#include "/Volumes/LPJ/S12/analysis/curve/DrawKine.h"
#include "/Volumes/LPJ/S12/analysis/curve/DrawQFS.h"
#include "/Volumes/LPJ/S12/analysis/curve/DrawDoubleRoot.h"
class DrawCurve{
	private:
			DrawKine *dk;
			DrawQFS *dq;
			DrawDoubleRoot *ddr;
	public:
		DrawCurve(){
			dk = new DrawKine();
			dq = new DrawQFS();
			ddr = new DrawDoubleRoot();
		}

		void drawA1A2PVBe10(){
			ddr->drawTheta1Theta2Be10();
		}
		void drawA1A2PVBe12(){
			ddr->drawTheta1Theta2Be12();
		}
		void drawA1A2PVBe14(){
			ddr->drawTheta1Theta2Be14();
		}

		void drawT1Theta1Be10(){
			dq->drawT1Theta1Be10();
			//ddr->drawT1Theta1Be10();
		}
		void drawT2Theta2Be10(){
			dq->drawT2Theta2Be10();
		}
		void drawTheta1Theta2Be10(){
			dq->drawTheta1Theta2Be10();
		}
		
		void drawT1T2Be10(){
			dq->drawT1T2Be10();
		}

		void drawT1Theta1Be12(){
			dq->drawT1Theta1Be12();
			//ddr->drawT1Theta1Be12();
		}
		void drawT2Theta2Be12(){
			dq->drawT2Theta2Be12();
		}
		void drawTheta1Theta2Be12(){
			dq->drawTheta1Theta2Be12();
			//ddr->drawTheta1Theta2Be12();
		}
		void drawT1T2Be12(){
			dq->drawT1T2Be12();
		}

		void drawT1Theta1Be14(){
			dq->drawT1Theta1Be14();
			//ddr->drawT1Theta1Be14();
		}
		void drawT2Theta2Be14(){
			dq->drawT2Theta2Be14();
		}
		void drawTheta1Theta2Be14(){
			dq->drawTheta1Theta2Be14();
			//ddr->drawTheta1Theta2Be14();
		}
		void drawT1T2Be14(){
			dq->drawT1T2Be14();
		}


		void drawPPEABe10(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/curve/protonCurve.root_Be10","READ");

				TGraph *gs = (TGraph *)gDirectory->Get("gs");
				TGraph *fex = (TGraph *)gDirectory->Get("fex");
				fCurve->Close();

				gs->SetLineColor(1);
				gs->SetLineWidth(1);
				//gs->SetLineStyle(3);

				fex->SetLineColor(1);
				fex->SetLineWidth(1);
				//fex->SetLineStyle(3);

				gs->Draw("l");
				fex->Draw("l");
		}
		void drawPPEABe12(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/curve/protonCurve.root_Be12","READ");
				TGraph *gs = (TGraph *)gDirectory->Get("gs");
				TGraph *fex = (TGraph *)gDirectory->Get("fex");
				TGraph *sn = (TGraph *)gDirectory->Get("sn");
				TGraph *mex = (TGraph *)gDirectory->Get("mex");
				fCurve->Close();

				gs->SetLineColor(1);
				//gs->SetLineStyle(2);
				gs->SetLineWidth(1);

				fex->SetLineColor(1);
				//fex->SetLineStyle(2);
				fex->SetLineWidth(1);


				gs->Draw("l");
				fex->Draw("l");
	
		}
	
		void drawPPEABe14(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/curve/protonCurve.root_Be14","READ");
				TGraph *gs = (TGraph *)gDirectory->Get("gs");
				TGraph *fex = (TGraph *)gDirectory->Get("fex");
				TGraph *sn = (TGraph *)gDirectory->Get("s2n");
				TGraph *mex = (TGraph *)gDirectory->Get("mex");
				fCurve->Close();

				gs->SetLineColor(1);
				//gs->SetLineStyle(2);
				gs->SetLineWidth(1);

				fex->SetLineColor(1);
				fex->SetLineStyle(2);
				fex->SetLineWidth(1);


				gs->Draw("l");
				fex->Draw("l");
	
		}
		void drawPRAngleBe10(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/curve/Be10Curve.root","READ");
				TGraph *ppBe10_gs = (TGraph *)gDirectory->Get("ppBe10_gs");
				ppBe10_gs->SetLineStyle(1);
				ppBe10_gs->Draw("lsame");
				TGraph *ppBe10_fex = (TGraph *)gDirectory->Get("ppBe10_fex");
				ppBe10_fex->SetLineStyle(2);
				ppBe10_fex->Draw("lsame");
				TGraph *ppBe10_sex = (TGraph *)gDirectory->Get("ppBe10_sex");
				ppBe10_sex->SetLineStyle(4);
				ppBe10_sex->Draw("lsame");
				fCurve->Close();
		}
		void drawPRAngleBe12(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/curve/Be12Curve.root","READ");
				TGraph *ppBe12_gs = (TGraph *)gDirectory->Get("ppBe12_gs");
				ppBe12_gs->SetLineStyle(1);
				ppBe12_gs->Draw("lsame");
				TGraph *ppBe12_fex = (TGraph *)gDirectory->Get("ppBe12_fex");
				ppBe12_fex->SetLineStyle(2);
				ppBe12_fex->Draw("lsame");
				TGraph *ppBe12_sn = (TGraph *)gDirectory->Get("ppBe12_sn");
				ppBe12_sn->SetLineStyle(4);
				ppBe12_sn->Draw("lsame");
				fCurve->Close();
		}

		void drawPRAngleBe14(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/curve/Be14Curve.root","READ");
				TGraph *ppBe14_gs = (TGraph *)gDirectory->Get("ppBe14_gs");
				ppBe14_gs->SetLineStyle(1);
				ppBe14_gs->Draw("lsame");
				//TGraph *ppBe14_fex = (TGraph *)gDirectory->Get("ppBe14_fex");
				//ppBe14_fex->SetLineStyle(2);
				//ppBe14_fex->Draw("lsame");

				TGraph *ppBe14_s2n = (TGraph *)gDirectory->Get("ppBe14_s2n");
				ppBe14_s2n->SetLineStyle(4);
				ppBe14_s2n->Draw("lsame");
				fCurve->Close();
		}

		void drawTheta1Theta3Be10T48(){
			dk->drawTheta1Theta3Be10T48();
		}

		void drawTheta1Theta2Be10T48(){
				dk->drawTheta1Theta2Be10T48();
		}
		void drawT1Theta3Be10Th65(){
				dk->drawT1Theta3Be10Th65();
		}
		void drawP3PrimeTheta3Be10Th65(){
				dk->drawP3PrimeTheta3Be10Th65();
		}
		void drawT1P3PrimeBe10Th65(){
				dk->drawT1P3PrimeBe10Th65();
		}
		void drawE1E2Be10Th65(){
				dk->drawE1E2Be10Th65();
		}
		void drawP3PrimeTheta3Be10T48(){
				dk->drawP3PrimeTheta3Be10T48();
		}
		void  drawTheta1P3PrimeBe10T48(){
				dk->drawTheta1P3PrimeBe10T48();
		}
		void drawT1T2Be12Th65(){
				dk->drawT1T2Be12Th65();
		}
		void drawT1P3PrimeBe12Th65(){
				dk->drawT1P3PrimeBe12Th65();
		}
		void drawP3PrimeTheta3Be12Th65(){
				dk->drawP3PrimeTheta3Be12Th65();
		}
		void drawT1Theta3Be12Th65(){
				dk->drawT1Theta3Be12Th65();
		}

		void drawT1T2Be12Th66(){
				dk->drawT1T2Be12Th66();
		}
		void drawT1P3PrimeBe12Th66(){
				dk->drawT1P3PrimeBe12Th66();
		}
		void drawP3PrimeTheta3Be12Th66(){
				dk->drawP3PrimeTheta3Be12Th66();
		}
		void drawT1Theta3Be12Th66(){
				dk->drawT1Theta3Be12Th66();
		}
		void drawTheta1Theta2Be12T41(){
				dk->drawTheta1Theta2Be12T41();
		}
		void drawTheta1P3PrimeBe12T41(){
			dk->drawTheta1P3PrimeBe12T41();
		}
		void drawP3PrimeTheta3Be12T41(){
			dk->drawP3PrimeTheta3Be12T41();
		}
		void drawTheta1Theta3Be12T41(){
			dk->drawTheta1Theta3Be12T41();
		}
		void drawT1Be10Th65(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/theory/theory.root_v1","READ");

				TGraph *t1Tdx = (TGraph *)gDirectory->Get("T1Tdx");
				fCurve->Close();
				t1Tdx->Draw("psame");
		}
		void drawP3BBe10Th65(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/theory/theory.root_v1","READ");

				TGraph *prTdx = (TGraph *)gDirectory->Get("PrTdx");
				fCurve->Close();
				prTdx->Draw("psame");
		}
		void drawTheta3Be10Th65(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/theory/theory.root_v1","READ");

				TGraph *thbTdx = (TGraph *)gDirectory->Get("Theta3Tdx");
				fCurve->Close();
				thbTdx->Draw("psame");
		}
		void drawTwoBodyA1A1CM(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/curve/TwoBody/Be10/twoBody.root","READ");
				TGraph *gr = (TGraph *)fCurve->Get("A1A1CM");
				fCurve->Close();
				gr->Draw("lsame");
		}
		void drawTwoBodyA2A2CM(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/curve/TwoBody/Be10/twoBody.root","READ");
				TGraph *gr = (TGraph *)fCurve->Get("A2A2CM");
				fCurve->Close();
				gr->Draw("lsame");
		}
		void drawTwoBodyA1A2Lab(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/curve/TwoBody/Be10/twoBody.root","READ");
				TGraph *gr = (TGraph *)fCurve->Get("A1A2Lab");
				fCurve->Close();
				gr->Draw("lsame");
		}

		void drawT1T2NormalKinBe10(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/kinetics/output/normalKinBe10.root","READ");
				TGraph *gr = (TGraph *)fCurve->Get("T1T2");
				gr->SetLineColor(1);
				gr->SetLineWidth(2);
				fCurve->Close();
				gr->Draw("csame");

		}
		void drawT1T2NormalKinBe12(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/kinetics/output/normalKinBe12.root","READ");
				TGraph *gr = (TGraph *)fCurve->Get("T1T2");
				gr->SetLineColor(1);
				gr->SetLineWidth(2);
				fCurve->Close();
				gr->Draw("csame");

		}
		void drawT1T2NormalKinBe14(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/kinetics/output/normalKinBe14.root","READ");
				TGraph *gr = (TGraph *)fCurve->Get("T1T2");
				gr->SetLineColor(1);
				gr->SetLineWidth(2);
				fCurve->Close();
				gr->Draw("csame");

		}
		void drawT1Theta1NormalKinBe10(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/kinetics/output/normalKinBe10.root","READ");
				TGraph *gr = (TGraph *)fCurve->Get("T1Theta1");
				gr->SetLineColor(1);
				gr->SetLineStyle(2);
				fCurve->Close();
				gr->Draw("lsame");

		}
		void drawT2Theta2NormalKinBe10(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/kinetics/output/normalKinBe10.root","READ");
				TGraph *gr = (TGraph *)fCurve->Get("T2Theta2");
				gr->SetLineColor(1);
				gr->SetLineStyle(2);
				fCurve->Close();
				gr->Draw("lsame");
		}
		void drawTheta1Theta2NormalKinBe10(){
				TFile *fCurve = new TFile("/Volumes/LPJ/S12/analysis/kinetics/output/normalKinBe10.root","READ");
				TGraph *gr = (TGraph *)fCurve->Get("Theta1Theta2");
				gr->SetLineColor(1);
				gr->SetLineStyle(2);
				fCurve->Close();
				gr->Draw("lsame");
		}

		~DrawCurve(){}
};


