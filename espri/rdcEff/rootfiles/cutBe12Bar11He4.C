{
//========= Macro generated from object: Be12Bar11He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be12Bar11He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][11]+hodTRaw[1][11])");
   cutg->SetVarY("hodBarQCal[11]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18140.5,905.751);
   cutg->SetPoint(1,18013.9,809.904);
   cutg->SetPoint(2,17964.9,594.249);
   cutg->SetPoint(3,17997.5,482.428);
   cutg->SetPoint(4,18185.5,434.505);
   cutg->SetPoint(5,18295.8,674.121);
   cutg->SetPoint(6,18389.7,777.955);
   cutg->SetPoint(7,18324.3,897.764);
   cutg->SetPoint(8,18222.2,969.649);
   cutg->SetPoint(9,18165,961.661);
   cutg->SetPoint(10,18140.5,905.751);
   cutg->Draw("");
}
