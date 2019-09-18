{
//========= Macro generated from object: Be14Bar20Be11/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar20Be11",10);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18306.1,2542.48);
   cutg->SetPoint(1,18289.9,2444.89);
   cutg->SetPoint(2,18302.9,2341.56);
   cutg->SetPoint(3,18329,2295.64);
   cutg->SetPoint(4,18358.3,2272.68);
   cutg->SetPoint(5,18420.2,2376);
   cutg->SetPoint(6,18413.7,2456.37);
   cutg->SetPoint(7,18387.6,2548.22);
   cutg->SetPoint(8,18407.1,2502.3);
   cutg->SetPoint(9,18306.1,2542.48);
   cutg->Draw("");
}
