{
//========= Macro generated from object: bar31Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar31Be14",8);
   cutg->SetVarX("0.5*(hodTRaw[0][31]+hodTRaw[1][31])");
   cutg->SetVarY("hodBarQCal[31]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1589.67,1537.81);
   cutg->SetPoint(1,1589.67,1275.32);
   cutg->SetPoint(2,1621.78,1256.15);
   cutg->SetPoint(3,1632.89,1450.8);
   cutg->SetPoint(4,1629.56,1621.86);
   cutg->SetPoint(5,1601.63,1677.9);
   cutg->SetPoint(6,1589.81,1543.71);
   cutg->SetPoint(7,1589.67,1537.81);
   cutg->Draw("");
}
