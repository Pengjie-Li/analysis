{
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version5.34/20
   
   TCutG *dcutg = new TCutG("dalpha",10);
   dcutg->SetVarX("CsI_LRB_E");
   dcutg->SetVarY("SiLB_E[26]");
   dcutg->SetTitle("Graph");
   dcutg->SetFillColor(1);
   dcutg->SetLineColor(2);
   dcutg->SetLineWidth(3);
   dcutg->SetPoint(0,72.6652,23340.5);
   dcutg->SetPoint(1,199.102,15361.1);
   dcutg->SetPoint(2,351.221,11336.8);
   dcutg->SetPoint(3,613.973,7381.78);
   dcutg->SetPoint(4,511.243,6757.31);
   dcutg->SetPoint(5,343.319,8908.26);
   dcutg->SetPoint(6,181.322,13418.3);
   dcutg->SetPoint(7,33.1537,22299.7);
   dcutg->SetPoint(8,68.7141,23340.5);
   dcutg->SetPoint(9,72.6652,23340.5);
   dcutg->Draw("same");
}
