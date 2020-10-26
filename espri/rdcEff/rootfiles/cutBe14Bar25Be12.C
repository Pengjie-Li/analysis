{
//========= Macro generated from object: Be14Bar25Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar25Be12",13);
   cutg->SetVarX("0.5*(hodTRaw[0][25]+hodTRaw[1][25])");
   cutg->SetVarY("hodBarQCal[25]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1602.12,3567.22);
   cutg->SetPoint(1,1572.7,2764.75);
   cutg->SetPoint(2,1563.74,2572.7);
   cutg->SetPoint(3,1585.49,2408.09);
   cutg->SetPoint(4,1609.8,2387.52);
   cutg->SetPoint(5,1686.57,2991.08);
   cutg->SetPoint(6,1690.4,3196.85);
   cutg->SetPoint(7,1676.33,3498.63);
   cutg->SetPoint(8,1654.58,3683.81);
   cutg->SetPoint(9,1622.59,3711.25);
   cutg->SetPoint(10,1602.12,3628.94);
   cutg->SetPoint(11,1602.12,3628.94);
   cutg->SetPoint(12,1602.12,3567.22);
   cutg->Draw("same");
}
