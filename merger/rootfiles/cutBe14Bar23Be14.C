{
//========= Macro generated from object: Be14Bar23Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar23Be14",9);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18622.2,3030.42);
   cutg->SetPoint(1,18576.6,2812.28);
   cutg->SetPoint(2,18622.2,2708.96);
   cutg->SetPoint(3,18661.3,2703.21);
   cutg->SetPoint(4,18697.1,2823.77);
   cutg->SetPoint(5,18706.9,2978.76);
   cutg->SetPoint(6,18690.6,3087.83);
   cutg->SetPoint(7,18706.9,3013.2);
   cutg->SetPoint(8,18622.2,3030.42);
   cutg->Draw("");
}
