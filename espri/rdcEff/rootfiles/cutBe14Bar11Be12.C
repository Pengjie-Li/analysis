{
//========= Macro generated from object: Be14Bar11Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar11Be12",14);
   cutg->SetVarX("0.5*(hodTRaw[0][11]+hodTRaw[1][11])");
   cutg->SetVarY("hodBarQCal[11]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18881.9,3306.58);
   cutg->SetPoint(1,18793.6,3114.54);
   cutg->SetPoint(2,18782.1,2888.2);
   cutg->SetPoint(3,18786,2778.46);
   cutg->SetPoint(4,18866.6,2778.46);
   cutg->SetPoint(5,19004.7,2949.93);
   cutg->SetPoint(6,19077.7,2977.37);
   cutg->SetPoint(7,19127.6,3087.11);
   cutg->SetPoint(8,19058.5,3217.42);
   cutg->SetPoint(9,19062.3,3299.73);
   cutg->SetPoint(10,18997.1,3388.89);
   cutg->SetPoint(11,18931.8,3382.03);
   cutg->SetPoint(12,18908.8,3361.45);
   cutg->SetPoint(13,18881.9,3306.58);
   cutg->Draw("same");
}
