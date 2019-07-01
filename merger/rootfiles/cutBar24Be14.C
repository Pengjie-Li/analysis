{
//========= Macro generated from object: Bar24Be14/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("Bar24Be14",6);
   cutg->SetVarX("0.5*(hodTRaw[0][24]+hodTRaw[1][24])");
   cutg->SetVarY("hodBarQCal[24]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1567.1,1629.24);
   cutg->SetPoint(1,1619.18,1523.31);
   cutg->SetPoint(2,1626.36,1904.66);
   cutg->SetPoint(3,1577.87,2000);
   cutg->SetPoint(4,1561.71,1713.98);
   cutg->SetPoint(5,1567.1,1629.24);
   cutg->Draw("");
}
