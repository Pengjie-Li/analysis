{
//========= Macro generated from object: Be14Bar34Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar34He8",13);
   cutg->SetVarX("0.5*(hodTRaw[0][34]+hodTRaw[1][34])");
   cutg->SetVarY("hodBarQCal[34]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1721.84,660.256);
   cutg->SetPoint(1,1642.93,600.16);
   cutg->SetPoint(2,1614.74,528.045);
   cutg->SetPoint(3,1627.42,451.923);
   cutg->SetPoint(4,1665.47,411.859);
   cutg->SetPoint(5,1740.16,433.894);
   cutg->SetPoint(6,1793.71,500);
   cutg->SetPoint(7,1828.95,568.109);
   cutg->SetPoint(8,1855.72,626.202);
   cutg->SetPoint(9,1824.72,662.26);
   cutg->SetPoint(10,1785.26,666.266);
   cutg->SetPoint(11,1741.57,668.269);
   cutg->SetPoint(12,1721.84,660.256);
   cutg->Draw("");
}
