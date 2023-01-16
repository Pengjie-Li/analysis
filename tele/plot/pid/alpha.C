{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version5.34/20
   
   TCutG *cutg = new TCutG("alpha",10);
   cutg->SetVarX("CsI_LRB_E");
   cutg->SetVarY("SiLB_E[26]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetLineColor(2);
   cutg->SetLineWidth(3);
   cutg->SetPoint(0,72.6652,23340.5);
   cutg->SetPoint(1,199.102,15361.1);
   cutg->SetPoint(2,351.221,11336.8);
   cutg->SetPoint(3,613.973,7381.78);
   cutg->SetPoint(4,511.243,6757.31);
   cutg->SetPoint(5,343.319,8908.26);
   cutg->SetPoint(6,181.322,13418.3);
   cutg->SetPoint(7,33.1537,22299.7);
   cutg->SetPoint(8,68.7141,23340.5);
   cutg->SetPoint(9,72.6652,23340.5);
   cutg->Draw("same");
}
