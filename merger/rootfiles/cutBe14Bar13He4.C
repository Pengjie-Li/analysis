{
//========= Macro generated from object: Be14Bar13He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar13He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][13]+hodTRaw[1][13])");
   cutg->SetVarY("hodBarQCal[13]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18097.1,786.92);
   cutg->SetPoint(1,18236.7,829.114);
   cutg->SetPoint(2,18306.6,850.211);
   cutg->SetPoint(3,18344.2,734.177);
   cutg->SetPoint(4,18285.1,639.24);
   cutg->SetPoint(5,18183,544.304);
   cutg->SetPoint(6,18118.6,544.304);
   cutg->SetPoint(7,18091.7,670.886);
   cutg->SetPoint(8,18091.7,755.274);
   cutg->SetPoint(9,18129.3,776.371);
   cutg->SetPoint(10,18097.1,786.92);
   cutg->Draw("");
}
