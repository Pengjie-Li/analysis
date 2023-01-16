{
	TString gate[8]={"","","","","","","",""};
	TString targetArea ;
	TString hodGate ;
	TString beamGate;
	TString defaultGate;
	TString protonGate;

	TString trigger = "Trig_BxESPRI>0&&Trig_DSB==0&&Trig_BxESPRIxTEL==0&&Trig_BxNEBULA==0&&Trig_BxTEL==0";
	defaultGate = trigger;
	protonGate = "Proton";
	targetArea = "sqrt((Target_X+2.13)*(Target_X+2.13)+(Target_Y+1.6)*(Target_Y+1.6))<13";
	hodGate = "(Be10Bar23Be10||Be10Bar22Be10||Be10Bar21Be10||Be10Bar20Be10||Be10Bar19Be10)";
	beamGate = "BeamBe10";


	gate[0] = defaultGate;
	gate[1] = defaultGate +"&&"+ protonGate;
	gate[2] = defaultGate +"&&"+ targetArea;
	gate[3] = protonGate +"&&"+ gate[2];
	gate[4] = defaultGate +"&&"+ beamGate;
	gate[5] = beamGate +"&&"+ gate[3];
	gate[6] = defaultGate+"&&" + hodGate;
	gate[7] = gate[5] +"&&"+ hodGate;

	gROOT->ProcessLine(".x cutBeamBe10.C");
	gROOT->ProcessLine(".x cutProtonBe10.C");
	gROOT->ProcessLine(".x cutTargetArea.C");

	gROOT->ProcessLine(".x cutBe10Bar23Be10.C");
	gROOT->ProcessLine(".x cutBe10Bar22Be10.C");
	gROOT->ProcessLine(".x cutBe10Bar21Be10.C");
	gROOT->ProcessLine(".x cutBe10Bar20Be10.C");
	gROOT->ProcessLine(".x cutBe10Bar19Be10.C");

	gROOT->ProcessLine(".x cutBe10Bar23Be9.C");
	gROOT->ProcessLine(".x cutBe10Bar22Be9.C");
	gROOT->ProcessLine(".x cutBe10Bar21Be9.C");
	gROOT->ProcessLine(".x cutBe10Bar20Be9.C");
	gROOT->ProcessLine(".x cutBe10Bar19Be9.C");

	tree->SetAlias("AMU","931.49410242*1");
	tree->SetAlias("MassBe10","10.0113*1");
	tree->SetAlias("MassH","1.007276*1");

	tree->SetAlias("beamMass","MassBe10*AMU");
	tree->SetAlias("protonMass","MassH*AMU");
	tree->SetAlias("beamEk","Ek713*MassBe10");

	tree->SetAlias("beamMomentum","sqrt(beamEk*beamEk+2*beamEk*beamMass)");
	tree->SetAlias("protonEk","espriPlasDeltaE+espriNaiEnergy");
	tree->SetAlias("protonMomentum","sqrt(protonEk*protonEk+2*protonEk*protonMass)");

	tree->SetAlias("residueMomentum","sqrt(beamMomentum*beamMomentum + protonMomentum*protonMomentum - 2*beamMomentum*protonMomentum*cos(protonTheta))");
	tree->SetAlias("residueEnergy","beamEk + beamMass - protonEk");
	tree->SetAlias("residueMass","sqrt(residueEnergy*residueEnergy - residueMomentum*residueMomentum)");
	tree->SetAlias("excitationEnergy","residueMass-beamMass");



}
