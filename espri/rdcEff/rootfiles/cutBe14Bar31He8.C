{
//========= Macro generated from object: Be14Bar31He8/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar31He8",12);
   cutg->SetVarX("0.5*(hodTRaw[0][31]+hodTRaw[1][31])");
   cutg->SetVarY("hodBarQCal[31]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1720.43,630.904);
   cutg->SetPoint(1,1610.51,590.135);
   cutg->SetPoint(2,1606.29,521.337);
   cutg->SetPoint(3,1609.1,434.702);
   cutg->SetPoint(4,1649.97,383.74);
   cutg->SetPoint(5,1727.48,388.837);
   cutg->SetPoint(6,1790.9,475.471);
   cutg->SetPoint(7,1797.94,592.683);
   cutg->SetPoint(8,1771.17,653.837);
   cutg->SetPoint(9,1741.57,646.192);
   cutg->SetPoint(10,1741.57,646.192);
   cutg->SetPoint(11,1720.43,630.904);
   cutg->Draw("");
}
