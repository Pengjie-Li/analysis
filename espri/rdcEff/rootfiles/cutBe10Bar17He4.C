{
//========= Macro generated from object: Be10Bar17He4/Graph
//========= by ROOT version5.34/20
   
   cutg = new TCutG("Be10Bar17He4",14);
   cutg->SetVarX("0.5*(hodTRaw[0][17]+hodTRaw[1][17])");
   cutg->SetVarY("hodBarQCal[17]");
   cutg->SetTitle("Graph");
   cutg->SetFillColor(1);
   cutg->SetPoint(0,18214.5,1067.16);
   cutg->SetPoint(1,18179.6,929.391);
   cutg->SetPoint(2,18192.3,837.543);
   cutg->SetPoint(3,18224,745.695);
   cutg->SetPoint(4,18281.1,716.992);
   cutg->SetPoint(5,18341.4,774.397);
   cutg->SetPoint(6,18363.6,808.84);
   cutg->SetPoint(7,18385.8,929.391);
   cutg->SetPoint(8,18344.5,1009.76);
   cutg->SetPoint(9,18303.3,1055.68);
   cutg->SetPoint(10,18258.9,1072.9);
   cutg->SetPoint(11,18227.2,1061.42);
   cutg->SetPoint(12,18224,1061.42);
   cutg->SetPoint(13,18214.5,1067.16);
   cutg->Draw("");
}
