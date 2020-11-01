{
	//tree->Draw("hodHitQ:hodHitId>>hHodWall(40,-0.5,39.5,500,0,4000)","","colz");
	tree->Draw("hodHitQ:hodHitT>>hHodWall(500,16000,20000,500,0,4000)","","colz");
	//tree->Draw("hodBarQCal:hodID>>hHodWall(40,-0.5,39.5,500,0,4000)",gate,"colz");
}
