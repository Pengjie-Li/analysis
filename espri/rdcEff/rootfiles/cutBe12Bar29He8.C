{
//========= Macro generated from object: Be12Bar29He8/Graph
//========= by ROOT version6.08/04
   
   cutg = new TCutG("Be12Bar29He8",10);
   cutg->SetVarX("0.5*(hodTRaw[0][29]+hodTRaw[1][29])");
   cutg->SetVarY("hodBarQCal[29]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1618.17,755.708);
   cutg->SetPoint(1,1676.41,767.123);
   cutg->SetPoint(2,1708.53,761.416);
   cutg->SetPoint(3,1698.49,601.598);
   cutg->SetPoint(4,1661.35,550.228);
   cutg->SetPoint(5,1631.22,550.228);
   cutg->SetPoint(6,1617.17,641.552);
   cutg->SetPoint(7,1619.18,732.877);
   cutg->SetPoint(8,1617.17,692.922);
   cutg->SetPoint(9,1618.17,755.708);
   cutg->Draw("");
}
