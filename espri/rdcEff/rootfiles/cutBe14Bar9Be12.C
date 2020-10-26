{
//========= Macro generated from object: Be14Bar9Be12/Graph
//========= by ROOT version5.34/36
   
   cutg = new TCutG("Be14Bar9Be12",14);
   cutg->SetVarX("0.5*(hodTRaw[0][9]+hodTRaw[1][9])");
   cutg->SetVarY("hodBarQCal[9]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,19012.4,3498.63);
   cutg->SetPoint(1,18908.8,3292.87);
   cutg->SetPoint(2,18881.9,3121.4);
   cutg->SetPoint(3,18874.2,2977.37);
   cutg->SetPoint(4,18947.2,2956.79);
   cutg->SetPoint(5,19047,3025.38);
   cutg->SetPoint(6,19127.6,3162.55);
   cutg->SetPoint(7,19196.6,3258.57);
   cutg->SetPoint(8,19215.8,3409.47);
   cutg->SetPoint(9,19177.5,3567.22);
   cutg->SetPoint(10,19096.9,3574.07);
   cutg->SetPoint(11,19031.6,3532.92);
   cutg->SetPoint(12,19031.6,3532.92);
   cutg->SetPoint(13,19012.4,3498.63);
   cutg->Draw("same");
}
