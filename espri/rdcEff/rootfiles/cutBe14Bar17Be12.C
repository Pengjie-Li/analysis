{
//========= Macro generated from object: Be14Bar17Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar17Be12",14);
   cutg->SetVarX("0.5*(hodTRaw[0][17]+hodTRaw[1][17])");
   cutg->SetVarY("hodBarQCal[17]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18601.7,3292.87);
   cutg->SetPoint(1,18528.8,3155.69);
   cutg->SetPoint(2,18517.3,3018.52);
   cutg->SetPoint(3,18528.8,2867.63);
   cutg->SetPoint(4,18574.8,2819.62);
   cutg->SetPoint(5,18674.6,2943.07);
   cutg->SetPoint(6,18797.5,2970.51);
   cutg->SetPoint(7,18820.5,3183.13);
   cutg->SetPoint(8,18782.1,3320.3);
   cutg->SetPoint(9,18690,3395.75);
   cutg->SetPoint(10,18620.9,3416.32);
   cutg->SetPoint(11,18609.4,3340.88);
   cutg->SetPoint(12,18609.4,3340.88);
   cutg->SetPoint(13,18601.7,3292.87);
   cutg->Draw("same");
}
