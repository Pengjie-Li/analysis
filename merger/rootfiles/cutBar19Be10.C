{
//========= Macro generated from object: Bar19Be10/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar19Be10",8);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18486.1,2843.37);
   cutg->SetPoint(1,18538.9,3138.55);
   cutg->SetPoint(2,18647.2,3006.02);
   cutg->SetPoint(3,18619.4,2813.25);
   cutg->SetPoint(4,18538.9,2734.94);
   cutg->SetPoint(5,18488.9,2783.13);
   cutg->SetPoint(6,18488.9,2831.33);
   cutg->SetPoint(7,18486.1,2843.37);
   cutg->Draw("");
}
