{
//========= Macro generated from object: Be10Bar12Be10/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar12Be10",13);
   cutg->SetVarX("0.5*(hodTRaw[0][12]+hodTRaw[1][12])");
   cutg->SetVarY("hodBarQCal[12]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18827.8,3275.28);
   cutg->SetPoint(1,18761.2,3235.96);
   cutg->SetPoint(2,18741.2,3162.92);
   cutg->SetPoint(3,18741.2,3050.56);
   cutg->SetPoint(4,18744.6,2971.91);
   cutg->SetPoint(5,18757.9,2915.73);
   cutg->SetPoint(6,18827.8,2921.35);
   cutg->SetPoint(7,18887.6,3005.62);
   cutg->SetPoint(8,18917.6,3191.01);
   cutg->SetPoint(9,18904.3,3252.81);
   cutg->SetPoint(10,18831.1,3280.9);
   cutg->SetPoint(11,18821.1,3280.9);
   cutg->SetPoint(12,18827.8,3275.28);
   cutg->Draw("");
}
