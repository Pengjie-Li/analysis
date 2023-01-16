{
//========= Macro generated from object: Be12Bar23He6/Graph
//========= by ROOT version6.08/04
   
   cutg = new TCutG("Be12Bar23He6",11);
   cutg->SetVarX("0.5*(hodTRaw[0][23]+hodTRaw[1][23])");
   cutg->SetVarY("hodBarQCal[23]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18233.7,947.543);
   cutg->SetPoint(1,18173.7,867.862);
   cutg->SetPoint(2,18177.5,768.26);
   cutg->SetPoint(3,18218.7,675.299);
   cutg->SetPoint(4,18312.5,628.818);
   cutg->SetPoint(5,18368.7,741.7);
   cutg->SetPoint(6,18380,841.301);
   cutg->SetPoint(7,18316.2,927.623);
   cutg->SetPoint(8,18256.2,947.543);
   cutg->SetPoint(9,18237.5,940.903);
   cutg->SetPoint(10,18233.7,947.543);
   cutg->Draw("");
}
