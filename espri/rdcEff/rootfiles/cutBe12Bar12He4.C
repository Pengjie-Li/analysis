{
//========= Macro generated from object: Be12Bar12He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be12Bar12He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][12]+hodTRaw[1][12])");
   cutg->SetVarY("hodBarQCal[12]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18124.2,969.649);
   cutg->SetPoint(1,17956.7,801.917);
   cutg->SetPoint(2,17948.5,578.275);
   cutg->SetPoint(3,18005.7,434.505);
   cutg->SetPoint(4,18087.4,482.428);
   cutg->SetPoint(5,18254.9,578.275);
   cutg->SetPoint(6,18373.4,777.955);
   cutg->SetPoint(7,18336.6,921.725);
   cutg->SetPoint(8,18242.6,1033.55);
   cutg->SetPoint(9,18165,1017.57);
   cutg->SetPoint(10,18124.2,969.649);
   cutg->Draw("");
}
