{
//========= Macro generated from object: Be14Bar4He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar4He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][4]+hodTRaw[1][4])");
   cutg->SetVarY("hodBarQCal[4]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18478.5,924.051);
   cutg->SetPoint(1,18731,1113.92);
   cutg->SetPoint(2,18817,934.599);
   cutg->SetPoint(3,18720.3,797.468);
   cutg->SetPoint(4,18628.9,691.983);
   cutg->SetPoint(5,18553.7,660.338);
   cutg->SetPoint(6,18500,734.177);
   cutg->SetPoint(7,18462.4,860.759);
   cutg->SetPoint(8,18478.5,902.954);
   cutg->SetPoint(9,18500,945.148);
   cutg->SetPoint(10,18478.5,924.051);
   cutg->Draw("");
}
