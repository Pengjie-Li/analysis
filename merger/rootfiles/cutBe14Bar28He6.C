{
//========= Macro generated from object: Be14Bar28He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar28He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][28]+hodTRaw[1][28])");
   cutg->SetVarY("hodBarQCal[28]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1513.67,407.003);
   cutg->SetPoint(1,1546.16,412.744);
   cutg->SetPoint(2,1550.22,521.814);
   cutg->SetPoint(3,1532.96,556.257);
   cutg->SetPoint(4,1523.82,556.257);
   cutg->SetPoint(5,1510.62,527.555);
   cutg->SetPoint(6,1503.51,487.371);
   cutg->SetPoint(7,1506.56,407.003);
   cutg->SetPoint(8,1512.65,412.744);
   cutg->SetPoint(9,1513.67,407.003);
   cutg->Draw("");
}
