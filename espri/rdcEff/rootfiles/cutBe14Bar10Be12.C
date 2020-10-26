{
//========= Macro generated from object: Be14Bar10Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar10Be12",14);
   cutg->SetVarX("0.5*(hodTRaw[0][10]+hodTRaw[1][10])");
   cutg->SetVarY("hodBarQCal[10]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18966.4,3526.06);
   cutg->SetPoint(1,18866.6,3320.3);
   cutg->SetPoint(2,18847.4,3141.98);
   cutg->SetPoint(3,18839.7,2970.51);
   cutg->SetPoint(4,18943.3,2977.37);
   cutg->SetPoint(5,19020.1,3114.54);
   cutg->SetPoint(6,19104.5,3210.56);
   cutg->SetPoint(7,19154.4,3340.88);
   cutg->SetPoint(8,19135.2,3505.49);
   cutg->SetPoint(9,19085.3,3574.07);
   cutg->SetPoint(10,19047,3615.23);
   cutg->SetPoint(11,18997.1,3574.07);
   cutg->SetPoint(12,18997.1,3574.07);
   cutg->SetPoint(13,18966.4,3526.06);
   cutg->Draw("same");
}
