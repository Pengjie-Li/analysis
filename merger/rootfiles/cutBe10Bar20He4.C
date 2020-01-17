{
//========= Macro generated from object: Be10Bar20He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar20He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18128.8,803.1);
   cutg->SetPoint(1,18081.2,699.77);
   cutg->SetPoint(2,18122.5,584.96);
   cutg->SetPoint(3,18208.1,573.479);
   cutg->SetPoint(4,18268.4,625.143);
   cutg->SetPoint(5,18287.4,722.732);
   cutg->SetPoint(6,18271.6,849.024);
   cutg->SetPoint(7,18195.4,843.284);
   cutg->SetPoint(8,18151,826.062);
   cutg->SetPoint(9,18128.8,791.619);
   cutg->SetPoint(10,18128.8,803.1);
   cutg->Draw("");
}
