{
//========= Macro generated from object: Be14Bar34He8/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar34He8",9);
   cutg->SetVarX("0.5*(hodTRaw[0][34]+hodTRaw[1][34])");
   cutg->SetVarY("hodBarQCal[34]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1660.91,561.998);
   cutg->SetPoint(1,1721.83,619.403);
   cutg->SetPoint(2,1778.7,607.922);
   cutg->SetPoint(3,1768.54,539.036);
   cutg->SetPoint(4,1710.66,470.149);
   cutg->SetPoint(5,1673.09,470.149);
   cutg->SetPoint(6,1658.87,516.073);
   cutg->SetPoint(7,1659.89,527.555);
   cutg->SetPoint(8,1660.91,561.998);
   cutg->Draw("");
}
