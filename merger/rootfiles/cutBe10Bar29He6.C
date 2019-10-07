{
//========= Macro generated from object: Be10Bar29He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar29He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][29]+hodTRaw[1][29])");
   cutg->SetVarY("hodBarQCal[29]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1612.72,564.389);
   cutg->SetPoint(1,1663.69,551.248);
   cutg->SetPoint(2,1694.27,643.233);
   cutg->SetPoint(3,1703.19,768.068);
   cutg->SetPoint(4,1686.62,846.912);
   cutg->SetPoint(5,1616.54,761.498);
   cutg->SetPoint(6,1608.89,748.357);
   cutg->SetPoint(7,1615.27,616.951);
   cutg->SetPoint(8,1615.27,584.1);
   cutg->SetPoint(9,1612.72,564.389);
   cutg->Draw("");
}
