{
	tree->SetAlias("AMU","931.49410242*1");
	tree->SetAlias("MassBe10","10.0113*1");
	tree->SetAlias("MassH","1.007276*1");

	tree->SetAlias("beamMass","MassBe10*AMU");
	tree->SetAlias("protonMass","MassH*AMU");
	tree->SetAlias("beamEnergy","Ek713*MassBe10");

	tree->SetAlias("beamMomentum","sqrt(beamEnergy*beamEnergy+2*beamEnergy*beamMass)");
	tree->SetAlias("protonEnergy","espriPlasDeltaE+espriNaiEnergy");
	tree->SetAlias("protonMomentum","sqrt(protonEnergy*protonEnergy+2*protonEnergy*protonMass)");

	tree->SetAlias("residueMomentum","sqrt(beamMomentum*beamMomentum + protonMomentum*protonMomentum - 2*beamMomentum*protonMomentum*cos(protonTheta))");
	tree->SetAlias("residueEnergy","beamEnergy + beamMass - protonEnergy");
	tree->SetAlias("residueMass","sqrt(residueEnergy*residueEnergy - residueMomentum*residueMomentum)");
	tree->SetAlias("excitationEnergy","residueMass-beamMass");
}
