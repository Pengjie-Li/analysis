{
//========= Macro generated from object: Be14Bar8He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar8He4",9);
   cutg->SetVarX("0.5*(hodTRaw[0][8]+hodTRaw[1][8])");
   cutg->SetVarY("hodBarQCal[8]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18156.2,860.759);
   cutg->SetPoint(1,18457,1092.83);
   cutg->SetPoint(2,18500,1092.83);
   cutg->SetPoint(3,18494.6,934.599);
   cutg->SetPoint(4,18451.6,808.017);
   cutg->SetPoint(5,18242.1,649.789);
   cutg->SetPoint(6,18145.4,681.435);
   cutg->SetPoint(7,18172.3,839.662);
   cutg->SetPoint(8,18156.2,860.759);
   cutg->Draw("");
}
