{
//========= Macro generated from object: Be12Bar14He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be12Bar14He4",14);
   cutg->SetVarX("0.5*(hodTRaw[0][14]+hodTRaw[1][14])");
   cutg->SetVarY("hodBarQCal[14]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,17907.7,458.466);
   cutg->SetPoint(1,17973,394.569);
   cutg->SetPoint(2,18087.4,490.415);
   cutg->SetPoint(3,18222.2,610.224);
   cutg->SetPoint(4,18246.7,777.955);
   cutg->SetPoint(5,18242.6,865.815);
   cutg->SetPoint(6,18181.4,897.764);
   cutg->SetPoint(7,18062.9,833.866);
   cutg->SetPoint(8,17944.4,769.968);
   cutg->SetPoint(9,17891.3,698.083);
   cutg->SetPoint(10,17858.7,594.249);
   cutg->SetPoint(11,17870.9,498.403);
   cutg->SetPoint(12,17870.9,498.403);
   cutg->SetPoint(13,17907.7,458.466);
   cutg->Draw("");
}
