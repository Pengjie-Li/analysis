{
//========= Macro generated from object: Proton/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Proton",14);
   cutg->SetVarX("espriNaiEnergy");
   cutg->SetVarY("espriPlasDeltaE");
 
   //cutg->SetVarX("naiQ[0]");
   //cutg->SetVarY("plasQ[0]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,1.08696,20.9174);
   cutg->SetPoint(1,8.71655,15.8716);
   cutg->SetPoint(2,16.4507,12.2018);
   cutg->SetPoint(3,38.6079,7.15596);
   cutg->SetPoint(4,51.1497,5.95183);
   cutg->SetPoint(5,61.7057,5.0344);
   cutg->SetPoint(6,59.4064,2.74083);
   cutg->SetPoint(7,45.0878,3.88761);
   cutg->SetPoint(8,27.6338,5.66514);
   cutg->SetPoint(9,17.3913,7.7867);
   cutg->SetPoint(10,6.83528,12.6032);
   cutg->SetPoint(11,0.773411,17.305);
   cutg->SetPoint(12,0.668896,20.5734);
   cutg->SetPoint(13,1.08696,20.9174);
   cutg->Draw("");
}
