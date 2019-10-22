{
//========= Macro generated from object: Be14Bar17He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar17He6",9);
   cutg->SetVarX("0.5*(hodTRaw[0][17]+hodTRaw[1][17])");
   cutg->SetVarY("hodBarQCal[17]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18589.9,1038.46);
   cutg->SetPoint(1,18723.9,1067.16);
   cutg->SetPoint(2,18763.5,1199.2);
   cutg->SetPoint(3,18629.5,1296.79);
   cutg->SetPoint(4,18568.5,1216.42);
   cutg->SetPoint(5,18550.3,1124.57);
   cutg->SetPoint(6,18596,1026.98);
   cutg->SetPoint(7,18592.9,1026.98);
   cutg->SetPoint(8,18589.9,1038.46);
   cutg->Draw("");
}
