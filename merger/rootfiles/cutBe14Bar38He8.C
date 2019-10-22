{
//========= Macro generated from object: Be14Bar38He8/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("Be14Bar38He8",11);
   cutg->SetVarX("0.5*(hodTRaw[0][38]+hodTRaw[1][38])");
   cutg->SetVarY("hodBarQCal[38]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1589.83,435.706);
   cutg->SetPoint(1,1657.86,441.447);
   cutg->SetPoint(2,1669.03,470.149);
   cutg->SetPoint(3,1671.06,533.295);
   cutg->SetPoint(4,1663.95,573.479);
   cutg->SetPoint(5,1614.2,544.776);
   cutg->SetPoint(6,1581.7,521.814);
   cutg->SetPoint(7,1580.69,493.111);
   cutg->SetPoint(8,1585.76,441.447);
   cutg->SetPoint(9,1602.01,429.966);
   cutg->SetPoint(10,1589.83,435.706);
   cutg->Draw("");
}
