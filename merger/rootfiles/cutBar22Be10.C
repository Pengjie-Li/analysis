{
//========= Macro generated from object: Bar22Be10/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Bar22Be10",9);
   cutg->SetVarX("0.5*(hodTRaw[0][22]+hodTRaw[1][22])");
   cutg->SetVarY("hodBarQCal[22]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18079.6,2245.43);
   cutg->SetPoint(1,18130.5,2319.63);
   cutg->SetPoint(2,18187.2,2239.73);
   cutg->SetPoint(3,18185.2,2068.49);
   cutg->SetPoint(4,18152,1988.58);
   cutg->SetPoint(5,18093.3,2028.54);
   cutg->SetPoint(6,18073.8,2131.28);
   cutg->SetPoint(7,18114.8,2234.02);
   cutg->SetPoint(8,18079.6,2245.43);
   cutg->Draw("");
}
