{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar19Be12",8);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18316,2892.65);
   cutg->SetPoint(1,18351.3,2582.66);
   cutg->SetPoint(2,18425.6,2548.22);
   cutg->SetPoint(3,18466.7,2823.77);
   cutg->SetPoint(4,18435.4,3013.2);
   cutg->SetPoint(5,18384.5,3018.94);
   cutg->SetPoint(6,18331.7,2909.87);
   cutg->SetPoint(7,18316,2892.65);
   cutg->Draw("");
}
