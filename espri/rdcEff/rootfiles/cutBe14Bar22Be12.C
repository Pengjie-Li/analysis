{
//========= Macro generated from object: Be14Bar22Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar22Be12",14);
   cutg->SetVarX("0.5*(hodTRaw[0][22]+hodTRaw[1][22])");
   cutg->SetVarY("hodBarQCal[22]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18352.2,2675.58);
   cutg->SetPoint(1,18317.7,2504.12);
   cutg->SetPoint(2,18329.2,2414.95);
   cutg->SetPoint(3,18379.1,2277.78);
   cutg->SetPoint(4,18440.5,2277.78);
   cutg->SetPoint(5,18517.3,2332.65);
   cutg->SetPoint(6,18551.8,2428.67);
   cutg->SetPoint(7,18563.3,2565.84);
   cutg->SetPoint(8,18513.4,2641.29);
   cutg->SetPoint(9,18444.3,2709.88);
   cutg->SetPoint(10,18390.6,2737.31);
   cutg->SetPoint(11,18379.1,2730.45);
   cutg->SetPoint(12,18371.4,2730.45);
   cutg->SetPoint(13,18352.2,2675.58);
   cutg->Draw("same");
}
