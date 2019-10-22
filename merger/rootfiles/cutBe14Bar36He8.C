{
//========= Macro generated from object: Be14Bar36He8/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar36He8",11);
   cutg->SetVarX("0.5*(hodTRaw[0][36]+hodTRaw[1][36])");
   cutg->SetVarY("hodBarQCal[36]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1630.44,458.668);
   cutg->SetPoint(1,1693.4,475.89);
   cutg->SetPoint(2,1743.16,498.852);
   cutg->SetPoint(3,1739.09,435.706);
   cutg->SetPoint(4,1725.89,395.522);
   cutg->SetPoint(5,1694.42,378.301);
   cutg->SetPoint(6,1652.78,372.56);
   cutg->SetPoint(7,1632.47,366.82);
   cutg->SetPoint(8,1629.43,429.966);
   cutg->SetPoint(9,1629.43,452.928);
   cutg->SetPoint(10,1630.44,458.668);
   cutg->Draw("");
}
