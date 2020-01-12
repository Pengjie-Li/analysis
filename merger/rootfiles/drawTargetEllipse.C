{
        double targetx=2.0;
        double targety=-1.10;
        //double targety=-1.50;
        //double targety=-1.60;
	double outerRadius = 16;

//        TEllipse *Si1 = new TEllipse(targetx,targety,outerRadius,outerRadius);
//        Si1->SetLineColor(2);
//        Si1->SetLineWidth(2);
//        Si1->SetFillStyle(0);
//        Si1->SetLineStyle(2);
//        Si1->Draw("same");
////        Si1->Draw();
//
//        Double_t targetRadius=15;
//        TEllipse *Si2 = new TEllipse(targetx,targety,targetRadius,targetRadius);
//        Si2->SetLineColor(2);
//        Si2->SetLineWidth(2);
//        Si2->SetFillStyle(0);
//        Si2->SetLineStyle(1);
//        Si2->Draw("same");
//
//        Double_t selectRadius=13;
//        TEllipse *Si3 = new TEllipse(targetx,targety,selectRadius,selectRadius);
//        Si3->SetLineColor(2);
//        Si3->SetLineWidth(2);
//        Si3->SetFillStyle(0);
//        Si3->SetLineStyle(2);
//        Si3->Draw("same");
//
//
        Double_t backRadius=21;
        TEllipse *Si = new TEllipse(targetx,targety,backRadius,backRadius);
        Si->SetLineColor(2);
        Si->SetLineWidth(2);
        Si->SetFillStyle(0);
        Si->SetLineStyle(2);
        Si->Draw("same");




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

	// draw text
//	TLatex l;
//	l.SetTextSize(0.025);
//	//l.SetTextAngle(30.);
//	l.SetTextAngle(0.);
//	//DrawLatex: xPos, yPos, Content
//	l.DrawLatex(0,-30,Form("(r1 = %g)",selectRadius));
//	l.DrawLatex(0,-33,Form("(r2 = %g)",targetRadius));
//	l.DrawLatex(0,-36,Form("(r3 = %g)",outerRadius));

}
