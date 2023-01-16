{
//========= Macro generated from object: Be14Bar19Be12/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar19Be12",15);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18491.9,3047.65);
   cutg->SetPoint(1,18472.3,2955.8);
   cutg->SetPoint(2,18475.6,2869.69);
   cutg->SetPoint(3,18478.8,2806.54);
   cutg->SetPoint(4,18488.6,2772.1);
   cutg->SetPoint(5,18508.1,2772.1);
   cutg->SetPoint(6,18560.3,2789.32);
   cutg->SetPoint(7,18592.9,2892.65);
   cutg->SetPoint(8,18609.1,3018.94);
   cutg->SetPoint(9,18605.9,3099.31);
   cutg->SetPoint(10,18583.1,3128.01);
   cutg->SetPoint(11,18563.5,3145.24);
   cutg->SetPoint(12,18508.1,3076.35);
   cutg->SetPoint(13,18488.6,3053.39);
   cutg->SetPoint(14,18491.9,3047.65);
   cutg->Draw("");
}
