{
//========= Macro generated from object: Be14Bar21Be10/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar21Be10",11);
   cutg->SetVarX("0.5*(hodTRaw[0][21]+hodTRaw[1][21])");
   cutg->SetVarY("hodBarQCal[21]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18104.1,2508.04);
   cutg->SetPoint(1,18084.6,2341.56);
   cutg->SetPoint(2,18084.6,2209.53);
   cutg->SetPoint(3,18107.4,2140.64);
   cutg->SetPoint(4,18159.5,2100.46);
   cutg->SetPoint(5,18214.9,2192.31);
   cutg->SetPoint(6,18228,2318.6);
   cutg->SetPoint(7,18195.4,2490.82);
   cutg->SetPoint(8,18153,2559.7);
   cutg->SetPoint(9,18107.4,2525.26);
   cutg->SetPoint(10,18104.1,2508.04);
   cutg->Draw("");
}
