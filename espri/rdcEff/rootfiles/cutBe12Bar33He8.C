{
//========= Macro generated from object: Be12Bar33He8/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar33He8",9);
   cutg->SetVarX("0.5*(hodTRaw[0][33]+hodTRaw[1][33])");
   cutg->SetVarY("hodBarQCal[33]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1579.67,612.288);
   cutg->SetPoint(1,1689.22,622.881);
   cutg->SetPoint(2,1730.53,516.949);
   cutg->SetPoint(3,1725.14,442.797);
   cutg->SetPoint(4,1671.26,400.424);
   cutg->SetPoint(5,1590.45,432.203);
   cutg->SetPoint(6,1588.65,538.136);
   cutg->SetPoint(7,1615.59,538.136);
   cutg->SetPoint(8,1579.67,612.288);
   cutg->Draw("");
}
