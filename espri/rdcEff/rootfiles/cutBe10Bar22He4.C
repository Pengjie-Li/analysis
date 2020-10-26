{
//========= Macro generated from object: Be10Bar22He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar22He4",13);
   cutg->SetVarX("0.5*(hodTRaw[0][22]+hodTRaw[1][22])");
   cutg->SetVarY("hodBarQCal[22]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18049.5,797.359);
   cutg->SetPoint(1,18014.6,659.587);
   cutg->SetPoint(2,18030.5,590.7);
   cutg->SetPoint(3,18074.9,533.295);
   cutg->SetPoint(4,18138.3,539.036);
   cutg->SetPoint(5,18208.1,625.143);
   cutg->SetPoint(6,18230.3,671.068);
   cutg->SetPoint(7,18198.6,774.397);
   cutg->SetPoint(8,18163.7,808.84);
   cutg->SetPoint(9,18128.8,814.581);
   cutg->SetPoint(10,18081.2,826.062);
   cutg->SetPoint(11,18112.9,826.062);
   cutg->SetPoint(12,18049.5,797.359);
   cutg->Draw("");
}
