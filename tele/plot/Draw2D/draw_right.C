{
        //TEllipse *Si1 = new TEllipse(0.0,0.0,15.0,15.0);
        //double x=4.95767e+01;double y=3.05135e+01;
        double x=4.85003e+01;double y=3.04654e+01;
        TEllipse *Si1 = new TEllipse(x,y,15.0,15.0);
        Si1->SetLineStyle(9);
        Si1->SetLineWidth(2);
        Si1->SetFillStyle(0);
        Si1->Draw("same");

        TEllipse *Si2 = new TEllipse(x,y,30,30);
        Si2->SetLineStyle(9);
        Si2->SetLineWidth(2);
        Si2->SetFillStyle(0);
        Si2->SetLineColor(5);
        Si2->Draw("same");



}

