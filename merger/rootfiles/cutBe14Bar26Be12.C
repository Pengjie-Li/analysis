{
//========= Macro generated from object: Be14Bar26Be12/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar26Be12",13);
   cutg->SetVarX("0.5*(hodTRaw[0][26]+hodTRaw[1][26])");
   cutg->SetVarY("hodBarQCal[26]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,1570.22,2381.75);
   cutg->SetPoint(1,1598.46,2846.73);
   cutg->SetPoint(2,1610.4,3271.53);
   cutg->SetPoint(3,1626.69,3415.04);
   cutg->SetPoint(4,1656.02,3483.93);
   cutg->SetPoint(5,1662.53,3225.6);
   cutg->SetPoint(6,1648.41,2973.02);
   cutg->SetPoint(7,1616.92,2599.89);
   cutg->SetPoint(8,1601.72,2404.71);
   cutg->SetPoint(9,1591.94,2353.04);
   cutg->SetPoint(10,1583.25,2324.34);
   cutg->SetPoint(11,1571.31,2416.19);
   cutg->SetPoint(12,1570.22,2381.75);
   cutg->Draw("");
}
