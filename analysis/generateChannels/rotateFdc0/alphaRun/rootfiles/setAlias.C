{
	tree->SetAlias("C0","(999.44/3281.41)");
	tree->SetAlias("C1","(3284.41/999.44)");
	tree->SetAlias("bdc1X","(bdc1Position.X())");
	tree->SetAlias("bdc1Y","(bdc1Position.Y())");
	tree->SetAlias("bdc2X","(bdc2Position.X())");
	tree->SetAlias("bdc2Y","(bdc2Position.Y())");
	tree->SetAlias("Fdc0X","(fdc0Position.X()+0.64)");
	tree->SetAlias("Fdc0Y","(fdc0Position.Y()+0.75)");

	//tree->SetAlias("rFDC0X","(fdc0X[0][6])");
	//tree->SetAlias("rFDC0Y","(fdc0Y[0][6])");
	
	//tree->SetAlias("dBDC2X","(1-C0)*bdc1X+C0*rFDC0X");
	//tree->SetAlias("dBDC2Y","(1-C0)*bdc1Y+C0*rFDC0Y");
	tree->SetAlias("dBDC2X","(1-C0)*bdc1X+C0*Fdc0X");
	tree->SetAlias("dBDC2Y","(1-C0)*bdc1Y+C0*Fdc0Y");


	tree->SetAlias("dFDC0X","(1-C1)*bdc1X+C1*bdc2X");
	tree->SetAlias("dFDC0Y","(1-C1)*bdc1Y+C1*bdc2Y");


	TString targetArea="sqrt((targetPosition.X()-2.0)*(targetPosition.X()-2.0)+(targetPosition.Y()+1.1)*(targetPosition.Y()+1.1))<13";
}
