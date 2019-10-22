{
//========= Macro generated from object: Be14Bar11He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar11He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][11]+hodTRaw[1][11])");
   cutg->SetVarY("hodBarQCal[11]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18867.9,1043.5);
   cutg->SetPoint(1,18931.9,1043.5);
   cutg->SetPoint(2,19052.7,1168.65);
   cutg->SetPoint(3,19098.9,1311.68);
   cutg->SetPoint(4,19098.9,1418.95);
   cutg->SetPoint(5,18871.4,1222.29);
   cutg->SetPoint(6,18807.5,1109.06);
   cutg->SetPoint(7,18853.7,1019.67);
   cutg->SetPoint(8,18867.9,1025.63);
   cutg->SetPoint(9,18867.9,1043.5);
   cutg->Draw("");
}
