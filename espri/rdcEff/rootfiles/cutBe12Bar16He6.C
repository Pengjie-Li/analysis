{
//========= Macro generated from object: Be12Bar16He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar16He6",11);
   cutg->SetVarX("0.5*(hodTRaw[0][16]+hodTRaw[1][16])");
   cutg->SetVarY("hodBarQCal[16]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18521.8,969.575);
   cutg->SetPoint(1,18491.8,923.651);
   cutg->SetPoint(2,18491.8,814.581);
   cutg->SetPoint(3,18524.5,757.176);
   cutg->SetPoint(4,18614.3,774.397);
   cutg->SetPoint(5,18666,866.246);
   cutg->SetPoint(6,18663.3,969.575);
   cutg->SetPoint(7,18589.8,992.537);
   cutg->SetPoint(8,18535.4,981.056);
   cutg->SetPoint(9,18524.5,975.316);
   cutg->SetPoint(10,18521.8,969.575);
   cutg->Draw("");
}
