{
//========= Macro generated from object: Be10Bar10Be10/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar10Be10",13);
   cutg->SetVarX("0.5*(hodTRaw[0][10]+hodTRaw[1][10])");
   cutg->SetVarY("hodBarQCal[10]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18914.3,3449.44);
   cutg->SetPoint(1,18851,3247.19);
   cutg->SetPoint(2,18841.1,3174.16);
   cutg->SetPoint(3,18844.4,3067.42);
   cutg->SetPoint(4,18947.5,3039.33);
   cutg->SetPoint(5,18997.4,3191.01);
   cutg->SetPoint(6,19020.7,3387.64);
   cutg->SetPoint(7,18990.8,3466.29);
   cutg->SetPoint(8,18947.5,3511.24);
   cutg->SetPoint(9,18924.2,3483.15);
   cutg->SetPoint(10,18917.6,3443.82);
   cutg->SetPoint(11,18914.3,3432.58);
   cutg->SetPoint(12,18914.3,3449.44);
   cutg->Draw("");
}
