{
//========= Macro generated from object: Be14Bar32Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar32Be14",12);
   cutg->SetVarX("0.5*(hodTRaw[0][32]+hodTRaw[1][32])");
   cutg->SetVarY("hodBarQCal[32]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1604.92,1731.31);
   cutg->SetPoint(1,1576.93,1573.6);
   cutg->SetPoint(2,1588.51,1404.21);
   cutg->SetPoint(3,1605.89,1334.11);
   cutg->SetPoint(4,1648.36,1380.84);
   cutg->SetPoint(5,1669.59,1433.41);
   cutg->SetPoint(6,1688.9,1608.64);
   cutg->SetPoint(7,1670.56,1742.99);
   cutg->SetPoint(8,1653.19,1795.56);
   cutg->SetPoint(9,1625.19,1760.51);
   cutg->SetPoint(10,1604.92,1725.47);
   cutg->SetPoint(11,1604.92,1731.31);
   cutg->Draw("");
}
