{
//========= Macro generated from object: Be14Bar28Be14/Graph
//========= by ROOT version5.34/36
   
   TCutG *cutg = new TCutG("Be14Bar28Be14",16);
   cutg->SetVarX("0.5*(hodTRaw[0][28]+hodTRaw[1][28])");
   cutg->SetVarY("hodBarQCal[28]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1648.51,1571.92);
   cutg->SetPoint(1,1660.79,1800.23);
   cutg->SetPoint(2,1675.91,2319.63);
   cutg->SetPoint(3,1694.8,2787.67);
   cutg->SetPoint(4,1690.08,3107.31);
   cutg->SetPoint(5,1683.47,3192.92);
   cutg->SetPoint(6,1645.67,3175.8);
   cutg->SetPoint(7,1628.67,3095.89);
   cutg->SetPoint(8,1623,2525.11);
   cutg->SetPoint(9,1598.43,2154.11);
   cutg->SetPoint(10,1588.04,1845.89);
   cutg->SetPoint(11,1594.65,1594.75);
   cutg->SetPoint(12,1616.38,1486.3);
   cutg->SetPoint(13,1650.4,1549.09);
   cutg->SetPoint(14,1650.4,1571.92);
   cutg->SetPoint(15,1648.51,1571.92);
   cutg->Draw("");
}
