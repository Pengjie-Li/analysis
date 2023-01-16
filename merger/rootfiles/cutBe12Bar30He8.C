{
//========= Macro generated from object: Be12Bar30He8/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar30He8",13);
   cutg->SetVarX("0.5*(hodTRaw[0][30]+hodTRaw[1][30])");
   cutg->SetVarY("hodBarQCal[30]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1576.08,695.254);
   cutg->SetPoint(1,1534.77,658.835);
   cutg->SetPoint(2,1532.97,509.11);
   cutg->SetPoint(3,1568.89,476.737);
   cutg->SetPoint(4,1617.39,517.203);
   cutg->SetPoint(5,1653.3,553.623);
   cutg->SetPoint(6,1653.3,630.508);
   cutg->SetPoint(7,1629.96,683.114);
   cutg->SetPoint(8,1612,691.208);
   cutg->SetPoint(9,1590.45,699.301);
   cutg->SetPoint(10,1583.26,699.301);
   cutg->SetPoint(11,1671.26,634.555);
   cutg->SetPoint(12,1576.08,695.254);
   cutg->Draw("");
}
