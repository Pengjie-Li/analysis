{
        //TEllipse *Si1 = new TEllipse(0.0,0.0,15.0,15.0);
        TEllipse *Si1 = new TEllipse(-2.13,-1.10,15.0,15.0);
        Si1->SetLineStyle(9);
        Si1->SetLineWidth(2);
        Si1->SetFillStyle(0);
        Si1->Draw("same");

        TEllipse *Si2 = new TEllipse(-2,-1,30,30);
        Si2->SetLineStyle(9);
        Si2->SetLineWidth(2);
        Si2->SetFillStyle(0);
        Si2->SetLineColor(5);
        Si2->Draw("same");


	TBox *b=new TBox(-32,-31,28,29);
        b->SetLineStyle(9);
        b->SetLineWidth(2);
        b->SetFillStyle(0);
        b->SetLineColor(2);
	b->Draw("same");
 

}

