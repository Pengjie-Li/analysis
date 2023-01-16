{
//========= Macro generated from object: Be10Bar31He6/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar31He6",9);
   cutg->SetVarX("0.5*(hodTRaw[0][31]+hodTRaw[1][31])");
   cutg->SetVarY("hodBarQCal[31]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1592.33,524.967);
   cutg->SetPoint(1,1664.96,544.678);
   cutg->SetPoint(2,1712.1,511.827);
   cutg->SetPoint(3,1700.64,432.983);
   cutg->SetPoint(4,1675.15,400.131);
   cutg->SetPoint(5,1611.44,360.71);
   cutg->SetPoint(6,1594.88,393.561);
   cutg->SetPoint(7,1594.88,478.975);
   cutg->SetPoint(8,1592.33,524.967);
   cutg->Draw("");
}
