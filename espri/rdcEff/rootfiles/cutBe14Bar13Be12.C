{
//========= Macro generated from object: Be14Bar13Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar13Be12",14);
   cutg->SetVarX("0.5*(hodTRaw[0][13]+hodTRaw[1][13])");
   cutg->SetVarY("hodBarQCal[13]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18793.6,3059.67);
   cutg->SetPoint(1,18705.3,2888.2);
   cutg->SetPoint(2,18720.7,2675.58);
   cutg->SetPoint(3,18759.1,2586.42);
   cutg->SetPoint(4,18866.6,2682.44);
   cutg->SetPoint(5,18951,2737.31);
   cutg->SetPoint(6,18997.1,2751.03);
   cutg->SetPoint(7,19035.4,2936.21);
   cutg->SetPoint(8,18985.5,3073.39);
   cutg->SetPoint(9,18912.6,3128.26);
   cutg->SetPoint(10,18851.2,3121.4);
   cutg->SetPoint(11,18839.7,3114.54);
   cutg->SetPoint(12,18820.5,3093.96);
   cutg->SetPoint(13,18793.6,3059.67);
   cutg->Draw("same");
}
