{
	tree->SetAlias("plasQLPed","sqrt(plasQPed[0]*plasQPed[1])");
	tree->SetAlias("plasQRPed","sqrt(plasQPed[2]*plasQPed[3])");
	tree->SetAlias("naiBar00QPed","sqrt(naiQPed[0][0]*naiQPed[1][0])");

	tree->SetAlias("AMU","931.49410242*1");
	tree->SetAlias("MassBe10","10.0113*1");
	tree->SetAlias("MassH","1.007276*1");

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
