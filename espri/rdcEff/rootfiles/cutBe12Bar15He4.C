{
//========= Macro generated from object: Be12Bar15He4/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be12Bar15He4",14);
   cutg->SetVarX("0.5*(hodTRaw[0][15]+hodTRaw[1][15])");
   cutg->SetVarY("hodBarQCal[15]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,17936.3,490.415);
   cutg->SetPoint(1,17956.7,442.492);
   cutg->SetPoint(2,18091.5,474.441);
   cutg->SetPoint(3,18234.5,594.249);
   cutg->SetPoint(4,18320.3,722.045);
   cutg->SetPoint(5,18299.8,889.776);
   cutg->SetPoint(6,18234.5,977.636);
   cutg->SetPoint(7,18124.2,961.661);
   cutg->SetPoint(8,18018,809.904);
   cutg->SetPoint(9,17891.3,706.07);
   cutg->SetPoint(10,17854.6,578.275);
   cutg->SetPoint(11,17891.3,514.377);
   cutg->SetPoint(12,17891.3,514.377);
   cutg->SetPoint(13,17936.3,490.415);
   cutg->Draw("");
}
