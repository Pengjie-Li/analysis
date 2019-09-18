{
//========= Macro generated from object: Be14Bar22Be10/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar22Be10",13);
   cutg->SetVarX("0.5*(hodTRaw[0][22]+hodTRaw[1][22])");
   cutg->SetVarY("hodBarQCal[22]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18100.9,2301.38);
   cutg->SetPoint(1,18071.6,2226.75);
   cutg->SetPoint(2,18065.1,2140.64);
   cutg->SetPoint(3,18078.1,2025.83);
   cutg->SetPoint(4,18107.4,1974.17);
   cutg->SetPoint(5,18146.5,1979.91);
   cutg->SetPoint(6,18195.4,2031.57);
   cutg->SetPoint(7,18188.9,2152.12);
   cutg->SetPoint(8,18169.3,2243.97);
   cutg->SetPoint(9,18143.2,2312.86);
   cutg->SetPoint(10,18113.9,2307.12);
   cutg->SetPoint(11,18104.1,2289.9);
   cutg->SetPoint(12,18100.9,2301.38);
   cutg->Draw("");
}
