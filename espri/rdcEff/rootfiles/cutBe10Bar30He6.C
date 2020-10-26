{
//========= Macro generated from object: Be10Bar30He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar30He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][30]+hodTRaw[1][30])");
   cutg->SetVarY("hodBarQCal[30]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1517.15,616.951);
   cutg->SetPoint(1,1566.85,669.514);
   cutg->SetPoint(2,1608.89,676.084);
   cutg->SetPoint(3,1626.73,643.233);
   cutg->SetPoint(4,1608.89,538.108);
   cutg->SetPoint(5,1583.41,505.256);
   cutg->SetPoint(6,1534.99,472.405);
   cutg->SetPoint(7,1526.07,524.967);
   cutg->SetPoint(8,1519.7,603.811);
   cutg->SetPoint(9,1517.15,616.951);
   cutg->Draw("");
}
