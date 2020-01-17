{
//========= Macro generated from object: Be10Bar15He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar15He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][15]+hodTRaw[1][15])");
   cutg->SetVarY("hodBarQCal[15]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18312,960.674);
   cutg->SetPoint(1,18242.1,820.225);
   cutg->SetPoint(2,18262.1,707.865);
   cutg->SetPoint(3,18272.1,702.247);
   cutg->SetPoint(4,18358.6,646.067);
   cutg->SetPoint(5,18428.5,702.247);
   cutg->SetPoint(6,18465.1,797.753);
   cutg->SetPoint(7,18448.4,921.348);
   cutg->SetPoint(8,18388.5,943.82);
   cutg->SetPoint(9,18431.8,932.584);
   cutg->SetPoint(10,18312,960.674);
   cutg->Draw("");
}
