{
//========= Macro generated from object: Be14Bar21Be11/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar21Be11",12);
   cutg->SetVarX("0.5*(hodTRaw[0][21]+hodTRaw[1][21])");
   cutg->SetVarY("hodBarQCal[21]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18244.2,2680.25);
   cutg->SetPoint(1,18234.5,2508.04);
   cutg->SetPoint(2,18237.7,2381.75);
   cutg->SetPoint(3,18280.1,2335.82);
   cutg->SetPoint(4,18309.4,2324.34);
   cutg->SetPoint(5,18364.8,2404.71);
   cutg->SetPoint(6,18368,2479.33);
   cutg->SetPoint(7,18358.3,2571.18);
   cutg->SetPoint(8,18312.7,2691.73);
   cutg->SetPoint(9,18263.8,2708.96);
   cutg->SetPoint(10,18250.8,2680.25);
   cutg->SetPoint(11,18244.2,2680.25);
   cutg->Draw("");
}
