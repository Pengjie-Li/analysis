{
//========= Macro generated from object: Be14Bar30Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar30Be14",11);
   cutg->SetVarX("0.5*(hodTRaw[0][30]+hodTRaw[1][30])");
   cutg->SetVarY("hodBarQCal[30]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1480.31,1334.44);
   cutg->SetPoint(1,1602.49,1533.11);
   cutg->SetPoint(2,1618.94,2658.94);
   cutg->SetPoint(3,1610.71,3268.21);
   cutg->SetPoint(4,1578.99,3427.15);
   cutg->SetPoint(5,1519.08,3447.02);
   cutg->SetPoint(6,1467.39,2996.69);
   cutg->SetPoint(7,1419.22,1672.19);
   cutg->SetPoint(8,1446.24,1347.68);
   cutg->SetPoint(9,1469.74,1341.06);
   cutg->SetPoint(10,1480.31,1334.44);
   cutg->Draw("same");
}
