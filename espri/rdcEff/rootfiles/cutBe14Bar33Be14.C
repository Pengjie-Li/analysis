{
//========= Macro generated from object: Be14Bar33Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar33Be14",10);
   cutg->SetVarX("0.5*(hodTRaw[0][33]+hodTRaw[1][33])");
   cutg->SetVarY("hodBarQCal[33]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1591.92,1413.91);
   cutg->SetPoint(1,1621.29,1327.81);
   cutg->SetPoint(2,1656.53,1427.15);
   cutg->SetPoint(3,1667.11,2281.46);
   cutg->SetPoint(4,1671.8,2771.52);
   cutg->SetPoint(5,1597.79,2930.46);
   cutg->SetPoint(6,1570.77,2533.11);
   cutg->SetPoint(7,1586.04,1586.09);
   cutg->SetPoint(8,1587.22,1460.26);
   cutg->SetPoint(9,1591.92,1413.91);
   cutg->Draw("same");
}
