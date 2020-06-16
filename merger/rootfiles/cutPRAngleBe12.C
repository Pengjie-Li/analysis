{
//========= Macro generated from object: PRAngle/Graph
//========= by ROOT version5.34/36
   
   TCutG *cutg = new TCutG("PRAngle",5);
   cutg->SetVarX("fdc0Angle");
   cutg->SetVarY("espriAngle");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1.97149,71.5503);
   cutg->SetPoint(1,3.62049,55.3032);
   cutg->SetPoint(2,4.45963,55.5892);
   cutg->SetPoint(3,2.81864,72.008);
   cutg->SetPoint(4,1.97149,71.5503);
   cutg->Draw("same");
}
