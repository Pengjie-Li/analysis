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
        Double_t targetRadius=15;
        TEllipse *targetArea = new TEllipse(targetx,targety,targetRadius,targetRadius);
        targetArea->SetLineColor(2);
        targetArea->SetLineWidth(2);
        targetArea->SetFillStyle(0);
        targetArea->SetLineStyle(1);
        targetArea->Draw("same");

        Double_t selectRadius=13;
        TEllipse *selectArea = new TEllipse(targetx,targety,selectRadius,selectRadius);
        selectArea->SetLineColor(2);
        selectArea->SetLineWidth(2);
        selectArea->SetFillStyle(0);
        selectArea->SetLineStyle(2);
        selectArea->Draw("same");
//
//
        Double_t backRadius=21;
        TEllipse *backWindow = new TEllipse(targetx,targety,backRadius,backRadius);
        backWindow->SetLineColor(2);
        backWindow->SetLineWidth(2);
        backWindow->SetFillStyle(0);
        backWindow->SetLineStyle(2);
        backWindow->Draw("same");




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
	TLatex l;
	l.SetTextSize(0.025);
	//l.SetTextAngle(30.);
	l.SetTextAngle(0.);
	//DrawLatex: xPos, yPos, Content
	l.DrawLatex(0,-30,Form("(selectRadius = %g)",selectRadius));
	l.DrawLatex(0,-33,Form("(targetRadius = %g)",targetRadius));
	//l.DrawLatex(0,-36,Form("(outerRadius = %g)",outerRadius));
	l.DrawLatex(0,-36,Form("(backRadius = %g)",backRadius));

}
