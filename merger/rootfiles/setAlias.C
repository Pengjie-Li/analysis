{


	TString hodBe10Be10 = "(Be10Bar23Be10||Be10Bar22Be10||Be10Bar21Be10||Be10Bar20Be10||Be10Bar19Be10)";
        TString hodBe10Be9  = "(Be10Bar23Be9||Be10Bar22Be9||Be10Bar21Be9||Be10Bar20Be9||Be10Bar19Be9)";
	TString hodBe10He6  = "(Be10Bar29He6||Be10Bar30He6||Be10Bar31He6||Be10Bar32He6||Be10Bar33He6||Be10Bar34He6)";
	TString	hodBe12He8  = "(Be12Bar30He8||Be12Bar31He8||Be12Bar32He8||Be12Bar33He8||Be12Bar34He8||Be12Bar35He8||Be12Bar36He8)";
	TString	hodBe12Be12 = "(Be12Bar23Be12||Be12Bar22Be12||Be12Bar21Be12||Be12Bar20Be12||Be12Bar19Be12)";

	TString hodBe14Bar30_27Be14 = "(Be14Bar30Be14||Be14Bar29Be14||Be14Bar28Be14||Be14Bar27Be14)";
	TString hodBe14Bar23_19Be14 = "(Be14Bar23Be14||Be14Bar22Be14||Be14Bar21Be14||Be14Bar20Be14||Be14Bar19Be14)";
	TString hodBe14Bar32_27Be14 = "(Be14Bar32Be14||Be14Bar31Be14||Be14Bar30Be14||Be14Bar29Be14||Be14Bar28Be14||Be14Bar27Be14)";
	TString hodBe14Be14 = "(Be14Bar32Be14||Be14Bar31Be14||Be14Bar30Be14||Be14Bar29Be14||Be14Bar28Be14||Be14Bar27Be14||Be14Bar23Be14||Be14Bar22Be14||Be14Bar21Be14||Be14Bar20Be14||Be14Bar19Be14)";

	TString hodBe14Be12 = "(Be14Bar26Be12||Be14Bar25Be12||Be14Bar24Be12||Be14Bar23Be12||Be14Bar22Be12||Be14Bar21Be12||Be14Bar20Be12||Be14Bar19Be12)";
	TString hodBe14Be11 = "(Be14Bar23Be11||Be14Bar22Be11||Be14Bar21Be11||Be14Bar20Be11||Be14Bar19Be11)";
	TString hodBe14Be10 = "(Be14Bar23Be10||Be14Bar22Be10||Be14Bar21Be10||Be14Bar20Be11||Be14Bar19Be10)";

	TString dssdFB = "((abs(dssdSideQ[0]-dssdSideQ[1])<1)||(abs(dssdSideQ[0]-dssdSideQ[1])<1))";
	TString lrSelect = "((plasQ[0]>2&&dssdSideQ[2]>2)||(plasQ[1]>2&&dssdSideQ[0]>2))";



	tree->SetAlias("SOL","299.792458*1");
	tree->SetAlias("AMU","931.49410242*1");
	tree->SetAlias("MassBe10","10.0113*1");
	tree->SetAlias("MassH","1.007276*1");

	tree->SetAlias("xB","vBeam.X()");
	tree->SetAlias("yB","vBeam.Y()");
	tree->SetAlias("zB","vBeam.Z()");

	tree->SetAlias("xP","vESPRI.X()");
	tree->SetAlias("yP","vESPRI.Y()");
	tree->SetAlias("zP","vESPRI.Z()");

	tree->SetAlias("xR","vFDC0.X()");
	tree->SetAlias("yR","vFDC0.Y()");
	tree->SetAlias("zR","vFDC0.Z()");

	TString planeOfBPR = "(xB*(yR*zP-yP*zR)+yB*(zR*xP-zP*xR)+zB*(xR*yP-xP*yR))";
	TString planeOfTest1 = "(TMath::Sqrt(1/3.)*(yR*zP-yP*zR)+TMath::Sqrt(1/3.)*(zR*xP-zP*xR)+TMath::Sqrt(1/3.)*(xR*yP-xP*yR))";
	TString planeOfTest2 = "(TMath::Sqrt(1/2.)*(yR*zP-yP*zR)+0.5*(zR*xP-zP*xR)+0.5*(xR*yP-xP*yR))";



	//tree->SetAlias("TOFSbtTarget","flightLengthBeamTarget/(Beta713*SOL-0.911)");
	tree->SetAlias("TOFSbtTarget","beamFL/(Beta713*SOL-0.911)");
	tree->SetAlias("F3TSlew0","F3TCal[0]+0.0015*F3QRaw[0]");
	tree->SetAlias("F3TSlew1","F3TCal[1]+0.0014*F3QRaw[1]");
	tree->SetAlias("F7TSlew0","F7TCal[0]+0.00092*F7QRaw[0]");
	tree->SetAlias("F7TSlew1","F7TCal[1]+0.00107*F7QRaw[1]");
	tree->SetAlias("SBT1TSlew0","SBT1TCal[0]");
	tree->SetAlias("SBT1TSlew1","SBT1TCal[1]+1.24");
	tree->SetAlias("SBT2TSlew0","SBT2TCal[0]");
	tree->SetAlias("SBT2TSlew1","SBT2TCal[1]-2.8");

	tree->SetAlias("F3TSlew","0.5*(F3TSlew0+F3TSlew1)");
	tree->SetAlias("F7TSlew","0.5*(F7TSlew0+F7TSlew1)");
	tree->SetAlias("SBT1TSlew","0.5*(SBT1TSlew0+SBT1TSlew1)");
	tree->SetAlias("SBT2TSlew","0.5*(SBT2TSlew0+SBT2TSlew1)");



	//tree->SetAlias("plasT0","(plasT[0]-0.01*(rdcY[0]-225)+0.000013*(rdcY[0]-225)*(rdcY[0]-225))");
	tree->SetAlias("plasT0","(plasT[0]-0.01*(rdcY[0]-225))");
	//tree->SetAlias("espriLTOF","((plasT[0]-F13T+895.2+19.84)-TOFSbtTarget)");
	tree->SetAlias("espriLTOF","(plasT0-F13T-TOFSbtTarget+895.2)+20.27-2.47");
	//tree->SetAlias("espriLTOF","1.4*(plasT0-F13T-TOFSbtTarget+895.2)+20.27");
	//tree->SetAlias("betaL","(flightLengthTargetESPRI+200)/(SOL*espriLTOF)");
	tree->SetAlias("betaL","(espriFL-150)/(SOL*espriLTOF)");
	tree->SetAlias("gammaL","1/sqrt(1-betaL*betaL)");
	tree->SetAlias("espriL_Ep","(gammaL-1)*AMU*MassH");

	tree->SetAlias("plasT1","plasT[1]-0.0115*(rdcY[1]-225)");
	//tree->SetAlias("espriRTOF","(plasT1-F13T-TOFSbtTarget+895)+20.27");
	tree->SetAlias("espriRTOF","(plasT1-F13T-TOFSbtTarget+895)+20.27-2.47");
	//tree->SetAlias("espriRTOF","1.4*(plasT1-F13T-TOFSbtTarget+895)+20.27");
	//tree->SetAlias("espriRTOF","((plasT[1]-F13T+895.2+19.84)-TOFSbtTarget)");
	//tree->SetAlias("betaR","(flightLengthTargetESPRI+200)/(SOL*espriRTOF)");
	tree->SetAlias("betaR","(espriFL-150)/(SOL*espriRTOF)");
	tree->SetAlias("gammaR","1/sqrt(1-betaR*betaR)");
	tree->SetAlias("espriR_Ep","(gammaR-1)*AMU*MassH");

	tree->SetAlias("beta","espriFL/(SOL*((plasTCal[3]-F13T+873+40.51)-TOFSbtTarget))");
	tree->SetAlias("gamma","1/sqrt(1-beta*beta)");
	tree->SetAlias("KEproton","(gamma-1)*AMU*MassH");




	tree->SetAlias("rltQPed","csiQRaw[0]-75.26");
	tree->SetAlias("rrtQPed","csiQRaw[1]-80.14");
	tree->SetAlias("rlbQPed","csiQRaw[2]-89.47");
	tree->SetAlias("rrbQPed","csiQRaw[3]-94.84");

	tree->SetAlias("llQPed","csiQRaw[4]-97.27");
	tree->SetAlias("lrtQPed","csiQRaw[5]-99.21");
	tree->SetAlias("lrbQPed","csiQRaw[6]-84.04");

	tree->SetAlias("rltQSync","0.841158*rltQPed/(1-1.79596e-05*rltQPed)");
	tree->SetAlias("rrtQSync","0.967906*rrtQPed/(1+4.94199e-05*rrtQPed)");
	tree->SetAlias("rlbQSync","rlbQPed");
	tree->SetAlias("rrbQSync","0.967843*rrbQPed/(1+4.51799e-05*rrbQPed)");

	tree->SetAlias("llQSync" ,"llQPed");
	tree->SetAlias("lrtQSync","0.763724*lrtQPed/(1+5.15633E-05*lrtQPed)");
	tree->SetAlias("lrbQSync","0.833370*lrbQPed/(1+4.58668E-05*lrbQPed)");

	tree->SetAlias("rltE","0.264445*rltQSync/(1-0.000153044*rltQSync)");
	tree->SetAlias("rlbE","0.264445*rlbQSync/(1-0.000153044*rlbQSync)");
	tree->SetAlias("rrtE","0.264445*rrtQSync/(1-0.000153044*rrtQSync)");
	tree->SetAlias("rrbE","0.264445*rrbQSync/(1-0.000153044*rrbQSync)");

	tree->SetAlias("llE","0.297221*llQSync/(1-0.000182688*llQSync)");
	tree->SetAlias("lrtE","0.297221*lrtQSync/(1-0.000182688*lrtQSync)");
	tree->SetAlias("lrbE","0.297221*lrbQSync/(1-0.000182688*lrbQSync)");


	tree->SetAlias("Target_X","vTarget.X()");
	tree->SetAlias("Target_Y","vTarget.Y()");



	tree->SetAlias("plasBarQPed0","sqrt(plasQPed[0]*plasQPed[1])");
	tree->SetAlias("plasBarQPed1","sqrt(plasQPed[2]*plasQPed[3])");
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 7; ++j) {

			tree->SetAlias(Form("naiBarQPed%d%d",i,j),Form("sqrt(naiQPed[%d][%d]*naiQPed[%d][%d])",2*i,j,2*i+1,j));
		}

	}

	tree->SetAlias("beamMass","MassBe10*AMU");
	tree->SetAlias("protonMass","MassH*AMU");
	tree->SetAlias("beamEk","Ek713*MassBe10");

	tree->SetAlias("beamMomentum","sqrt(beamEk*beamEk+2*beamEk*beamMass)");
	tree->SetAlias("protonEk","espriPlasDeltaE+espriNaiEnergy");
	tree->SetAlias("protonMomentum","sqrt(protonEk*protonEk+2*protonEk*protonMass)");

	tree->SetAlias("residueMomentum","sqrt(beamMomentum*beamMomentum + protonMomentum*protonMomentum - 2*beamMomentum*protonMomentum*cos(protonTheta*TMath::DegToRad()))");
	tree->SetAlias("residueEnergy","beamEk + beamMass - protonEk");
	tree->SetAlias("residueMass","sqrt(residueEnergy*residueEnergy - residueMomentum*residueMomentum)");
	tree->SetAlias("excitationEnergy","residueMass-beamMass");
}
