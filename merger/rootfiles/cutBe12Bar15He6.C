{
//========= Macro generated from object: Be12Bar15He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar15He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][15]+hodTRaw[1][15])");
   cutg->SetVarY("hodBarQCal[15]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18529.9,854.765);
   cutg->SetPoint(1,18649.7,808.84);
   cutg->SetPoint(2,18690.5,958.094);
   cutg->SetPoint(3,18649.7,1072.9);
   cutg->SetPoint(4,18576.2,1095.87);
   cutg->SetPoint(5,18532.7,1049.94);
   cutg->SetPoint(6,18513.6,952.354);
   cutg->SetPoint(7,18521.8,854.765);
   cutg->SetPoint(8,18546.3,860.505);
   cutg->SetPoint(9,18529.9,854.765);
   cutg->Draw("");
}
