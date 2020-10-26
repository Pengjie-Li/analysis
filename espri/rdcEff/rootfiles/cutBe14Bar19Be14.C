{
//========= Macro generated from object: Be14Bar19Be14/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar19Be14",14);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18814.4,3483.93);
   cutg->SetPoint(1,18794.9,3254.31);
   cutg->SetPoint(2,18814.4,3070.61);
   cutg->SetPoint(3,18847,3036.17);
   cutg->SetPoint(4,18873,3036.17);
   cutg->SetPoint(5,18899.1,3145.24);
   cutg->SetPoint(6,18915.4,3317.45);
   cutg->SetPoint(7,18921.9,3518.37);
   cutg->SetPoint(8,18899.1,3570.03);
   cutg->SetPoint(9,18869.8,3558.55);
   cutg->SetPoint(10,18843.7,3518.37);
   cutg->SetPoint(11,18824.2,3495.41);
   cutg->SetPoint(12,18807.9,3472.45);
   cutg->SetPoint(13,18814.4,3483.93);
   cutg->Draw("");
}
