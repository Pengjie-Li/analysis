{
//========= Macro generated from object: Be10Bar32He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar32He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][32]+hodTRaw[1][32])");
   cutg->SetVarY("hodBarQCal[32]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1599.97,518.397);
   cutg->SetPoint(1,1685.35,597.24);
   cutg->SetPoint(2,1710.83,570.959);
   cutg->SetPoint(3,1710.83,505.256);
   cutg->SetPoint(4,1686.62,426.413);
   cutg->SetPoint(5,1598.7,380.42);
   cutg->SetPoint(6,1598.7,478.975);
   cutg->SetPoint(7,1605.07,531.537);
   cutg->SetPoint(8,1605.07,531.537);
   cutg->SetPoint(9,1599.97,518.397);
   cutg->Draw("");
}
