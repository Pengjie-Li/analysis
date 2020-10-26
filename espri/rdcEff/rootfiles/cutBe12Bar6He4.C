{
//========= Macro generated from object: Be12Bar6He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be12Bar6He4",10);
   cutg->SetVarX("0.5*(hodTRaw[0][6]+hodTRaw[1][6])");
   cutg->SetVarY("hodBarQCal[6]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18393.8,1017.57);
   cutg->SetPoint(1,18283.5,897.764);
   cutg->SetPoint(2,18275.3,714.057);
   cutg->SetPoint(3,18352.9,610.224);
   cutg->SetPoint(4,18500,698.083);
   cutg->SetPoint(5,18638.9,905.751);
   cutg->SetPoint(6,18671.6,1121.41);
   cutg->SetPoint(7,18495.9,1145.37);
   cutg->SetPoint(8,18414.2,1041.53);
   cutg->SetPoint(9,18393.8,1017.57);
   cutg->Draw("");
}
