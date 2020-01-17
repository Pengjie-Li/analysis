{
//========= Macro generated from object: Be10Bar9Be10/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar9Be10",12);
   cutg->SetVarX("0.5*(hodTRaw[0][9]+hodTRaw[1][9])");
   cutg->SetVarY("hodBarQCal[9]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18934.2,3443.82);
   cutg->SetPoint(1,18891,3297.75);
   cutg->SetPoint(2,18864.4,3106.74);
   cutg->SetPoint(3,18881,3022.47);
   cutg->SetPoint(4,18964.2,3011.24);
   cutg->SetPoint(5,19030.7,3112.36);
   cutg->SetPoint(6,19064,3269.66);
   cutg->SetPoint(7,19064,3443.82);
   cutg->SetPoint(8,18974.2,3483.15);
   cutg->SetPoint(9,18937.6,3438.2);
   cutg->SetPoint(10,18937.6,3438.2);
   cutg->SetPoint(11,18934.2,3443.82);
   cutg->Draw("");
}
