{
//========= Macro generated from object: Be14Bar23Be10/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar23Be10",11);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18048.8,2347.3);
   cutg->SetPoint(1,18026,2163.61);
   cutg->SetPoint(2,18061.8,2031.57);
   cutg->SetPoint(3,18130.2,2123.42);
   cutg->SetPoint(4,18146.5,2226.75);
   cutg->SetPoint(5,18130.2,2307.12);
   cutg->SetPoint(6,18120.4,2358.78);
   cutg->SetPoint(7,18100.9,2398.97);
   cutg->SetPoint(8,18061.8,2398.97);
   cutg->SetPoint(9,18048.8,2318.6);
   cutg->SetPoint(10,18048.8,2347.3);
   cutg->Draw("");
}
