{
//========= Macro generated from object: Be14Bar8Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar8Be12",14);
   cutg->SetVarX("0.5*(hodTRaw[0][8]+hodTRaw[1][8])");
   cutg->SetVarY("hodBarQCal[8]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,19108.4,3443.76);
   cutg->SetPoint(1,18989.4,3169.41);
   cutg->SetPoint(2,18924.1,3025.38);
   cutg->SetPoint(3,18908.8,2943.07);
   cutg->SetPoint(4,18931.8,2874.49);
   cutg->SetPoint(5,19070,2895.06);
   cutg->SetPoint(6,19185.1,3032.24);
   cutg->SetPoint(7,19261.9,3203.7);
   cutg->SetPoint(8,19269.6,3354.6);
   cutg->SetPoint(9,19258.1,3436.9);
   cutg->SetPoint(10,19231.2,3532.92);
   cutg->SetPoint(11,19135.2,3478.05);
   cutg->SetPoint(12,19127.6,3464.33);
   cutg->SetPoint(13,19108.4,3443.76);
   cutg->Draw("same");
}
