{
//========= Macro generated from object: Be14Bar21He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar21He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][21]+hodTRaw[1][21])");
   cutg->SetVarY("hodBarQCal[21]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18461.9,797.359);
   cutg->SetPoint(1,18504.6,791.619);
   cutg->SetPoint(2,18611.2,900.689);
   cutg->SetPoint(3,18568.5,1049.94);
   cutg->SetPoint(4,18458.9,1090.13);
   cutg->SetPoint(5,18404,1015.5);
   cutg->SetPoint(6,18373.6,952.354);
   cutg->SetPoint(7,18458.9,803.1);
   cutg->SetPoint(8,18370.5,871.986);
   cutg->SetPoint(9,18461.9,797.359);
   cutg->Draw("");
}
