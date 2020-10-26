{
//========= Macro generated from object: Be12Bar18He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar18He6",13);
   cutg->SetVarX("0.5*(hodTRaw[0][18]+hodTRaw[1][18])");
   cutg->SetVarY("hodBarQCal[18]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18478.2,728.473);
   cutg->SetPoint(1,18549,780.138);
   cutg->SetPoint(2,18608.9,883.467);
   cutg->SetPoint(3,18584.4,981.056);
   cutg->SetPoint(4,18524.5,986.797);
   cutg->SetPoint(5,18451,992.537);
   cutg->SetPoint(6,18429.2,883.467);
   cutg->SetPoint(7,18418.4,791.619);
   cutg->SetPoint(8,18440.1,762.916);
   cutg->SetPoint(9,18475.5,711.251);
   cutg->SetPoint(10,18500,728.473);
   cutg->SetPoint(11,18500,728.473);
   cutg->SetPoint(12,18478.2,728.473);
   cutg->Draw("");
}
