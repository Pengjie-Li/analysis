{
//========= Macro generated from object: Be12Bar35He8/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar35He8",8);
   cutg->SetVarX("0.5*(hodTRaw[0][35]+hodTRaw[1][35])");
   cutg->SetVarY("hodBarQCal[35]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1594.04,506.356);
   cutg->SetPoint(1,1698.2,633.475);
   cutg->SetPoint(2,1735.92,463.983);
   cutg->SetPoint(3,1703.59,379.237);
   cutg->SetPoint(4,1608.41,368.644);
   cutg->SetPoint(5,1594.04,506.356);
   cutg->SetPoint(6,1594.04,506.356);
   cutg->SetPoint(7,1594.04,506.356);
   cutg->Draw("");
}
