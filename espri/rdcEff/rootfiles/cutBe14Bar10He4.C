{
//========= Macro generated from object: Be14Bar10He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar10He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][10]+hodTRaw[1][10])");
   cutg->SetVarY("hodBarQCal[10]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18123.9,776.371);
   cutg->SetPoint(1,18295.8,945.148);
   cutg->SetPoint(2,18430.2,1008.44);
   cutg->SetPoint(3,18462.4,987.342);
   cutg->SetPoint(4,18435.5,808.017);
   cutg->SetPoint(5,18295.8,649.789);
   cutg->SetPoint(6,18209.9,597.046);
   cutg->SetPoint(7,18172.3,691.983);
   cutg->SetPoint(8,18145.4,786.92);
   cutg->SetPoint(9,18145.4,786.92);
   cutg->SetPoint(10,18123.9,776.371);
   cutg->Draw("");
}
