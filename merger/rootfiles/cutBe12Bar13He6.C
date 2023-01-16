{
//========= Macro generated from object: Be12Bar13He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar13He6",13);
   cutg->SetVarX("0.5*(hodTRaw[0][13]+hodTRaw[1][13])");
   cutg->SetVarY("hodBarQCal[13]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18478.2,728.473);
   cutg->SetPoint(1,18551.7,986.797);
   cutg->SetPoint(2,18573.5,849.024);
   cutg->SetPoint(3,18647,808.84);
   cutg->SetPoint(4,18728.6,854.765);
   cutg->SetPoint(5,18791.2,946.613);
   cutg->SetPoint(6,18785.7,1136.05);
   cutg->SetPoint(7,18715,1199.2);
   cutg->SetPoint(8,18657.8,1193.46);
   cutg->SetPoint(9,18622.5,1181.97);
   cutg->SetPoint(10,18614.3,1164.75);
   cutg->SetPoint(11,18614.3,1164.75);
   cutg->SetPoint(12,18478.2,728.473);
   cutg->Draw("");
}
