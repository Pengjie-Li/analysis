{
        tree->SetAlias("plasBarQPed0","sqrt(plasQPed[0]*plasQPed[1])");
        tree->SetAlias("plasBarQPed1","sqrt(plasQPed[2]*plasQPed[3])");
        for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 7; ++j) {

                        tree->SetAlias(Form("naiBarQPed%d%d",i,j),Form("sqrt(naiQPed[%d][%d]*naiQPed[%d][%d])",2*i,j,2*i+1,j));
                        tree->SetAlias(Form("naiBarQRaw%d%d",i,j),Form("sqrt(naiQRaw[%d][%d]*naiQRaw[%d][%d])",2*i,j,2*i+1,j));
                }

        }

        tree->SetAlias("SOL","299.792458*1");
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
