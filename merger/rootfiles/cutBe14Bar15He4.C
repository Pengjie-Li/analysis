{
//========= Macro generated from object: Be14Bar15He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar15He4",8);
   cutg->SetVarX("0.5*(hodTRaw[0][15]+hodTRaw[1][15])");
   cutg->SetVarY("hodBarQCal[15]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18059.5,765.823);
   cutg->SetPoint(1,18247.5,871.308);
   cutg->SetPoint(2,18263.6,702.532);
   cutg->SetPoint(3,18134.7,565.401);
   cutg->SetPoint(4,18059.5,544.304);
   cutg->SetPoint(5,18038,691.983);
   cutg->SetPoint(6,18064.8,786.92);
   cutg->SetPoint(7,18059.5,765.823);
   cutg->Draw("");
}
