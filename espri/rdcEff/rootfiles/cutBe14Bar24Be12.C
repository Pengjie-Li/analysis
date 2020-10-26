{
//========= Macro generated from object: Be14Bar24Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar24Be12",14);
   cutg->SetVarX("0.5*(hodTRaw[0][24]+hodTRaw[1][24])");
   cutg->SetVarY("hodBarQCal[24]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1558.62,1564.47);
   cutg->SetPoint(1,1589.33,1475.31);
   cutg->SetPoint(2,1618.76,1530.18);
   cutg->SetPoint(3,1639.23,1859.4);
   cutg->SetPoint(4,1654.58,2353.22);
   cutg->SetPoint(5,1650.74,3189.99);
   cutg->SetPoint(6,1645.62,3498.63);
   cutg->SetPoint(7,1618.76,3649.52);
   cutg->SetPoint(8,1589.33,3683.81);
   cutg->SetPoint(9,1570.14,2949.93);
   cutg->SetPoint(10,1565.02,2325.79);
   cutg->SetPoint(11,1557.34,1770.23);
   cutg->SetPoint(12,1550.95,1660.49);
   cutg->SetPoint(13,1558.62,1564.47);
   cutg->Draw("same");
}
