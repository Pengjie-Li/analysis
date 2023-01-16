{
//========= Macro generated from object: Be10Bar23He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar23He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18040,854.765);
   cutg->SetPoint(1,17998.7,768.657);
   cutg->SetPoint(2,17982.9,636.625);
   cutg->SetPoint(3,18059,533.295);
   cutg->SetPoint(4,18128.8,550.517);
   cutg->SetPoint(5,18182.7,671.068);
   cutg->SetPoint(6,18170.1,797.359);
   cutg->SetPoint(7,18106.6,877.727);
   cutg->SetPoint(8,18055.8,860.505);
   cutg->SetPoint(9,18043.1,849.024);
   cutg->SetPoint(10,18040,854.765);
   cutg->Draw("");
}
