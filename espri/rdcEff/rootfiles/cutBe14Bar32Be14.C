{
//========= Macro generated from object: Be14Bar32Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar32Be14",10);
   cutg->SetVarX("0.5*(hodTRaw[0][32]+hodTRaw[1][32])");
   cutg->SetVarY("hodBarQCal[32]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1613.06,1248.34);
   cutg->SetPoint(1,1662.41,1142.38);
   cutg->SetPoint(2,1680.03,1168.87);
   cutg->SetPoint(3,1705.87,2003.31);
   cutg->SetPoint(4,1698.83,2360.93);
   cutg->SetPoint(5,1618.94,2360.93);
   cutg->SetPoint(6,1590.74,1738.41);
   cutg->SetPoint(7,1610.71,1321.19);
   cutg->SetPoint(8,1610.71,1321.19);
   cutg->SetPoint(9,1613.06,1248.34);
   cutg->Draw("same");
}
