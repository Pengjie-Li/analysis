{
//========= Macro generated from object: Be14Bar20Be10/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be14Bar20Be10",13);
   cutg->SetVarX("0.5*(hodTRaw[0][20]+hodTRaw[1][20])");
   cutg->SetVarY("hodBarQCal[20]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(2);
   cutg->SetPoint(0,18156.3,2421.93);
   cutg->SetPoint(1,18123.7,2341.56);
   cutg->SetPoint(2,18127,2221.01);
   cutg->SetPoint(3,18149.8,2140.64);
   cutg->SetPoint(4,18162.8,2077.5);
   cutg->SetPoint(5,18221.4,2060.28);
   cutg->SetPoint(6,18270.3,2123.42);
   cutg->SetPoint(7,18273.6,2198.05);
   cutg->SetPoint(8,18263.8,2335.82);
   cutg->SetPoint(9,18234.5,2427.67);
   cutg->SetPoint(10,18195.4,2450.63);
   cutg->SetPoint(11,18179.1,2444.89);
   cutg->SetPoint(12,18156.3,2421.93);
   cutg->Draw("");
}
