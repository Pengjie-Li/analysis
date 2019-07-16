{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("CUTG",8);
   cutg->SetVarX("0.5*(hodTRaw[0][31]+hodTRaw[1][31])");
   cutg->SetVarY("hodBarQCal[31]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1330.87,1621.1);
   cutg->SetPoint(1,1566.1,1547.87);
   cutg->SetPoint(2,1583.59,1312.47);
   cutg->SetPoint(3,1537.91,1139.85);
   cutg->SetPoint(4,1368.78,1103.23);
   cutg->SetPoint(5,1334.76,1343.86);
   cutg->SetPoint(6,1332.82,1631.57);
   cutg->SetPoint(7,1330.87,1621.1);
   cutg->Draw("");
}
