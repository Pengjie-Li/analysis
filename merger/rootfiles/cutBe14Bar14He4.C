{
//========= Macro generated from object: Be14Bar14He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar14He4",10);
   cutg->SetVarX("0.5*(hodTRaw[0][14]+hodTRaw[1][14])");
   cutg->SetVarY("hodBarQCal[14]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18054.1,755.274);
   cutg->SetPoint(1,18204.5,860.759);
   cutg->SetPoint(2,18306.6,797.468);
   cutg->SetPoint(3,18269,670.886);
   cutg->SetPoint(4,18156.2,554.852);
   cutg->SetPoint(5,18080.9,554.852);
   cutg->SetPoint(6,18064.8,575.949);
   cutg->SetPoint(7,18054.1,670.886);
   cutg->SetPoint(8,18070.2,786.92);
   cutg->SetPoint(9,18054.1,755.274);
   cutg->Draw("");
}
