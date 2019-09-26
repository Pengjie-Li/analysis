{
//========= Macro generated from object: Be12Bar36He8/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be12Bar36He8",8);
   cutg->SetVarX("0.5*(hodTRaw[0][36]+hodTRaw[1][36])");
   cutg->SetVarY("hodBarQCal[36]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1647.92,315.678);
   cutg->SetPoint(1,1721.55,326.271);
   cutg->SetPoint(2,1723.35,569.915);
   cutg->SetPoint(3,1646.12,527.542);
   cutg->SetPoint(4,1617.39,474.576);
   cutg->SetPoint(5,1633.55,358.051);
   cutg->SetPoint(6,1642.53,326.271);
   cutg->SetPoint(7,1647.92,315.678);
   cutg->Draw("");
}
