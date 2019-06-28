{
	//int barID = 32;
	if(barID<24)	tree->Draw(Form("hodBarQCal[%d]:0.5*(hodTRaw[0][%d]+hodTRaw[1][%d])>>hHod%d(1000,17000,20000,1000,0,4000)",barID,barID,barID,barID),gate,"colz");
	else tree->Draw(Form("hodBarQCal[%d]:0.5*(hodTRaw[0][%d]+hodTRaw[1][%d])>>hHod%d(1000,1200,2200,1000,0,4000)",barID,barID,barID,barID),gate,"colz");

}
