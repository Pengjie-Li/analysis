{
//========= Macro generated from object: Be14Bar31He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar31He6",11);
   cutg->SetVarX("0.5*(hodTRaw[0][31]+hodTRaw[1][31])");
   cutg->SetVarY("hodBarQCal[31]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1519.76,274.971);
   cutg->SetPoint(1,1524.84,303.674);
   cutg->SetPoint(2,1528.9,395.522);
   cutg->SetPoint(3,1512.65,447.187);
   cutg->SetPoint(4,1498.44,435.706);
   cutg->SetPoint(5,1488.28,407.003);
   cutg->SetPoint(6,1486.25,361.079);
   cutg->SetPoint(7,1497.42,303.674);
   cutg->SetPoint(8,1513.67,292.193);
   cutg->SetPoint(9,1519.76,309.414);
   cutg->SetPoint(10,1519.76,274.971);
   cutg->Draw("");
}
