{
//========= Macro generated from object: Be10Bar14Be10/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be10Bar14Be10",11);
   cutg->SetVarX("0.5*(hodTRaw[0][14]+hodTRaw[1][14])");
   cutg->SetVarY("hodBarQCal[14]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18725.7,2913.24);
   cutg->SetPoint(1,18675.1,2776.26);
   cutg->SetPoint(2,18653,2679.22);
   cutg->SetPoint(3,18683.9,2565.07);
   cutg->SetPoint(4,18763.1,2525.11);
   cutg->SetPoint(5,18767.5,2565.07);
   cutg->SetPoint(6,18813.8,2719.18);
   cutg->SetPoint(7,18824.8,2810.5);
   cutg->SetPoint(8,18769.7,2884.7);
   cutg->SetPoint(9,18738.9,2901.83);
   cutg->SetPoint(10,18725.7,2913.24);
   cutg->Draw("");
}
