{
//========= Macro generated from object: Be12Bar14He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar14He6",13);
   cutg->SetVarX("0.5*(hodTRaw[0][14]+hodTRaw[1][14])");
   cutg->SetVarY("hodBarQCal[14]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18551.7,854.765);
   cutg->SetPoint(1,18638.8,808.84);
   cutg->SetPoint(2,18712.3,877.727);
   cutg->SetPoint(3,18725.9,1026.98);
   cutg->SetPoint(4,18652.4,1084.39);
   cutg->SetPoint(5,18598,1084.39);
   cutg->SetPoint(6,18554.4,1061.42);
   cutg->SetPoint(7,18543.5,986.797);
   cutg->SetPoint(8,18538.1,917.91);
   cutg->SetPoint(9,18549,871.986);
   cutg->SetPoint(10,18562.6,860.505);
   cutg->SetPoint(11,18581.6,837.543);
   cutg->SetPoint(12,18551.7,854.765);
   cutg->Draw("");
}
