{
//========= Macro generated from object: Be14Bar24He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar24He6",9);
   cutg->SetVarX("0.5*(hodTRaw[0][24]+hodTRaw[1][24])");
   cutg->SetVarY("hodBarQCal[24]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1547.18,504.592);
   cutg->SetPoint(1,1547.18,504.592);
   cutg->SetPoint(2,1620.29,452.928);
   cutg->SetPoint(3,1632.47,539.036);
   cutg->SetPoint(4,1625.37,636.625);
   cutg->SetPoint(5,1588.81,630.884);
   cutg->SetPoint(6,1542.1,636.625);
   cutg->SetPoint(7,1552.25,539.036);
   cutg->SetPoint(8,1547.18,504.592);
   cutg->Draw("");
}
