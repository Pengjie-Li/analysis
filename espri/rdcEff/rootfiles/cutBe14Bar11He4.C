{
//========= Macro generated from object: Be14Bar11He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar11He4",10);
   cutg->SetVarX("0.5*(hodTRaw[0][11]+hodTRaw[1][11])");
   cutg->SetVarY("hodBarQCal[11]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18150.8,829.114);
   cutg->SetPoint(1,18290.5,913.502);
   cutg->SetPoint(2,18376.4,881.857);
   cutg->SetPoint(3,18403.3,829.114);
   cutg->SetPoint(4,18354.9,744.726);
   cutg->SetPoint(5,18226,554.852);
   cutg->SetPoint(6,18140,586.498);
   cutg->SetPoint(7,18118.6,618.143);
   cutg->SetPoint(8,18156.2,860.759);
   cutg->SetPoint(9,18150.8,829.114);
   cutg->Draw("");
}
