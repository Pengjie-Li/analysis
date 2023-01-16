{
//========= Macro generated from object: Be14Bar7He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar7He4",10);
   cutg->SetVarX("0.5*(hodTRaw[0][7]+hodTRaw[1][7])");
   cutg->SetVarY("hodBarQCal[7]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18344.2,786.92);
   cutg->SetPoint(1,18478.5,902.954);
   cutg->SetPoint(2,18639.7,987.342);
   cutg->SetPoint(3,18725.6,1040.08);
   cutg->SetPoint(4,18774,881.857);
   cutg->SetPoint(5,18510.7,660.338);
   cutg->SetPoint(6,18397.9,618.143);
   cutg->SetPoint(7,18354.9,660.338);
   cutg->SetPoint(8,18338.8,734.177);
   cutg->SetPoint(9,18344.2,786.92);
   cutg->Draw("");
}
