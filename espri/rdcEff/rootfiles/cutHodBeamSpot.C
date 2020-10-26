{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("CUTG",8);
   cutg->SetVarX("0.5*(hodTRaw[0][10]+hodTRaw[1][10])");
   cutg->SetVarY("hodBarQCal[10]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18849.1,3232.56);
   cutg->SetPoint(1,18905.4,3459.3);
   cutg->SetPoint(2,18959.5,3488.37);
   cutg->SetPoint(3,19000,3337.21);
   cutg->SetPoint(4,18934.7,3087.21);
   cutg->SetPoint(5,18876.1,3069.77);
   cutg->SetPoint(6,18855.9,3220.93);
   cutg->SetPoint(7,18849.1,3232.56);
   cutg->Draw("");
}
