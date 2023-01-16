{
//========= Macro generated from object: Bar27Be14/Graph
//========= by ROOT version5.34/36
   
   TCutG *cutg = new TCutG("Bar27Be14",10);
   cutg->SetVarX("0.5*(hodTRaw[0][27]+hodTRaw[1][27])");
   cutg->SetVarY("hodBarQCal[27]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1628.96,1965.75);
   cutg->SetPoint(1,1654.38,2542.24);
   cutg->SetPoint(2,1676.54,2605.02);
   cutg->SetPoint(3,1673.28,2228.31);
   cutg->SetPoint(4,1672.63,1937.21);
   cutg->SetPoint(5,1658.94,1697.49);
   cutg->SetPoint(6,1643.95,1668.95);
   cutg->SetPoint(7,1624.4,1817.35);
   cutg->SetPoint(8,1632.22,1977.17);
   cutg->SetPoint(9,1628.96,1965.75);
   cutg->Draw("");
}
