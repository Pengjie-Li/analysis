{
//========= Macro generated from object: Be12Bar31He8/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar31He8",8);
   cutg->SetVarX("0.5*(hodTRaw[0][31]+hodTRaw[1][31])");
   cutg->SetVarY("hodBarQCal[31]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1608.41,538.136);
   cutg->SetPoint(1,1698.2,601.695);
   cutg->SetPoint(2,1726.94,516.949);
   cutg->SetPoint(3,1708.98,432.203);
   cutg->SetPoint(4,1638.94,379.237);
   cutg->SetPoint(5,1608.41,421.61);
   cutg->SetPoint(6,1610.2,538.136);
   cutg->SetPoint(7,1608.41,538.136);
   cutg->Draw("");
}
