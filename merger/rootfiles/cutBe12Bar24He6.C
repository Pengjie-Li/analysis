{
//========= Macro generated from object: Be12Bar24He6/Graph
//========= by ROOT version6.08/04
   
   cutg = new TCutG("Be12Bar24He6",5);
   cutg->SetVarX("0.5*(hodTRaw[0][24]+hodTRaw[1][24])");
   cutg->SetVarY("hodBarQCal[24]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1550.9,396.119);
   cutg->SetPoint(1,1593.07,458.904);
   cutg->SetPoint(2,1575,658.676);
   cutg->SetPoint(3,1543.88,573.059);
   cutg->SetPoint(4,1550.9,396.119);
   cutg->Draw("");
}
