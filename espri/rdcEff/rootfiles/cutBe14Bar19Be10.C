{
//========= Macro generated from object: Be14Bar19Be10/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar19Be10",11);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18205.1,2726.18);
   cutg->SetPoint(1,18169.3,2611.37);
   cutg->SetPoint(2,18172.6,2479.33);
   cutg->SetPoint(3,18201.9,2376);
   cutg->SetPoint(4,18244.2,2353.04);
   cutg->SetPoint(5,18289.9,2467.85);
   cutg->SetPoint(6,18306.1,2536.74);
   cutg->SetPoint(7,18299.6,2680.25);
   cutg->SetPoint(8,18280.1,2720.44);
   cutg->SetPoint(9,18296.4,2685.99);
   cutg->SetPoint(10,18205.1,2726.18);
   cutg->Draw("");
}
