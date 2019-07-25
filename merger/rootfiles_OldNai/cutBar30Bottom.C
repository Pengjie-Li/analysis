{
//========= Macro generated from object: Bar30Bottom/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar30Bottom",6);
   cutg->SetVarX("0.5*(hodTRaw[0][30]+hodTRaw[1][30])");
   cutg->SetVarY("hodBarQCal[30]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1501.01,1529.94);
   cutg->SetPoint(1,1508.13,314.387);
   cutg->SetPoint(2,1605.17,297.811);
   cutg->SetPoint(3,1600.71,1502.32);
   cutg->SetPoint(4,1502.79,1552.05);
   cutg->SetPoint(5,1501.01,1529.94);
   cutg->Draw("");
}
