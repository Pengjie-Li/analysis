{
//========= Macro generated from object: Be10Bar20Be10/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be10Bar20Be10",15);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18490.1,2776.26);
   cutg->SetPoint(1,18424,2684.93);
   cutg->SetPoint(2,18446.1,2559.36);
   cutg->SetPoint(3,18454.9,2450.91);
   cutg->SetPoint(4,18516.5,2433.79);
   cutg->SetPoint(5,18553.9,2468.04);
   cutg->SetPoint(6,18615.6,2536.53);
   cutg->SetPoint(7,18655.2,2559.36);
   cutg->SetPoint(8,18688.3,2662.1);
   cutg->SetPoint(9,18644.2,2702.05);
   cutg->SetPoint(10,18582.6,2719.18);
   cutg->SetPoint(11,18536.3,2742.01);
   cutg->SetPoint(12,18507.7,2770.55);
   cutg->SetPoint(13,18494.5,2770.55);
   cutg->SetPoint(14,18490.1,2776.26);
   cutg->Draw("");
}
