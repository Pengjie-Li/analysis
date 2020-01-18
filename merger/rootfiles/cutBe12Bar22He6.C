{
//========= Macro generated from object: Be12Bar22He6/Graph
//========= by ROOT version6.08/04
   
   cutg = new TCutG("Be12Bar22He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][22]+hodTRaw[1][22])");
   cutg->SetVarY("hodBarQCal[22]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18211.2,648.738);
   cutg->SetPoint(1,18361.2,668.659);
   cutg->SetPoint(2,18440,774.9);
   cutg->SetPoint(3,18421.2,894.422);
   cutg->SetPoint(4,18308.7,867.862);
   cutg->SetPoint(5,18241.2,841.301);
   cutg->SetPoint(6,18233.7,788.181);
   cutg->SetPoint(7,18211.2,688.579);
   cutg->SetPoint(8,18207.5,655.378);
   cutg->SetPoint(9,18211.2,648.738);
   cutg->Draw("");
}
