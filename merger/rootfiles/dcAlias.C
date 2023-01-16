{
	tree->SetAlias("C0","(999.44/3281.41)");
	tree->SetAlias("C1","(3284.41/999.44)");
	tree->SetAlias("bdc1X","(bdc1Position.X())");
	tree->SetAlias("bdc1Y","(bdc1Position.Y())");
	tree->SetAlias("bdc2X","(bdc2Position.X())");
	tree->SetAlias("bdc2Y","(bdc2Position.Y())");
	tree->SetAlias("fdc0X","(fdc0Position.X())");
	tree->SetAlias("fdc0Y","(fdc0Position.Y())");

	tree->SetAlias("dBDC2X","(1-C0)*bdc1X+C0*fdc0X");
	tree->SetAlias("dBDC2Y","(1-C0)*bdc1Y+C0*fdc0Y");


	tree->SetAlias("dFDC0X","(1-C1)*bdc1X+C1*bdc2X");
	tree->SetAlias("dFDC0Y","(1-C1)*bdc1Y+C1*bdc2Y");
}
