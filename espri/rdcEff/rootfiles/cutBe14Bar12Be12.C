{
//========= Macro generated from object: Be14Bar12Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar12Be12",15);
   cutg->SetVarX("0.5*(hodTRaw[0][12]+hodTRaw[1][12])");
   cutg->SetVarY("hodBarQCal[12]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18866.6,3388.89);
   cutg->SetPoint(1,18751.4,3196.85);
   cutg->SetPoint(2,18751.4,3039.09);
   cutg->SetPoint(3,18755.2,2874.49);
   cutg->SetPoint(4,18805.1,2867.63);
   cutg->SetPoint(5,18881.9,2949.93);
   cutg->SetPoint(6,18958.7,3018.52);
   cutg->SetPoint(7,19023.9,3018.52);
   cutg->SetPoint(8,19085.3,3087.11);
   cutg->SetPoint(9,19081.5,3272.29);
   cutg->SetPoint(10,19008.6,3279.15);
   cutg->SetPoint(11,19008.6,3388.89);
   cutg->SetPoint(12,18943.3,3450.62);
   cutg->SetPoint(13,18897.3,3423.18);
   cutg->SetPoint(14,18866.6,3388.89);
   cutg->Draw("same");
}
