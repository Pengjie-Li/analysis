{
//========= Macro generated from object: Be14Bar19He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar19He4",10);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,17880.1,539.036);
   cutg->SetPoint(1,18035.4,539.036);
   cutg->SetPoint(2,18078.1,694.03);
   cutg->SetPoint(3,18044.6,768.657);
   cutg->SetPoint(4,17928.8,757.176);
   cutg->SetPoint(5,17837.4,722.732);
   cutg->SetPoint(6,17794.8,630.884);
   cutg->SetPoint(7,17828.3,527.555);
   cutg->SetPoint(8,17889.2,533.295);
   cutg->SetPoint(9,17880.1,539.036);
   cutg->Draw("");
}
