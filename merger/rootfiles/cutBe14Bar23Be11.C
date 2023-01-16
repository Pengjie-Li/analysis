{
//========= Macro generated from object: Be14Bar23Be11/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar23Be11",12);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18185.6,2502.3);
   cutg->SetPoint(1,18153,2410.45);
   cutg->SetPoint(2,18159.5,2301.38);
   cutg->SetPoint(3,18185.6,2175.09);
   cutg->SetPoint(4,18208.4,2163.61);
   cutg->SetPoint(5,18280.1,2238.23);
   cutg->SetPoint(6,18319.2,2358.78);
   cutg->SetPoint(7,18312.7,2410.45);
   cutg->SetPoint(8,18267.1,2525.26);
   cutg->SetPoint(9,18221.4,2588.4);
   cutg->SetPoint(10,18221.4,2588.4);
   cutg->SetPoint(11,18185.6,2502.3);
   cutg->Draw("");
}
