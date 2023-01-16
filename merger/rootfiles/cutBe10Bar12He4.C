{
//========= Macro generated from object: Be10Bar12He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar12He4",10);
   cutg->SetVarX("0.5*(hodTRaw[0][12]+hodTRaw[1][12])");
   cutg->SetVarY("hodBarQCal[12]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18461.7,1044.94);
   cutg->SetPoint(1,18365.2,960.674);
   cutg->SetPoint(2,18348.6,853.933);
   cutg->SetPoint(3,18378.5,758.427);
   cutg->SetPoint(4,18458.4,764.045);
   cutg->SetPoint(5,18525,853.933);
   cutg->SetPoint(6,18551.6,1022.47);
   cutg->SetPoint(7,18495,1050.56);
   cutg->SetPoint(8,18465.1,1033.71);
   cutg->SetPoint(9,18461.7,1044.94);
   cutg->Draw("");
}
