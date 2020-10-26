{
//========= Macro generated from object: Be14Bar14He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar14He6",10);
   cutg->SetVarX("0.5*(hodTRaw[0][14]+hodTRaw[1][14])");
   cutg->SetVarY("hodBarQCal[14]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18779,930.274);
   cutg->SetPoint(1,18853.7,948.153);
   cutg->SetPoint(2,18924.8,1067.34);
   cutg->SetPoint(3,18892.8,1204.41);
   cutg->SetPoint(4,18764.8,1186.53);
   cutg->SetPoint(5,18711.5,1115.02);
   cutg->SetPoint(6,18686.6,1007.75);
   cutg->SetPoint(7,18697.3,942.193);
   cutg->SetPoint(8,18779,924.315);
   cutg->SetPoint(9,18779,930.274);
   cutg->Draw("");
}
