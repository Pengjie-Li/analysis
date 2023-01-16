{
//========= Macro generated from object: Be14Bar19He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar19He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18507.6,929.391);
   cutg->SetPoint(1,18623.4,871.986);
   cutg->SetPoint(2,18675.2,1072.9);
   cutg->SetPoint(3,18602.1,1181.97);
   cutg->SetPoint(4,18538.1,1164.75);
   cutg->SetPoint(5,18465,1067.16);
   cutg->SetPoint(6,18477.2,952.354);
   cutg->SetPoint(7,18507.6,917.91);
   cutg->SetPoint(8,18513.7,917.91);
   cutg->SetPoint(9,18507.6,929.391);
   cutg->Draw("");
}
