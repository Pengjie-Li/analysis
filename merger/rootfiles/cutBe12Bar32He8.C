{
//========= Macro generated from object: Be12Bar32He8/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar32He8",10);
   cutg->SetVarX("0.5*(hodTRaw[0][32]+hodTRaw[1][32])");
   cutg->SetVarY("hodBarQCal[32]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1613.79,559.322);
   cutg->SetPoint(1,1723.35,601.695);
   cutg->SetPoint(2,1746.7,421.61);
   cutg->SetPoint(3,1714.37,432.203);
   cutg->SetPoint(4,1637.14,389.83);
   cutg->SetPoint(5,1610.2,474.576);
   cutg->SetPoint(6,1610.2,495.763);
   cutg->SetPoint(7,1613.79,527.542);
   cutg->SetPoint(8,1613.79,527.542);
   cutg->SetPoint(9,1613.79,559.322);
   cutg->Draw("");
}
