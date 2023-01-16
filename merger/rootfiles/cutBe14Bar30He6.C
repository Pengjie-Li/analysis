{
//========= Macro generated from object: Be14Bar30He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar30He6",12);
   cutg->SetVarX("0.5*(hodTRaw[0][30]+hodTRaw[1][30])");
   cutg->SetVarY("hodBarQCal[30]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1414.16,508.533);
   cutg->SetPoint(1,1408.06,454.544);
   cutg->SetPoint(2,1420.25,418.223);
   cutg->SetPoint(3,1430.4,395.646);
   cutg->SetPoint(4,1443.6,398.591);
   cutg->SetPoint(5,1465.94,434.911);
   cutg->SetPoint(6,1457.82,485.956);
   cutg->SetPoint(7,1453.76,526.203);
   cutg->SetPoint(8,1428.37,530.129);
   cutg->SetPoint(9,1418.22,516.386);
   cutg->SetPoint(10,1417.2,510.497);
   cutg->SetPoint(11,1414.16,508.533);
   cutg->Draw("");
}
