{
//========= Macro generated from object: Be10Bar18He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar18He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][18]+hodTRaw[1][18])");
   cutg->SetVarY("hodBarQCal[18]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18243,883.467);
   cutg->SetPoint(1,18195.4,808.84);
   cutg->SetPoint(2,18208.1,705.511);
   cutg->SetPoint(3,18252.5,590.7);
   cutg->SetPoint(4,18331.9,636.625);
   cutg->SetPoint(5,18382.6,739.954);
   cutg->SetPoint(6,18373.1,860.505);
   cutg->SetPoint(7,18293.8,923.651);
   cutg->SetPoint(8,18236.7,894.948);
   cutg->SetPoint(9,18239.8,871.986);
   cutg->SetPoint(10,18243,883.467);
   cutg->Draw("");
}
