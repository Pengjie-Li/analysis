{
//========= Macro generated from object: Be14Bar28Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar28Be14",12);
   cutg->SetVarX("0.5*(hodTRaw[0][28]+hodTRaw[1][28])");
   cutg->SetVarY("hodBarQCal[28]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1608.36,3261.59);
   cutg->SetPoint(1,1547.27,2142.38);
   cutg->SetPoint(2,1560.2,1433.77);
   cutg->SetPoint(3,1591.92,1294.7);
   cutg->SetPoint(4,1682.38,1420.53);
   cutg->SetPoint(5,1729.37,1639.07);
   cutg->SetPoint(6,1762.27,3175.5);
   cutg->SetPoint(7,1744.64,3427.15);
   cutg->SetPoint(8,1658.88,3427.15);
   cutg->SetPoint(9,1616.59,3334.44);
   cutg->SetPoint(10,1616.59,3334.44);
   cutg->SetPoint(11,1608.36,3261.59);
   cutg->Draw("same");
}
