{
//========= Macro generated from object: Be14Bar24Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar24Be14",11);
   cutg->SetVarX("0.5*(hodTRaw[0][24]+hodTRaw[1][24])");
   cutg->SetVarY("hodBarQCal[24]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1675.76,2321.72);
   cutg->SetPoint(1,1654.68,2038.37);
   cutg->SetPoint(2,1657.84,1855.37);
   cutg->SetPoint(3,1672.6,1713.7);
   cutg->SetPoint(4,1721.08,1713.7);
   cutg->SetPoint(5,1748.48,2050.18);
   cutg->SetPoint(6,1744.27,2274.5);
   cutg->SetPoint(7,1709.49,2475.21);
   cutg->SetPoint(8,1689.46,2457.5);
   cutg->SetPoint(9,1676.81,2304.01);
   cutg->SetPoint(10,1675.76,2321.72);
   cutg->Draw("");
}
