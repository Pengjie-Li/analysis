class DrawTree{
	private:
		TChain *tree;
		int markerStyle;
		TString gate;

		TString varX;
		TString varY;
		TString varH;

		int binX,binY;
		double minX,minY,maxX,maxY;
		int binH;
		double minH,maxH;

	public:
		DrawTree(){
			tree = new TChain("tree");
			markerStyle = 1;
		}
		void addFile(TString fileName){
			tree->Add(fileName);
		}
		void setMarkerStyle(int style){
			markerStyle = style;
		}
		void loadCut(){

                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar27He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar28He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar29He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar30He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar31He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar32He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar33He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar34He6.C");

			gROOT->ProcessLine(".x rootfiles/cutBe10Bar9He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar10He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar11He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar12He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar13He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar14He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar15He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar16He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar17He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar18He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar19He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar20He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar21He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar22He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe10Bar23He4.C");


                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar28He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar29He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar30He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar31He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar32He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar33He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar34He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar35He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar36He8.C");


			gROOT->ProcessLine(".x rootfiles/cutBe12Bar9He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar10He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar11He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar12He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar13He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar14He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar15He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar16He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar17He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar18He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar19He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar20He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar21He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar22He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar23He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe12Bar24He6.C");



                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar3He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar4He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar5He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar6He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar7He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar8He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar9He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar10He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar11He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar12He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar13He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar14He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar15He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar16He4.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar17He4.C");

                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar11He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar12He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar13He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar14He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar15He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar16He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar17He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar18He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar19He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar20He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar21He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar22He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar23He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar24He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar26He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar27He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar28He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar29He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar30He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar31He6.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar32He6.C");

                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar33He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar34He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar35He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar36He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar37He8.C");
                        gROOT->ProcessLine(".x rootfiles/cutBe14Bar38He8.C");

		}
		void setAlias(){

			tree->SetAlias("SOL","299.792458*1");
			tree->SetAlias("AMU","931.49410242*1");

			tree->SetAlias("MassBe10","10.0113404*1");
			tree->SetAlias("MassBe12","12.02472781*1");
			tree->SetAlias("MassBe14","14.04069708*1");

			tree->SetAlias("MassH","1.007276452*1");
			tree->SetAlias("MassHe4","4.001506105*1");
			tree->SetAlias("MassHe6","6.017788744*1");
			tree->SetAlias("MassHe8","8.032837245*1");
			tree->SetAlias("MassHe10","10.050167077*1");
			//tree->SetAlias("MassHe10","10.05171959*1");

			tree->SetAlias("MassBe","MassBe10*1");
			tree->SetAlias("residueRestMass","MassHe6*AMU");

			//tree->SetAlias("MassBe","MassBe12*1");
			//tree->SetAlias("residueRestMass","MassHe8*AMU");

			//tree->SetAlias("MassBe","MassBe14*1");
			//tree->SetAlias("residueRestMass","MassHe10*AMU");

			tree->SetAlias("beamMass","MassBe*AMU");
			tree->SetAlias("targetMass","MassH*AMU");
			tree->SetAlias("protonMass","MassH*AMU");
			tree->SetAlias("alphaMass","MassHe4*AMU");
			tree->SetAlias("alphaAngle","teleAngle");
			tree->SetAlias("protonAngle","espriAngle");

			// 	
			tree->SetAlias("beamEk","beamEnergy*MassBe");
			tree->SetAlias("beamMomentum","sqrt(beamEk*beamEk+2*beamEk*beamMass)");

			tree->SetAlias("xB","vBeam.X()");
			tree->SetAlias("yB","vBeam.Y()");
			tree->SetAlias("zB","vBeam.Z()");
			tree->SetAlias("xP","vESPRI.X()");
			tree->SetAlias("yP","vESPRI.Y()");
			tree->SetAlias("zP","vESPRI.Z()");
			tree->SetAlias("xA","vTele.X()");
			tree->SetAlias("yA","vTele.Y()");
			tree->SetAlias("zA","vTele.Z()");
			tree->SetAlias("xR","vFDC0.X()");
			tree->SetAlias("yR","vFDC0.Y()");
			tree->SetAlias("zR","vFDC0.Z()");

			TString planeOfBPA = "(xB*(yA*zP-yP*zA)+yB*(zA*xP-zP*xA)+zB*(xA*yP-xP*yA))";


	
			tree->SetAlias("A1","yP*zB-zP*yB");
			tree->SetAlias("B1","zP*xB-xP*zB");
			tree->SetAlias("C1","xP*yB-yP*xB");
                                                      
			tree->SetAlias("A2","yA*zB-zA*yB");
			tree->SetAlias("B2","zA*xB-xA*zB");
			tree->SetAlias("C2","xA*yB-yA*xB");
	
			tree->SetAlias("cosPhi12","(A1*A2+B1*B2+C1*C2)/(sqrt(A1*A1+B1*B1+C1*C1)*sqrt(A2*A2+B2*B2+C2*C2))");

			tree->SetAlias("cosTheta12","cos(theta1)*cos(theta2)+sin(theta1)*sin(theta2)*cosPhi12");

			tree->SetAlias("protonGamma","(protonEnergy/protonMass+1)");
			tree->SetAlias("protonBeta","sqrt(1-1/(protonGamma*protonGamma))");
			tree->SetAlias("protonVelocity","protonBeta*SOL");
			tree->SetAlias("protonMomentum","sqrt(protonEnergy*protonEnergy+2*protonEnergy*protonMass)");

			tree->SetAlias("alphaGamma","(alphaEnergy/alphaMass+1)");
			tree->SetAlias("alphaBeta","sqrt(1-1/(alphaGamma*alphaGamma))");
			tree->SetAlias("alphaVelocity","alphaBeta*SOL");
			tree->SetAlias("alphaMomentum","sqrt(alphaEnergy*alphaEnergy+2*alphaEnergy*alphaMass)");


			tree->SetAlias("E0","beamEk+beamMass+targetMass");
			tree->SetAlias("P0","beamMomentum");

			tree->SetAlias("E1","protonEnergy+protonMass");
			tree->SetAlias("P1","protonMomentum");
			tree->SetAlias("theta1","protonAngle*TMath::DegToRad()");

			tree->SetAlias("E2","alphaEnergy+alphaMass");
			tree->SetAlias("P2","alphaMomentum");
			tree->SetAlias("theta2","alphaAngle*TMath::DegToRad()");
			


			tree->SetAlias("residueMomentum","sqrt(P0*P0 + P1*P1+ P2*P2 - 2*P0*P1*cos(theta1) - 2*P0*P2*cos(theta2) + 2*P1*P2*cosTheta12)");

			tree->SetAlias("residueEnergy","E0-E1-E2");

			tree->SetAlias("residueMass","sqrt(residueEnergy*residueEnergy - residueMomentum*residueMomentum)");
			tree->SetAlias("exEnergy","residueMass-residueRestMass");

		}

		void setGate(TString g){
			gate = g;
		}
		void addGate(TString g){
			gate = gate+"&&"+g;
		}

		void setVar(TString vY,TString vX){
			varX = vX;	
			varY = vY;	
		}
		void setVar(TString vH){
			varH = vH;
		}
		void setBin(int bX,double miX,double maX,int bY,double miY,double maY){
			binX = bX; minX = miX; maxX = maX;
			binY = bY; minY = miY; maxY = maY;
		}
		void setBin(int bH,double miH,double maH){
			binH = bH; minH = miH; maxH = maH;
		}
		void drawH(){
			TString draw = varH + Form(">>(%d,%2f,%2f)",binH,minH,maxH);	
			tree->Draw(draw,gate);
		}
		void draw2D(){
			TString draw = varY+":"+varX + Form(">>(%d,%2f,%2f,%d,%2f,%2f)",binX,minX,maxX,binY,minY,maxY);	
			tree->Draw(draw,gate,"colz");
		}



		~DrawTree(){
			delete tree;
		}
};

