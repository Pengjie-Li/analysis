{
//========= Macro generated from object: Be14Bar17He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar17He4",8);
   cutg->SetVarX("0.5*(hodTRaw[0][17]+hodTRaw[1][17])");
   cutg->SetVarY("hodBarQCal[17]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,17984.2,786.92);
   cutg->SetPoint(1,18123.9,881.857);
   cutg->SetPoint(2,18150.8,786.92);
   cutg->SetPoint(3,18059.5,618.143);
   cutg->SetPoint(4,18005.7,618.143);
   cutg->SetPoint(5,17973.5,639.24);
   cutg->SetPoint(6,17989.6,786.92);
   cutg->SetPoint(7,17984.2,786.92);
   cutg->Draw("");
}
