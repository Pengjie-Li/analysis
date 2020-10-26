{
//========= Macro generated from object: Bar30Top/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("Bar30Top",6);
   cutg->SetVarX("0.5*(hodTRaw[0][30]+hodTRaw[1][30])");
   cutg->SetVarY("hodBarQCal[30]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1501.01,3535.61);
   cutg->SetPoint(1,1505.46,2060.37);
   cutg->SetPoint(2,1582.02,2038.27);
   cutg->SetPoint(3,1574.01,3596.39);
   cutg->SetPoint(4,1507.24,3607.44);
   cutg->SetPoint(5,1501.01,3535.61);
   cutg->Draw("");
}
