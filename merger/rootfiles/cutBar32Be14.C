{
//========= Macro generated from object: Bar32Be14/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("Bar32Be14",6);
   cutg->SetVarX("0.5*(hodTRaw[0][32]+hodTRaw[1][32])");
   cutg->SetVarY("hodBarQCal[32]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1588.77,1663.61);
   cutg->SetPoint(1,1588.77,1373.09);
   cutg->SetPoint(2,1649.68,1334.86);
   cutg->SetPoint(3,1648.36,1732.42);
   cutg->SetPoint(4,1587.45,1740.06);
   cutg->SetPoint(5,1588.77,1663.61);
   cutg->Draw("");
}
