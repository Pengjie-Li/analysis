{
//========= Macro generated from object: Be14Bar6He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar6He4",11);
   cutg->SetVarX("0.5*(hodTRaw[0][6]+hodTRaw[1][6])");
   cutg->SetVarY("hodBarQCal[6]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18376.4,913.502);
   cutg->SetPoint(1,18607.4,1103.38);
   cutg->SetPoint(2,18741.8,1156.12);
   cutg->SetPoint(3,18741.8,1018.99);
   cutg->SetPoint(4,18688,924.051);
   cutg->SetPoint(5,18628.9,850.211);
   cutg->SetPoint(6,18516.1,723.629);
   cutg->SetPoint(7,18457,744.726);
   cutg->SetPoint(8,18419.4,797.468);
   cutg->SetPoint(9,18403.3,892.405);
   cutg->SetPoint(10,18376.4,913.502);
   cutg->Draw("");
}
