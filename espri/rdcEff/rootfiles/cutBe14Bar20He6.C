{
//========= Macro generated from object: Be14Bar20He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar20He6",8);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18434.5,814.581);
   cutg->SetPoint(1,18620.3,785.878);
   cutg->SetPoint(2,18653.8,952.354);
   cutg->SetPoint(3,18592.9,1055.68);
   cutg->SetPoint(4,18440.6,975.316);
   cutg->SetPoint(5,18404,952.354);
   cutg->SetPoint(6,18437.6,814.581);
   cutg->SetPoint(7,18434.5,814.581);
   cutg->Draw("");
}
