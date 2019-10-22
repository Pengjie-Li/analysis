{
//========= Macro generated from object: Be14Bar12He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar12He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][12]+hodTRaw[1][12])");
   cutg->SetVarY("hodBarQCal[12]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18818.1,1031.59);
   cutg->SetPoint(1,18946.1,1115.02);
   cutg->SetPoint(2,18995.9,1216.33);
   cutg->SetPoint(3,19017.2,1341.48);
   cutg->SetPoint(4,18921.2,1371.28);
   cutg->SetPoint(5,18839.5,1264);
   cutg->SetPoint(6,18764.8,1210.37);
   cutg->SetPoint(7,18775.5,1120.98);
   cutg->SetPoint(8,18811,1031.59);
   cutg->SetPoint(9,18818.1,1031.59);
   cutg->Draw("");
}
