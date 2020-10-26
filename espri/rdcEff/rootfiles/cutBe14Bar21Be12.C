{
//========= Macro generated from object: Be14Bar21Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar21Be12",13);
   cutg->SetVarX("0.5*(hodTRaw[0][21]+hodTRaw[1][21])");
   cutg->SetVarY("hodBarQCal[21]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18367.6,2908.78);
   cutg->SetPoint(1,18452,2991.08);
   cutg->SetPoint(2,18548,2874.49);
   cutg->SetPoint(3,18586.4,2716.74);
   cutg->SetPoint(4,18590.2,2510.97);
   cutg->SetPoint(5,18452,2462.96);
   cutg->SetPoint(6,18394.4,2462.96);
   cutg->SetPoint(7,18371.4,2517.83);
   cutg->SetPoint(8,18352.2,2613.85);
   cutg->SetPoint(9,18356.1,2744.17);
   cutg->SetPoint(10,18363.7,2895.06);
   cutg->SetPoint(11,18363.7,2895.06);
   cutg->SetPoint(12,18367.6,2908.78);
   cutg->Draw("same");
}
