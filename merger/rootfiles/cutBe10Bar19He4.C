{
//========= Macro generated from object: Be10Bar19He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar19He4",10);
   cutg->SetVarX("0.5*(hodTRaw[0][19]+hodTRaw[1][19])");
   cutg->SetVarY("hodBarQCal[19]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18163.7,935.132);
   cutg->SetPoint(1,18138.3,780.138);
   cutg->SetPoint(2,18170.1,653.846);
   cutg->SetPoint(3,18227.2,613.662);
   cutg->SetPoint(4,18293.8,682.549);
   cutg->SetPoint(5,18325.5,768.657);
   cutg->SetPoint(6,18255.7,923.651);
   cutg->SetPoint(7,18233.5,940.873);
   cutg->SetPoint(8,18173.2,958.094);
   cutg->SetPoint(9,18163.7,935.132);
   cutg->Draw("");
}
