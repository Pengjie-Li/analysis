{
//========= Macro generated from object: Be14Bar26He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar26He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][26]+hodTRaw[1][26])");
   cutg->SetVarY("hodBarQCal[26]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1530.93,722.732);
   cutg->SetPoint(1,1520.78,539.036);
   cutg->SetPoint(2,1526.87,464.409);
   cutg->SetPoint(3,1552.25,521.814);
   cutg->SetPoint(4,1564.44,619.403);
   cutg->SetPoint(5,1573.58,728.473);
   cutg->SetPoint(6,1554.29,768.657);
   cutg->SetPoint(7,1534.99,722.732);
   cutg->SetPoint(8,1531.95,722.732);
   cutg->SetPoint(9,1530.93,722.732);
   cutg->Draw("");
}
