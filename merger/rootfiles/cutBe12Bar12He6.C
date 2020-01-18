{
//========= Macro generated from object: Be12Bar12He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar12He6",13);
   cutg->SetVarX("0.5*(hodTRaw[0][12]+hodTRaw[1][12])");
   cutg->SetVarY("hodBarQCal[12]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18690.5,1199.2);
   cutg->SetPoint(1,18625.2,1090.13);
   cutg->SetPoint(2,18619.7,935.132);
   cutg->SetPoint(3,18674.2,866.246);
   cutg->SetPoint(4,18758.5,912.17);
   cutg->SetPoint(5,18842.9,1026.98);
   cutg->SetPoint(6,18845.6,1216.42);
   cutg->SetPoint(7,18777.6,1245.12);
   cutg->SetPoint(8,18706.8,1210.68);
   cutg->SetPoint(9,18690.5,1199.2);
   cutg->SetPoint(10,18682.3,1187.72);
   cutg->SetPoint(11,18682.3,1187.72);
   cutg->SetPoint(12,18690.5,1199.2);
   cutg->Draw("");
}
