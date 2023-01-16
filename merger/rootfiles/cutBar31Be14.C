{
//========= Macro generated from object: Bar31Be14/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("Bar31Be14",9);
   cutg->SetVarX("0.5*(hodTRaw[0][31]+hodTRaw[1][31])");
   cutg->SetVarY("hodBarQCal[31]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1578.65,1440.3);
   cutg->SetPoint(1,1623.02,1704.36);
   cutg->SetPoint(2,1639.98,1566.59);
   cutg->SetPoint(3,1632.8,1336.97);
   cutg->SetPoint(4,1606.05,1245.12);
   cutg->SetPoint(5,1576.7,1348.45);
   cutg->SetPoint(6,1581.26,1491.96);
   cutg->SetPoint(7,1587.79,1497.7);
   cutg->SetPoint(8,1578.65,1440.3);
   cutg->Draw("");
}
