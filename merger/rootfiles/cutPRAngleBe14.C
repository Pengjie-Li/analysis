{
//========= Macro generated from object: PRAngle/Graph
//========= by ROOT version5.34/36
   
   TCutG *cutg = new TCutG("PRAngle",5);
   cutg->SetVarX("fdc0Angle");
   cutg->SetVarY("espriAngle");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1.59414,72.0938);
   cutg->SetPoint(1,3.08875,55.532);
   cutg->SetPoint(2,3.91664,55.6178);
   cutg->SetPoint(3,2.38351,72.7517);
   cutg->SetPoint(4,1.59414,72.0938);
   cutg->Draw("same");
}
