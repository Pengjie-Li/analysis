{
	//int barId = 32;
	if(barId<24)	tree->Draw(Form("hodBarQCal[%d]:0.5*(hodTRaw[0][%d]+hodTRaw[1][%d])>>hHod%d(1000,17000,20000,1000,0,4000)",barId,barId,barId,barId),gate+Form("&&hodBarQCal[%d]>0&&hodTRaw[0][%d]!=-1&&hodTRaw[1][%d]!=-1",barId,barId,barId),"colz");
	else tree->Draw(Form("hodBarQCal[%d]:0.5*(hodTRaw[0][%d]+hodTRaw[1][%d])>>hHod%d(1000,1200,2200,1000,0,4000)",barId,barId,barId,barId),gate+Form("&&hodBarQCal[%d]>0&&hodTRaw[0][%d]!=-1&&hodTRaw[1][%d]!=-1",barId,barId,barId),"colz");

}
