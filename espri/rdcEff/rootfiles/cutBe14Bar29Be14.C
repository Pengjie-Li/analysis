{
//========= Macro generated from object: Be14Bar29Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar29Be14",11);
   cutg->SetVarX("0.5*(hodTRaw[0][29]+hodTRaw[1][29])");
   cutg->SetVarY("hodBarQCal[29]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1561.37,1672.19);
   cutg->SetPoint(1,1661.23,1632.45);
   cutg->SetPoint(2,1703.52,1711.92);
   cutg->SetPoint(3,1719.97,3175.5);
   cutg->SetPoint(4,1670.63,3526.49);
   cutg->SetPoint(5,1598.97,3307.95);
   cutg->SetPoint(6,1559.02,3016.56);
   cutg->SetPoint(7,1549.62,2241.72);
   cutg->SetPoint(8,1543.75,1758.28);
   cutg->SetPoint(9,1555.5,1698.68);
   cutg->SetPoint(10,1561.37,1672.19);
   cutg->Draw("same");
}
