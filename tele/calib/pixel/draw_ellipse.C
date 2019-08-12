{
        double targetx=-2.13;
        //double targety=-1.10;
        //double targety=-1.50;
        double targety=-1.60;
        TEllipse *Si1 = new TEllipse(targetx,targety,15.0,15.0);
        Si1->SetLineStyle(9);
        Si1->SetLineWidth(2);
        Si1->SetFillStyle(0);
        Si1->Draw("same");
//        Si1->Draw();

        Double_t R2=21;
        TEllipse *Si2 = new TEllipse(targetx,targety,R2,R2);
        Si2->SetLineStyle(9);
        Si2->SetLineWidth(2);
        Si2->SetFillStyle(0);
        Si2->SetLineColor(5);
        Si2->Draw("same");


	TBox *b=new TBox(targetx-30,targety-35,targetx+30,targety+25);
        b->SetLineStyle(9);
        b->SetLineWidth(2);
        b->SetFillStyle(0);
        b->SetLineColor(2);
	b->Draw("same");

	TBox *bneck=new TBox(targetx-4,targety+15,targetx+4,targety+25);
        bneck->SetLineStyle(9);
        bneck->SetLineWidth(2);
        bneck->SetFillStyle(0);
        bneck->SetLineColor(2);
	bneck->Draw("same");
 

 

}

