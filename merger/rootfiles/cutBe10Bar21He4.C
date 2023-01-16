{
//========= Macro generated from object: Be10Bar21He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar21He4",13);
   cutg->SetVarX("0.5*(hodTRaw[0][21]+hodTRaw[1][21])");
   cutg->SetVarY("hodBarQCal[21]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18093.9,883.467);
   cutg->SetPoint(1,18052.7,826.062);
   cutg->SetPoint(2,18036.8,711.251);
   cutg->SetPoint(3,18052.7,630.884);
   cutg->SetPoint(4,18100.3,596.441);
   cutg->SetPoint(5,18154.2,579.219);
   cutg->SetPoint(6,18227.2,619.403);
   cutg->SetPoint(7,18249.4,739.954);
   cutg->SetPoint(8,18189.1,831.803);
   cutg->SetPoint(9,18125.6,860.505);
   cutg->SetPoint(10,18100.3,871.986);
   cutg->SetPoint(11,18090.7,871.986);
   cutg->SetPoint(12,18093.9,883.467);
   cutg->Draw("");
}
