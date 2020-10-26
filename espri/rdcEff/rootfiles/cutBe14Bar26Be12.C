{
//========= Macro generated from object: Be14Bar26Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar26Be12",11);
   cutg->SetVarX("0.5*(hodTRaw[0][26]+hodTRaw[1][26])");
   cutg->SetVarY("hodBarQCal[26]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1589.33,3683.81);
   cutg->SetPoint(1,1570.14,2812.76);
   cutg->SetPoint(2,1552.23,2380.66);
   cutg->SetPoint(3,1567.58,2222.91);
   cutg->SetPoint(4,1585.49,2154.32);
   cutg->SetPoint(5,1677.61,3244.86);
   cutg->SetPoint(6,1684.01,3587.79);
   cutg->SetPoint(7,1646.9,3704.39);
   cutg->SetPoint(8,1613.64,3718.11);
   cutg->SetPoint(9,1603.4,3704.39);
   cutg->SetPoint(10,1589.33,3683.81);
   cutg->Draw("same");
}
