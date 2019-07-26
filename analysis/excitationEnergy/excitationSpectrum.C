
class ReadFile{
	private:
	public:
		ReadFile(){}	
		~ReadFile(){}	
};
void excitationSpectrum(){
        if (!gROOT->GetClass("TGenPhaseSpace")) gSystem->Load("libPhysics");

       // Double_t Mass_p=938.28e-3; //Mev
       // Double_t Mass_Beam=Mass_p; //Mev
       // double E_beam=165.e-3+Mass_Beam;;// GeV

       // TLorentzVector P4_Beam ;
       // TVector3 P_Beam(0,0,1) ;
       // P_Beam.SetMag(sqrt(E_beam*E_beam-Mass_Beam*Mass_Beam));// E_beam before vertex
       // P4_Beam.SetVectM(P_Beam,Mass_Beam);

       // TLorentzVector target  ;
       // target.SetPxPyPzE(0,0,0,Mass_p);
       // TLorentzVector W = P4_Beam + target ;


}
