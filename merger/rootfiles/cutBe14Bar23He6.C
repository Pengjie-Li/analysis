{
//========= Macro generated from object: Be14Bar23He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar23He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18373.6,785.878);
   cutg->SetPoint(1,18440.6,768.657);
   cutg->SetPoint(2,18480.2,814.581);
   cutg->SetPoint(3,18480.2,940.873);
   cutg->SetPoint(4,18407.1,992.537);
   cutg->SetPoint(5,18349.2,952.354);
   cutg->SetPoint(6,18330.9,871.986);
   cutg->SetPoint(7,18355.3,768.657);
   cutg->SetPoint(8,18388.8,762.916);
   cutg->SetPoint(9,18373.6,785.878);
   cutg->Draw("");
}
