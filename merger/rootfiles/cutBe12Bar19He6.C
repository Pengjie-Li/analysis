{
//========= Macro generated from object: Be12Bar19He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar19He6",13);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18366.7,797.359);
   cutg->SetPoint(1,18489.1,808.84);
   cutg->SetPoint(2,18538.1,917.91);
   cutg->SetPoint(3,18532.7,981.056);
   cutg->SetPoint(4,18475.5,1049.94);
   cutg->SetPoint(5,18426.5,1049.94);
   cutg->SetPoint(6,18358.5,1032.72);
   cutg->SetPoint(7,18342.2,940.873);
   cutg->SetPoint(8,18342.2,866.246);
   cutg->SetPoint(9,18372.1,820.321);
   cutg->SetPoint(10,18374.8,797.359);
   cutg->SetPoint(11,18374.8,797.359);
   cutg->SetPoint(12,18366.7,797.359);
   cutg->Draw("");
}
