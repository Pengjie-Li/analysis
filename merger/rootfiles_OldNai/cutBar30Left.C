{
//========= Macro generated from object: Bar30Left/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Bar30Left",8);
   cutg->SetVarX("0.5*(hodTRaw[0][30]+hodTRaw[1][30])");
   cutg->SetVarY("hodBarQCal[30]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1274,2005.12);
   cutg->SetPoint(1,1476.97,2154.3);
   cutg->SetPoint(2,1482.31,1518.89);
   cutg->SetPoint(3,1389.73,1369.71);
   cutg->SetPoint(4,1257.98,1491.27);
   cutg->SetPoint(5,1234.83,1850.41);
   cutg->SetPoint(6,1252.64,1966.44);
   cutg->SetPoint(7,1274,2005.12);
   cutg->Draw("");
}
