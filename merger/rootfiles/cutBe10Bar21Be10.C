{
//========= Macro generated from object: Be10Bar21Be10/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be10Bar21Be10",15);
   cutg->SetVarX("0.5*(hodTRaw[0][21]+hodTRaw[1][21])");
   cutg->SetVarY("hodBarQCal[21]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18380,2867.58);
   cutg->SetPoint(1,18369,2742.01);
   cutg->SetPoint(2,18375.6,2690.64);
   cutg->SetPoint(3,18386.6,2530.82);
   cutg->SetPoint(4,18415.2,2433.79);
   cutg->SetPoint(5,18448.3,2428.08);
   cutg->SetPoint(6,18531.9,2530.82);
   cutg->SetPoint(7,18589.2,2644.98);
   cutg->SetPoint(8,18595.8,2753.42);
   cutg->SetPoint(9,18551.7,2867.58);
   cutg->SetPoint(10,18509.9,2867.58);
   cutg->SetPoint(11,18468.1,2873.29);
   cutg->SetPoint(12,18388.8,2884.7);
   cutg->SetPoint(13,18384.4,2879);
   cutg->SetPoint(14,18380,2867.58);
   cutg->Draw("");
}
