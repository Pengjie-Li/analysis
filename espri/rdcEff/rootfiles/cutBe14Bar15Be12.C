{
//========= Macro generated from object: Be14Bar15Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar15Be12",15);
   cutg->SetVarX("0.5*(hodTRaw[0][15]+hodTRaw[1][15])");
   cutg->SetVarY("hodBarQCal[15]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18674.6,3141.98);
   cutg->SetPoint(1,18628.6,2956.79);
   cutg->SetPoint(2,18628.6,2819.62);
   cutg->SetPoint(3,18647.8,2634.43);
   cutg->SetPoint(4,18678.5,2607);
   cutg->SetPoint(5,18774.4,2661.87);
   cutg->SetPoint(6,18874.2,2805.9);
   cutg->SetPoint(7,18931.8,2908.78);
   cutg->SetPoint(8,18977.9,3052.81);
   cutg->SetPoint(9,18947.2,3203.7);
   cutg->SetPoint(10,18866.6,3265.43);
   cutg->SetPoint(11,18832,3327.16);
   cutg->SetPoint(12,18743.7,3251.71);
   cutg->SetPoint(13,18713,3217.42);
   cutg->SetPoint(14,18674.6,3141.98);
   cutg->Draw("same");
}
