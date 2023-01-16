{
//========= Macro generated from object: PRAngle/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("PRAngle",5);
   cutg->SetVarX("fdc0Angle");
   cutg->SetVarY("espriAngle");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,2.1,71.3501);
   cutg->SetPoint(1,3.23467,71.8078);
   cutg->SetPoint(2,5.16456,55.8467);
   cutg->SetPoint(3,4.3,55.8);
   cutg->SetPoint(4,2.1,71.3501);
   cutg->Draw("same");
}
