{
//========= Macro generated from object: Be10Bar11He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar11He4",12);
   cutg->SetVarX("0.5*(hodTRaw[0][11]+hodTRaw[1][11])");
   cutg->SetVarY("hodBarQCal[11]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18458.4,983.146);
   cutg->SetPoint(1,18371.9,904.494);
   cutg->SetPoint(2,18381.9,797.753);
   cutg->SetPoint(3,18411.8,752.809);
   cutg->SetPoint(4,18518.3,792.135);
   cutg->SetPoint(5,18601.5,904.494);
   cutg->SetPoint(6,18614.8,1000);
   cutg->SetPoint(7,18544.9,1033.71);
   cutg->SetPoint(8,18485,1016.85);
   cutg->SetPoint(9,18461.7,983.146);
   cutg->SetPoint(10,18451.8,977.528);
   cutg->SetPoint(11,18458.4,983.146);
   cutg->Draw("");
}
