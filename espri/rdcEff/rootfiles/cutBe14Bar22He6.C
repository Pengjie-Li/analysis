{
//========= Macro generated from object: Be14Bar22He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar22He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][22]+hodTRaw[1][22])");
   cutg->SetVarY("hodBarQCal[22]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18303.5,780.138);
   cutg->SetPoint(1,18498.5,745.695);
   cutg->SetPoint(2,18571.6,843.284);
   cutg->SetPoint(3,18504.6,923.651);
   cutg->SetPoint(4,18376.6,929.391);
   cutg->SetPoint(5,18303.5,923.651);
   cutg->SetPoint(6,18279.1,854.765);
   cutg->SetPoint(7,18294.4,785.878);
   cutg->SetPoint(8,18309.6,768.657);
   cutg->SetPoint(9,18303.5,780.138);
   cutg->Draw("");
}
