{
//========= Macro generated from object: Be12Bar34He8/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar34He8",8);
   cutg->SetVarX("0.5*(hodTRaw[0][34]+hodTRaw[1][34])");
   cutg->SetVarY("hodBarQCal[34]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1628.16,516.949);
   cutg->SetPoint(1,1732.33,654.661);
   cutg->SetPoint(2,1782.61,527.542);
   cutg->SetPoint(3,1746.7,368.644);
   cutg->SetPoint(4,1669.47,400.424);
   cutg->SetPoint(5,1633.55,453.39);
   cutg->SetPoint(6,1633.55,516.949);
   cutg->SetPoint(7,1628.16,516.949);
   cutg->Draw("");
}
