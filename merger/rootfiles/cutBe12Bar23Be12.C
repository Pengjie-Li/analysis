{
//========= Macro generated from object: Bar23Be12/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar23Be12",8);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18181,2462.11);
   cutg->SetPoint(1,18192.7,2198.05);
   cutg->SetPoint(2,18284.7,2169.35);
   cutg->SetPoint(3,18323.9,2456.37);
   cutg->SetPoint(4,18273,2657.29);
   cutg->SetPoint(5,18182.9,2599.89);
   cutg->SetPoint(6,18179,2450.63);
   cutg->SetPoint(7,18181,2462.11);
   cutg->Draw("");
}
