{
//========= Macro generated from object: Be12Bar20He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar20He6",12);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18325.8,940.873);
   cutg->SetPoint(1,18298.6,728.473);
   cutg->SetPoint(2,18361.2,688.289);
   cutg->SetPoint(3,18437.4,699.77);
   cutg->SetPoint(4,18513.6,780.138);
   cutg->SetPoint(5,18494.6,883.467);
   cutg->SetPoint(6,18453.7,923.651);
   cutg->SetPoint(7,18369.4,923.651);
   cutg->SetPoint(8,18347.6,935.132);
   cutg->SetPoint(9,18328.6,935.132);
   cutg->SetPoint(10,18328.6,935.132);
   cutg->SetPoint(11,18325.8,940.873);
   cutg->Draw("");
}
