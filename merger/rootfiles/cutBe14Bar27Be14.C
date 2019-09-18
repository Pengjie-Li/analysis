{
//========= Macro generated from object: Be14Bar27Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar27Be14",11);
   cutg->SetVarX("0.5*(hodTRaw[0][27]+hodTRaw[1][27])");
   cutg->SetVarY("hodBarQCal[27]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,1635.38,1790.47);
   cutg->SetPoint(1,1651.67,2358.78);
   cutg->SetPoint(2,1670.13,2634.33);
   cutg->SetPoint(3,1687.51,2611.37);
   cutg->SetPoint(4,1680.99,2398.97);
   cutg->SetPoint(5,1679.91,2066.02);
   cutg->SetPoint(6,1679.91,1836.39);
   cutg->SetPoint(7,1665.79,1773.25);
   cutg->SetPoint(8,1650.59,1733.07);
   cutg->SetPoint(9,1635.38,1778.99);
   cutg->SetPoint(10,1635.38,1790.47);
   cutg->Draw("");
}
