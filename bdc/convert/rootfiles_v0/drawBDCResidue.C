{
	TCanvas *c1=new TCanvas();
	c1->Divide(2,2);

	c1->cd(1);
	TH1F *hBDC1[8];
	TH1F *hBDC2[8];
	for(int i=0;i<8;i++){
		CalTreeBDC->Draw(Form("BDC1_Track_dXY[%d]>>hBDC1_%d(100,-1,1)",i,i));
		CalTreeBDC->Draw(Form("BDC2_Track_dXY[%d]>>hBDC2_%d(100,-1,1)",i,i));

		hBDC1[i]=(TH1F*)gDirectory->Get(Form("hBDC1_%d",i));
		hBDC2[i]=(TH1F*)gDirectory->Get(Form("hBDC2_%d",i));
	}

	//hBDC1XResidue->Add(hBDC1[0],1);
//	hBDC1[0]->Add(hBDC1[1],1);
//	hBDC1[0]->Add(hBDC1[4],1);
//	hBDC1[0]->Add(hBDC1[5],1);

//	hBDC1YResidue->Add(hBDC1[2],1);
//	hBDC1YResidue->Add(hBDC1[3],1);
//	hBDC1YResidue->Add(hBDC1[6],1);
//	hBDC1YResidue->Add(hBDC1[7],1);
//
//	hBDC2XResidue->Add(hBDC1[0],1);
//	hBDC2XResidue->Add(hBDC1[1],1);
//	hBDC2XResidue->Add(hBDC1[4],1);
//	hBDC2XResidue->Add(hBDC1[5],1);
//
//	hBDC2YResidue->Add(hBDC1[2],1);
//	hBDC2YResidue->Add(hBDC1[3],1);
//	hBDC2YResidue->Add(hBDC1[6],1);
//	hBDC2YResidue->Add(hBDC1[7],1);


	c1->cd(1);
	hBDC1[0]->Draw();
	c1->cd(2);

	hBDC1[2]->Draw();
	c1->cd(3);
	hBDC2[0]->Draw();
	c1->cd(4);
	hBDC2[2]->Draw();

}
