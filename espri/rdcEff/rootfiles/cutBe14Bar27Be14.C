{
//========= Macro generated from object: Be14Bar27Be14/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar27Be14",9);
   cutg->SetVarX("0.5*(hodTRaw[0][27]+hodTRaw[1][27])");
   cutg->SetVarY("hodBarQCal[27]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,1667.11,2778.15);
   cutg->SetPoint(1,1628.34,1976.82);
   cutg->SetPoint(2,1631.86,1559.6);
   cutg->SetPoint(3,1712.92,1705.3);
   cutg->SetPoint(4,1742.29,1903.97);
   cutg->SetPoint(5,1762.27,2605.96);
   cutg->SetPoint(6,1701.17,2850.99);
   cutg->SetPoint(7,1677.68,2844.37);
   cutg->SetPoint(8,1667.11,2778.15);
   cutg->Draw("same");
}
