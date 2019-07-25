{
//========= Macro generated from object: Bar18Be10/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Bar18Be10",8);
   cutg->SetVarX("0.5*(hodTRaw[0][18]+hodTRaw[1][18])");
   cutg->SetVarY("hodBarQCal[18]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18232.1,2519.41);
   cutg->SetPoint(1,18302.5,2644.98);
   cutg->SetPoint(2,18365.1,2576.48);
   cutg->SetPoint(3,18347.5,2245.43);
   cutg->SetPoint(4,18283,2228.31);
   cutg->SetPoint(5,18249.7,2336.76);
   cutg->SetPoint(6,18240,2507.99);
   cutg->SetPoint(7,18232.1,2519.41);
   cutg->Draw("");
}
